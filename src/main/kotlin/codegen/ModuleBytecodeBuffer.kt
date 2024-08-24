/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.codegen

import cum.jesus.jesusasm.util.extensions.align16
import java.io.OutputStream

enum class Section {
    Functions,
    Classes,
    ConstPool,
    StringTable,
    Bytecode,
}

const val MAGIC_NUMBER: UInt = 0x4E696765u
    
private class ModuleSection(val sectionType: Section) {
    val buffer = mutableListOf<Byte>()

    fun write(data: UByte) {
        buffer.add(data.toByte())
    }

    fun write(data: UShort) {
        buffer.add((data.toInt() shr 8 and 0xFF).toByte())
        buffer.add((data and 0xFFu).toByte())
    }

    fun write(data: UInt) {
        buffer.add((data shr 24 and 0xFFu).toByte())
        buffer.add((data shr 16 and 0xFFu).toByte())
        buffer.add((data shr 8 and 0xFFu).toByte())
        buffer.add((data and 0xFFu).toByte())
    }

    fun write(data: ULong) {
        buffer.add((data shr 56 and 0xFFu).toByte())
        buffer.add((data shr 48 and 0xFFu).toByte())
        buffer.add((data shr 40 and 0xFFu).toByte())
        buffer.add((data shr 32 and 0xFFu).toByte())
        buffer.add((data shr 24 and 0xFFu).toByte())
        buffer.add((data shr 16 and 0xFFu).toByte())
        buffer.add((data shr 8 and 0xFFu).toByte())
        buffer.add((data and 0xFFu).toByte())
    }

    fun write(data: String) {
        for (c in data.toByteArray()) {
            buffer.add(c)
        }
    }
}

class ModuleBytecodeBuffer(name: String, val entryIndex: UInt) {
    private val sections = mutableListOf(
        ModuleSection(Section.Functions),
        ModuleSection(Section.Classes),
        ModuleSection(Section.ConstPool),
        ModuleSection(Section.StringTable),
        ModuleSection(Section.Bytecode),
    )

    private val symbols = mutableMapOf<String, Long>()

    private val nameIndex: UInt = 0u

    var functionCount = 0u
    var classCount = 0u
    var constPoolElementCount = 0u

    init {
        write(name.length.toUShort(), Section.StringTable)
        write(name, Section.StringTable)
    }

    fun write(data: UByte, section: Section) {
        getModuleSection(section).write(data)
    }

    fun write(data: UShort, section: Section) {
        getModuleSection(section).write(data)
    }

    fun write(data: UInt, section: Section) {
        getModuleSection(section).write(data)
    }

    fun write(data: ULong, section: Section) {
        getModuleSection(section).write(data)
    }

    fun write(data: String, section: Section) {
        getModuleSection(section).write(data)
    }

    fun getPosition(section: Section): Long {
        return getModuleSection(section).buffer.size.toLong()
    }

    fun addSymbol(name: String, value: Long) {
        symbols[name] = value
    }

    /**
     * @return null if the symbol doesn't exist (possibly forward label)
     */
    fun getSymbol(name: String): Long {
        return symbols[name] ?: -1
    }

    fun hasSymbol(name: String): Boolean {
        return symbols.contains(name)
    }

    fun patchForwardSymbol(name: String, section: Section, size: OperandSize, location: Int, origin: Int) {
        val sect = getModuleSection(section)

        val symbol = getSymbol(name) - origin
        when (size) {
            OperandSize.Byte -> {
                sect.buffer[location] = symbol.toByte()
            }

            OperandSize.Short -> {
                sect.buffer[location] = (symbol and 0xFF).toByte()
                sect.buffer[location + 1] = (symbol shr 8 and 0xFF).toByte()
            }

            OperandSize.Int -> {
                sect.buffer[location] = (symbol and 0xFF).toByte()
                sect.buffer[location + 1] = (symbol shr 8 and 0xFF).toByte()
                sect.buffer[location + 2] = (symbol shr 16 and 0xFF).toByte()
                sect.buffer[location + 3] = (symbol shr 24 and 0xFF).toByte()
            }

            OperandSize.Long -> {
                sect.buffer[location] = (symbol and 0xFF).toByte()
                sect.buffer[location + 1] = (symbol shr 8 and 0xFF).toByte()
                sect.buffer[location + 2] = (symbol shr 16 and 0xFF).toByte()
                sect.buffer[location + 3] = (symbol shr 24 and 0xFF).toByte()
                sect.buffer[location + 4] = (symbol shr 32 and 0xFF).toByte()
                sect.buffer[location + 5] = (symbol shr 40 and 0xFF).toByte()
                sect.buffer[location + 6] = (symbol shr 48 and 0xFF).toByte()
                sect.buffer[location + 7] = (symbol shr 56 and 0xFF).toByte()
            }

            OperandSize.None -> {
            }
        }
    }

    fun print(out: OutputStream) {
        writeMod(out, MAGIC_NUMBER)
        writeMod(out, nameIndex)
        writeMod(out, entryIndex)
        writeMod(out, getModuleSection(Section.Functions).buffer.size.toUInt().align16())
        writeMod(out, functionCount)
        writeMod(out, getModuleSection(Section.Classes).buffer.size.toUInt().align16())
        writeMod(out, classCount)
        writeMod(out, getModuleSection(Section.ConstPool).buffer.size.toUInt().align16())
        writeMod(out, constPoolElementCount)
        writeMod(out, getModuleSection(Section.StringTable).buffer.size.toUInt().align16())
        writeMod(out, getModuleSection(Section.Bytecode).buffer.size.toUInt().align16())

        var written: ULong = 0u
        var alignedWritten: ULong = 0u
        for (section in sections) {
            for (i in 0uL until alignedWritten - written) {
                out.write(0)
            }
            written = alignedWritten

            out.write(section.buffer.toByteArray())

            written += section.buffer.size.toUInt()
            alignedWritten = (written + 15u) and 15u.inv().toULong()
        }
    }

    private fun getModuleSection(section: Section): ModuleSection {
        return sections.find {
            it.sectionType == section
        } ?: throw NullPointerException("what the fuck")
    }
}

private inline fun writeMod(out: OutputStream, data: UInt) {
    out.write((data shr 24 and 0xFFu).toInt())
    out.write((data shr 16 and 0xFFu).toInt())
    out.write((data shr 8 and 0xFFu).toInt())
    out.write((data and 0xFFu).toInt())
}
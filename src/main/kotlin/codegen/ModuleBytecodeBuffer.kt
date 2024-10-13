/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.codegen

import java.io.OutputStream

//enum class Section {
//    Functions,
//    Classes,
//    ConstPool,
//    StringTable,
//    Bytecode,
//}

typealias Section = String

const val MAGIC_NUMBER: UInt = 0x4E696765u

private class ModuleSection(val name: String, val nameIndex: UInt) {
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
    private val primarySections = mutableListOf(
        ModuleSection("functions", 0u),
        ModuleSection("classes", 0u),
        ModuleSection("constpool", 0u),
        ModuleSection("strtab", 0u),
        ModuleSection("code", 0u),
    )

    private val sections = mutableListOf<ModuleSection>()

    private val symbols = mutableMapOf<String, Long>()

    private val nameIndex: UInt = 0u

    var functionCount = 0u
    var classCount = 0u
    var constPoolElementCount = 0u

    init {
        write(name.length.toUShort(), "strtab")
        write(name, "strtab")
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

    fun pad(size: Int, section: Section) {
        val section = getModuleSection(section)

        repeat(size) {
            section.write(0.toUByte())
        }
    }

    fun getPosition(section: Section): Long {
        return getModuleSection(section).buffer.size.toLong()
    }

    fun getSection(name: String): Section {
        return getModuleSection(name).name
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
        sections.removeIf { it.buffer.size == 0 } // don't want empty sections wasting space with their headers

        writeMod(out, MAGIC_NUMBER)
        writeMod(out, nameIndex)
        writeMod(out, entryIndex)
        writeMod(out, getModuleSection("functions").buffer.size.toUInt())
        writeMod(out, functionCount)
        writeMod(out, getModuleSection("classes").buffer.size.toUInt())
        writeMod(out, classCount)
        writeMod(out, getModuleSection("constpool").buffer.size.toUInt())
        writeMod(out, constPoolElementCount)
        writeMod(out, getModuleSection("strtab").buffer.size.toUInt())
        writeMod(out, getModuleSection("code").buffer.size.toUInt())
        writeMod(out, sections.size.toUInt()) // amount of sections outside the primary ones

        for (section in primarySections) {
            out.write(section.buffer.toByteArray())
        }

        for (section in sections) {
            writeMod(out, section.nameIndex)
            writeMod(out, section.buffer.size.toUInt())
            out.write(section.buffer.toByteArray())
        }
    }

    private fun getModuleSection(section: Section): ModuleSection {
        return primarySections.find {
            it.name == section
        } ?: sections.find {
            it.name == section
        } ?: createSection(section)
    }

    private fun createSection(section: Section): ModuleSection {
        val strtab = getModuleSection("strtab")
        val nameIndex = strtab.buffer.size.toUInt();

        strtab.write(section.length.toUShort())
        strtab.write(section)

        val newSection = ModuleSection(section, nameIndex)
        sections.add(newSection)

        return newSection
    }
}

private inline fun writeMod(out: OutputStream, data: UInt) {
    out.write((data shr 24 and 0xFFu).toInt())
    out.write((data shr 16 and 0xFFu).toInt())
    out.write((data shr 8 and 0xFFu).toInt())
    out.write((data and 0xFFu).toInt())
}
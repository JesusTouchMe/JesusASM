package cum.jesus.jesusasm.codegen

enum class OperandSize {
    Byte,
    Short,
    Int,
    Long,

    None
}

typealias Opcode = UByte
typealias Prefix = UByte

enum class Modifier(val bitmask: UShort) {
    Public(0x0001u),
    Private(0x0002u),
    Virtual(0x0004u),
}

enum class ConstantKind(val byte: UByte) {
    Function(1u),
    Class(2u),
    Field(3u),
    Method(4u),
}

const val NOP: Opcode = 0x00u
const val POP: Opcode = 0x01u
const val DUP: Opcode = 0x02u
const val LOAD: Opcode = 0x03u
const val LOADOBJ: Opcode = 0x04u
const val STORE: Opcode = 0x05u
const val STOREOBJ: Opcode = 0x06u
const val ALOAD: Opcode = 0x07u
const val ALOADOBJ: Opcode = 0x08u
const val ASTORE: Opcode = 0x09u
const val ASTOREOBJ: Opcode = 0x0Au
const val NEW: Opcode = 0x0Bu
const val NEWARRAY: Opcode = 0x0Cu
const val NEWARRAYPRIM: Opcode = 0x0Du
const val GETFIELD: Opcode = 0x0Eu
const val PUTFIELD: Opcode = 0x0Fu
const val ADD: Opcode = 0x10u
const val SUB: Opcode = 0x11u
const val MUL: Opcode = 0x12u
const val DIV: Opcode = 0x13u
const val AND: Opcode = 0x14u
const val OR: Opcode = 0x15u
const val XOR: Opcode = 0x16u
const val INC: Opcode = 0x17u
const val DEC: Opcode = 0x18u
const val NOT: Opcode = 0x19u
const val NEG: Opcode = 0x1Au
const val CMP: Opcode = 0x1Bu
const val JMP: Opcode = 0x1Cu
const val JMPREL: Opcode = 0x1Du
const val JEQ: Opcode = 0x1Eu
const val JEQREL: Opcode = 0x1Fu
const val JNE: Opcode = 0x20u
const val JNEREL: Opcode = 0x21u
const val JLT: Opcode = 0x22u
const val JLTREL: Opcode = 0x23u
const val JGT: Opcode = 0x24u
const val JGTREL: Opcode = 0x25u
const val JLE: Opcode = 0x26u
const val JLEREL: Opcode = 0x27u
const val JGE: Opcode = 0x28u
const val JGEREL: Opcode = 0x29u
const val CALL: Opcode = 0x2Au
const val RET: Opcode = 0x2Bu
const val LDC: Opcode = 0x2Cu
const val LDI: Opcode = 0x2Du
const val LDI_0: Opcode = 0x2Eu
const val WIDE: Prefix = 0x2Fu
const val DEBUG: Opcode = 0x30u
const val HLT: Opcode = 0x31u
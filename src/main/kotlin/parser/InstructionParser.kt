package cum.jesus.jesusasm.parser

import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.environment.GlobalContext
import cum.jesus.jesusasm.instruction.*
import cum.jesus.jesusasm.instruction.operand.LabelOperand
import cum.jesus.jesusasm.instruction.singleoperandinstruction.*
import cum.jesus.jesusasm.lexer.TokenType
import kotlin.reflect.full.createInstance
import kotlin.reflect.full.primaryConstructor

class InstructionParser(private val tokenStream: TokenStream, private val globalContext: GlobalContext) {
    private var functionContext: FunctionContext? = null

    private val parserFunctions = mutableMapOf(
        "nop" to  { parseNoOperandInstruction<NopInstruction>() },
        "pop" to { parseNoOperandInstruction<PopInstruction>() },
        "dup" to { parseNoOperandInstruction<DupInstruction>() },
        "load" to ::parseLoad,
        "store" to ::parseStore,
        "add" to { parseNoOperandInstruction<AddInstruction>() },
        "sub" to { parseNoOperandInstruction<SubInstruction>() },
        "mul" to { parseNoOperandInstruction<MulInstruction>() },
        "div" to { parseNoOperandInstruction<DivInstruction>() },
        "and" to { parseNoOperandInstruction<AndInstruction>() },
        "or" to { parseNoOperandInstruction<OrInstruction>() },
        "xor" to { parseNoOperandInstruction<XorInstruction>() },
        "inc" to { parseNoOperandInstruction<IncInstruction>() },
        "dec" to { parseNoOperandInstruction<DecInstruction>() },
        "not" to { parseNoOperandInstruction<NotInstruction>() },
        "neg" to { parseNoOperandInstruction<NegInstruction>() },
        "cmp" to { parseNoOperandInstruction<CmpInstruction>() },
        "jmp" to { parseJumpInstruction<JmpInstruction>() },
        "jeq" to { parseJumpInstruction<JeqInstruction>() },
        "jne" to { parseJumpInstruction<JneInstruction>() },
        "jlt" to { parseJumpInstruction<JltInstruction>() },
        "jgt" to { parseJumpInstruction<JgtInstruction>() },
        "jle" to { parseJumpInstruction<JleInstruction>() },
        "jge" to { parseJumpInstruction<JgeInstruction>() },
        "call" to ::parseCall,
        "ret" to { parseNoOperandInstruction<RetInstruction>() },
        "constload" to ::parseConstLoad,
        "ldi" to ::parseLdi,
        "debug" to { parseNoOperandInstruction<DebugInstruction>() },
        "hlt" to { parseNoOperandInstruction<HltInstruction>() },
    )

    fun parse(functionContext: FunctionContext?): Instruction {
        this.functionContext = functionContext

        val parser = parserFunctions[consume().text]!!
        return parser()
    }

    private inline fun <reified T : NoOperandInstruction> parseNoOperandInstruction() = T::class.createInstance()

    private fun parseLoad(): Instruction {
        return LoadInstruction(parseImmediate())
    }

    private fun parseStore(): Instruction {
        return StoreInstruction(parseImmediate())
    }

    private inline fun <reified T : BaseJmpInstruction> parseJumpInstruction(): Instruction {
        if (current().tokenType == TokenType.Identifier) {
            return T::class.primaryConstructor?.call(parseLabel()) ?: throw RuntimeException("bad instruction class")
        }

        return T::class.primaryConstructor?.call(null) ?: throw RuntimeException("bad instruction class")
    }

    private fun parseCall(): Instruction {
        return CallInstruction(parseImmediate())
    }

    private fun parseConstLoad(): Instruction {
        return ConstLoadInstruction(parseImmediate())
    }

    private fun parseLdi(): Instruction {
        return LdiInstruction(parseImmediate())
    }

    private fun parseImmediate(): ULong {
        if (current().tokenType == TokenType.String) {
            return globalContext.constants[consume().text]!!.toULong()
        }

        expectToken(TokenType.Immediate)
        return consume().text.toULong()
    }

    private fun parseLabel(): LabelOperand {
        expectToken(TokenType.Identifier)
        return LabelOperand(consume().text)
    }

    private inline fun expectToken(type: TokenType) = tokenStream.expectToken(type)

    private inline fun expectTokens(vararg types: TokenType) = tokenStream.expectTokens(*types)

    private inline fun current() = tokenStream.current()

    private inline fun consume() = tokenStream.consume()

    private inline fun peek(offset: Int) = tokenStream.peek(offset)
}
package cum.jesus.jesusasm.parser

import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.environment.GlobalContext
import cum.jesus.jesusasm.instruction.*
import cum.jesus.jesusasm.instruction.operand.LabelOperand
import cum.jesus.jesusasm.instruction.singleoperandinstruction.*
import cum.jesus.jesusasm.lexer.TokenType
import cum.jesus.jesusasm.type.getType
import cum.jesus.jesusasm.type.isType
import kotlin.reflect.full.createInstance
import kotlin.reflect.full.primaryConstructor

class InstructionParser(private val tokenStream: TokenStream, private val globalContext: GlobalContext, private val expressionParser: ExpressionParser) {
    private var functionContext: FunctionContext? = null

    private val parserFunctions = mutableMapOf(
        "nop" to  { parseNoOperandInstruction<NopInstruction>() },
        "pop" to { parseNoOperandInstruction<PopInstruction>() },
        "dup" to { parseNoOperandInstruction<DupInstruction>() },
        "load" to ::parseLoad,
        "loadobj" to ::parseLoadObj,
        "store" to ::parseStore,
        "storeobj" to ::parseStoreObj,
        "aload" to { parseNoOperandInstruction<ALoadInstruction>() },
        "aloadobj" to { parseNoOperandInstruction<ALoadObjInstruction>() },
        "astore" to { parseNoOperandInstruction<AStoreInstruction>() },
        "astoreobj" to { parseNoOperandInstruction<AStoreObjInstruction>() },
        "new" to ::parseNew,
        "newarray" to ::parseNewArray,
        "newarrayprim" to ::parseNewArrayPrim,
        "getfield" to ::parseGetField,
        "putfield" to ::parsePutField,
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
        "ldc" to ::parseConstLoad,
        "ldi" to ::parseLdi,
        "ldi_0" to { parseNoOperandInstruction<Ldi0Instruction>() },
        "debug" to { parseNoOperandInstruction<DebugInstruction>() },
        "hlt" to { parseNoOperandInstruction<HltInstruction>() },
        "byte" to { ByteInstruction(expressionParser.parse(functionContext!!).toUByte()) },
        "short" to { ShortInstruction(expressionParser.parse(functionContext!!).toUShort()) },
        "int" to { IntInstruction(expressionParser.parse(functionContext!!).toUInt()) },
        "long" to { LongInstruction(expressionParser.parse(functionContext!!)) },
    )

    fun parse(functionContext: FunctionContext?): Instruction {
        this.functionContext = functionContext

        val parser = parserFunctions[consume().text]!!
        return parser()
    }

    private inline fun <reified T : NoOperandInstruction> parseNoOperandInstruction() = T::class.createInstance()

    private fun parseLoad(): Instruction {
        return LoadInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseLoadObj(): Instruction {
        return LoadObjInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseStore(): Instruction {
        return StoreInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseStoreObj(): Instruction {
        return StoreObjInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseNew(): Instruction {
        return NewInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseNewArray(): Instruction {
        return NewArrayInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseNewArrayPrim(): Instruction {
        return NewArrayPrimInstruction(parsePrimTypeId())
    }

    private fun parseGetField(): Instruction {
        return GetFieldInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parsePutField(): Instruction {
        return PutFieldInstruction(expressionParser.parse(functionContext!!))
    }

    private inline fun <reified T : BaseJmpInstruction> parseJumpInstruction(): Instruction {
        if (current().tokenType == TokenType.Identifier) {
            return T::class.primaryConstructor?.call(parseLabel()) ?: throw RuntimeException("bad instruction class")
        }

        return T::class.primaryConstructor?.call(null) ?: throw RuntimeException("bad instruction class")
    }

    private fun parseCall(): Instruction {
        return CallInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseConstLoad(): Instruction {
        return LdcInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parseLdi(): Instruction {
        return LdiInstruction(expressionParser.parse(functionContext!!))
    }

    private fun parsePrimTypeId(): UByte {
        require(isType(current().text)) { "has to be type" }

        return getType(consume().text)!!.primitiveId
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
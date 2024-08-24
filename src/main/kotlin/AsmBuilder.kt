package cum.jesus.jesusasm

import cum.jesus.jesusasm.codegen.*
import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.instruction.*
import cum.jesus.jesusasm.instruction.Function
import cum.jesus.jesusasm.instruction.operand.LabelOperand
import cum.jesus.jesusasm.instruction.singleoperandinstruction.*
import cum.jesus.jesusasm.type.FunctionType
import cum.jesus.jesusasm.type.Type
import kotlin.reflect.jvm.internal.ReflectProperties.Val

class AsmBuilder(val module: String, private val values: MutableList<Value> = mutableListOf()) {
    private val labels = mutableMapOf<String, LabelOperand>()
    private val constpool = mutableListOf<Value>()

    private var localIndex: UShort = 0u

    var section: Section = Section.Bytecode
        set(value) {
            field = value

            value(SectionDirective2(value))
        }

    fun nop() = value(NopInstruction())

    fun pop() = value(PopInstruction())

    fun dup() = value(DupInstruction())

    fun load(index: Int) = value(LoadInstruction(index.toULong()))
    fun load(index: ULong) = value(LoadInstruction(index))

    fun loadobj(index: Int) = value(LoadObjInstruction(index.toULong()))
    fun loadobj(index: ULong) = value(LoadObjInstruction(index))

    fun store(index: Int) = value(StoreInstruction(index.toULong()))
    fun store(index: ULong) = value(StoreInstruction(index))

    fun storeobj(index: Int) = value(StoreObjInstruction(index.toULong()))
    fun storeobj(index: ULong) = value(StoreObjInstruction(index))

    fun aload() = value(ALoadInstruction())

    fun aloadobj() = value(ALoadObjInstruction())

    fun astore() = value(AStoreInstruction())

    fun astoreobj() = value(AStoreObjInstruction())

    fun new(index: Int) = value(NewInstruction(index.toULong()))
    fun new(index: ULong) = value(NewInstruction(index))

    fun newarray(index: Int) = value(NewArrayInstruction(index.toULong()))
    fun newarray(index: ULong) = value(NewArrayInstruction(index))

    fun newarrayprim(type: Type) = value(NewArrayPrimInstruction(type.primitiveId))

    fun getfield(index: Int) = value(GetFieldInstruction(index.toULong()))
    fun getfield(index: ULong) = value(GetFieldInstruction(index))

    fun putfield(index: Int) = value(PutFieldInstruction(index.toULong()))
    fun putfield(index: ULong) = value(PutFieldInstruction(index))

    fun add() = value(AddInstruction())

    fun sub() = value(SubInstruction())

    fun mul() = value(MulInstruction())

    fun div() = value(DivInstruction())

    fun and() = value(AndInstruction())

    fun or() = value(OrInstruction())

    fun xor() = value(XorInstruction())

    fun inc() = value(IncInstruction())

    fun dec() = value(DecInstruction())

    fun not() = value(NotInstruction())

    fun neg() = value(NegInstruction())

    fun cmp() = value(CmpInstruction())

    fun jmp(label: LabelOperand) = value(JmpInstruction(label))

    fun jeq(label: LabelOperand) = value(JeqInstruction(label))

    fun jne(label: LabelOperand) = value(JneInstruction(label))

    fun jlt(label: LabelOperand) = value(JltInstruction(label))

    fun jgt(label: LabelOperand) = value(JgtInstruction(label))

    fun jle(label: LabelOperand) = value(JleInstruction(label))

    fun jge(label: LabelOperand) = value(JgeInstruction(label))

    fun call(index: Int) = value(CallInstruction(index.toULong()))
    fun call(index: ULong) = value(CallInstruction(index))

    fun ret() = value(RetInstruction())

    fun constload(index: Int) = value(ConstLoadInstruction(index.toULong()))

    fun ldi(value: Int) = value(LdiInstruction(value.toULong()))
    fun ldi(value: Long) = value(LdiInstruction(value.toULong()))
    fun ldi(value: ULong) = value(LdiInstruction(value))

    fun ldi_0() = value(Ldi0Instruction())

    fun debug() = value(DebugInstruction())

    fun hlt() = value(HltInstruction())

    fun createLabel(name: String = "." + values.size.toString()): LabelOperand {
        if (labels.contains(name)) {
            throw RuntimeException("label $name already exists")
        }

        val label = LabelOperand(name)
        labels[name] = label

        value(Label(name))

        return label
    }

    fun makeLabel(name: String = "." + values.size.toString()) = LabelOperand(name)

    fun placeLabel(label: LabelOperand) = apply {
        labels[label.name] = label
        value(Label(label.name))
    }

    fun findLabel(name: String): LabelOperand {
        return labels[name] ?: throw RuntimeException("label $name doesn't exist")
    }

    fun jump(condition: JumpCondition, label: LabelOperand) = value(BaseJmpInstruction(condition.opcode, condition.codeName, label))

    fun int(number: Int) = apply {
        if (number == 0) {
            ldi_0()
        } else {
            ldi(number)
        }
    }

    fun int(number: UInt) = apply {
        if (number == 0u) {
            ldi_0()
        } else {
            ldi(number.toULong())
        }
    }

    fun long(number: Long) = apply {
        if (number == 0L) {
            ldi_0()
        } else {
            ldi(number)
        }
    }

    fun long(number: ULong) = apply {
        if (number == 0uL) {
            ldi_0()
        } else {
            ldi(number)
        }
    }

    fun function(name: String, type: FunctionType, modifiers: Collection<Modifier>, localCount: UShort): FunctionId {
        val context = FunctionContext()
        context.locals = localCount

        value(Function(name, type, modifiers, context))

        constpool.forEachIndexed { index, constant ->
            if (constant is ConstantFunction) {
                if (constant.module == module && constant.name == name && constant.functionType == type) {
                    return FunctionId(index.toUInt())
                }
            }
        }

        val index = constpool.size.toUInt()
        value(ConstantFunction(module, name, type))

        return FunctionId(index)
    }

    fun call(id: FunctionId) = apply {
        call(id.constIndex.toULong())
    }

    fun local(type: LocalType) = Local(localIndex++, type)

    fun getLocal(local: Local) = apply {
        if (local.type == LocalType.Object) {
            loadobj(local.index.toULong())
        } else {
            load(local.index.toULong())
        }
    }

    /**
     * Ensure stack is set up correctly
     */
    fun putLocal(local: Local) = apply {
        if (local.type == LocalType.Object) {
            storeobj(local.index.toULong())
        } else {
            store(local.index.toULong())
        }
    }

    fun ifClause(vararg conditions: JumpCondition, code: AsmBuilder.() -> Unit) = apply {
        val label = makeLabel()

        for (condition in conditions) {
            jump(condition, label)
        }

        this.code()

        placeLabel(label)
    }

    fun ifElseClause(vararg conditions: JumpCondition, builder: IfElseBuilder.() -> Unit) = apply {
        val ifElse = IfElseBuilder(values)

        ifElse.builder()

        val ifLabel = makeLabel()
        val endLabel = makeLabel()

        for (condition in conditions) {
            jump(condition, ifLabel)
        }

        insert(ifElse.elseCode)

        jump(JumpCondition.Goto, endLabel)

        placeLabel(ifLabel)

        insert(ifElse.ifCode)

        placeLabel(endLabel)
    }

    fun build(): Collection<Value> {
        val res = values.toList()
        values.clear()

        return res;
    }

    fun insert(builder: Collection<Value>) {
        values.addAll(builder)
    }

    internal inline fun value(value: Value) = apply {
        values.add(value)
    }
}

enum class JumpCondition(val opcode: Opcode, val codeName: String) {
    Goto(JMP, "jmp"),

    Equal(JEQ, "jeq"),
    NotEqual(JNE, "jne"),
    LessThan(JLT, "jlt"),
    GreaterThan(JGT, "jgt"),
    LessOrEqual(JLE, "jle"),
    GreaterOrEqual(JGE, "jge"),
}

enum class LocalType {
    Object,
    Bool,
    Byte,
    Short,
    Int,
    Long
}

class IfElseBuilder(private val values: MutableList<Value>) {
    var ifCode: Collection<Value> = listOf<Value>()
    var elseCode: Collection<Value> = listOf<Value>()

    fun ifCode(code: AsmBuilder.() -> Unit)  = apply {
        val builder = AsmBuilder("0", values)

        builder.code()

        ifCode = builder.build()
    }

    fun elseCode(code: AsmBuilder.() -> Unit) {
        val builder = AsmBuilder("0", values)

        builder.code()

        elseCode = builder.build()
    }
}

data class Local(val index: UShort, val type: LocalType)

data class FunctionId(val constIndex: UInt)
package cum.jesus.jesusasm.instruction

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.codegen.Section
import cum.jesus.jesusasm.codegen.builder.BytecodeBuilder
import cum.jesus.jesusasm.codegen.builder.Class
import cum.jesus.jesusasm.environment.ClassContext
import cum.jesus.jesusasm.type.Type
import cum.jesus.jesusasm.type.getClassType
import java.io.PrintStream

class Field(val type: Type, val name: String, val modifiers: List<Modifier>) {
    fun emit(builder: BytecodeBuilder, clas: Class) {
        clas.fields.add(cum.jesus.jesusasm.codegen.builder.Field(builder.getString(type.id), builder.getString(name), modifiers))
    }
}

class Method(val functionName: String) {
    fun emit(builder: BytecodeBuilder, clas: Class) {
        clas.methods.add(cum.jesus.jesusasm.codegen.builder.Method(builder.getString(functionName)))
    }
}

class Class(val name: String, val superClassModule: String?, val superClass: String?, val modifiers: Collection<Modifier>, val context: ClassContext) : Value {
    init {
        getClassType(context.name, name)
    }

    override fun print(stream: PrintStream): Boolean {
        stream.print("\nclass $name")

        if (superClass != null) {
            if (!superClassModule.isNullOrEmpty()) {
                stream.print(" extends $superClassModule/$superClass")
            } else {
                stream.print(" extends $superClass")
            }
        }

        stream.print(":")

        for (field in context.fields) {
            stream.print("\nfield ${field.modifiers.joinToString(" ") { it.name.lowercase() }} ${field.type.name} ${field.name}")
        }

        if (context.fields.isNotEmpty() && context.methods.isNotEmpty()) {
            stream.println()
        }

        for (method in context.methods) {
            stream.print("\nmethod ${method.functionName}()") // not much to do here since method named are done by the perser
        }

        return true
    }

    override fun emit(builder: BytecodeBuilder, section: Section) {
        builder.clas(section) {
            modifiers.addAll(this@Class.modifiers)

            name = builder.getString(this@Class.name)
            if (superClassModule != null) superClassModuleName = builder.getString(superClassModule)

            if (superClass != null) superClassName = builder.getString(superClass)

            for (field in context.fields) {
                field.emit(builder, this)
            }

            for (method in context.methods) {
                method.emit(builder, this)
            }
        }

        builder.incClassCount()
    }
}
package cum.jesus.jesusasm.codegen.builder.constants

class ClassSymbol(val module: UInt, val name: UInt)

class FieldSymbol(val module: UInt, val clas: UInt, val name:  UInt)

class MethodSymbol(val module: UInt, val clas: UInt, val descriptor: UInt)
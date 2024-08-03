package cum.jesus.jesusasm.codegen.builder.constants

/**
 * @param module Index to the module name in the string table
 * @param descriptor Index to the function descriptor in the string table
 */
class FunctionSymbol(val module: UInt, val descriptor: UInt)
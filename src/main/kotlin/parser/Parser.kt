/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.parser

import cum.jesus.jesusasm.codegen.Modifier
import cum.jesus.jesusasm.environment.ClassContext
import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.environment.GlobalContext
import cum.jesus.jesusasm.instruction.*
import cum.jesus.jesusasm.instruction.Function
import cum.jesus.jesusasm.lexer.Token
import cum.jesus.jesusasm.lexer.TokenType
import cum.jesus.jesusasm.type.*
import kotlin.math.exp

class TokenStream (val tokens: List<Token>) {
    var position: Int = 0

    fun current() = tokens[position]

    fun consume() = tokens[position++]

    fun peek(offset: Int) = tokens[position + offset]

    fun expectToken(type: TokenType) {
        val token = current()
        if (token.tokenType != type) {
            println("error $token, expected $type")
            throw RuntimeException()
        }
    }

    fun expectTokens(vararg types: TokenType) {
        val token = current()

        for (type in types) {
            if (token.tokenType == type) return
        }

        throw RuntimeException("error $token, expected $types")
    }
}

class Parser(val fileName: String, tokens: List<Token>) {
    val metaData = MetaData()
    val globalContext = GlobalContext()
    var currentFunctionContext: FunctionContext? = null
    var currentClassContext: ClassContext? = null

    private val tokenStream = TokenStream(tokens)
    private val expressionParser = ExpressionParser(tokenStream, globalContext)
    private val instructionParser = InstructionParser(tokenStream, globalContext, expressionParser)

    fun parse(): List<Value> {
        val values = mutableListOf<Value>()

        while (current().tokenType != TokenType.End) {
            val value = parseStatement()
            if (value != null) values.add(value)
        }

        return values
    }

    private fun parseStatement(): Value? {
        val token = current()

        when (token.tokenType) {
            TokenType.Error -> {
                println("error $token")
                throw RuntimeException()
            }

            TokenType.Dot -> {
                return parseDotStatement()
            }

            TokenType.Identifier -> {
                return parseLabel()
            }

            TokenType.Class -> {
                return parseClass()
            }

            TokenType.Field -> {
                return parseField()
            }

            TokenType.Method -> {
                return parseMethod()
            }

            TokenType.Function -> {
                return parseFunction()
            }

            TokenType.Define -> {
                return parseDefine()
            }

            TokenType.Const -> {
                return parseConstant()
            }

            TokenType.Section -> {
                consume()
                return SectionDirective(consume().text)
            }

            TokenType.Instruction -> {
                return instructionParser.parse(currentFunctionContext)
            }

            else -> {
                throw RuntimeException("bad $token")
            }
        }
    }

    private fun parseDotStatement(): Value? {
        consume() // .

        val token = current()

        when (token.tokenType) {
            TokenType.Module -> {
                consume()
                expectToken(TokenType.String)

                metaData.module = consume().text

                return null
            }

            TokenType.Entry -> {
                consume()
                expectToken(TokenType.String)

                metaData.entry = consume().text

                return null
            }

            TokenType.Locals -> {
                consume()

                if (current().tokenType == TokenType.Bind) {
                    return parseLocalsBind()
                }

                expectToken(TokenType.Immediate)

                val value = consume().text.toUShort()

                if (currentFunctionContext == null) {
                    throw RuntimeException(".locals when a function hasn't been declared yet")
                }

                currentFunctionContext!!.localCount = value

                return null
            }

            TokenType.Function -> {
                return parseConstantFunction()
            }

            TokenType.Class -> {
                return parseConstantClass()
            }

            TokenType.Field -> {
                return parseConstantField()
            }

            TokenType.Method -> {
                return parseConstantMethod()
            }

            else -> {
                throw RuntimeException("bad $token")
            }
        }
    }

    private fun parseType(): Type {
        if (current().tokenType == TokenType.Class) {
            consume()

            val moduleParts = mutableListOf<String>()
            var className = "0"

            while (current().tokenType != TokenType.End) {
                if (current().tokenType == TokenType.Identifier) {
                    val text = consume().text

                    if (current().tokenType == TokenType.Slash) {
                        moduleParts.add(text)
                        consume()
                    } else {
                        className = text
                        break
                    }
                } else {
                    throw RuntimeException("bad ${current()}")
                }
            }

            if (moduleParts.isEmpty()) {
                return getClassType(metaData.module, className)
            } else {
                return getClassType(moduleParts.joinToString("/"), className)
            }
        }

        return getType(consume().text)!!
    }

    private fun parseModifier(): Modifier {
        expectTokens(TokenType.Public, TokenType.Private)
        val modifier = consume()

        return when (modifier.tokenType) {
            TokenType.Public -> Modifier.Public
            TokenType.Private -> Modifier.Private

            else -> throw RuntimeException("unreachable")
        }
    }

    private fun parseLabel(): Value {
        val name = consume().text
        expectToken(TokenType.Colon)
        consume()

        return Label(name)
    }

    private fun parseField(): Value? {
        consume() // field

        val modifiers = mutableListOf<Modifier>()

        while (current().tokenType.isModifier()) {
            modifiers.add(parseModifier())
        }

        val type = parseType()
        val name = consume().text

        currentClassContext!!.fields.add(Field(type, name, modifiers))

        return null
    }

    private fun parseMethod(): Value? {
        consume() // method

        val modifiers = mutableListOf<Modifier>()

        while (current().tokenType.isModifier()) {
            modifiers.add(parseModifier())
        }

        val returnType = parseType()

        expectTokens(TokenType.Identifier, TokenType.Instruction)
        val name = consume().text
        val argumentTypes = mutableListOf<Type>()

        expectToken(TokenType.LeftParen)
        consume()

        while (current().tokenType != TokenType.RightParen) {
            val type = parseType()
            argumentTypes.add(type)

            if (current().tokenType != TokenType.RightParen) {
                expectToken(TokenType.Comma)
                consume()
            }
        }
        consume()

        val type = getFunctionType(returnType, argumentTypes)

        currentClassContext!!.methods.add(Method(currentClassContext!!.name + "::" + name + type.id))

        return null
    }

    private fun parseClass(): Value {
        consume() // class

        val modifiers = mutableListOf<Modifier>()

        while (current().tokenType != TokenType.Identifier) {
            modifiers.add(parseModifier())
        }

        val name = consume().text
        var superModule: String? = null
        var superClass: String? = null

       if (current().tokenType == TokenType.Extends) {
           consume()

           val moduleParts = mutableListOf<String>()

           while (current().tokenType != TokenType.End) {
               if (current().tokenType == TokenType.Identifier) {
                   val text = consume().text

                   if (current().tokenType == TokenType.Slash) {
                       moduleParts.add(text)
                       consume()
                   } else {
                       superClass = text
                       break
                   }
               } else {
                   throw RuntimeException("bad ${current()}")
               }
           }

           superModule = moduleParts.joinToString("/")
       }

        expectToken(TokenType.Colon)
        consume()

        currentClassContext = ClassContext(name)

        return Class(name, superModule, superClass, modifiers, currentClassContext!!)
    }

    private fun parseFunction(): Value {
        consume() // function

        val modifiers = mutableListOf<Modifier>()

        while (current().tokenType.isModifier()) {
            modifiers.add(parseModifier())
        }

        val returnType = parseType()

        expectTokens(TokenType.Identifier, TokenType.Instruction)
        var name = consume().text

        if (current().tokenType == TokenType.DoubleColon) {
            consume()
            expectTokens(TokenType.Identifier, TokenType.Instruction)

            name += "::" + consume().text
        }

        expectToken(TokenType.LeftParen)
        consume()

        val argumentTypes = mutableListOf<Type>()

        currentFunctionContext = FunctionContext()

        while (current().tokenType != TokenType.RightParen) {
            val type = parseType()
            argumentTypes.add(type)

            if (current().tokenType != TokenType.RightParen) {
                expectToken(TokenType.Comma)
                consume()
            }
        }
        consume()

        expectToken(TokenType.Colon)
        consume()

        val type = getFunctionType(returnType, argumentTypes)
        return Function(name, type, modifiers, currentFunctionContext!!)
    }

    private fun parseDefine(): Value? {
        consume() // define

        expectToken(TokenType.Identifier)
        val name = consume().text

        expectToken(TokenType.Equals)
        consume()

        val value = expressionParser.parse(currentFunctionContext)

        globalContext.defineConstant(name, value)

        return null
    }

    private fun parseConstant(): Value {
        consume() // const

        expectToken(TokenType.String)
        val name = consume().text

        expectToken(TokenType.Equals)
        consume()

        globalContext.addConstant(name)

        return parseConstantValue()
    }

    private fun parseConstantValue(): Value {
        expectToken(TokenType.Dot)
        consume()

        val token = current()

        when (token.tokenType) {
            TokenType.Function -> {
                return parseConstantFunction()
            }

            TokenType.Class -> {
                return parseConstantClass()
            }

            TokenType.Field -> {
                return parseConstantField()
            }

            TokenType.Method -> {
                return parseConstantMethod()
            }

            else -> {
                throw RuntimeException("bad $token")
            }
        }
    }

    private fun parseLocalsBind(): Value? {
        consume() // bind

        expectToken(TokenType.LeftParen)
        consume()

        if (currentFunctionContext == null) {
            throw RuntimeException("can't bind locals without a function being declared")
        }

        while (current().tokenType != TokenType.RightParen) {
            expectToken(TokenType.Immediate)

            val index = consume().text.toUShort()

            expectToken(TokenType.Colon)
            consume()

            expectToken(TokenType.Identifier)
            val name = consume().text

            if (currentFunctionContext!!.locals.contains(name)) {
                throw RuntimeException("there's already a local named $name which is bound to ${currentFunctionContext!!.locals[name]}")
            }

            currentFunctionContext!!.locals[name] = index
        }
        consume()

        return null
    }

    private fun parseConstantFunction(): Value {
        consume() // function

        val returnType = parseType()

        expectToken(TokenType.Identifier)

        val moduleParts = mutableListOf<String>()
        var name = "0"

        while (current().tokenType != TokenType.End) {
            if (current().tokenType == TokenType.Identifier) {
                val text = consume().text

                if (current().tokenType == TokenType.Slash) {
                    moduleParts.add(text)
                    consume()
                } else {
                    name = text
                    break
                }
            } else {
                throw RuntimeException("bad ${current()}")
            }
        }

        if (current().tokenType == TokenType.DoubleColon) {
            consume()
            expectToken(TokenType.Identifier)

            name += "::" + consume().text
        }

        val module = moduleParts.joinToString("/")

        expectToken(TokenType.LeftParen)
        consume()

        val argumentTypes = mutableListOf<Type>()

        while (current().tokenType != TokenType.RightParen) {
            val type = parseType()
            argumentTypes.add(type)

            if (current().tokenType != TokenType.RightParen) {
                expectToken(TokenType.Comma)
                consume()
            }
        }
        consume()

        val functionType = getFunctionType(returnType, argumentTypes)
        return ConstantFunction(module, name, functionType)
    }

    private fun parseConstantClass(): Value {
        consume() // class

        val moduleParts = mutableListOf<String>()
        var name = "0"

        while (current().tokenType != TokenType.End) {
            if (current().tokenType == TokenType.Identifier) {
                val text = consume().text

                if (current().tokenType == TokenType.Slash) {
                    moduleParts.add(text)
                    consume()
                } else {
                    name = text
                    break
                }
            } else {
                throw RuntimeException("bad ${current()}")
            }
        }

        val module = moduleParts.joinToString("/")

        return ConstantClass(module, name)
    }

    private fun parseConstantField(): Value {
        consume() // field

        val type = parseType()

        val moduleParts = mutableListOf<String>()
        var className = "0"

        while (current().tokenType != TokenType.End) {
            if (current().tokenType == TokenType.Identifier) {
                val text = consume().text

                if (current().tokenType == TokenType.Slash) {
                    moduleParts.add(text)
                    consume()
                } else {
                    className = text
                    break
                }
            } else {
                throw RuntimeException("bad ${current()}")
            }
        }

        val module = moduleParts.joinToString("/")

        expectToken(TokenType.DoubleColon)
        consume()

        val name = consume().text

        return ConstantField(module, className, name)
    }

    private fun parseConstantMethod(): Value {
        consume() // field

        val returnType = parseType()

        val moduleParts = mutableListOf<String>()
        var className = "0"

        while (current().tokenType != TokenType.End) {
            if (current().tokenType == TokenType.Identifier) {
                val text = consume().text

                if (current().tokenType == TokenType.Slash) {
                    moduleParts.add(text)
                    consume()
                } else {
                    className = text
                    break
                }
            } else {
                throw RuntimeException("bad ${current()}")
            }
        }

        val module = moduleParts.joinToString("/")

        expectToken(TokenType.DoubleColon)
        consume()

        val name = consume().text

        expectToken(TokenType.LeftParen)
        consume()

        val argumentTypes = mutableListOf<Type>()

        while (current().tokenType != TokenType.RightParen) {
            val type = parseType()
            argumentTypes.add(type)

            if (current().tokenType != TokenType.RightParen) {
                expectToken(TokenType.Comma)
                consume()
            }
        }
        consume()

        val functionType = getFunctionType(returnType, argumentTypes)
        return ConstantMethod(module, className, name, functionType)
    }

    private inline fun expectToken(type: TokenType) = tokenStream.expectToken(type)

    private inline fun expectTokens(vararg types: TokenType) = tokenStream.expectTokens(*types)

    private inline fun current() = tokenStream.current()

    private inline fun consume() = tokenStream.consume()

    private inline fun peek(offset: Int) = tokenStream.peek(offset)
}

fun TokenType.isModifier(): Boolean {
    return this in arrayOf(TokenType.Public, TokenType.Private)
}
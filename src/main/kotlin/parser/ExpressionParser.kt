package cum.jesus.jesusasm.parser

import cum.jesus.jesusasm.environment.FunctionContext
import cum.jesus.jesusasm.environment.GlobalContext
import cum.jesus.jesusasm.lexer.TokenType

class ExpressionParser(private val tokenStream: TokenStream, private val globalContext: GlobalContext) {
    private var functionContext: FunctionContext? = null

    fun parse(functionContext: FunctionContext?): ULong {
        this.functionContext = functionContext

        return parseExpression()
    }

    private fun getBinaryOperatorPrecedence(tokenType: TokenType): Int {
        return when (tokenType) {
            TokenType.LeftParen -> 90

            TokenType.Star, TokenType.Slash -> 75

            TokenType.Plus, TokenType.Minus -> 70

            else -> 0
        }
    }

    private fun getPrefixUnaryOperatorPrecedence(tokenType: TokenType): Int {
        return when (tokenType) {
            TokenType.Minus, TokenType.LeftParen -> 85

            else -> 0
        }
    }

    private fun parseExpression(precedence: Int = 1): ULong {
        var lhs: ULong
        val prefixOperatorPrecedence = getPrefixUnaryOperatorPrecedence(current().tokenType)

        if (prefixOperatorPrecedence >= precedence) {
            val operatorToken = consume()

            when (operatorToken.tokenType) {
                TokenType.Minus -> {
                    lhs = parseExpression(prefixOperatorPrecedence)
                    lhs = (-lhs.toLong()).toULong()
                }
                TokenType.LeftParen -> {
                    lhs = parseParenExpression()
                }

                else -> throw RuntimeException("unreachable")
            }
        } else {
            lhs = parsePrimary()
        }

        while (true) {
            val binaryOperatorPrecedence = getBinaryOperatorPrecedence(current().tokenType)
            if (binaryOperatorPrecedence < precedence) {
                break
            }

            val operatorToken = consume()

            when (operatorToken.tokenType) {
                TokenType.Plus -> {
                    val rhs = parseExpression(binaryOperatorPrecedence)
                    lhs += rhs
                }
                TokenType.Minus -> {
                    val rhs = parseExpression(binaryOperatorPrecedence)
                    lhs -= rhs
                }
                TokenType.Star -> {
                    val rhs = parseExpression(binaryOperatorPrecedence)
                    lhs *= rhs
                }
                TokenType.Slash -> {
                    val rhs = parseExpression(binaryOperatorPrecedence)
                    lhs /= rhs
                }

                else -> throw RuntimeException("should be unreachabke")
            }
        }

        return lhs
    }

    private fun parsePrimary(): ULong {
        when (current().tokenType) {
            TokenType.String -> return parseConstant()
            TokenType.Identifier -> return parseVariable()

            TokenType.Immediate -> return parseImmediate()

            else -> throw RuntimeException("erm")
        }
    }

    private fun parseConstant(): ULong {
        val name = consume().text
        return globalContext.constants[name]!!.toULong()
    }

    private fun parseVariable(): ULong {
        val name = consume().text
        return globalContext.defines[name]!!
    }

    private fun parseParenExpression(): ULong {
        val expr = parseExpression()

        expectToken(TokenType.RightParen)
        consume()

        return expr
    }

    private fun parseImmediate(): ULong {
        return consume().text.toULong()
    }

    private inline fun expectToken(type: TokenType) = tokenStream.expectToken(type)

    private inline fun expectTokens(vararg types: TokenType) = tokenStream.expectTokens(*types)

    private inline fun current() = tokenStream.current()

    private inline fun consume() = tokenStream.consume()

    private inline fun peek(offset: Int) = tokenStream.peek(offset)
}
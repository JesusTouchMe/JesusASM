/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.lexer

import cum.jesus.jesusasm.type.isType
import cum.jesus.jesusasm.util.extensions.isBinDigit
import cum.jesus.jesusasm.util.extensions.isHexDigit
import cum.jesus.jesusasm.util.extensions.isOctDigit

val instructions = hashSetOf(
    "nop",
    "pop",
    "dup",
    "load",
    "loadobj",
    "store",
    "storeobj",
    "aload",
    "aloadobj",
    "astore",
    "astoreobj",
    "new",
    "newarray",
    "newarrayprim",
    "getfield",
    "putfield",
    "add",
    "sub",
    "mul",
    "div",
    "and",
    "or",
    "xor",
    "inc",
    "dec",
    "not",
    "neg",
    "cmp",
    "jmp",
    "jeq",
    "jne",
    "jlt",
    "jgt",
    "jle",
    "jge",
    "call",
    "ret",
    "constload",
    "ldi",
    "ldi_0",
    "debug",
    "hlt",
)

val keywords = hashMapOf(
    "module" to TokenType.Module,
    "entry" to TokenType.Entry,
    "locals" to TokenType.Locals,
    "class" to TokenType.Class,
    "extends" to TokenType.Extends,
    "field" to TokenType.Field,
    "method" to TokenType.Method,
    "function" to TokenType.Function,
    "define" to TokenType.Define,
    "const" to TokenType.Const,
    "section" to TokenType.Section,
    "public" to TokenType.Public,
    "private" to TokenType.Private,
)

class Lexer(val text: String) {
    private var position = 0
    private var line = 1
    private var column = 1

    fun lex(): List<Token> {
        val tokens = mutableListOf<Token>()

        while (position < text.length) {
            val token = nextToken()

            if (token != null) {
                tokens.add(token)
            }

            consume()
        }

        tokens.add(Token(SourceLocation(line, column), TokenType.End))

        return tokens
    }

    private fun nextToken(): Token? {
        val startSourceLocation = SourceLocation(line, column)

        if (current().isLetter() || current() == '_') {
            val sb = StringBuilder().append(current())

            while (peek(1).isLetterOrDigit() || peek(1) == '_') {
                consume()
                sb.append(current())
            }

            val text = sb.toString()

            if (text.lowercase() in instructions) {
                return Token(startSourceLocation, TokenType.Instruction, text.lowercase())
            }

            val it = keywords[text.lowercase()]
            if (it != null) {
                return Token(startSourceLocation, it, text.lowercase())
            }

            if (isType(text)) {
                return Token(startSourceLocation, TokenType.Type, text)
            }

            return Token(startSourceLocation, TokenType.Identifier, text)
        }

        if (current().isWhitespace()) {
            return null
        }

        if (current().isDigit()) {
            val sb = StringBuilder().append(current())

            if (current() == '0') {
                if (peek(1) == 'x') {
                    consume()
                    sb.append(current())

                    while (peek(1).isHexDigit()) {
                        consume()
                        sb.append(current())
                    }
                } else if (peek(1) == 'b') {
                    consume()
                    sb.append(current())

                    while (peek(1).isBinDigit()) {
                        consume()
                        sb.append(current())
                    }
                } else {
                    while (peek(1).isOctDigit()) {
                        consume()
                        sb.append(current())
                    }
                }
            } else {
                while (peek(1).isDigit()) {
                    consume()
                    sb.append(current())
                }
            }

            return Token(startSourceLocation, TokenType.Immediate, sb.toString())
        }

        when (current()) {
            '$' -> return Token(startSourceLocation, TokenType.Dollar, "$")

            '+' -> return Token(startSourceLocation, TokenType.Plus, "+")
            '-' -> return Token(startSourceLocation, TokenType.Minus, "-")
            '*' -> return Token(startSourceLocation, TokenType.Star, "*")
            '/' -> return Token(startSourceLocation, TokenType.Slash, "/")

            '(' -> return Token(startSourceLocation, TokenType.LeftParen, "(")
            ')' -> return Token(startSourceLocation, TokenType.RightParen, ")")

            ',' -> return Token(startSourceLocation, TokenType.Comma, ",")
            '.' -> return Token(startSourceLocation, TokenType.Dot, ".")
            ';' -> {
                while (current() != '\n') {
                    consume()
                }

                return null
            }
            ':' -> {
                if (peek(1) == ':') {
                    consume()
                    return Token(startSourceLocation, TokenType.DoubleColon, "::")
                }

                return Token(startSourceLocation, TokenType.Colon, ":")
            }

            '=' -> return Token(startSourceLocation, TokenType.Equals, "=")

            '"' -> {
                consume()
                val sb = StringBuilder()

                while (current() != '"') {
                    when (current()) {
                        '\\' -> {
                            consume()

                            sb.append(when (current()) {
                                'n' -> '\n'
                                't' -> '\t'
                                'r' -> '\r'
                                '\'' -> '\''
                                '\\' -> '\\'

                                else -> return Token(startSourceLocation, TokenType.Error)
                            })
                        }

                        else -> sb.append(current())
                    }

                    consume()
                }

                return Token(startSourceLocation, TokenType.String, sb.toString())
            }

            else -> return Token(startSourceLocation, TokenType.Error)
        }
    }

    private fun current(): Char {
        return text[position]
    }

    private fun consume(): Char {
        val c = text[position++]

        if (c == '\n') {
            column = 1
            line += 1
        } else {
            column += 1
        }

        return c
    }

    private fun peek(offset: Int): Char {
        try {
            return text[position + offset]
        } catch (_: Throwable) {
            return 0.toChar()
        }
    }
}
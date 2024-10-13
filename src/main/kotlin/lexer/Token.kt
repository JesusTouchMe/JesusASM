/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.lexer

enum class TokenType {
    Error,

    Dollar,

    Plus, Minus,
    Star, Slash,

    LeftParen, RightParen,

    Comma,
    Dot, Colon,
    DoubleColon,

    Equals,

    Identifier,

    Immediate,
    String,

    Module,
    Entry,

    Locals,
    Bind,

    Class,
    Extends,
    Field,
    Method,
    Function,

    Define,
    Const,
    Section,

    Public,
    Private,

    Instruction,

    End,
}

data class SourceLocation(val line: Int, val column: Int)

data class Token(val sourceLocation: SourceLocation, val tokenType: TokenType, val text: String = "") {
    override operator fun equals(other: Any?): Boolean {
        if (other !is Token) return false

        return text == other.text && tokenType == other.tokenType;
    }
}
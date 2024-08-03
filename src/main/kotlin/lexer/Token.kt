/*
Copied from https://github.com/viper-org/vasm and adapted to JesusASM syntax and architecture

Credit to the goat solar mist for letting me use his code
*/

package cum.jesus.jesusasm.lexer

enum class TokenType {
    Error,

    Dollar,

    Slash,

    LeftParen, RightParen,

    Comma,
    Dot, Colon,

    Equals,

    Identifier,

    Immediate,
    String,

    Module,
    Stack,
    Entry,

    Locals,

    Function,

    Const,
    Section,

    Public,
    Private,

    Type,

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
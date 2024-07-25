package cum.jesus.jesusasm.lexer

enum class TokenType {
    Error,

    Dollar,

    Comma,
    Dot, Colon,

    Identifier,

    Immediate,
    String,

    Module,
    Stack,
    Function,
    Entry,

    Const,
    Public,
    Private,
    Section,

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
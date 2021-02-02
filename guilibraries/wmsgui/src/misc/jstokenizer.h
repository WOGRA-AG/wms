
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <vector>

#include "jsenv.h"
/**
Enumerates the different token types.
*/
enum InputTokenType {
    // Marks a token variables a unassigned
    TT_EMPTY,
    // Marks the end of input
    TT_EOF,
    // Represents an unknown token.
    TT_UNKNOWN,
    // Represents a comment. This is used by the syntax highlighter.
    TT_COMMENT,
    // Represents a name
    TT_NAME,
    // Represents a symbol starting with #
    TT_SYMBOL,
    // Represents a string constant
    TT_STRING,
    // Represents a numeric constant
    TT_NUMBER,
    // Represents a decimal constant
    TT_DECIMAL,
    // ;
    TT_SEMICOLON,
    // :=
    TT_ASSIGNMENT,
    // ::=
    TT_GLOBAL_ASSIGNMENT,
    // :
    TT_COLON,
    // ,
    TT_KOMMA,
    // .
    TT_DOT,
    // +
    TT_PLUS,
    // -
    TT_MINUS,
    // *
    TT_MUL,
    // %
    TT_MOD,
    // /
    TT_DIV,
    // &&
    TT_AND,
    // ||
    TT_OR,
    // &
    TT_CONCAT,
    // |
    TT_SPLIT,
    // =
    TT_EQ,
    // !
    TT_NOT,
    // !=
    TT_NE,
    // >
    TT_GT,
    // <
    TT_LT,
    // >=
    TT_GTEQ,
    // <=
    TT_LTEQ,
    // (
    TT_L_BRACE,
    // )
    TT_R_BRACE,
    // [
    TT_L_BRACKET,
    // ]
    TT_R_BRACKET,
    // {
    TT_L_CURLY,
    // }
    TT_R_CURLY,
    // ->
    TT_ARROW,
    // #(
    TT_LIST_START
};

/**
Represents a token which is encountered during parsing.
*/
struct InputToken {
    // Contains the type of the token
    InputTokenType type;

    // Contains the position of the token
    int line;
    int pos;

    // used for syntax highlighting etc.
    int absolutePos;

    // Contains the length of the token.
    int length;
};

/**
Represents the tokenizer.
*/
class Tokenizer
{
private:
    /**
Determines if comments are ignored.
*/
    bool ignoreComments;

    /**
Contains the current line
*/
    int line;
    /**
Contains the column within the current line
*/
    int pos;

    /**
Contains the absolute pos since teh start of the input.
In constast: pos is relative to the current line.
*/
    int absolutePos;

    /**
Contains the inputstream which provides the source code.
*/
    QString input;

    /**
Contains the current character.
*/
    QChar ch;

    /**
Contains the current token.
*/
    InputToken current;

    /**
Contains the current lookahead. (Next after current).
*/
    InputToken lookahead;

    /**
Contains the current +2 lookahead. (Next after lookahead).
*/
    InputToken lookahead2;

    /**
Fetches the next char.
*/
    QChar nextChar();

    /**
Checks if we already reached the end of the input.
*/
    bool more();

    /**
Checks if there is another character available after the current one.
*/
    bool hasPreview();

    /**
Returns a preview for the next character.
*/
    QChar preview();

    /**
Computes the next token.
*/
    InputToken fetchToken();

    /**
Fetches a name-token.
*/
    InputToken parseName(InputTokenType type, bool acceptDashes);

    /**
Fetches a symbol-token.
*/
    InputToken parseSymbol();

    /**
Fetches a numeric-token.
*/
    InputToken parseNumber();

    /**
Fetches a string-token.
*/
    InputToken parseString();

    /**
Fetches a operator-token.
*/
    InputToken parseOperator();

    /**
Fetches a comment-token.
*/
    InputToken parseComment();

    /**
Skips blanks, tabs and new-lines.
*/
    void skipWhitespace();
public:
    /**
Returns the current token.
*/
    InputToken getCurrent();

    /**
Returns whether the current token has the given type.
*/
    bool isCurrent(InputTokenType type);

    /**
Returns whether the lookahead token has the given type.
*/
    bool isLookahead(InputTokenType type);

    /**
Returns whether the second lookahead token has the given type.
*/
    bool isLookahead2(InputTokenType type);

    /**
Fetches the next token.
*/
    InputToken fetch();

    /**
Returns the next token, without discarding the current.
*/
    InputToken getLookahead();

    /**
Returns the token after lookahead() without discarding the two
previous.
*/
    InputToken getLookahead2();

    /**
Returns the string representation of the given token.
*/
    QString getString(InputToken token);

    /**
Returns the string representation of the current token.
*/
    QString getCurrentString();

    /**
Initializes the tokenizer with a given stream.
*/
    Tokenizer(const QString& input, bool ignoreComments);
};

#endif // // TOKENIZER_H

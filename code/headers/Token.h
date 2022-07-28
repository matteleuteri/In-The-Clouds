#ifndef _TOKEN
#define _TOKEN

#include <string>

class Token 
{
public:
    enum TokenType
    {
        OPEN_BRACE,
        CLOSED_BRACE,
        OPEN_BRACKET,
        CLOSED_BRACKET,
        ANIMATIONCONTROLLERNAME,
        ANIMATIONNAME,
        ATTRIBUTE,
        VALUE
    };
    Token::Token(char c);
    TokenType tokenType;
    char tokenValue;
};

#endif
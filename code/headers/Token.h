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
    TokenType tokenType;
    std::string tokenValue;
};
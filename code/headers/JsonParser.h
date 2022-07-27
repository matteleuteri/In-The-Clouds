#ifndef _JSONPARSER
#define _JSONPARSER

#include <string>
#include <vector>
#include <windows.h>
#include <filesystem>

#include "AnimationController.h"
#include "Animation.h"
#include "Token.h"

class JsonParser
{
public:
    std::filesystem::path p;
    JsonParser::JsonParser(std::filesystem::path p);   
    std::vector<AnimationController*> controllers;
    void JsonParser::parse();
    std::vector<Token*> JsonParser::tokenizeFileContents(char fileContents[1000000]);
    void JsonParser::readIn(char *fileContents, LPCSTR fname);
    int JsonParser::findCorrespondingBracket(char fileContents[1000000], int i);
    std::vector<AnimationController*> JsonParser::getControllers(char fileContents[1000000]);
};

#endif
#include "headers/JsonParser.h"

JsonParser::JsonParser(std::filesystem::path): p(p)
{}

void JsonParser::readIn(char *fileContents, LPCSTR fname)
{
    HANDLE fileHandle = CreateFileA(fname,  GENERIC_READ, FILE_SHARE_READ, 
                NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL , NULL);
    
    ReadFile(fileHandle, fileContents, 100, NULL, NULL);
    // if(fileHandle == INVALID_HANDLE_VALUE)
    // {
        // OutputDebugStringA("invalid handle name\n");
    // }
    // else
    // {
        // OutputDebugStringA("good handle name\n");
    // }
    // if(ReadFile(fileHandle, fileContents, 100, NULL, NULL) == 0)
    // {
        // OutputDebugStringA("file could not be read\n");
    // }
    // else 
    // {
        // OutputDebugStringA("file successfully read\n");
    // }
}

void JsonParser::parse()
{
    LPCSTR fname = "C:\\Users\\meleu\\OneDrive\\Desktop\\In-The-Clouds\\assets\\ResourceTree.json";
    char fileContents[1000000];
    readIn(fileContents, fname);
    std::vector<AnimationController*> animationControllers = getControllers(fileContents);
}

int JsonParser::findCorrespondingBracket(char fileContents[1000000], int i)
{
    return 1;
}

std::vector<AnimationController*> JsonParser::getControllers(char fileContents[1000000])
{
    std::vector<AnimationController*> res = { };
    
    for(int i = 0; i < sizeof(fileContents) / sizeof(fileContents[0]); i++)
    {
        if(fileContents[i] == '{')
        {
            // int j = findCorrespondingBracket(fileContents, i);
            // createObjects(i+1);
        }
    }
    return res;
}

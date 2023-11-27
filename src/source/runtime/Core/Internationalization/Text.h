//
// Created by natha on 11/11/2023.
//

#ifndef TEXT_H
#define TEXT_H

#include <Container/String.h>
#include <map>

class Text : public String
{
public:
    Text();
    Text(const std::string& str);
    Text(const char* str);

private:
    std::map<uint8_t, std::string> msgtext;
    //void trEngineParse();
    //void trParse();
};



#endif //TEXT_H

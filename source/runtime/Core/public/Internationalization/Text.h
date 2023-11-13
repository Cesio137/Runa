//
// Created by natha on 11/11/2023.
//

#ifndef TEXT_H
#define TEXT_H

#include <Container/String.h>
#include <map>

using namespace std;

class Text : public String
{
public:
    Text();
    Text(const string& str);
    Text(const char* str);

private:
    map<uint8_t, string> msgtext;
    //void trEngineParse();
    //void trParse();
};



#endif //TEXT_H

//
// Created by natha on 09/11/2023.
//

#ifndef NANOMETRO_FSTRING_H
#define NANOMETRO_FSTRING_H

#include <string>

using namespace std;

class FString : public string
{
public:
    FString() : string("") {}
    FString(const string& str) : string(str) {}
    FString(const char* str) : string{str} {}
};

#endif //NANOMETRO_FSTRING_H

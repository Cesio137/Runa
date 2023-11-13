//
// Created by natha on 11/11/2023.
//

#include "String.h"

String::String()
{

}

String::String(const string &str)
    : string(str)
{

}

String::String(const char* str)
    : string(str)
{

}

string String::toUpper()
{
    string str = data();
    to_upper(str);
    return str;
}

string String::toLower()
{
    string str = data();
    to_lower(str);
    return str;
}





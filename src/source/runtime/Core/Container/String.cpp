//
// Created by natha on 11/11/2023.
//

#include "String.h"

using namespace std;

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
    for (char& c : str) {
        c = std::toupper(c);
    }
    return str;
}

string String::toLower()
{
    string str = data();
    for (char& c : str) {
        c = std::tolower(c);
    }
    return str;
}





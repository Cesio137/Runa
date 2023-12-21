#include "String.h"
#include <CoreMinimal.h>

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
        c = toupper(c);
    }
    return str;
}

string String::toLower()
{
    string str = data();
    for (char& c : str) {
        c = tolower(c);
    }
    return str;
}





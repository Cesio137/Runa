//
// Created by natha on 11/11/2023.
//

#ifndef STRING_H
#define STRING_H

#include <string>
#include <cctype>

class String : public std::string
{
public:
    String();
    String(const std::string& str);
    String(const char* str);

    std::string toUpper();
    std::string toLower();
};



#endif //STRING_H

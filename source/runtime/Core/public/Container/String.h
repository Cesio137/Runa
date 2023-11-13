//
// Created by natha on 11/11/2023.
//

#ifndef STRING_H
#define STRING_H

#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/fiber/algo/algorithm.hpp>

using namespace std;
using namespace boost::algorithm;

class String : public string
{
public:
    String();
    String(const string& str);
    String(const char* str);

    string toUpper();
    string toLower();
};



#endif //STRING_H

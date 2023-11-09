#ifndef FTEXT_H
#define FTEXT_H

#include <Core/FString.h>

using namespace std;

class FText : public FString
{
public:
    FText(const string& s) : FString(s) {}
    FText(const char* s) : FString{s} {}
};

#endif // FTEXT_H

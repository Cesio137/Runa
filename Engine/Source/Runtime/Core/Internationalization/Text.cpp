#include "Text.h"
#include <CoreMinimal.h>

Text::Text()
{

}

Text::Text(const string& str)
    : String(str)
{

}

Text::Text(const char* str)
    : String(str)
{

}

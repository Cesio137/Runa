#include "FileStream.h"

FileStream::FileStream(const string& file)
    : fstream(file)
{

}

FileStream::FileStream(const char* file)
    : fstream(file)
{

}

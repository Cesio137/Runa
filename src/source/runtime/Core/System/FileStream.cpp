//
// Created by natha on 11/11/2023.
//

#include "FileStream.h"

using namespace std;

FileStream::FileStream(const string& file)
    : fstream(file)
{

}

FileStream::FileStream(const char* file)
    : fstream(file)
{

}

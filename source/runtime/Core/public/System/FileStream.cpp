//
// Created by natha on 11/11/2023.
//

#include "FileStream.h"

FileStream::FileStream(const string& file)
    : fstream(file)
{

}

FileStream::FileStream(const char* file)
    : fstream(file)
{

}

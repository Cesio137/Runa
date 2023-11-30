//
// Created by natha on 11/11/2023.
//

#ifndef NANOMETRO_FILE_H
#define NANOMETRO_FILE_H

#include <fstream>
#include <System/Dir.h>
#include <string>

class FileStream : public std::fstream
{
public:
    FileStream(const std::string& file);
    FileStream(const char* file);
};


#endif //NANOMETRO_FILE_H

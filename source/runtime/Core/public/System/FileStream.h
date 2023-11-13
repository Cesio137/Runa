//
// Created by natha on 11/11/2023.
//

#ifndef NANOMETRO_FILE_H
#define NANOMETRO_FILE_H

#include <fstream>
#include <System/Dir.h>
#include <string>

using namespace std;

class FileStream : public fstream
{
public:
    FileStream(const string& file);
    FileStream(const char* file);
};


#endif //NANOMETRO_FILE_H

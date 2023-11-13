//
// Created by natha on 11/11/2023.
//

#ifndef DIR_H
#define DIR_H

#include <Container/String.h>
#include <filesystem>
#include <Config.h>

class Dir : public std::filesystem::path
{
public:
    Dir();
    explicit Dir(const path& paths);
    explicit Dir(path&& pathses);
    explicit Dir(string_type&& _Source);
    Dir(string_type&& _Source, format format);

    static String nativeSeparator(String dir);
    static String HomeLocation();
    static String AppDataLocation();
    static String DesktopLocation();
    static String DownloadLocation();
    static String DocumentsLocation();

};



#endif //DIR_H

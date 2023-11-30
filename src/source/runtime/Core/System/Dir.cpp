//
// Created by natha on 11/11/2023.
//

#include "Dir.h"
#include <System/Enviroment.h>

using namespace std;

Dir::Dir()
{

}

Dir::Dir(const path& paths)
    : path(paths)
{

}

Dir::Dir(path&& pathses)
    : path(pathses)
{

}

Dir::Dir(string_type&& _Source)
    : path(_Source)
{

}

Dir::Dir(string_type&& _Source, format format)
    : path(_Source, format)
{
    
}

String Dir::nativeSeparator(String dir)
{
    if (dir.empty())
        return "";

    path directory(dir.c_str());

    return directory.make_preferred().string();
}

String Dir::HomeLocation()
{
    String path;

#ifdef HOST_SYSTEM_WINDOWS
    if (!Enviroment::GetVariable("USERPROFILE").empty())
    {
        path = Enviroment::GetVariable("USERPROFILE");
    }
#else
    if (!Enviroment::GetVariable("HOME").empty())
    {
        path = Enviroment::GetVariable("HOME");
    }
#endif

    return  path;
}

String Dir::AppDataLocation()
{
    String path;

#ifdef HOST_SYSTEM_WINDOWS
    if (!Enviroment::GetVariable("APPDATA").empty())
    {
        path = Enviroment::GetVariable("APPDATA");
    }
#else
    if (!HomeLocation().empty())
    {
        path = HomeLocation() + nativeSeparator("/.local/share");
    }
#endif
    
    return  path;
}

String Dir::DesktopLocation()
{
	if (!HomeLocation().empty())
	{
        return HomeLocation() + nativeSeparator("/Desktop");
	}
    return "";
}

String Dir::DownloadLocation()
{
    if (!HomeLocation().empty())
    {
        return HomeLocation() + nativeSeparator("/Downloads");
    }
    return "";
}

String Dir::DocumentsLocation()
{
    if (!HomeLocation().empty())
    {
        return HomeLocation() + nativeSeparator("/Documents");
    }
    return "";
}

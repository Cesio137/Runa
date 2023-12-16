#pragma once

#include <Container/String.h>
#include <Config.h>
#ifndef HOST_SYSTEM_WINDOWS
#include <cstdlib>
#endif

class Enviroment
{
public:
	static String GetVariable(String var);
	static String GetUserName();

private:

};
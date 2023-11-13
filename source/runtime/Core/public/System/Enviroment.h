#pragma once

#include <Container/String.h>
#include <Config.h>

class Enviroment
{
public:
	static String GetVariable(String var);
	static String GetUserName();

private:

};
#ifndef _BENCALCULATOR_H_
#define _BENCALCULATOR_H_

#pragma once

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include "resource.h"
#include "string"
#include "stdlib.h"
#include "sstream"
#include "cstdlib"
#include "vector"


class WCalculator
{
public:
	WCalculator(HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow);
	~WCalculator();
};

#endif
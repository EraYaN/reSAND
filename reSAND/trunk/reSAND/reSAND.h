#pragma once
#include <windows.h>
#include <tchar.h>
#include "sandManager.h"
/*******************************************************************
* Global Variables
*******************************************************************/
HWND hWnd;					//window handle
int windowWidth = 1000;	
int windowHeight = 1000;

//directX manager
dxManager dx;
sandManager sandM;
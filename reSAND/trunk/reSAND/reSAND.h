#pragma once
#include <windows.h>
#include <tchar.h>
#include <stdio.h>


#include "dxManager.h"
#include "sandManager.h"
/*******************************************************************
* Global Variables
*******************************************************************/
HWND hWnd;					//window handle
int windowWidth = 1024;	
int windowHeight = 768;

//directX manager
dxManager dx;
sandManager sandM;
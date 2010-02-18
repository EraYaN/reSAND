#pragma once
#include <windows.h>
#include <Winuser.h>
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

//world settings
UINT max_sands = 1000000;

//Cursor setting
int bsize = 10; //size of brush used for spawning
float smallest_unit_x = (20/(float)windowWidth);//used for physics and spawning
float smallest_unit_y = (20/(float)windowHeight);//used for physics and spawning
int brushtype = 0;
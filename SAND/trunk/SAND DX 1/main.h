#pragma once
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <list>
#include <algorithm>
#include "sand_phys.h"
// define the screen resolution
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
// global declarations
LPDIRECT3D9 d3d;    // the pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;    // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
LPD3DXFONT m_font;

std::vector<SAND_TYPE> sand_types;
std::vector<SAND> sands;
struct CUSTOMVERTEX {FLOAT X, Y, Z, RHW; DWORD COLOR;};
std::vector<CUSTOMVERTEX> SAND_vertices;
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
;
// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame(void);    // renders a single frame
void cleanD3D(void);    // closes Direct3D and releases memory
void init_graphics(void);    // 3D declarations
void update_graphics(void);    // 3D declarations
POINT mouse_coord;
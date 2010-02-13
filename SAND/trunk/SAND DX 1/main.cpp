// include the basic windows header files and the Direct3D header file
#include "main.h"



// define the screen resolution
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024

// include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")




// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow = 3)
{
    HWND hWnd;
    WNDCLASSEX wc;
	
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
                          L"WindowClass",
                          L"iSAND",
                          WS_OVERLAPPEDWINDOW,
                          0, 0,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, SW_MAXIMIZE);

	//save initail mouse coord
	
	GetCursorPos(&mouse_coord);

	// set up and initialize Direct3D
    initD3D(hWnd);

    // enter the main loop:

    MSG msg;

    while(TRUE)
    {
       
	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
		
       if(msg.message == WM_QUIT)
            break;
		
		     
	/*	if(msg.message == WM_LBUTTONDOWN){
			float xPos = GET_X_LPARAM(msg.lParam); 
			float yPos = GET_Y_LPARAM(msg.lParam);
			GetCursorPos(&mouse_coord);
			
		}*/

	GetCursorPos(&mouse_coord);		
render_frame();
       
    }

    // clean up DirectX and COM
    cleanD3D();

    return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}


// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hWnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = SCREEN_WIDTH;
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;

    // create a device class using this information and the info from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);

    init_graphics();    // call the function to initialize the graphics
}


// this is the function used to render a single frame
void render_frame(void)
{
update_graphics();    
d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	// create the vertices using the CUSTOMVERTEX struct
    
    d3ddev->BeginScene();
	// Create a colour for the text - in this case blue
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255,255,255,255);   

	// Create a rectangle to indicate where on the screen it should be drawn
	RECT rct;
	rct.left=10;
	rct.right=500;
	rct.top=10;
	rct.bottom=rct.top+25;
 	TCHAR buffer[80];
	// Draw some text
	_stprintf_s(buffer,L"Mouse Position: (X,Y) (%d,%d)",mouse_coord.x,mouse_coord.y);
	m_font->DrawText(NULL, buffer, -1, &rct, 0, fontColor );
        // select which vertex format we are using
        d3ddev->SetFVF(CUSTOMFVF);

        // select the vertex buffer to display
        d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
		int size = sizeof( v_buffer) / sizeof( v_buffer[0] );
        // copy the vertex buffer to the back buffer
        d3ddev->DrawPrimitive(D3DPT_POINTLIST, 0, size);

    d3ddev->EndScene();

    d3ddev->Present(NULL, NULL, NULL, NULL);
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
    v_buffer->Release();    // close and release the vertex buffer
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}


// this is the function that puts the 3D models into video RAM
void init_graphics(void)
{
    
	// create a vertex buffer interface called v_buffer
    d3ddev->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX),
                               0,
                               CUSTOMFVF,
                               D3DPOOL_MANAGED,
                               &v_buffer,
                               NULL);
	D3DXCreateFont( d3ddev, 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );
}
void update_graphics(void)
{
    
for_each(sands.begin(), sands.end(), &sand_phys::add_sands_to_vertex);
    VOID* pVoid;    // a void pointer
	
	// lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, &SAND_vertices[0], sizeof(SAND_vertices));
    v_buffer->Unlock();
}

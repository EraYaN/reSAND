#include "reSAND.h"
/*******************************************************************
extra implemetation for sandManager class
*******************************************************************/
/*vertex* sandManager::sand2vertex(){
	UINT numVertices = sandM.SANDS.size();
	vertex* iV = new vertex;
	for (unsigned long index=0; index<numVertices; ++index) {
    	iV[index] = vertex( D3DXVECTOR3(sandM.SANDS.at(index).X,
										sandM.SANDS.at(index).Y,
										0),
							D3DXVECTOR4(sandM.SAND_TYPES.at(sandM.SANDS.at(index).type).R,
										sandM.SAND_TYPES.at(sandM.SANDS.at(index).type).G,
										sandM.SAND_TYPES.at(sandM.SANDS.at(index).type).B,
										1)
							);		
    }
	return iV;
}*/


/*******************************************************************
end of extra implemetation for sandManager class
begin vertexbuffer fill function
*******************************************************************/
UINT writevertexbuffer(void){
	//fill vertex buffer with vertices
	UINT numVertices = sandM.SANDS.size();	
	vertex* v = NULL;	

	//lock vertex buffer for CPU use
	dx.pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &v );
	
	for(unsigned int index = 0;index<numVertices;++index){
		v[index] = vertex( D3DXVECTOR3(sandM.SANDS.at(index).X,
										sandM.SANDS.at(index).Y,
										0),
							D3DXVECTOR4(sandM.SAND_TYPES.at(sandM.SANDS.at(index).type).R,
										sandM.SAND_TYPES.at(sandM.SANDS.at(index).type).G,
										sandM.SAND_TYPES.at(sandM.SANDS.at(index).type).B,
										1)
							);		

	}
	dx.pVertexBuffer->Unmap();
	return numVertices;
}
/*******************************************************************
end vertex buffer fill function
* Main Window Procedure - handles application events
*******************************************************************/
LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		// Allow the user to press the escape key to end the application
        case WM_KEYDOWN	:	switch(wParam)
							{
								// Check if the user hit the escape key
								case VK_ESCAPE : PostQuitMessage(0);
								break;
								case VK_SPACE : brushtype+=1;
								if(brushtype>=sandM.SAND_TYPES.size()){
								brushtype = 0;
								}
									
								break;
							}
		
        break;	
		case WM_LBUTTONDOWN:
		if(lParam != NULL){
			float NY = (((float)HIWORD(lParam)-((float)windowHeight/2))/((float)windowHeight/20))*-1;
			float NX = ((float)LOWORD(lParam)-((float)windowWidth/2))/((float)windowHeight/20);
			/*int pty = HIWORD(lParam);
			int ptx = LOWORD(lParam);
  			 float NX = ptx/((windowWidth/2)-1)/(windowWidth/windowHeight);
 			 float NY = (1-pty)/(windowHeight/2);*/
			 float urc_x = NX-(((float)bsize/2)*smallest_unit_x);
			 float urc_y = NY-(((float)bsize/2)*smallest_unit_y);
			 float offset_x = 0.0;
			 float offset_y = 0.0;

			 for(int ispawn = 0; ispawn<(bsize*bsize); ++ispawn){
			 	
				offset_x += smallest_unit_x;
				if(offset_x>bsize*smallest_unit_x){
					offset_x = 0.0;
					offset_y += smallest_unit_y;
				}
				if(sandM.SANDS.size()<max_sands){
				sandM.SANDS.push_back(SAND((urc_x+offset_x),(urc_y+offset_y),brushtype));
				}
			 }
			//sandM.SANDS.push_back(SAND(NX,NY,0));
			//char msg;
			//sprintf(&msg,"X: %f Y: %f",NX*10,NY*10);
			//MessageBox(hWnd, (LPCSTR)msg, "Fatal Error!", MB_ICONERROR);
			}
        break;		
	
		// The user hit the close button, close the application
		case WM_DESTROY	:	PostQuitMessage(0);
		break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*******************************************************************
* Initialize Main Window
********************************************************************/
bool initWindow(HWND &hWnd, HINSTANCE hInstance, int width, int height)
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)wndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= TEXT("reSAND");
	wcex.hIconSm		= 0;
	RegisterClassEx(&wcex);

	//Resize the window
	RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);

	//create the window from the class above
	//disable resizing and correct for extra width and height
	hWnd = CreateWindow( "reSAND", 
						 "reSAND -  by Erwin de Haan",
						 WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
						 CW_USEDEFAULT, 
						 CW_USEDEFAULT, 
						 rect.right - rect.left, 
						 rect.bottom - rect.top, 
						 NULL, 
						 NULL, 
						 hInstance, 
						 NULL);
   
	//window handle not created
	if (!hWnd) return false;
	
	//if window creation was successful
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	return true;
}

/*******************************************************************
* WinMain
*******************************************************************/
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Set up the application window
	if ( !initWindow(hWnd, hInstance, windowWidth, windowHeight)) return 0;
	
	//set up directx manager
	if ( !dx.initialize(&hWnd, max_sands) ) return 0;
	
	// Main message loop
    MSG msg = {0};
    while (WM_QUIT != msg.message)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);			
		}	
		sandM.calc_phys(smallest_unit_x,smallest_unit_y);
		//dx.renderScene(sandM.sand2vertex(), sandM.getNumberOfSands());
		dx.renderScene(writevertexbuffer());
		//dx.renderScene(v, numVertices);

	

    }

	return (int) msg.wParam;
}

#include <windows.h> 
#include <d3d10.h> 
#include <d3dx10.h>

#define Error(X) MessageBox(NULL, X, "Error", MB_OK)

class Application
{
public:

    Application();
    ~Application();

    bool CreateD3DWindow(int width, int height);

    bool Initialize(); 
    void Render(float deltaTime);
    void MainLoop();

private:

    static LRESULT CALLBACK WndProc( HWND hWnd , UINT message , 
                                     WPARAM wParam , LPARAM lParam);

    HWND                        hWnd; 
    IDXGISwapChain*                pSwapChain;
    ID3D10RenderTargetView*        pRenderTargetView;
    ID3D10Device*                pDevice; 
    int                            width, height;
};

#pragma comment (lib, "d3d10.lib")
#pragma comment (lib, "d3dx10.lib")

Application::Application()
{
}

Application::~Application()
{
}

LRESULT CALLBACK Application::WndProc( HWND hWnd , UINT message , 
                                       WPARAM wParam , LPARAM lParam)
{ 
    switch(message){ 
    case WM_CLOSE: 
    case WM_DESTROY: 
        PostQuitMessage(0); 
        break;; 
    } 
    return DefWindowProc(hWnd,message,wParam,lParam); 
} 

bool Application::CreateD3DWindow(int width, int height)
{ 
    this->width = width;
    this->height = height;
    
    // Create A Window Class Structure 
    WNDCLASSEX wc; 
    ZeroMemory(&wc, sizeof(wc));        
    wc.cbSize = sizeof(wc);                
    wc.hInstance = GetModuleHandle(NULL);        
    wc.lpfnWndProc = WndProc;                    
    wc.lpszClassName = "GPORG";                        
    wc.style = CS_HREDRAW | CS_VREDRAW;            
    
    // Register Window Class 
    RegisterClassEx(&wc); 
    
    // Create Window 
    hWnd = CreateWindowEx(0, "GPORG", 
           "GameProgrammer.org Direct3D 10 Tutorial", 
           WS_OVERLAPPEDWINDOW|WS_VISIBLE, CW_USEDEFAULT, 
           CW_USEDEFAULT, width, height, NULL,NULL,wc.hInstance,0);
    
    return true; 
} 

bool Application::Initialize()
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory( &swapChainDesc, sizeof(swapChainDesc) );
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;

    if( FAILED( D3D10CreateDeviceAndSwapChain( NULL, 
        D3D10_DRIVER_TYPE_HARDWARE, NULL, 
        0, D3D10_SDK_VERSION, &swapChainDesc, 
        &pSwapChain, &pDevice ) ) )
    {
        if( FAILED( D3D10CreateDeviceAndSwapChain( NULL, 
            D3D10_DRIVER_TYPE_REFERENCE, NULL, 
            0, D3D10_SDK_VERSION, &swapChainDesc, 
            &pSwapChain, &pDevice ) ) )
        {
            Error("Failed to create device and swap chain.");
            return false;
        }
    }

    ID3D10Texture2D *pBackBuffer;
    if( FAILED( pSwapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), 
              (LPVOID*)&pBackBuffer ) ) )
    {
        Error("Failed to create back buffer.");
        return false;
    }

    if(FAILED( pDevice->CreateRenderTargetView( pBackBuffer, 
               NULL, &pRenderTargetView )))
    {
        Error("Failed to create render target view.");
        return false;
    }

    pBackBuffer->Release();

    pDevice->OMSetRenderTargets( 1, &pRenderTargetView, NULL );

    D3D10_VIEWPORT vp = {0, 0, width, height, 0, 1};
    pDevice->RSSetViewports( 1, &vp );
    
    return true; 
} 

void Application::Render(float deltaTime)
{
    pDevice->ClearRenderTargetView( pRenderTargetView, 
                                       D3DXVECTOR4(0, 0, 0, 1) );

    pSwapChain->Present( 0, 0 );
} 

void Application::MainLoop()
{ 
    MSG msg; 
    long prevTime = GetTickCount(), curTime = GetTickCount();
    while(true)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message==WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else{
            Render((curTime-prevTime)/1000.f);
            prevTime = curTime;
            curTime = GetTickCount();
        }
    }
} 

INT WINAPI WinMain( HINSTANCE , HINSTANCE , LPSTR , INT )
{ 
    Application app;
    
    if(app.CreateD3DWindow(640, 480))
    {
        if(app.Initialize())
        {
            app.MainLoop();
        }
    }
    
    return 0; 
}
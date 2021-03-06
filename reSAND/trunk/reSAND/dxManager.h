#pragma once
#ifndef DXMANAGER
#define DXMANAGER
#include <windows.h>
#include <d3d10.h>
#include <d3dx10.h>


//create a basic vertex container
struct vertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR4 color;

	vertex( D3DXVECTOR3 p, D3DXVECTOR4 c )
	{
		pos = p;
		color = c;
	}
	vertex(void)
	{
		pos = D3DXVECTOR3();
		color = D3DXVECTOR4();
	}
};

class dxManager
{
	/*******************************************************************
	* Members
	********************************************************************/	
private:

	//window handle
	HWND*						hWnd;
	
	//device vars
	ID3D10Device*				pD3DDevice;
	IDXGISwapChain*				pSwapChain;
	ID3D10RenderTargetView*		pRenderTargetView;
	D3D10_VIEWPORT				viewPort;

	//input layout	
	ID3D10InputLayout*			pVertexLayout;

	//effects and techniques
	ID3D10Effect*				pBasicEffect;
	ID3D10EffectTechnique*		pBasicTechnique;

	//effect variable pointers
	ID3D10EffectMatrixVariable* pViewMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pProjectionMatrixEffectVariable;
	ID3D10EffectMatrixVariable* pWorldMatrixEffectVariable;
	
	//projection and view matrices
	D3DXMATRIX                  viewMatrix;
	D3DXMATRIX                  projectionMatrix;

	

	/*******************************************************************
	* Methods
	********************************************************************/	
public:
	//Font Interface
	//ID3D10XFont *m_font;
	//Vertex buffer
	ID3D10Buffer*				pVertexBuffer;
	//constructor and destructor
	dxManager();
	~dxManager();

	//initialize directx device
	bool initialize(HWND*, UINT max_vert);	

	//renderScene
	void renderScene(UINT numVertices);	
	void renderScene(vertex* iV, UINT numVertices);	


private:

	//fatal error handler
	bool fatalError(LPCSTR msg); 
};

#endif
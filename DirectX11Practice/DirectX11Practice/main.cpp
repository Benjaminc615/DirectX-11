#pragma once
//#pragma comment(lib, "Effects11d.lib")
#include "d3dx11effect.h"       
#include "Defines.h"
#include "Mathfunc.h"



using namespace std;
using namespace DirectX;



HINSTANCE					g_hInst = NULL;
HWND						g_hWnd = NULL;
wstring						g_wndName;

D3D_DRIVER_TYPE				g_driveType = D3D_DRIVER_TYPE_HARDWARE;
D3D_FEATURE_LEVEL			g_featureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*				g_device = NULL;
ID3D11DeviceContext*		g_context = NULL;
IDXGISwapChain*				g_swapChain = NULL;
ID3D11InputLayout*			g_inputLayout = NULL;
ID3D11BlendState*			g_transparency = NULL;
ID3D11RasterizerState*		g_CWcullMode = NULL;
ID3D11RasterizerState*		g_CCWcullMode = NULL;
ID3D11RasterizerState*		g_RSCullNone = NULL;
ID3D11RasterizerState*		g_RSCullNoneFW = NULL;

ID3D11RenderTargetView*		g_renderTargetView = NULL;
ID3D11DepthStencilView*		g_DepthStencilView = NULL;
ID3D11DepthStencilState*	g_depthStencilState = NULL;
ID3D10Blob*					g_vertSBuffer = NULL;
ID3D10Blob*					g_pixelSBuffer = NULL;
ID3D11VertexShader*			g_vertexShader = NULL;
ID3D11PixelShader*			g_pixelShader = NULL;
ID3D11Buffer*				g_squareVertexBuffer = NULL;
ID3D11Buffer*				g_squareIndexBuffer = NULL;
ID3D11Buffer*				g_constantBuffer = NULL;
ID3D11ShaderResourceView*	g_cubeTexture = NULL;
ID3D11SamplerState*			g_cubeSampler = NULL;
UINT screenWidth ;
UINT screenHeight;


//Input
IDirectInputDevice8*		g_keyboard;
IDirectInputDevice8*		g_mouse;
DIMOUSESTATE				g_mouseLastState;
LPDIRECTINPUT8				g_directInput;
float						g_rotX = 0;
float						g_rotZ = 0;
float						g_scaleX = 1.0f;
float						g_scaleY = 1.0f;
float						g_zoomIn = 1.0f;

XMMATRIX					g_rotationX;
XMMATRIX					g_rotationZ;

///Ground variables
//
ID3D11Buffer*				g_groundVertexBuffer = NULL;
ID3D11Buffer*				g_groundIndexBuffer = NULL;
ID3D11ShaderResourceView*	g_groundTexture = NULL;
XMMATRIX groundWorld = XMMatrixIdentity();
//

///Loading Models variable
s_OBJModel spaceRoom;
s_OBJModel grassGround;
s_OBJModel pickingObject;
s_OBJModel dogPNTModel;

///dogPNTModel variables
//
ID3D11HullShader*			g_dogPNTHS = NULL;
ID3D11DomainShader*			g_dogPNTDS = NULL;
ID3D11VertexShader*			g_dogPNTVS = NULL;
ID3D10Blob*					g_dogPNTVSB = NULL;
ID3D10Blob*					g_dogPNTHSBuffer = NULL;
ID3D10Blob*					g_dogPNTDSBuffer = NULL;
bool isGDown = false;
bool isPhongTessel = false;
ID3D11InputLayout*			g_dogPNTInputLayout = NULL;
//

///picking objects variables
//
XMMATRIX pickingObjectWorld[820];
int* pickingObjectHit = new int[820];
int numPinckingObject = 820;
int g_clientWidth = 0;
int g_clientHeight = 0;
int pickMode = 0;
float pickingDist = 0.0f;
double pickOpSpeed = 0.0f;
bool isShoot = false;
bool isPDown = false;
XMVECTOR objCenterOffset;
float objBoundingSphere = 0.0f;
std::vector<XMFLOAT3> objBoundingBoxVertPosArray;
std::vector<DWORD> objBoundingBoxVertIndexArray;
XMVECTOR objBoundingBoxMinVertex[820];
XMVECTOR objBoundingBoxMaxVertex[820];
GameTimer g_PickingTimer;
//

///throwing object
//
XMMATRIX throwingObjWorld;
XMVECTOR throwingObjBoundingBoxMinVertex;
XMVECTOR throwingObjBoundingBoxMaxVertex;
XMVECTOR throwingObjDir;
bool objFlying;

///terrain variables
//
int g_terrainFaces = 0;
int g_terrainVertices = 0;
s_HeightMapInfo g_terrain;

ID3D11Buffer*				g_terrainVB = NULL;
ID3D11Buffer*				g_terrainIB = NULL;
ID3D11VertexShader*			g_terrainVS = NULL;
ID3D10Blob*					g_terrainVSB = NULL;
ID3D11InputLayout*			g_terrainInputLayout = NULL;
ID3D11ShaderResourceView*	g_terrainTexture = NULL;
ID3D11ShaderResourceView*	g_terrainNormalmap = NULL;
XMMATRIX					g_terrainWorld = XMMatrixIdentity();
//

/// debugging lines variables
//
ID3D11Buffer*				g_debugTerrainVB = NULL;
ID3D11Buffer*				g_debugTerrainIB = NULL;
//


///Tessellation variables
//
ID3D11HullShader*			g_HS = NULL;
ID3D11DomainShader*			g_DS = NULL;
ID3D10Blob*					g_HSBuffer = NULL;
ID3D10Blob*					g_DSBuffer = NULL;
//



///Skybox variables
//
ID3D11Buffer*				g_skyBoxVB = NULL;
ID3D11Buffer*				g_skyBoxIB = NULL;
ID3D10Blob*					g_skyBoxVSBuffer = NULL;
ID3D10Blob*					g_skyBoxPSBuffer = NULL;

ID3D11VertexShader*			g_skyBoxVS = NULL;
ID3D11PixelShader*			g_skyBoxPS = NULL;
ID3D11ShaderResourceView*	g_skyBoxShaderResourceView = NULL;
ID3D11DepthStencilState*	g_skyBoxDepthStencilState = NULL;
ID3D11SamplerState*			g_skyBoxSampler = NULL;

s_MeshData g_skyBoxMesh;
XMMATRIX skyBoxWorld = XMMatrixIdentity();
//

///camera variables
//
float g_aspectRatio;

XMMATRIX WVP;
XMMATRIX cube1World = XMMatrixIdentity();
XMMATRIX cube2World = XMMatrixIdentity();
XMMATRIX camView;
XMMATRIX camProjection;

XMVECTOR camPosition;
XMVECTOR camTarget;
XMVECTOR camUp;

XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
XMVECTOR camUpward = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

XMMATRIX camRotation;

float camMoveRL = 0.0f;
float camMoveBF = 0.0f;
float camMoveUD = 0.0f;

float camYaw = 0.0f;
float camPitch = 0.0f;

s_ConstantBuffer constantBuffer;
//

///Light setting
//
s_Light Light;
s_Light Dir_Light;
s_Light Con_Light1;
s_Light Con_Light2;
s_Light Con_Light3;
ID3D11Buffer*				g_lightConstantBuffer = NULL;
s_LightConstantBuffer lightConstantBuffer;
//


///Shadow mapping
//
ID3D11SamplerState*			g_samplerClamp = NULL;
ID3D11ShaderResourceView*	g_depthMapTexture = NULL;
ID3D11VertexShader*			g_shadowVS = NULL;
ID3D11PixelShader*			g_shadowPS = NULL;
ID3D10Blob*					g_shadowVSB = NULL;
ID3D10Blob*					g_shadowPSB = NULL;
ID3D11InputLayout*			g_shadowInputLayout = NULL;
//

///Render to Texture
//
int textureWidth = 1024;
int textureHeight = 1024;
ID3D11Texture2D*			g_renderTargetTextureMap = NULL;
ID3D11RenderTargetView*		g_shadowRTV = NULL;
ID3D11ShaderResourceView*	g_shadewResourceViewMap = NULL;
ID3D11DepthStencilView*		g_shadowDepthStencilView = NULL;
ID3D10Blob*					g_renderToTexturePSB = NULL;
ID3D11Buffer*				d2dVertBuffer;
ID3D11Buffer*				d2dIndexBuffer;
ID3D11PixelShader*			D2D_PS;
//


///Transformation variables
//
XMMATRIX scale;
XMMATRIX translation;
XMMATRIX rotation;
float rotating = 0.01f;
//

GameTimer g_Timer;
bool g_appPaused = false;

HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow);
HRESULT InitDevice();
HRESULT InitScene();
HRESULT InitDirectInput(HINSTANCE hInstance);
void CleanUpDevice();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DetectInput(double deltaTime);
void CalculateFrameStates();
void UpdateScene(float deltaTime);
void UpdateCamera();
void Render();
void RenderShadowToTexture();

HRESULT RenderToTextureInitialize();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	if (FAILED(InitWindow(hInstance, nCmdShow)))
	{
		MessageBox(0, L"InitWindow- Failed", L"Error", MB_OK);
		return 0;
	}

	if (FAILED(InitDevice()))
	{
		CleanUpDevice();
		MessageBox(0, L"InitDevice- Failed", L"Error", MB_OK);
		return 0;
	}

	if (FAILED(InitScene()))
	{
		MessageBox(0, L"InitScene- Failed", L"Error", MB_OK);
		return 0;
	}

	if (FAILED(InitDirectInput(hInstance)))
	{
		MessageBox(0, L"InitDirectInput- Failed", L"Error", MB_OK);
		return 0;
	}


	MSG msg = { 0 };
	g_Timer.Reset();
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_Timer.Tick();
			if (!g_appPaused)
			{
				CalculateFrameStates();
				DetectInput(g_Timer.DeltaTime());
				UpdateScene(g_Timer.DeltaTime());

				Render();
			}
			else
			{
				Sleep(100);
			}
		}
	}

	CleanUpDevice();

	return (int)msg.wParam;
}

//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	g_wndName = L"PracticeProject";

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.lpszClassName = L"PracticeDirectX11";
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	g_hInst = hInstance;
	RECT rc = { 0, 0,  GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"PracticeDirectX11", g_wndName.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL,
		hInstance, NULL);

	if (!g_hWnd)
	{
		return E_FAIL;
	}

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}

HRESULT InitDevice()
{
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif // defined(DEBUG) || defined(_DEBUG)

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;


	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;


	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, g_driveType, NULL, createDeviceFlags, NULL, NULL, D3D11_SDK_VERSION, &sd, &g_swapChain, &g_device, &g_featureLevel, &g_context);
	if (FAILED(hr))	return hr;

	UINT m4xMsaaQuality;

	hr = g_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
	if (FAILED(hr))	return hr;

	ID3D11Texture2D* pBackBuffer = NULL;
	hr = g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))	return hr;

	hr = g_device->CreateRenderTargetView(pBackBuffer, NULL, &g_renderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))	return hr;

	D3D11_TEXTURE2D_DESC depthBufferDec;
	ZeroMemory(&depthBufferDec, sizeof(D3D11_TEXTURE2D_DESC));
	depthBufferDec.Height = height;
	depthBufferDec.Width = width;
	depthBufferDec.MipLevels = 1;
	depthBufferDec.ArraySize = 1;
	depthBufferDec.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDec.SampleDesc.Count = 1;
	depthBufferDec.SampleDesc.Quality = m4xMsaaQuality - 1;
	depthBufferDec.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDec.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDec.CPUAccessFlags = 0;
	depthBufferDec.MiscFlags = 0;

	ID3D11Texture2D *mDepthStencilBuffer = NULL;
	hr = g_device->CreateTexture2D(&depthBufferDec, NULL, &mDepthStencilBuffer);
	if (FAILED(hr))	return hr;

	hr = g_device->CreateDepthStencilView(mDepthStencilBuffer, 0, &g_DepthStencilView);
	if (FAILED(hr))	return hr;

	mDepthStencilBuffer->Release();

	//OUT MERGE STAGE
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	return S_OK;
}

HRESULT InitScene()
{

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	//UINT screenWidth =  rc.right - rc.left;
	//UINT screenHeight =  rc.bottom - rc.top;

	DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "VS", "vs_5_0", shaderFlags, 0, 0, &g_vertSBuffer, 0, 0);
	if (FAILED(hr)) return hr;

	hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "PS", "ps_5_0", shaderFlags, 0, 0, &g_pixelSBuffer, 0, 0);
	if (FAILED(hr))	return hr;

	g_device->CreateVertexShader(g_vertSBuffer->GetBufferPointer(), g_vertSBuffer->GetBufferSize(), NULL, &g_vertexShader);
	g_device->CreatePixelShader(g_pixelSBuffer->GetBufferPointer(), g_pixelSBuffer->GetBufferSize(), NULL, &g_pixelShader);

	//create skybox shaders 
	hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "SkyBoxMap_VS", "vs_5_0", shaderFlags, 0, 0, &g_skyBoxVSBuffer, 0, 0);
	if (FAILED(hr)) return hr;
	hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "SkyBoxMap_PS", "ps_5_0", shaderFlags, 0, 0, &g_skyBoxPSBuffer, 0, 0);
	if (FAILED(hr))	return hr;

	g_device->CreateVertexShader(g_skyBoxVSBuffer->GetBufferPointer(), g_skyBoxVSBuffer->GetBufferSize(), NULL, &g_skyBoxVS);
	g_device->CreatePixelShader(g_skyBoxPSBuffer->GetBufferPointer(), g_skyBoxPSBuffer->GetBufferSize(), NULL, &g_skyBoxPS);


	//create shadow shaders
	hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "DepthVS", "vs_5_0", shaderFlags, 0, 0, &g_shadowVSB, 0, 0);
	if (FAILED(hr)) return hr;

	hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "DepthPS", "ps_5_0", shaderFlags, 0, 0, &g_shadowPSB, 0, 0);
	if (FAILED(hr))	return hr;

	g_device->CreateVertexShader(g_shadowVSB->GetBufferPointer(), g_shadowVSB->GetBufferSize(), NULL, &g_shadowVS);
	g_device->CreatePixelShader(g_shadowPSB->GetBufferPointer(), g_shadowPSB->GetBufferSize(), NULL, &g_shadowPS);

	//create render to texture pixel shader

	hr = D3DX11CompileFromFile(L"Shader.fx", 0, 0, "D2D_PS", "ps_5_0", shaderFlags, 0, 0, &g_renderToTexturePSB, 0, 0);
	if (FAILED(hr))	return hr;
	g_device->CreatePixelShader(g_renderToTexturePSB->GetBufferPointer(), g_renderToTexturePSB->GetBufferSize(), NULL, &D2D_PS);



	//create terrain shaders
	hr = D3DX11CompileFromFile(L"TerrainShader.fx", 0, 0, "VS", "vs_5_0", shaderFlags, 0, 0, &g_terrainVSB, 0, 0);
	if (FAILED(hr))	return hr;
	hr = D3DX11CompileFromFile(L"TerrainShader.fx", 0, 0, "HS", "hs_5_0", shaderFlags, 0, 0, &g_HSBuffer, 0, 0);
	if (FAILED(hr))	return hr;
	hr = D3DX11CompileFromFile(L"TerrainShader.fx", 0, 0, "DS", "ds_5_0", shaderFlags, 0, 0, &g_DSBuffer, 0, 0);
	if (FAILED(hr))	return hr;

	g_device->CreateVertexShader(g_terrainVSB->GetBufferPointer(), g_terrainVSB->GetBufferSize(), NULL, &g_terrainVS);
	g_device->CreateHullShader(g_HSBuffer->GetBufferPointer(), g_HSBuffer->GetBufferSize(), NULL, &g_HS);
	g_device->CreateDomainShader(g_DSBuffer->GetBufferPointer(), g_DSBuffer->GetBufferSize(), NULL, &g_DS);


	//create PN-Triangle shaders
	hr = D3DX11CompileFromFile(L"PhongTessel.fx", 0, 0, "VS", "vs_5_0", shaderFlags, 0, 0, &g_dogPNTVSB, 0, 0);
	if (FAILED(hr))	return hr;
	hr = D3DX11CompileFromFile(L"PhongTessel.fx", 0, 0, "HS", "hs_5_0", shaderFlags, 0, 0, &g_dogPNTHSBuffer, 0, 0);
	if (FAILED(hr))	return hr;
	hr = D3DX11CompileFromFile(L"PhongTessel.fx", 0, 0, "DS", "ds_5_0", shaderFlags, 0, 0, &g_dogPNTDSBuffer, 0, 0);
	if (FAILED(hr))	return hr;

	g_device->CreateVertexShader(g_dogPNTVSB->GetBufferPointer(), g_dogPNTVSB->GetBufferSize(), NULL, &g_dogPNTVS);
	g_device->CreateHullShader(g_dogPNTHSBuffer->GetBufferPointer(), g_dogPNTHSBuffer->GetBufferSize(), NULL, &g_dogPNTHS);
	g_device->CreateDomainShader(g_dogPNTDSBuffer->GetBufferPointer(), g_dogPNTDSBuffer->GetBufferSize(), NULL, &g_dogPNTDS);

	///create the vertex buffer
	//
	s_Vertex vertices[] =
	{
		//front
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f,  0.0f, -1.0f) },
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f,  0.0f, -1.0f) },
		{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f,  0.0f, -1.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f,  0.0f, -1.0f) },

		//back
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f,  0.0f,  1.0f) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f,  0.0f,  1.0f) },
		{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f,  0.0f,  1.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f,  0.0f,  1.0f) },

		//top												    
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f,  1.0f,  0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f,  1.0f,  0.0f) },
		{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f,  1.0f,  0.0f) },
		{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f,  1.0f,  0.0f) },

		//bottom
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f,  0.0f) },
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(0.0f, -1.0f,  0.0f) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(0.0f, -1.0f,  0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(0.0f, -1.0f,  0.0f) },

		//left
		{ XMFLOAT3(-0.5f, -0.5f,  0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(-1.0f,  0.0f,  0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f,  0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(-1.0f,  0.0f,  0.0f) },
		{ XMFLOAT3(-0.5f,  0.5f, -0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(-1.0f,  0.0f,  0.0f) },
		{ XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(-1.0f,  0.0f,  0.0f) },

		//right
		{ XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT2(0.0f, 1.0f), XMFLOAT3(1.0f,  0.0f,  0.0f) },
		{ XMFLOAT3(0.5f,  0.5f, -0.5f), XMFLOAT2(0.0f, 0.0f), XMFLOAT3(1.0f,  0.0f,  0.0f) },
		{ XMFLOAT3(0.5f,  0.5f,  0.5f), XMFLOAT2(1.0f, 0.0f), XMFLOAT3(1.0f,  0.0f,  0.0f) },
		{ XMFLOAT3(0.5f, -0.5f,  0.5f), XMFLOAT2(1.0f, 1.0f), XMFLOAT3(1.0f,  0.0f,  0.0f) },
	};

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(D3D11_BUFFER_DESC));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.ByteWidth = sizeof(vertices);
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = 0;
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(D3D11_SUBRESOURCE_DATA));

	vertexData.pSysMem = vertices;

	hr = g_device->CreateBuffer(&vertexDesc, &vertexData, &g_squareVertexBuffer);
	if (FAILED(hr))	return hr;
	//



	///create the index buffer
	//
	DWORD indices[] =
	{
		// Front Face
		0,  1,  2,
		0,  2,  3,

		// Back Face
		4,  5,  6,
		4,  6,  7,

		// Top Face
		8,  9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(indices);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indicesData;
	ZeroMemory(&indicesData, sizeof(D3D11_SUBRESOURCE_DATA));
	indicesData.pSysMem = indices;

	hr = g_device->CreateBuffer(&indexBufferDesc, &indicesData, &g_squareIndexBuffer);
	if (FAILED(hr))	return hr;
	//

	///LoadMesh
	// spaceCompound
	hr = LoadOBJModel(L"spaceCompound.obj", &spaceRoom.VB, &spaceRoom.IB, &g_device, spaceRoom.SubsetsIndexStart,
		spaceRoom.SubsetsTexture, spaceRoom.Material, spaceRoom.TextureNameArray,
		spaceRoom.SRV, spaceRoom.Subsets, true, true, spaceRoom.VertPosArray, spaceRoom.VertIndexArray);
	if (FAILED(hr)) return hr;
	//ground Grass
	hr = LoadOBJModel(L"ground.obj", &grassGround.VB, &grassGround.IB, &g_device, grassGround.SubsetsIndexStart,
		grassGround.SubsetsTexture, grassGround.Material, grassGround.TextureNameArray,
		grassGround.SRV, grassGround.Subsets, true, true, grassGround.VertPosArray, grassGround.VertIndexArray);
	if (FAILED(hr)) return hr;

	//male head
	hr = LoadOBJModel(L"GermanShephardLowPoly.obj", &dogPNTModel.VB, &dogPNTModel.IB, &g_device, dogPNTModel.SubsetsIndexStart,
		dogPNTModel.SubsetsTexture, dogPNTModel.Material, dogPNTModel.TextureNameArray,
		dogPNTModel.SRV, dogPNTModel.Subsets, true, true, dogPNTModel.VertPosArray, dogPNTModel.VertIndexArray);
	if (FAILED(hr)) return hr;



	//picking bottles
	hr = LoadOBJModel(L"bottle.obj", &pickingObject.VB, &pickingObject.IB, &g_device, pickingObject.SubsetsIndexStart,
		pickingObject.SubsetsTexture, pickingObject.Material, pickingObject.TextureNameArray,
		pickingObject.SRV, pickingObject.Subsets, true, true, pickingObject.VertPosArray, pickingObject.VertIndexArray);
	if (FAILED(hr)) return hr;

	CreateBoundingVolumes(pickingObject.VertPosArray, objBoundingBoxVertPosArray, objBoundingBoxVertIndexArray, objBoundingSphere, objCenterOffset);

	//

	///pickObject(bottle) setting
	//
	float objectXPos = -25.0f;
	float objectZPos = 50.0f;
	int objRows = 40;
	int counter = 0;

	for (int j = 0; j < objRows; j++)
	{
		for (int k = 0; k < objRows - j; k++)
		{
			pickingObjectHit[counter] = 0;

			// set the loaded bottles world space
			pickingObjectWorld[counter] = XMMatrixIdentity();

			translation = XMMatrixTranslation(objectXPos + k + j*0.5f, j*2.25 + 1, objectZPos);

			pickingObjectWorld[counter] = translation;

			//Update the objects AABB every time the object is transformed
			CalculateAABB(objBoundingBoxVertPosArray, pickingObjectWorld[counter], objBoundingBoxMinVertex[counter], objBoundingBoxMaxVertex[counter]);

			counter++;
		}
	}

	//

	///create the vertex of the grid for terrain
	//

	HeightMapLoading("heightmap.bmp", g_terrain);

	int cols = g_terrain.TerrainWidth;
	int rows = g_terrain.TerrainHeight;

	//create the grid
	g_terrainVertices = rows * cols;
	g_terrainFaces = (rows - 1) * (cols - 1) * 6;

	std::vector<s_Vertex> terrainVerts(g_terrainVertices);

	if (!CalculateNormal(g_terrain))
	{
		return S_FALSE;
	}


	//create the index list and setting the texture coordinates
	std::vector<DWORD> terrainIndices(g_terrainFaces * 3);
	int k = 0;
	int texUIndex = 0;
	int texVIndex = 0;

	for (DWORD i = 0; i < rows - 1; i++)
	{
		for (DWORD j = 0; j < cols - 1; j++)
		{
			terrainIndices[k] = i* cols + j; //bottom left of quad
			terrainVerts[i*cols + j].Pos = g_terrain.HieghtMap[i*cols + j];
			terrainVerts[i*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 0.0f);
			terrainVerts[i*cols + j].Normal = g_terrain.HieghtMapNormal[i*cols + j];

			terrainIndices[k + 1] = i* cols + j + 1; //bottom right of quad
			terrainVerts[i*cols + j + 1].Pos = g_terrain.HieghtMap[i*cols + j + 1];
			terrainVerts[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 0.0f);
			terrainVerts[i*cols + j + 1].Normal = g_terrain.HieghtMapNormal[i*cols + j + 1];

			terrainIndices[k + 2] = (i + 1)* cols + j; //top left of quad
			terrainVerts[(i + 1)*cols + j].Pos = g_terrain.HieghtMap[(i + 1)*cols + j];
			terrainVerts[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 1.0f);
			terrainVerts[(i + 1)*cols + j].Normal = g_terrain.HieghtMapNormal[(i + 1)*cols + j];

			terrainIndices[k + 3] = (i + 1)* cols + j; //top left of quad
			terrainVerts[(i + 1)*cols + j].Pos = g_terrain.HieghtMap[(i + 1)*cols + j];
			terrainVerts[(i + 1)*cols + j].texCoord = XMFLOAT2(texUIndex + 0.0f, texVIndex + 1.0f);
			terrainVerts[(i + 1)*cols + j].Normal = g_terrain.HieghtMapNormal[(i + 1)*cols + j];

			terrainIndices[k + 4] = i* cols + j + 1; //bottom right of quad
			terrainVerts[i*cols + j + 1].Pos = g_terrain.HieghtMap[i*cols + j + 1];
			terrainVerts[i*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 0.0f);
			terrainVerts[i*cols + j + 1].Normal = g_terrain.HieghtMapNormal[i*cols + j + 1];

			terrainIndices[k + 5] = (i + 1)* cols + j + 1; //top right of quad
			terrainVerts[(i + 1)*cols + j + 1].Pos = g_terrain.HieghtMap[(i + 1)*cols + j + 1];
			terrainVerts[(i + 1)*cols + j + 1].texCoord = XMFLOAT2(texUIndex + 1.0f, texVIndex + 1.0f);
			terrainVerts[(i + 1)*cols + j + 1].Normal = g_terrain.HieghtMapNormal[(i + 1)*cols + j + 1];

			k += 6;
			texUIndex++;
		}

		texUIndex = 0;
		texVIndex++;
	}




	D3D11_BUFFER_DESC terrainVBDesc;
	ZeroMemory(&terrainVBDesc, sizeof(terrainVBDesc));
	terrainVBDesc.Usage = D3D11_USAGE_DEFAULT;
	terrainVBDesc.ByteWidth = sizeof(s_Vertex) * g_terrainVertices;
	terrainVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	terrainVBDesc.CPUAccessFlags = 0;
	terrainVBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA terrainVBData;
	ZeroMemory(&terrainVBData, sizeof(terrainVBData));
	terrainVBData.pSysMem = &terrainVerts[0];
	hr = g_device->CreateBuffer(&terrainVBDesc, &terrainVBData, &g_terrainVB);
	if (FAILED(hr))	return hr;

	D3D11_BUFFER_DESC terrainIBDesc;
	ZeroMemory(&terrainIBDesc, sizeof(terrainIBDesc));
	terrainIBDesc.Usage = D3D11_USAGE_DEFAULT;
	terrainIBDesc.ByteWidth = sizeof(DWORD) * g_terrainFaces * 3;
	terrainIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	terrainIBDesc.CPUAccessFlags = 0;
	terrainIBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA terrainIBData;
	ZeroMemory(&terrainIBData, sizeof(terrainIBData));
	terrainIBData.pSysMem = &terrainIndices[0];
	hr = g_device->CreateBuffer(&terrainIBDesc, &terrainIBData, &g_terrainIB);
	if (FAILED(hr))	return hr;

	//loading the terrain normal map
	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"terrainNormalMap.png", NULL, NULL, &g_terrainNormalmap, NULL);
	if (FAILED(hr))	return hr;
	//


	///render to texture  vertex buffer
	//Create the vertex buffer
	s_Vertex RTTvertices[] =
	{
		//front
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT2(0.0f, 1.0), XMFLOAT3(-1.0f, -1.0f, -1.0f) },
		{ XMFLOAT3(-1.0f,  1.0f, -1.0f), XMFLOAT2(0.0f, 0.0), XMFLOAT3(-1.0f,  1.0f, -1.0f) },
		{ XMFLOAT3(1.0f,  1.0f, -1.0f),  XMFLOAT2(1.0f, 0.0), XMFLOAT3(1.0f,  1.0f, -1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f),  XMFLOAT2(1.0f, 1.0), XMFLOAT3(1.0f, -1.0f, -1.0f) },

	};

	DWORD RTTindices[] = {
		// Front Face
		0,  1,  2,
		0,  2,  3,
	};

	D3D11_BUFFER_DESC RTTindexBufferDesc;
	ZeroMemory(&RTTindexBufferDesc, sizeof(RTTindexBufferDesc));

	RTTindexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	RTTindexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
	RTTindexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	RTTindexBufferDesc.CPUAccessFlags = 0;
	RTTindexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = RTTindices;
	g_device->CreateBuffer(&RTTindexBufferDesc, &iinitData, &d2dIndexBuffer);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(s_Vertex) * 4;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = RTTvertices;
	hr = g_device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &d2dVertBuffer);
	//


	///setting dubegging lines
	//
	std::vector<s_Vertex> debugTerrainVerts(g_terrainVertices * 2);
	std::vector<DWORD> debugTerrainIndices(g_terrainVertices * 2);
	int index = 0;
	for (int i = 0; i < terrainVerts.size(); i++)
	{
		debugTerrainVerts[index].Pos = terrainVerts[i].Pos;
		debugTerrainVerts[index + 1].Pos.x = terrainVerts[i].Pos.x + terrainVerts[i].Normal.x;
		debugTerrainVerts[index + 1].Pos.y = terrainVerts[i].Pos.y + terrainVerts[i].Normal.y;
		debugTerrainVerts[index + 1].Pos.z = terrainVerts[i].Pos.z + terrainVerts[i].Normal.z;
		debugTerrainIndices[index] = index;
		debugTerrainIndices[index + 1] = index + 1;
		index += 2;
	}





	D3D11_BUFFER_DESC DebugTerrainVBDesc;
	ZeroMemory(&DebugTerrainVBDesc, sizeof(DebugTerrainVBDesc));
	DebugTerrainVBDesc.Usage = D3D11_USAGE_DEFAULT;
	DebugTerrainVBDesc.ByteWidth = sizeof(s_Vertex) * debugTerrainVerts.size();
	DebugTerrainVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	DebugTerrainVBDesc.CPUAccessFlags = 0;
	DebugTerrainVBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA DebugTerrainVBData;
	ZeroMemory(&DebugTerrainVBData, sizeof(DebugTerrainVBData));
	DebugTerrainVBData.pSysMem = &debugTerrainVerts[0];
	hr = g_device->CreateBuffer(&DebugTerrainVBDesc, &DebugTerrainVBData, &g_debugTerrainVB);
	if (FAILED(hr))	return hr;


	D3D11_BUFFER_DESC DebugTerrainIBDesc;
	ZeroMemory(&DebugTerrainIBDesc, sizeof(DebugTerrainIBDesc));
	DebugTerrainIBDesc.Usage = D3D11_USAGE_DEFAULT;
	DebugTerrainIBDesc.ByteWidth = sizeof(DWORD) * debugTerrainIndices.size();
	DebugTerrainIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	DebugTerrainIBDesc.CPUAccessFlags = 0;
	DebugTerrainIBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA DebugTerrainIBData;
	ZeroMemory(&DebugTerrainIBData, sizeof(DebugTerrainIBData));
	DebugTerrainIBData.pSysMem = &debugTerrainIndices[0];
	hr = g_device->CreateBuffer(&DebugTerrainIBDesc, &DebugTerrainIBData, &g_debugTerrainIB);
	if (FAILED(hr))	return hr;

	//

	///create SkyBox vertex and index buffer
	//
	CreateSphere(30, 0, g_skyBoxMesh);

	D3D11_BUFFER_DESC skyBoxVBDesc;
	ZeroMemory(&skyBoxVBDesc, sizeof(skyBoxVBDesc));
	skyBoxVBDesc.Usage = D3D11_USAGE_DEFAULT;
	skyBoxVBDesc.ByteWidth = sizeof(s_Vertex)*g_skyBoxMesh.Vertices.size();
	skyBoxVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	skyBoxVBDesc.CPUAccessFlags = 0;
	skyBoxVBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA skyBoxVBData;
	ZeroMemory(&skyBoxVBData, sizeof(skyBoxVBData));
	skyBoxVBData.pSysMem = &g_skyBoxMesh.Vertices[0];

	g_device->CreateBuffer(&skyBoxVBDesc, &skyBoxVBData, &g_skyBoxVB);

	D3D11_BUFFER_DESC skyBoxIBDesc;
	ZeroMemory(&skyBoxIBDesc, sizeof(skyBoxIBDesc));
	skyBoxIBDesc.Usage = D3D11_USAGE_DEFAULT;
	skyBoxIBDesc.ByteWidth = sizeof(UINT) * g_skyBoxMesh.Indices.size();
	skyBoxIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	skyBoxIBDesc.CPUAccessFlags = 0;
	skyBoxIBDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA skyBoxIBData;
	ZeroMemory(&skyBoxIBData, sizeof(skyBoxIBData));
	skyBoxIBData.pSysMem = &g_skyBoxMesh.Indices[0];

	hr = g_device->CreateBuffer(&skyBoxIBDesc, &skyBoxIBData, &g_skyBoxIB);
	if (FAILED(hr))	return hr;

	D3D11_DEPTH_STENCIL_DESC skyBoxDepthStencilDesc;
	ZeroMemory(&skyBoxDepthStencilDesc, sizeof(skyBoxDepthStencilDesc));
	skyBoxDepthStencilDesc.DepthEnable = true;
	skyBoxDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	skyBoxDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	hr = g_device->CreateDepthStencilState(&skyBoxDepthStencilDesc, &g_skyBoxDepthStencilState);
	if (FAILED(hr))	return hr;

	//

	///Load the CubeMap
	//
	D3DX11_IMAGE_LOAD_INFO skyBoxLoadInfo;
	skyBoxLoadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	ID3D11Texture2D* skyBoxText = 0;
	hr = D3DX11CreateTextureFromFile(g_device, L"SkyBox.dds", &skyBoxLoadInfo, 0, (ID3D11Resource**)&skyBoxText, 0);
	if (FAILED(hr))	return hr;

	D3D11_TEXTURE2D_DESC skyBoxTextDesc;
	skyBoxText->GetDesc(&skyBoxTextDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC skyBoxShaderResourceViewDesc;
	skyBoxShaderResourceViewDesc.Format = skyBoxTextDesc.Format;
	skyBoxShaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	skyBoxShaderResourceViewDesc.TextureCube.MipLevels = skyBoxTextDesc.MipLevels;
	skyBoxShaderResourceViewDesc.TextureCube.MostDetailedMip = 0;

	hr = g_device->CreateShaderResourceView(skyBoxText, &skyBoxShaderResourceViewDesc, &g_skyBoxShaderResourceView);
	if (FAILED(hr))	return hr;
	//

	///Create constantbuffer
	//
	D3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = 208;// sizeof(s_ConstantBuffer);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;

	hr = g_device->CreateBuffer(&constantBufferDesc, NULL, &g_constantBuffer);
	if (FAILED(hr))	return hr;
	//

	///create the light constantbuffer
	//
	D3D11_BUFFER_DESC lightConstantBufferDesc;
	ZeroMemory(&lightConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	lightConstantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	lightConstantBufferDesc.ByteWidth = sizeof(s_LightConstantBuffer);
	lightConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightConstantBufferDesc.CPUAccessFlags = 0;
	lightConstantBufferDesc.MiscFlags = 0;

	hr = g_device->CreateBuffer(&lightConstantBufferDesc, NULL, &g_lightConstantBuffer);
	if (FAILED(hr))	return hr;
	//

	///create the ShaderResourceViewFromFile
	//
	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"Box.png", NULL, NULL, &g_cubeTexture, NULL);
	if (FAILED(hr))	return hr;

	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"RockGround.dds", NULL, NULL, &g_terrainTexture, NULL);
	if (FAILED(hr))	return hr;
	//

	///create the samplerstate
	//
	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MipLODBias = 0.0f;
	SamplerDesc.MaxAnisotropy = 1;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	SamplerDesc.BorderColor[0] = 0;
	SamplerDesc.BorderColor[1] = 0;
	SamplerDesc.BorderColor[2] = 0;
	SamplerDesc.BorderColor[3] = 0;
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = g_device->CreateSamplerState(&SamplerDesc, &g_cubeSampler);
	if (FAILED(hr))	return hr;
	//

	///create the shadow mapping clamp based sampler
	//
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

	hr = g_device->CreateSamplerState(&SamplerDesc, &g_samplerClamp);
	if (FAILED(hr))	return hr;
	//

	// Render to texture Initialize
	RenderToTextureInitialize();

	//Initialize the description of the stencil state.
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	hr = g_device->CreateDepthStencilState(&depthStencilDesc, &g_depthStencilState);
	if (FAILED(hr))	return hr;

	//

	///create the BlendState
	//
	D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc;
	ZeroMemory(&renderTargetBlendDesc, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));
	renderTargetBlendDesc.BlendEnable = true;
	renderTargetBlendDesc.SrcBlend = D3D11_BLEND_SRC_COLOR;
	renderTargetBlendDesc.DestBlend = D3D11_BLEND_BLEND_FACTOR;
	renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
	renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	D3D11_BLEND_DESC blendStateDec;
	ZeroMemory(&blendStateDec, sizeof(D3D11_BLEND_DESC));
	blendStateDec.AlphaToCoverageEnable = false;
	blendStateDec.RenderTarget[0] = renderTargetBlendDesc;

	g_device->CreateBlendState(&blendStateDec, &g_transparency);
	//

	///the space room window transparency setting
	//
	ZeroMemory(&renderTargetBlendDesc, sizeof(renderTargetBlendDesc));
	renderTargetBlendDesc.BlendEnable = true;
	renderTargetBlendDesc.SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
	renderTargetBlendDesc.DestBlend = D3D11_BLEND_SRC_ALPHA;
	renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
	renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	blendStateDec.AlphaToCoverageEnable = false;
	blendStateDec.RenderTarget[0] = renderTargetBlendDesc;

	g_device->CreateBlendState(&blendStateDec, &spaceRoom.Transparency);
	//


	///create Rasterizer
	//
	D3D11_RASTERIZER_DESC cullingModeDecs;
	ZeroMemory(&cullingModeDecs, sizeof(D3D11_RASTERIZER_DESC));
	cullingModeDecs.FillMode = D3D11_FILL_SOLID;
	cullingModeDecs.CullMode = D3D11_CULL_BACK;
	cullingModeDecs.FrontCounterClockwise = true;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_CCWcullMode);
	if (FAILED(hr))	return hr;

	cullingModeDecs.FrontCounterClockwise = false;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_CWcullMode);
	if (FAILED(hr))	return hr;

	cullingModeDecs.CullMode = D3D11_CULL_NONE;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_RSCullNone);
	cullingModeDecs.FillMode = D3D11_FILL_WIREFRAME;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_RSCullNoneFW);

	if (FAILED(hr))	return hr;
	//

	/// create INPUTLAYOUTS
	D3D11_INPUT_ELEMENT_DESC VertexLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	g_device->CreateInputLayout(VertexLayout, ARRAYSIZE(VertexLayout), g_vertSBuffer->GetBufferPointer(), g_vertSBuffer->GetBufferSize(), &g_inputLayout);
	g_device->CreateInputLayout(VertexLayout, ARRAYSIZE(VertexLayout), g_shadowVSB->GetBufferPointer(), g_shadowVSB->GetBufferSize(), &g_shadowInputLayout);
	g_device->CreateInputLayout(VertexLayout, ARRAYSIZE(VertexLayout), g_terrainVSB->GetBufferPointer(), g_terrainVSB->GetBufferSize(), &g_terrainInputLayout);

	g_device->CreateInputLayout(VertexLayout, ARRAYSIZE(VertexLayout), g_dogPNTVSB->GetBufferPointer(), g_dogPNTVSB->GetBufferSize(), &g_dogPNTInputLayout);

	//

	///set the inputoutlay
	//
	g_context->IASetInputLayout(g_inputLayout);
	//

	///set the Primitve Topology
	//
	g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//

	///seting the camera data
	//
	camPosition = XMVectorSet(0.0f, 2.0f, -8.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	g_aspectRatio = (float)screenWidth / (float)screenHeight;

	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	camProjection = XMMatrixPerspectiveFovLH(0.25f*XM_PI, g_aspectRatio, 1.0f, 1000.0f);
	//

	///setting the Light value
	//
	float range = 20;
	float cone = 36;

	
	//point light
	Light.Dir = XMFLOAT3(1.1f, 2.2f, 3.3f);
	Light.Cone = 8;
	Light.Pos = XMFLOAT3(0.0f, 4.0f, 15.0f);
	Light.Range = 7;
	Light.Attenuation = XMFLOAT3(1.0f, 0.1f, 0.0f);
	Light.pad = 99;
	Light.Ambient = XMFLOAT4(1.f, 1.f, 1.f, 1.0f);
	Light.Diffuse = XMFLOAT4(1.0f, 0.0f, 0.7f, 1.0f);
	
	//direct light
	Dir_Light.Dir = XMFLOAT3(-0.5f, -1.0f, -0.5f);
	Dir_Light.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	//Dir_Light.Diffuse = XMFLOAT4(209.f / 255, 135.f / 255, 0.0f, 1.0f);
	Dir_Light.Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	//cone light 1
	Con_Light1.Dir = XMFLOAT3(0.0f, -1.0f, 0.0f);
	Con_Light1.Pos = XMFLOAT3(0.0f, 8.0f, 0.0f);
	Con_Light1.Range = range;
	Con_Light1.Cone = cone;
	Con_Light1.Attenuation = XMFLOAT3(1.0f, 0.0f, 0.0f);
	Con_Light1.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	Con_Light1.Diffuse = XMFLOAT4(1.0f, .1f, .3f, 1.0f);

	//cone light 2
	Con_Light2.Dir = XMFLOAT3(0.0f, -1.0f, 0.0f);
	Con_Light2.Pos = XMFLOAT3(-3.0f, 8.0f, 3.0f);
	Con_Light2.Range = range;
	Con_Light2.Cone = cone;
	Con_Light2.Attenuation = XMFLOAT3(1.0f, 0.0f, 0.0f);
	Con_Light2.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	Con_Light2.Diffuse = XMFLOAT4(0.0f, 1.0f, .0f, 1.0f);

	//cone light 3
	Con_Light3.Dir = XMFLOAT3(0.0f, -1.0f, 0.0f);
	Con_Light3.Pos = XMFLOAT3(0.0f, 8.0f, -3.0f);
	Con_Light3.Range = range;
	Con_Light3.Cone = cone;
	Con_Light3.Attenuation = XMFLOAT3(1.0f, 0.0f, 0.0f);
	Con_Light3.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	Con_Light3.Diffuse = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);

	//

	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);

	return S_OK;
}

HRESULT InitDirectInput(HINSTANCE hInstance)
{
	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_directInput, NULL);
	if (FAILED(hr))	return hr;

	hr = g_directInput->CreateDevice(GUID_SysKeyboard, &g_keyboard, NULL);
	if (FAILED(hr))	return hr;

	hr = g_directInput->CreateDevice(GUID_SysMouse, &g_mouse, NULL);
	if (FAILED(hr))	return hr;

	hr = g_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))	return hr;

	hr = g_keyboard->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))	return hr;

	hr = g_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))	return hr;

	hr = g_mouse->SetCooperativeLevel(g_hWnd, DISCL_NONEXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	if (FAILED(hr))	return hr;

	return S_OK;
}

void CleanUpDevice()
{
	if (g_context) g_context->ClearState();

	if (g_renderTargetView) g_renderTargetView->Release();
	if (g_swapChain) g_swapChain->Release();
	if (g_context) g_context->Release();
	if (g_DepthStencilView) g_DepthStencilView->Release();
	if (g_device) g_device->Release();
	if (g_squareIndexBuffer) g_squareIndexBuffer->Release();
	if (g_squareVertexBuffer) g_squareVertexBuffer->Release();
	if (g_groundVertexBuffer) g_groundVertexBuffer->Release();
	if (g_groundIndexBuffer)  g_groundIndexBuffer->Release();
	if (g_vertSBuffer) g_vertSBuffer->Release();
	if (g_vertexShader) g_vertexShader->Release();
	if (g_pixelSBuffer) g_pixelSBuffer->Release();
	if (g_pixelShader) g_pixelShader->Release();
	if (g_constantBuffer) g_constantBuffer->Release();
	if (g_CWcullMode) g_CWcullMode->Release();
	if (g_CCWcullMode) g_CCWcullMode->Release();
	if (g_cubeSampler) g_cubeSampler->Release();
	if (g_cubeTexture) g_cubeTexture->Release();
	if (g_lightConstantBuffer) g_lightConstantBuffer->Release();

	if (spaceRoom.VB) spaceRoom.VB->Release();
	if (spaceRoom.IB) spaceRoom.IB->Release();
	if (spaceRoom.Transparency) spaceRoom.Transparency->Release();

	if (grassGround.VB) grassGround.VB->Release();
	if (grassGround.IB) grassGround.IB->Release();
	if (grassGround.Transparency) grassGround.Transparency->Release();

	if (dogPNTModel.VB) dogPNTModel.VB->Release();
	if (dogPNTModel.IB) dogPNTModel.IB->Release();
	if (dogPNTModel.Transparency) dogPNTModel.Transparency->Release();
	if (g_dogPNTHS) g_dogPNTHS->Release();
	if (g_dogPNTDS) g_dogPNTDS->Release();
	if (g_dogPNTHSBuffer) g_dogPNTHSBuffer->Release();
	if (g_dogPNTDSBuffer) g_dogPNTDSBuffer->Release();


	if (pickingObject.VB) pickingObject.VB->Release();
	if (pickingObject.IB) pickingObject.IB->Release();
	if (pickingObject.Transparency) pickingObject.Transparency->Release();

	if (g_mouse) g_mouse->Unacquire();
	if (g_keyboard) g_keyboard->Unacquire();
	if (g_directInput) g_directInput->Release();

	if (g_terrainVB) g_terrainVB->Release();
	if (g_HS) g_HS->Release();
	if (g_DS) g_DS->Release();
	if (g_HSBuffer) g_HSBuffer->Release();
	if (g_DSBuffer) g_DSBuffer->Release();

	if (g_samplerClamp) g_samplerClamp->Release();
	if (g_depthMapTexture) g_depthMapTexture->Release();
	if (g_shadowVS) g_shadowVS->Release();
	if (g_shadowPS) g_shadowPS->Release();
	if (g_shadowDepthStencilView) g_shadowDepthStencilView->Release();

	if (g_shadowPSB) g_shadowPSB->Release();
	if (g_shadowVSB) g_shadowVSB->Release();
	if (g_renderToTexturePSB) g_renderToTexturePSB->Release();
}

//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	if (GetAsyncKeyState(VK_ESCAPE))
		message = WM_DESTROY;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

		//case WM_ACTIVATE:
		//	if (LOWORD(wParam) == WA_INACTIVE)
		//	{
		//		g_appPaused = true;
		//		g_Timer.Stop();
		//	}
		//	else
		//	{
		//		g_appPaused = false;
		//		g_Timer.Start();
		//	}
		//	return 0;
		//
		//case WM_SIZE:
	case WM_SIZE:
		g_clientWidth = LOWORD(lParam);
		g_clientHeight = HIWORD(lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void DetectInput(double deltaTime)
{
	DIMOUSESTATE mouseCurrState;

	BYTE keyboardState[256];
	g_keyboard->Acquire();
	g_mouse->Acquire();

	g_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);
	g_keyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);


	float speed = 25.0f * deltaTime;
	if (keyboardState[DIK_A] & 0x80)
	{
		camMoveRL -= speed;
	}
	if (keyboardState[DIK_D] & 0x80)
	{
		camMoveRL += speed;
	}
	if (keyboardState[DIK_W] & 0x80)
	{
		camMoveBF += speed;
	}
	if (keyboardState[DIK_S] & 0x80)
	{
		camMoveBF -= speed;
	}

	if (keyboardState[DIK_Z] & 0x80)
	{
		camMoveUD += speed;
	}
	if (keyboardState[DIK_X] & 0x80)
	{
		camMoveUD -= speed;
	}

	if (keyboardState[DIK_P] & 0x80)
	{
		if (!isPDown)
		{
			pickMode++;
			if (pickMode == 2)
				pickMode = 0;
			isPDown = true;
		}
	}
	if (!(keyboardState[DIK_P] & 0x80))
	{
		isPDown = false;
	}

	if (keyboardState[DIK_G] & 0x80)
	{
		if (!isGDown)
		{
			isPhongTessel = !isPhongTessel;
			
			isGDown = true;
		}
	}
	if (!(keyboardState[DIK_G] & 0x80))
	{
		isGDown = false;
	}

	if (mouseCurrState.rgbButtons[0])
	{
		if (!isShoot)
		{
			//shooting setting
			objFlying = true;

			throwingObjWorld = XMMatrixIdentity();
			translation = XMMatrixTranslation(XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition));
			throwingObjWorld = translation;
			throwingObjDir = camTarget - camPosition;


			// Picking setting
			POINT mousePos;
			GetCursorPos(&mousePos);
			ScreenToClient(g_hWnd, &mousePos);

			int mouseX = mousePos.x;
			int mouseY = mousePos.y;

			int hitIndex;
			float tempDist;
			float closestDist = FLT_MAX;


			XMVECTOR prwPos, prwDir;
			PickRayVector(mouseX, mouseY,g_clientWidth, g_clientHeight,camProjection, camView, prwPos, prwDir);
			g_PickingTimer.Reset();
			g_PickingTimer.Tick();

			for (int i = 0; i < numPinckingObject; i++)
			{
				if (pickingObjectHit[i] == 0)
				{
					tempDist = FLT_MAX;

					if (pickMode == 0)
					{
						float pickRayToPointDist = 0.0f;
						XMVECTOR objPos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
						XMVECTOR pointOnLineNearObj = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

						objPos = XMVector3TransformCoord(objPos, pickingObjectWorld[i]) + objCenterOffset;
						pointOnLineNearObj = prwPos + XMVector3Dot((objPos - prwPos), prwDir) / XMVector3Dot(prwDir, prwDir) * prwDir;

						pickRayToPointDist = XMVectorGetX(XMVector3Length(pointOnLineNearObj - objPos));

						if (pickRayToPointDist < objBoundingSphere)
						{
							tempDist = Pick(prwPos, prwDir, pickingObject.VertPosArray, pickingObject.VertIndexArray, pickingObjectWorld[i]);
						}
					}
					if (pickMode == 1)
						tempDist = Pick(prwPos, prwDir, objBoundingBoxVertPosArray, objBoundingBoxVertIndexArray, pickingObjectWorld[i]);

					if (pickMode == 2)
					tempDist = Pick(prwPos, prwDir, pickingObject.VertPosArray, pickingObject.VertIndexArray, pickingObjectWorld[i]);

					if (tempDist < closestDist)
					{
						closestDist = tempDist;
						hitIndex = i;
					}
				}
			}
			g_PickingTimer.Stop();
			pickOpSpeed = g_PickingTimer.TotalTime();

			if (closestDist < FLT_MAX)
			{
				pickingObjectHit[hitIndex] = 1;
				pickingDist = closestDist;
			}
			

			isShoot = true;
		}
	}
	if (!mouseCurrState.rgbButtons[0])
	{
		isShoot = false;
	}

	if (keyboardState[DIK_LEFT] & 0x80)
	{
		g_rotZ -= 1.0f * deltaTime;
	}
	if (keyboardState[DIK_RIGHT] & 0x80)
	{
		g_rotZ += 1.0f * deltaTime;
	}
	if (keyboardState[DIK_UP] & 0x80)
	{
		g_rotX += 1.0f * deltaTime;
	}
	if (keyboardState[DIK_DOWN] & 0x80)
	{
		g_rotX -= 1.0f * deltaTime;
	}
	if ((mouseCurrState.lX != g_mouseLastState.lX) || (mouseCurrState.lY != g_mouseLastState.lY))
	{
		camYaw += (mouseCurrState.lX * 0.001f);
		camPitch += (mouseCurrState.lY * 0.001f);
	}

	if (mouseCurrState.lZ != g_mouseLastState.lZ)
	{
		g_zoomIn += (mouseCurrState.lZ * 0.004f);
	}

	if (g_rotX > 6.28f)
	{
		g_rotX -= 6.28f;
	}
	else if (g_rotX < 0)
	{
		g_rotX = 6.28 + g_rotX;
	}
	if (g_rotZ > 6.28f)
	{
		g_rotZ -= 6.28f;
	}
	else if (g_rotZ < 0)
	{
		g_rotZ = 6.28 + g_rotZ;
	}

	g_mouseLastState = mouseCurrState;

	UpdateCamera();

}

void CalculateFrameStates()
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;

	frameCount++;

	if ((g_Timer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCount;
		float mspf = 1000.0f / fps;

		wostringstream outs;
		outs.precision(6);
		outs << g_wndName << L"    " << L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)" << L"    " << L"Picking Speed: ( " << camPosition.m128_f32[0]<< L", " << camPosition.m128_f32[1] << L", " << camPosition.m128_f32[2] << L")";
		SetWindowText(g_hWnd, outs.str().c_str());

		frameCount = 0;
		timeElapsed += 1.0f;
	}
}

void UpdateScene(float deltaTime)
{
	rotating += deltaTime;
	if (rotating > 6.26f)
	{
		rotating = 0.0f;
	}

	XMVECTOR rotXAxis = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR rotYAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR rotZAxis = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	//reset skyBoxWorld
	skyBoxWorld = XMMatrixIdentity();
	scale = XMMatrixScaling(5.0f, 5.0f, 5.0f);
	translation = XMMatrixTranslation(XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition));
	skyBoxWorld = scale * translation;

	groundWorld = XMMatrixIdentity();
	scale = XMMatrixScaling(500.0f, 10.0f, 500.0f);

	//translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	groundWorld = scale;


	cube1World = XMMatrixIdentity();
	rotation = XMMatrixRotationAxis(rotYAxis, rotating);
	g_rotationX = XMMatrixRotationAxis(rotXAxis, g_rotX);
	g_rotationZ = XMMatrixRotationAxis(rotZAxis, g_rotZ);

	translation = XMMatrixTranslation(0.0f, 1.0f, 3.0f);

	//cube1World =  rotation * g_rotationX * g_rotationZ * translation;
	cube1World = translation * rotation * g_rotationX * g_rotationZ;

	cube2World = XMMatrixIdentity();
	//rotaxis = XMVectorSet(0.3f, 0.7f, 0.0f, 0.0f);
	rotation = XMMatrixRotationAxis(rotYAxis, -rotating);

	translation = XMMatrixTranslation(0.0f, 1.0, 0.0f);
	scale = XMMatrixScaling(1, 1, 1.0f);

	//cube2World = translation * rotation *scale;
	cube2World = scale * rotation *  translation;

	//g_spaceRoom world setting
	spaceRoom.World = XMMatrixIdentity();
	rotation = XMMatrixRotationY(3.14f);
	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	translation = XMMatrixTranslation(0.0f, 0.0, 0.0f);
	spaceRoom.World = rotation * scale * translation;

	//terrain world setting
	g_terrainWorld = XMMatrixIdentity();
	scale = XMMatrixScaling(5.0f, 4.0f, 5.0f);
	translation = XMMatrixTranslation(-100.0f, -50.0f, -100.0f);

	g_terrainWorld = scale * translation;

	///update throwing obj 
	if (objFlying)
	{
		XMVECTOR tempFlyingObjPos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		tempFlyingObjPos = XMVector3TransformCoord(tempFlyingObjPos, throwingObjWorld) + (throwingObjDir *  deltaTime * 10.0f);
		throwingObjWorld = XMMatrixIdentity();
		//adjust the horizontal angle
		float theta = acosf(XMVectorGetX(XMVector3Dot(XMVector3Normalize(XMVectorSet(XMVectorGetX(throwingObjDir), 0.0f, XMVectorGetZ(throwingObjDir), 0.0f)), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f))));
		//adjust the elevation angle
		float theta2 = acosf(XMVectorGetX(XMVector3Dot(throwingObjDir, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))));
		//detecting if the thrownDirection is at the right of vector(0,0,1,0) or left; 
		float angle = acosf(XMVectorGetX(XMVector3Dot(camUp, XMVector3Cross(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), throwingObjDir))));

		if (angle > 1.57f)
		{
			theta *= -1.0f;
		}
		//float theta = acosf(XMVectorGetX(XMVector3Dot()))

		rotation = XMMatrixRotationX(theta2) * XMMatrixRotationY(theta);
		translation = XMMatrixTranslation(XMVectorGetX(tempFlyingObjPos), XMVectorGetY(tempFlyingObjPos), XMVectorGetZ(tempFlyingObjPos));
		throwingObjWorld = rotation * translation;

		CalculateAABB(objBoundingBoxVertPosArray, throwingObjWorld, throwingObjBoundingBoxMinVertex, throwingObjBoundingBoxMaxVertex);

		for (int i = 0; i < numPinckingObject; i++)
		{
			if (pickingObjectHit[i] == 0)
			{
				if (pickMode == 0)
				{
					if (BoundingSphereCollision(objBoundingSphere, objCenterOffset, throwingObjWorld, objBoundingSphere, objCenterOffset, pickingObjectWorld[i]))
					{
						pickingObjectHit[i] = 1;
						objFlying = false;
					}
				}

				if (pickMode == 1)
				{
					if (BoundingBoxCollision(throwingObjBoundingBoxMinVertex, throwingObjBoundingBoxMaxVertex, throwingObjWorld, objBoundingBoxMinVertex[i], objBoundingBoxMaxVertex[i], pickingObjectWorld[i]))
					{
						pickingObjectHit[i] = 1;
						objFlying = false;
					}
				}
			}
		}


	}

	///point Light update
	XMVECTOR lightVector = XMVectorSet(0.0f, cosf(rotating) * 15, 0.0f, 0.0f);
	lightVector = XMVector3TransformCoord(lightVector, XMMatrixIdentity());
	//Light.Pos.y = XMVectorGetY(lightVector);


	XMMATRIX lightView;
	XMVECTOR lightPos;
	XMMATRIX lightViewProjection;
	lightPos = XMVectorSet(Con_Light1.Pos.x, Con_Light1.Pos.y, Con_Light1.Pos.z, 0.0f);
	lightView = XMMatrixLookAtLH(lightPos, XMVectorSet(Con_Light1.Pos.x, Con_Light1.Pos.y -10.0f, Con_Light1.Pos.z,0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
	lightViewProjection = XMMatrixPerspectiveFovLH(XM_PI / 4.0f , 1.0f, 1.0f, 1000.0f);
	Con_Light1.lightView = lightView;
	Con_Light1.lightProj = lightViewProjection;


	Con_Light3.Pos.x = XMVectorGetX(camPosition);
	Con_Light3.Pos.y = XMVectorGetY(camPosition);
	Con_Light3.Pos.z = XMVectorGetZ(camPosition);

	Con_Light3.Dir.x = XMVectorGetX(camTarget) - Con_Light3.Pos.x;
	Con_Light3.Dir.y = XMVectorGetY(camTarget) - Con_Light3.Pos.y;
	Con_Light3.Dir.z = XMVectorGetZ(camTarget) - Con_Light3.Pos.z;


}

void UpdateCamera()
{
	///Camera Update
	//XMVECTOR CamVector = XMVector4Normalize(camTarget - camPosition);
	camPosition += g_zoomIn * camForward;
	g_zoomIn = 0.0f;

	//rotating cam
	camRotation = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = XMVector3TransformCoord(DefaultForward, camRotation);
	camTarget = XMVector3Normalize(camTarget);

	//update camforward camup camright
	XMMATRIX RotationYTamp;
	RotationYTamp = XMMatrixRotationY(camYaw);
	camRight = XMVector3TransformCoord(DefaultRight, RotationYTamp);
	camUp = XMVector3TransformCoord(camUp, RotationYTamp);
	camForward = XMVector3TransformCoord(DefaultForward, RotationYTamp);

	//moving cam
	camPosition += camMoveRL * camRight;
	camPosition += camMoveBF * camForward;
	camPosition += camMoveUD * camUpward;

	camMoveBF = 0.0f;
	camMoveRL = 0.0f;
	camMoveUD = 0.0f;

	camTarget = camPosition + camTarget;
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);
	camProjection = XMMatrixPerspectiveFovLH(0.25f*XM_PI, g_aspectRatio, 1.0f, 1000.0f);
}

void Render()
{
	//setting the light
	RenderShadowToTexture();
	lightConstantBuffer.Light[0] = Light;
	lightConstantBuffer.Light[1] = Dir_Light;
	lightConstantBuffer.Light[2] = Con_Light1;
	lightConstantBuffer.Light[3] = Con_Light2;
	lightConstantBuffer.Light[4] = Con_Light3;
	g_context->UpdateSubresource(g_lightConstantBuffer, 0, NULL, &lightConstantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(0, 1, &g_lightConstantBuffer);
	g_context->PSSetConstantBuffers(0, 1, &g_lightConstantBuffer);

	g_context->PSSetShaderResources(2, 1, &g_shadewResourceViewMap);
	g_context->PSSetSamplers(1, 1, &g_samplerClamp);
	//Clear backbuffer
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	g_context->ClearRenderTargetView(g_renderTargetView, ClearColor);
	//Refresh the Depth/Stencil view
	g_context->ClearDepthStencilView(g_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	UINT stride = sizeof(s_Vertex);
	UINT offset = 0;
	g_context->OMSetBlendState(NULL, NULL, 0xffffffff);



	///Draw terrain
	//

	g_context->IASetInputLayout(g_terrainInputLayout);
	g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);

	g_context->IASetIndexBuffer(g_terrainIB, DXGI_FORMAT_R32_UINT, 0);
	g_context->IASetVertexBuffers(0, 1, &g_terrainVB, &stride, &offset);


	g_context->VSSetShader(g_terrainVS, 0, 0);
	g_context->HSSetShader(g_HS, 0, 0);
	g_context->DSSetShader(g_DS, 0, 0);
	g_context->PSSetShader(g_pixelShader, 0, 0);

	WVP = g_terrainWorld * camView * camProjection;
	constantBuffer.WVP = XMMatrixTranspose(WVP);
	constantBuffer.World = XMMatrixTranspose(g_terrainWorld);
	constantBuffer.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
	constantBuffer.CamPos = camPosition;
	constantBuffer.HasTexture = true;
	constantBuffer.HasNormalMap = false;

	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);
	g_context->HSSetConstantBuffers(0, 1, &g_constantBuffer);
	g_context->DSSetConstantBuffers(0, 1, &g_constantBuffer);
	g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);

	g_context->PSSetShaderResources(0, 1, &g_terrainTexture);
	g_context->PSSetShaderResources(1, 1, &g_terrainNormalmap);
	g_context->PSSetSamplers(0, 1, &g_cubeSampler);
	g_context->RSSetState(g_RSCullNoneFW);

	//g_context->DrawIndexed(g_terrainFaces * 3, 0, 0);

	//



	///Draw dogPNTModel
	//
	g_context->IASetIndexBuffer(dogPNTModel.IB, DXGI_FORMAT_R32_UINT, 0);
	g_context->IASetVertexBuffers(0, 1, &dogPNTModel.VB, &stride, &offset);
	g_context->VSSetShader(g_dogPNTVS, 0, 0);
	g_context->HSSetShader(g_dogPNTHS, 0, 0);
	g_context->DSSetShader(g_dogPNTDS, 0, 0);
	g_context->PSSetShader(g_pixelShader, 0, 0);

	for (int i = 0; i < dogPNTModel.Subsets; i++)
	{
		dogPNTModel.World = XMMatrixTranslation(0.0f, 0.0f, 8.0f);
		WVP = dogPNTModel.World * camView * camProjection;
		constantBuffer.WVP = XMMatrixTranspose(WVP);
		constantBuffer.World = XMMatrixTranspose(dogPNTModel.World);
		constantBuffer.Diffuse = XMFLOAT4(0.7f, 0.7,0.7,1.0);
		constantBuffer.HasTexture = dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].HasTexture;
		constantBuffer.IsPhongTessel = isPhongTessel;
		constantBuffer.HasNormalMap = dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].HasNormalMap;

		g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
		g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);
		g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);
		if (dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].HasTexture)
			g_context->PSSetShaderResources(0, 1, &dogPNTModel.SRV[dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].TexArrayIndex]);
		if (dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].HasNormalMap)
			g_context->PSSetShaderResources(1, 1, &dogPNTModel.SRV[dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].NormalMapTexArrayIndex]);

		g_context->PSSetSamplers(0, 1, &g_cubeSampler);

		g_context->RSSetState(g_RSCullNone);
		int indexStart = dogPNTModel.SubsetsIndexStart[i];
		int indexDrawAmount = dogPNTModel.SubsetsIndexStart[i + 1] - dogPNTModel.SubsetsIndexStart[i];
		if (!dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].Transparent)
		{
			//g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
		}
	}
	//


	///set SkyBox vertex/index buffer
	//
	g_context->IASetInputLayout(g_inputLayout);
	g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_context->IASetVertexBuffers(0, 1, &g_skyBoxVB, &stride, &offset);
	g_context->IASetIndexBuffer(g_skyBoxIB, DXGI_FORMAT_R32_UINT, 0);

	g_context->VSSetShader(g_skyBoxVS, 0, 0);
	g_context->HSSetShader(NULL, 0, 0);
	g_context->DSSetShader(NULL, 0, 0);
	g_context->PSSetShader(g_skyBoxPS, 0, 0);

	WVP = skyBoxWorld * camView * camProjection;
	constantBuffer.WVP = XMMatrixTranspose(WVP);
	constantBuffer.World = XMMatrixTranspose(skyBoxWorld);
	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(0, 1, &g_constantBuffer);

	g_context->PSSetShaderResources(3, 1, &g_skyBoxShaderResourceView);
	g_context->PSSetSamplers(0, 1, &g_skyBoxSampler);

	//set new depth/stencil state
	g_context->OMSetDepthStencilState(g_skyBoxDepthStencilState, 0);
	//set the RS state
	g_context->RSSetState(g_RSCullNone);

	g_context->DrawIndexed(g_skyBoxMesh.Indices.size(), 0, 0);


	//set the default depth/stencil state
	g_context->OMSetDepthStencilState(g_depthStencilState, 0);
	g_context->VSSetConstantBuffers(0, 1, &g_lightConstantBuffer);


	//reset vertex and pixel shader
	g_context->VSSetShader(g_vertexShader, 0, 0);
	g_context->HSSetShader(NULL, 0, 0);
	g_context->DSSetShader(NULL, 0, 0);
	g_context->PSSetShader(g_pixelShader, 0, 0);

	///Draw cubes
	//set the cubes vertex buffer
	g_context->IASetVertexBuffers(0, 1, &g_squareVertexBuffer, &stride, &offset);
	//set the index buffer
	g_context->IASetIndexBuffer(g_squareIndexBuffer, DXGI_FORMAT_R32_UINT, offset);
	XMFLOAT4 temp = XMFLOAT4(0.5f, 0.5f, 0.0f, 1.0f);
	//Set the World/ View/ Projection matrix, send it to contstant buffer in effect file
	WVP = cube1World * camView * camProjection;
	constantBuffer.World = XMMatrixTranspose(cube1World);
	constantBuffer.WVP = XMMatrixTranspose(WVP);
	constantBuffer.Diffuse = XMFLOAT4(0.5f, 0.2f, 0.5f, 0.5f);
	constantBuffer.HasTexture = 1;
	constantBuffer.HasNormalMap = false;
	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);
	//set pixel shader resourece (texture uv value)
	g_context->PSSetShaderResources(0, 1, &g_cubeTexture);
	//seting the samplerstate
	g_context->PSSetSamplers(0, 1, &g_cubeSampler);

	g_context->RSSetState(g_RSCullNone);

	//Draw the first cube
	g_context->DrawIndexed(36, 0, 0);

	//Set the World/ View/ Projection matrix, send it to contstant buffer in effect file
	WVP = cube2World * camView * camProjection;
	constantBuffer.World = XMMatrixTranspose(cube2World);
	constantBuffer.WVP = XMMatrixTranspose(WVP);
	constantBuffer.Diffuse = XMFLOAT4(0.5f, 0.3f, 0.5f, 0.5f);
	constantBuffer.HasTexture = 1;
	constantBuffer.HasNormalMap = false;
	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	//g_context->VSSetConstantBuffers(0, 1, &g_constantBuffer);
	//set pixel shader resourece (texture uv value)
	//g_context->PSSetShaderResources(0, 1, &g_cubeTexture);
	//seting the samplerstate
	//g_context->PSSetSamplers(0, 1, &g_cubeSampler);

	//Draw the second cube
	g_context->DrawIndexed(36, 0, 0);


	

	///Draw debug lines
	//
	//setting the primitve to line list
	//g_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
	//g_context->IASetIndexBuffer(g_debugTerrainIB, DXGI_FORMAT_R32_UINT, 0);
	//g_context->IASetVertexBuffers(0, 1, &g_debugTerrainVB, &stride, &offset);

	//WVP = g_terrainWorld * camView * camProjection;
	//constantBuffer.WVP = XMMatrixTranspose(WVP);
	//constantBuffer.World = XMMatrixTranspose(g_terrainWorld);
	//constantBuffer.Diffuse = XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);
	//constantBuffer.HasTexture = false;
	//constantBuffer.HasNormalMap = false;

	//g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	//g_context->VSSetConstantBuffers(0, 1, &g_constantBuffer);
	//g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);

	//g_context->DrawIndexed(g_terrainFaces * 2 * 3, 0, 0);

	//

	//setting back the primitive to triangle list 
	//g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	///Draw meshes
	//Draw grassGround
	/*for (int i = 0; i < grassGround.Subsets; i++)
	{
		g_context->IASetIndexBuffer(grassGround.IB, DXGI_FORMAT_R32_UINT, 0);
		g_context->IASetVertexBuffers(0, 1, &grassGround.VB, &stride, &offset);
		grassGround.World = XMMatrixTranslation(0.0f, -2.0f, 0.0f);
		WVP = grassGround.World * camView * camProjection;
		constantBuffer.WVP = XMMatrixTranspose(WVP);
		constantBuffer.World = XMMatrixTranspose(grassGround.World);
		constantBuffer.Diffuse = grassGround.Material[grassGround.SubsetsTexture[i]].Diffuse;
		constantBuffer.HasTexture = grassGround.Material[grassGround.SubsetsTexture[i]].HasTexture;
		constantBuffer.HasNormalMap = grassGround.Material[grassGround.SubsetsTexture[i]].HasNormalMap;

		g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
		g_context->VSSetConstantBuffers(0, 1, &g_constantBuffer);
		g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);
		if (grassGround.Material[grassGround.SubsetsTexture[i]].HasTexture)
			g_context->PSSetShaderResources(0, 1, &grassGround.SRV[grassGround.Material[grassGround.SubsetsTexture[i]].TexArrayIndex]);
		if (grassGround.Material[grassGround.SubsetsTexture[i]].HasNormalMap)
			g_context->PSSetShaderResources(1, 1, &grassGround.SRV[grassGround.Material[grassGround.SubsetsTexture[i]].NormalMapTexArrayIndex]);

		g_context->PSSetSamplers(0, 1, &g_cubeSampler);

		g_context->RSSetState(g_RSCullNone);
		int indexStart = grassGround.SubsetsIndexStart[i];
		int indexDrawAmount = grassGround.SubsetsIndexStart[i+1] - grassGround.SubsetsIndexStart[i];
		if (!grassGround.Material[grassGround.SubsetsTexture[i]].Transparent)
		{
			g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
		}
	}*/
	



	///Draw the pickObject
	
	//
	/*for (int j = 0; j < numPinckingObject; j++)
	{
		if (pickingObjectHit[j] == 0)
		{
			for (int i = 0; i < pickingObject.Subsets; i++)
			{
				g_context->IASetIndexBuffer(pickingObject.IB, DXGI_FORMAT_R32_UINT, 0);
				g_context->IASetVertexBuffers(0, 1, &pickingObject.VB, &stride, &offset);

				pickingObject.World = pickingObjectWorld[j];
				WVP = pickingObject.World * camView * camProjection;
				constantBuffer.WVP = XMMatrixTranspose(WVP);
				constantBuffer.World = XMMatrixTranspose(pickingObject.World);
				constantBuffer.Diffuse = pickingObject.Material[pickingObject.SubsetsTexture[i]].Diffuse;
				constantBuffer.HasTexture = pickingObject.Material[pickingObject.SubsetsTexture[i]].HasTexture;
				constantBuffer.HasNormalMap = pickingObject.Material[pickingObject.SubsetsTexture[i]].HasNormalMap;

				g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
				g_context->VSSetConstantBuffers(0, 1, &g_constantBuffer);
				g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);
				if (pickingObject.Material[pickingObject.SubsetsTexture[i]].HasTexture)
					g_context->PSSetShaderResources(0, 1, &pickingObject.SRV[pickingObject.Material[pickingObject.SubsetsTexture[i]].TexArrayIndex]);
				if (pickingObject.Material[pickingObject.SubsetsTexture[i]].HasNormalMap)
					g_context->PSSetShaderResources(1, 1, &pickingObject.SRV[pickingObject.Material[pickingObject.SubsetsTexture[i]].NormalMapTexArrayIndex]);

				g_context->PSSetSamplers(0, 1, &g_cubeSampler);

				g_context->RSSetState(g_RSCullNone);
				int indexStart = pickingObject.SubsetsIndexStart[i];
				int indexDrawAmount = pickingObject.SubsetsIndexStart[i + 1] - pickingObject.SubsetsIndexStart[i];
				if (!pickingObject.Material[pickingObject.SubsetsTexture[i]].Transparent)
				{
					g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
				}
			}
		}
	}

	///Draw the shooting obj
	if (objFlying)
	{
		for (int i = 0; i < pickingObject.Subsets; i++)
		{
			g_context->IASetIndexBuffer(pickingObject.IB, DXGI_FORMAT_R32_UINT, 0);
			g_context->IASetVertexBuffers(0, 1, &pickingObject.VB, &stride, &offset);

			WVP = throwingObjWorld * camView * camProjection;
			constantBuffer.WVP = XMMatrixTranspose(WVP);
			constantBuffer.World = XMMatrixTranspose(throwingObjWorld);
			constantBuffer.Diffuse = pickingObject.Material[pickingObject.SubsetsTexture[i]].Diffuse;
			constantBuffer.HasTexture = pickingObject.Material[pickingObject.SubsetsTexture[i]].HasTexture;
			constantBuffer.HasNormalMap = pickingObject.Material[pickingObject.SubsetsTexture[i]].HasNormalMap;

			g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
			g_context->VSSetConstantBuffers(0, 1, &g_constantBuffer);
			g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);
			if (pickingObject.Material[pickingObject.SubsetsTexture[i]].HasTexture)
				g_context->PSSetShaderResources(0, 1, &pickingObject.SRV[pickingObject.Material[pickingObject.SubsetsTexture[i]].TexArrayIndex]);
			if (pickingObject.Material[pickingObject.SubsetsTexture[i]].HasNormalMap)
				g_context->PSSetShaderResources(1, 1, &pickingObject.SRV[pickingObject.Material[pickingObject.SubsetsTexture[i]].NormalMapTexArrayIndex]);

			g_context->PSSetSamplers(0, 1, &g_cubeSampler);

			g_context->RSSetState(g_RSCullNone);
			int indexStart = pickingObject.SubsetsIndexStart[i];
			int indexDrawAmount = pickingObject.SubsetsIndexStart[i + 1] - pickingObject.SubsetsIndexStart[i];
			if (!pickingObject.Material[pickingObject.SubsetsTexture[i]].Transparent)
			{
				g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
			}
		}
	}*/


	///Draw the spaceRoom's non-transparency parts

	for (int i = 0; i < spaceRoom.Subsets; i++)
	{

		//if it is a transparency subset then we dont waste time to load the data. we will do it later.
		if (!spaceRoom.Material[spaceRoom.SubsetsTexture[i]].Transparent)
		{
			g_context->IASetIndexBuffer(spaceRoom.IB, DXGI_FORMAT_R32_UINT, 0);
			g_context->IASetVertexBuffers(0, 1, &spaceRoom.VB, &stride, &offset);
			WVP = spaceRoom.World * camView * camProjection;
			constantBuffer.WVP = XMMatrixTranspose(WVP);
			constantBuffer.World = XMMatrixTranspose(spaceRoom.World);
			constantBuffer.Diffuse = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].Diffuse;
			constantBuffer.HasTexture = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasTexture;
			constantBuffer.HasNormalMap = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasNormalMap;

			g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
			g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);
			g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);
			if (spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasTexture)
				g_context->PSSetShaderResources(0, 1, &spaceRoom.SRV[spaceRoom.Material[spaceRoom.SubsetsTexture[i]].TexArrayIndex]);
			if (spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasNormalMap)
				g_context->PSSetShaderResources(1, 1, &spaceRoom.SRV[spaceRoom.Material[spaceRoom.SubsetsTexture[i]].NormalMapTexArrayIndex]);

			g_context->PSSetSamplers(0, 1, &g_cubeSampler); // the sampler could share with others

			g_context->RSSetState(g_RSCullNone);
			int indexStart = spaceRoom.SubsetsIndexStart[i];
			int indexDrawAmount = spaceRoom.SubsetsIndexStart[i + 1] - spaceRoom.SubsetsIndexStart[i];

			g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
		}
	}

	///Draw the spaceRoom's transparency parts

	//set the blend state
	g_context->OMSetBlendState(spaceRoom.Transparency, NULL, 0xffffffff);

	for (int i = 0; i < spaceRoom.Subsets; i++)
	{

		g_context->IASetIndexBuffer(spaceRoom.IB, DXGI_FORMAT_R32_UINT, 0);
		g_context->IASetVertexBuffers(0, 1, &spaceRoom.VB, &stride, &offset);
		//check if the subset is transparency
		if (spaceRoom.Material[spaceRoom.SubsetsTexture[i]].Transparent)
		{
			WVP = spaceRoom.World * camView * camProjection;
			constantBuffer.WVP = XMMatrixTranspose(WVP);
			constantBuffer.World = XMMatrixTranspose(spaceRoom.World);
			constantBuffer.Diffuse = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].Diffuse;
			constantBuffer.HasTexture = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasTexture;
			constantBuffer.HasNormalMap = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasNormalMap;

			g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
			g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);
			g_context->PSSetConstantBuffers(1, 1, &g_constantBuffer);
			if (spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasTexture)
				g_context->PSSetShaderResources(0, 1, &spaceRoom.SRV[spaceRoom.Material[spaceRoom.SubsetsTexture[i]].TexArrayIndex]);
			if (spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasNormalMap)
				g_context->PSSetShaderResources(1, 1, &spaceRoom.SRV[spaceRoom.Material[spaceRoom.SubsetsTexture[i]].NormalMapTexArrayIndex]);

			g_context->PSSetSamplers(0, 1, &g_cubeSampler); // the sampler could share with others

			g_context->RSSetState(g_RSCullNone);
			int indexStart = spaceRoom.SubsetsIndexStart[i];
			int indexDrawAmount = spaceRoom.SubsetsIndexStart[i + 1] - spaceRoom.SubsetsIndexStart[i];

			g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
		}
	}

	

	

	
	//Present the backbuffer to the screen
	g_swapChain->Present(0, 0);
}

void RenderShadowToTexture()
{
	UINT stride = sizeof(s_Vertex);
	UINT offset = 0;
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)textureWidth;
	vp.Height = (FLOAT)textureHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;


	g_context->OMSetRenderTargets(1, &g_shadowRTV, g_shadowDepthStencilView);
	g_context->RSSetViewports(1, &vp);

	//clear the shadow RenderTarget
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	g_context->ClearRenderTargetView(g_shadowRTV, ClearColor);
	g_context->ClearDepthStencilView(g_shadowDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	g_context->RSSetState(g_RSCullNone);

	

	//g_context->IASetInputLayout(g_shadowInputLayout);
	//g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//g_context->IASetIndexBuffer(g_terrainIB, DXGI_FORMAT_R32_UINT, 0);
	//g_context->IASetVertexBuffers(0, 1, &g_terrainVB, &stride, &offset);


	g_context->VSSetShader(g_shadowVS, 0, 0);
	g_context->HSSetShader(NULL, 0, 0);
	g_context->DSSetShader(NULL, 0, 0);
	g_context->PSSetShader(g_shadowPS, 0, 0);

	//WVP = g_terrainWorld * Light.lightView * Light.lightProj;
	//constantBuffer.WVP = XMMatrixTranspose(WVP);
	//constantBuffer.World = XMMatrixTranspose(g_terrainWorld);
	//constantBuffer.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f);
	//constantBuffer.CamPos = camPosition;
	//constantBuffer.HasTexture = true;
	//constantBuffer.HasNormalMap = false;

	//g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	//g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);

	////draw the terrain on the shadowRTV
	//g_context->DrawIndexed(g_terrainFaces * 3, 0, 0);


	////render dogModel
	//g_context->IASetIndexBuffer(dogPNTModel.IB, DXGI_FORMAT_R32_UINT, 0);
	//g_context->IASetVertexBuffers(0, 1, &dogPNTModel.VB, &stride, &offset);

	//for (int i = 0; i < dogPNTModel.Subsets; i++)
	//{
	//	dogPNTModel.World = XMMatrixTranslation(0.0f, 0.0f, 8.0f);
	//	WVP = dogPNTModel.World * Light.lightView * Light.lightProj;
	//	constantBuffer.WVP = XMMatrixTranspose(WVP);
	//	constantBuffer.World = XMMatrixTranspose(dogPNTModel.World);
	//	constantBuffer.Diffuse = XMFLOAT4(0.7f, 0.7, 0.7, 1.0);
	//	constantBuffer.HasTexture = dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].HasTexture;
	//	constantBuffer.IsPhongTessel = isPhongTessel;
	//	constantBuffer.HasNormalMap = dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].HasNormalMap;

	//	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	//	g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);

	//	int indexStart = dogPNTModel.SubsetsIndexStart[i];
	//	int indexDrawAmount = dogPNTModel.SubsetsIndexStart[i + 1] - dogPNTModel.SubsetsIndexStart[i];
	//	if (!dogPNTModel.Material[dogPNTModel.SubsetsTexture[i]].Transparent)
	//	{
	//		g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
	//	}
	//}


	g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_context->IASetVertexBuffers(0, 1, &g_squareVertexBuffer, &stride, &offset);
	//set the index buffer
	g_context->IASetIndexBuffer(g_squareIndexBuffer, DXGI_FORMAT_R32_UINT, offset);

	//Set the World/ View/ Projection matrix, send it to contstant buffer in effect file
	WVP = cube1World * Con_Light1.lightView * Con_Light1.lightProj;
	constantBuffer.World = XMMatrixTranspose(cube1World);
	constantBuffer.WVP = XMMatrixTranspose(WVP);
	constantBuffer.Diffuse = XMFLOAT4(0.5f, 0.2f, 0.5f, 0.5f);
	constantBuffer.HasTexture = 1;
	constantBuffer.HasNormalMap = false;
	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);

	//Draw the first cube on the shadowRTV
	g_context->DrawIndexed(36, 0, 0);

	//Set the World/ View/ Projection matrix, send it to contstant buffer in effect file
	WVP = cube2World * Con_Light1.lightView * Con_Light1.lightProj;
	constantBuffer.World = XMMatrixTranspose(cube2World);
	constantBuffer.WVP = XMMatrixTranspose(WVP);
	constantBuffer.Diffuse = XMFLOAT4(0.5f, 0.3f, 0.5f, 0.5f);
	constantBuffer.HasTexture = 1;
	constantBuffer.HasNormalMap = false;
	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);

	//Draw the second cube on the shadowRTV
	g_context->DrawIndexed(36, 0, 0);


	for (int i = 0; i < spaceRoom.Subsets; i++)
	{

		//if it is a transparency subset then we dont waste time to load the data. we will do it later.
		if (!spaceRoom.Material[spaceRoom.SubsetsTexture[i]].Transparent)
		{
			g_context->IASetIndexBuffer(spaceRoom.IB, DXGI_FORMAT_R32_UINT, 0);
			g_context->IASetVertexBuffers(0, 1, &spaceRoom.VB, &stride, &offset);
			WVP = spaceRoom.World * Con_Light1.lightView * Con_Light1.lightProj;
			constantBuffer.WVP = XMMatrixTranspose(WVP);
			constantBuffer.World = XMMatrixTranspose(spaceRoom.World);
			constantBuffer.Diffuse = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].Diffuse;
			constantBuffer.HasTexture = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasTexture;
			constantBuffer.HasNormalMap = spaceRoom.Material[spaceRoom.SubsetsTexture[i]].HasNormalMap;

			g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
			g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);

			int indexStart = spaceRoom.SubsetsIndexStart[i];
			int indexDrawAmount = spaceRoom.SubsetsIndexStart[i + 1] - spaceRoom.SubsetsIndexStart[i];

			g_context->DrawIndexed(indexDrawAmount, indexStart, 0);
		}
	}

	


	//set the Render Target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//reset viewport 
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	g_context->RSSetViewports(1, &vp);

	//draw depth map at the corner
	g_context->VSSetShader(g_vertexShader, 0, 0);
	g_context->PSSetShader(D2D_PS, 0, 0);
	g_context->IASetIndexBuffer(d2dIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	g_context->IASetVertexBuffers(0, 1, &d2dVertBuffer, &stride, &offset);

	WVP = XMMatrixScaling(0.5f, 0.5f, 0.0f) * XMMatrixTranslation(0.5f, -0.5f, 0.0f);
	constantBuffer.WVP = XMMatrixTranspose(WVP);
	g_context->UpdateSubresource(g_constantBuffer, 0, NULL, &constantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(1, 1, &g_constantBuffer);
	g_context->PSSetShaderResources(2, 1, &g_shadewResourceViewMap); 
	g_context->PSSetSamplers(0, 1, &g_cubeSampler);
	g_context->RSSetState(g_RSCullNone);

	g_context->DrawIndexed(6, 0, 0);
}

HRESULT RenderToTextureInitialize()
{
	///initialize render shadow to texture 
	//
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = textureWidth; // texture width size
	textureDesc.Height = textureHeight; // texture height size
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	//create the texture for depth buffer
	HRESULT hr = g_device->CreateTexture2D(&textureDesc, NULL, &g_renderTargetTextureMap);
	if (FAILED(hr))	return hr;

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	//create render target view for shadow map
	hr = g_device->CreateRenderTargetView(g_renderTargetTextureMap, &renderTargetViewDesc, &g_shadowRTV);
	if (FAILED(hr))	return hr;

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = textureDesc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	//create shader resource view for shadow map
	hr = g_device->CreateShaderResourceView(g_renderTargetTextureMap, &shaderResourceViewDesc, &g_shadewResourceViewMap);
	if (FAILED(hr))	return hr;


	D3D11_TEXTURE2D_DESC depthBufferDesc;

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = textureWidth;
	depthBufferDesc.Height = textureHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	ID3D11Texture2D *mShadowDepthStencilBuffer;

	hr = g_device->CreateTexture2D(&depthBufferDesc, NULL, &mShadowDepthStencilBuffer);
	if (FAILED(hr))	return hr;


	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	hr = g_device->CreateDepthStencilView(mShadowDepthStencilBuffer, &depthStencilViewDesc, &g_shadowDepthStencilView);
	if (FAILED(hr))	return hr;

	return S_OK;

}





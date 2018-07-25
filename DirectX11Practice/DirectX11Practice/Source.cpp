#pragma once
//#pragma comment(lib, "Effects11d.lib")
#include "d3dx11effect.h"       
#include "Defines.h"
#include "Mathfunc.h"
#include "ObjModelClass.h"
#include "DepthShaderClass.h"
#include "ShadowShaderClass.h"
#include "RenderToTextureClass.h"
#include "DebuggingLineClass.h"
#include "OrthowindowClass.h"
#include "HorizontialBlurShaderClass.h"
#include "VerticalBlurShaderClass.h"
#include "BlackWhiteShadowShaderClass.h"
#include "TextureShaderClass.h"
#include "TerrainClass.h"
#include "TerrainShaderClass.h"
#include "PhongShaderClass.h"
#include "EnvironmentClass.h"
#include "EnvironmentShaderClass.h"
#include "SkyBoxClass.h"
#include "SkyBoxShaderClass.h"




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
float blendFactor[4];
ID3D11RasterizerState*		g_CWcullMode = NULL;
ID3D11RasterizerState*		g_CCWcullMode = NULL;
ID3D11RasterizerState*		g_RSCullNone = NULL;
ID3D11RasterizerState*		g_RSCullNoneFW = NULL;

ID3D11RenderTargetView*		g_renderTargetView = NULL;
ID3D11DepthStencilView*		g_DepthStencilView = NULL;
ID3D10Blob*					g_vertSBuffer = NULL;
ID3D10Blob*					g_pixelSBuffer = NULL;
ID3D11VertexShader*			g_vertexShader = NULL;
ID3D11PixelShader*			g_pixelShader = NULL;
ID3D11Buffer*				g_constantBuffer = NULL;
ID3D11ShaderResourceView*	g_cubeTexture = NULL;
ID3D11SamplerState*			g_cubeSampler = NULL;

ID3D11DepthStencilState*	g_enableDepthStencilState = NULL;
ID3D11DepthStencilState*	g_disableDepthStencilState = NULL;


UINT screenWidth = GetSystemMetrics(SM_CXSCREEN);
UINT screenHeight = GetSystemMetrics(SM_CYSCREEN);

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


///Loading Models variable
s_OBJModel spaceRoom;
s_OBJModel pickingObject;

ObjModelClass* g_dogPNTModel;
ObjModelClass* g_CubeModel;
ObjModelClass* g_CubeModel2;
ObjModelClass* g_spaceroomModel;
ObjModelClass* g_flashlightModel;

DepthShaderClass* g_depthShader;  //spotlight for cubes
DepthShaderClass* g_depthShader1; //spotlight for flashlight
DepthShaderClass* g_depthShader2; //spotlight for dog

///dogPNTModel variables
//
bool isGDown = false;		//check g key if pressed
bool isPhongTessel = false;

bool isFDown = false;		//check f key if pressed
bool isWireMode = false;

bool isEDown = false;		//check e key if pressed
bool isFlahslightOff = false;

ID3D11InputLayout*			g_dogPNTInputLayout = NULL;

ID3D11ShaderResourceView*	g_dogTexture = NULL;
//

///picking objects variables
//
ObjModelClass*		g_arrowModel;
ObjModelClass*		g_baloonModel;

XMMATRIX baloonWorld0;
XMMATRIX baloonWorld1;
XMMATRIX baloonWorld2;
ID3D11ShaderResourceView*	g_baloonTexture0 = NULL;
ID3D11ShaderResourceView*	g_baloonTexture1 = NULL;
ID3D11ShaderResourceView*	g_baloonTexture2 = NULL;
ID3D11ShaderResourceView*	g_TextureR = NULL;
ID3D11ShaderResourceView*	g_TextureG = NULL;
ID3D11ShaderResourceView*	g_TextureB = NULL;
ID3D11ShaderResourceView*	g_arrowTexture = NULL;
int isAlive1st;
int isAlive2rd;
int isAlive3th;


XMMATRIX pickingObjectWorld[3];
int* pickingObjectHit = new int[3];
int numPinckingObject = 3;
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
XMVECTOR objBoundingBoxMinVertex[3];
XMVECTOR objBoundingBoxMaxVertex[3];
GameTimer g_PickingTimer;
//

///throwing object
//
XMVECTOR throwingobjCenterOffset;
float throwingobjBoundingSphere = 0.0f;
std::vector<XMFLOAT3> throwingobjBoundingBoxVertPosArray;
std::vector<DWORD> throwingobjBoundingBoxVertIndexArray;
XMMATRIX throwingObjWorld;
XMVECTOR throwingObjBoundingBoxMinVertex;
XMVECTOR throwingObjBoundingBoxMaxVertex;
XMVECTOR throwingObjDir;
bool objFlying;

///terrain variables
//
TerrainClass*				g_terrainClass = NULL;
TerrainShaderClass*			g_terrainShaderClass = NULL;
//

/// debugging lines variables
//
ID3D11Buffer*				g_debugTerrainVB = NULL;
ID3D11Buffer*				g_debugTerrainIB = NULL;

DebuggingLineClass*			g_debugCube = NULL;
DebuggingLineClass*			g_debugLine = NULL;
//

//

///camera variables
//
float g_aspectRatio;

XMMATRIX WVP;
XMMATRIX cube1World = XMMatrixIdentity();
XMMATRIX cube2World = XMMatrixIdentity();
XMMATRIX camView;
XMMATRIX camBaseView;
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


ShadowShaderClass*			g_ShadowShader = NULL;
PhongShaderClass*			g_PhongShader = NULL;
//

///Render to Texture
//
int textureWidth = 1024;
int textureHeight = 1024;

//spotlight for cubes shadow variables
RenderToTextureClass*		g_SLDepthTexture = NULL; // spotlight for cubes
RenderToTextureClass*		g_blackWhiteShadowTexture = NULL; // blackwhite
RenderToTextureClass*		g_downSampleTexture = NULL;
RenderToTextureClass*		g_horizontalBlurTexture = NULL;
RenderToTextureClass*		g_verticalBlurTexture = NULL;
RenderToTextureClass*		g_upSampleTexture = NULL;

OrthowindowClass*			g_smallWindow = NULL;
OrthowindowClass*			g_fullWindow = NULL;

BlackWhiteShadowShaderClass*g_blackWhiteShadowShader = NULL;
HorizontalBlurShaderClass*  g_horizontalBlurShader = NULL;
VerticalBlurShaderClass*	g_verticalBlurShader = NULL;
TextureShaderClass*			g_textureShader = NULL;

//flashlight shadow variables
RenderToTextureClass*		g_camSpotDepthTexture = NULL; // CamSpotlight
RenderToTextureClass*		g_camSpotBWShadowTexture = NULL; // camSpotlight blackwhite texture
RenderToTextureClass*		g_camSpotLightdownSampleTexture = NULL;
RenderToTextureClass*		g_camSpotLighthorizontalBlurTexture = NULL;
RenderToTextureClass*		g_camSpotLightverticalBlurTexture = NULL;
RenderToTextureClass*		g_camSpotLightupSampleTexture = NULL;

OrthowindowClass*			g_camSpotLightsmallWindow = NULL;
OrthowindowClass*			g_camSpotLightfullWindow = NULL;

BlackWhiteShadowShaderClass*g_camSpotLightBWShadowShader = NULL;
HorizontalBlurShaderClass*  g_camSpotLighthorizontalBlurShader = NULL;
VerticalBlurShaderClass*	g_camSpotLightverticalBlurShader = NULL;
TextureShaderClass*			g_camSpotLighttextureShader = NULL;

//spotlight for dogmodel shadow variables
RenderToTextureClass*		g_dogLightDepthTexture = NULL; //Spotlight for dog
RenderToTextureClass*		g_dogLightBWShadowTexture = NULL; // camSpotlight blackwhite texture
RenderToTextureClass*		g_dogLightdownSampleTexture = NULL;
RenderToTextureClass*		g_dogLighthorizontalBlurTexture = NULL;
RenderToTextureClass*		g_dogLightverticalBlurTexture = NULL;
RenderToTextureClass*		g_dogLightupSampleTexture = NULL;

OrthowindowClass*			g_dogLightsmallWindow = NULL;
OrthowindowClass*			g_dogLightfullWindow = NULL;

BlackWhiteShadowShaderClass*g_dogLightBWShadowShader = NULL;
HorizontalBlurShaderClass*  g_dogLighthorizontalBlurShader = NULL;
VerticalBlurShaderClass*	g_dogLightverticalBlurShader = NULL;
TextureShaderClass*			g_dogLighttextureShader = NULL;

//Environment Mapping
EnvironmentClass*			g_environmentClass = NULL;
EnvironmentShaderClass*		g_environmentShaderClass = NULL;
RenderToTextureClass*		g_envCubesBWShadowTexture = NULL;
RenderToTextureClass*		g_envFlashLightBWShadowTexture = NULL;
RenderToTextureClass*		g_envDogBWShadowTexture = NULL;


BlackWhiteShadowShaderClass*g_envCubesLightBWShadowShader = NULL;
BlackWhiteShadowShaderClass*g_envFlashLightBWShadowShader = NULL;
BlackWhiteShadowShaderClass*g_envDogLightBWShadowShader = NULL;


//sky box 
SkyBoxClass*				g_skyBoxClass = NULL;
SkyBoxShaderClass*			g_skyBoxShaderClass = NULL;
XMMATRIX skyBoxWorld = XMMatrixIdentity();


///Transformation variables
//
XMMATRIX scale;
XMMATRIX translation;
XMMATRIX rotation;
float rotating = 0.0f;
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
void RenderBlackWhiteShadow();
void DownSampleTexture();
void HorizontalBlurToTexture();
void VerticalBlurToTexture();
void UpSampleTexture();
// camSpotLightShadow
void RenderShadowToTexture1();
void RenderBlackWhiteShadow1();
void DownSampleTexture1();
void HorizontalBlurToTexture1();
void VerticalBlurToTexture1();
void UpSampleTexture1();
//dogSpotLight shadow
void RenderShadowToTexture2();
void RenderBlackWhiteShadow2();
void DownSampleTexture2();
void HorizontalBlurToTexture2();
void VerticalBlurToTexture2();
void UpSampleTexture2();

void RenderEnvironmentCubeTexture();

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

	g_wndName = L"DirectXDemo";

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	ShowCursor(FALSE);
	wcex.lpszClassName = L"DirectX11";
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOWFRAME);
	if (!RegisterClassEx(&wcex))
		return E_FAIL;

	g_hInst = hInstance;
	RECT rc = { 0, 0,  GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(L"DirectX11", g_wndName.c_str(), WS_OVERLAPPEDWINDOW,
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
	sd.SampleDesc.Count = 4;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = FALSE;


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
	depthBufferDec.SampleDesc.Count = 4;
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
	//create PN-Triangle shaders
	HRESULT hr;
	g_ShadowShader = new ShadowShaderClass;
	hr = g_ShadowShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_PhongShader = new PhongShaderClass;
	hr = g_PhongShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_blackWhiteShadowShader = new BlackWhiteShadowShaderClass;
	hr = g_blackWhiteShadowShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_camSpotLightBWShadowShader = new BlackWhiteShadowShaderClass;
	hr = g_camSpotLightBWShadowShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_dogLightBWShadowShader = new BlackWhiteShadowShaderClass;
	hr = g_dogLightBWShadowShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_envCubesLightBWShadowShader = new BlackWhiteShadowShaderClass;
	hr = g_envCubesLightBWShadowShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_envFlashLightBWShadowShader = new BlackWhiteShadowShaderClass;
	hr = g_envFlashLightBWShadowShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_envDogLightBWShadowShader = new BlackWhiteShadowShaderClass;
	hr = g_envDogLightBWShadowShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;
	
	///initialize the dog model class
	g_dogPNTModel = new ObjModelClass;
	if (!g_dogPNTModel) return false;
	hr = g_dogPNTModel->Initialize(g_device, L"GermanShephardLowPoly.obj", L"test.dds", true, true);
	if (FAILED(hr)) return hr;

	///initialize the cube model class
	g_CubeModel = new ObjModelClass;
	if (!g_CubeModel) return false;
	hr = g_CubeModel->Initialize(g_device, L"Cube.obj", L"test.dds", true, true);
	if (FAILED(hr)) return hr;

	g_CubeModel2 = new ObjModelClass;
	if (!g_CubeModel2) return false;
	hr = g_CubeModel2->Initialize(g_device, L"Cube.obj", L"test.dds", true, true);
	if (FAILED(hr)) return hr;


	g_spaceroomModel = new ObjModelClass;
	if (!g_spaceroomModel) return false;
	hr = g_spaceroomModel->Initialize(g_device, L"spaceCompound.obj", NULL, true, true);
	if (FAILED(hr)) return hr;

	g_flashlightModel = new ObjModelClass;
	if (!g_flashlightModel) return false;
	hr = g_flashlightModel->Initialize(g_device, L"flashlight.obj", NULL, true, true);
	if (FAILED(hr)) return hr;

	g_baloonModel = new ObjModelClass;
	if (!g_baloonModel) return false;
	hr = g_baloonModel->Initialize(g_device, L"baloon.obj", NULL, true, true);
	if (FAILED(hr)) return hr;

	g_arrowModel = new ObjModelClass;
	if (!g_arrowModel) return false;
	hr = g_arrowModel->Initialize(g_device, L"arrow.obj", NULL, true, true);
	if (FAILED(hr)) return hr;
	


	g_depthShader = new DepthShaderClass; 
	if (!g_depthShader) return false;
	hr = g_depthShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr)) return hr;

	g_depthShader1 = new DepthShaderClass;
	if (!g_depthShader1) return false;
	hr = g_depthShader1->Initialize(g_device, g_hWnd);
	if (FAILED(hr)) return hr;

	g_depthShader2 = new DepthShaderClass;
	if (!g_depthShader2) return false;
	hr = g_depthShader2->Initialize(g_device, g_hWnd);
	if (FAILED(hr)) return hr;


	///

	///pickObject setting
	//
	CreateBoundingVolumes(g_baloonModel->VertPosArray, objBoundingBoxVertPosArray, objBoundingBoxVertIndexArray, objBoundingSphere, objCenterOffset);
	CreateBoundingVolumes(g_arrowModel->VertPosArray, throwingobjBoundingBoxVertPosArray, throwingobjBoundingBoxVertIndexArray, throwingobjBoundingSphere, throwingobjCenterOffset);

	//baloon world setting
	translation = XMMatrixTranslation(-26.0f, 3.0f, 0.0f);
	baloonWorld0 = translation;
	translation = XMMatrixTranslation(-26.0f, 3.0f, -6.0f);
	baloonWorld1 = translation;
	translation = XMMatrixTranslation(-26.0f, 3.0f, 6.0f);
	baloonWorld2 = translation;
	// set the loaded bottles world space
	pickingObjectWorld[0] = baloonWorld0;
	pickingObjectWorld[1] = baloonWorld1;
	pickingObjectWorld[2] = baloonWorld2;
	for (int k = 0; k < 3; k++)
	{
		pickingObjectHit[k] = 0;
		//Update the objects AABB every time the object is transformed
		CalculateAABB(objBoundingBoxVertPosArray, pickingObjectWorld[k], objBoundingBoxMinVertex[k], objBoundingBoxMaxVertex[k]);
	}
	
	///setting dubegging lines
	//
	g_debugCube = new DebuggingLineClass;
	g_debugCube->Initialize(g_device, g_hWnd, g_CubeModel);

	g_debugLine = new DebuggingLineClass;
	g_debugLine->Initialize(g_device, g_hWnd, g_dogPNTModel);
	//

	//for 2D rendering which dont use the z buffer
	D3D11_DEPTH_STENCIL_DESC depthDisableStencilDesc;
	depthDisableStencilDesc.DepthEnable = false;
	depthDisableStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthDisableStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthDisableStencilDesc.StencilEnable = true;
	depthDisableStencilDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depthDisableStencilDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	depthDisableStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthDisableStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthDisableStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthDisableStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthDisableStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	hr = g_device->CreateDepthStencilState(&depthDisableStencilDesc, &g_disableDepthStencilState);
	if (FAILED(hr))	return hr;


	//for 3D rendering which uses the z buffer
	D3D11_DEPTH_STENCIL_DESC depthEnableStencilDesc;
	depthEnableStencilDesc = depthDisableStencilDesc;
	depthEnableStencilDesc.DepthEnable = true;
	hr = g_device->CreateDepthStencilState(&depthEnableStencilDesc, &g_enableDepthStencilState);
	if (FAILED(hr))	return hr;


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

	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"metal.dds", NULL, NULL, &g_dogTexture, NULL);
	if (FAILED(hr))	return hr;
	//
	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"red.jpg", NULL, NULL, &g_TextureR, NULL);
	if (FAILED(hr))	return hr;
	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"green.jpg", NULL, NULL, &g_TextureG, NULL);
	if (FAILED(hr))	return hr;
	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"blue.jpg", NULL, NULL, &g_TextureB, NULL);
	if (FAILED(hr))	return hr;

	hr = D3DX11CreateShaderResourceViewFromFile(g_device, L"arrow.jpg", NULL, NULL, &g_arrowTexture, NULL);
	if (FAILED(hr))	return hr;
	
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



	g_SLDepthTexture = new RenderToTextureClass;
	if (!g_SLDepthTexture)	return S_FALSE;

	hr = g_SLDepthTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_camSpotDepthTexture = new RenderToTextureClass;
	if (!g_camSpotDepthTexture)	return S_FALSE;

	hr = g_camSpotDepthTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_dogLightDepthTexture = new RenderToTextureClass;
	if (!g_dogLightDepthTexture)	return S_FALSE;

	hr = g_dogLightDepthTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_blackWhiteShadowTexture = new RenderToTextureClass; 
	if (!g_blackWhiteShadowTexture)	return S_FALSE;

	hr = g_blackWhiteShadowTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_camSpotBWShadowTexture = new RenderToTextureClass;
	if (!g_camSpotBWShadowTexture)	return S_FALSE;

	hr = g_camSpotBWShadowTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_dogLightBWShadowTexture = new RenderToTextureClass;
	if (!g_dogLightBWShadowTexture)	return S_FALSE;

	hr = g_dogLightBWShadowTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_envCubesBWShadowTexture = new RenderToTextureClass;
	if (!g_envCubesBWShadowTexture)	return S_FALSE;
	hr = g_envCubesBWShadowTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_envFlashLightBWShadowTexture = new RenderToTextureClass;
	if (!g_envFlashLightBWShadowTexture)	return S_FALSE;
	hr = g_envFlashLightBWShadowTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_envDogBWShadowTexture = new RenderToTextureClass;
	if (!g_envDogBWShadowTexture)	return S_FALSE;
	hr = g_envDogBWShadowTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;


	int downSampleWidth = textureWidth / 2; 
	int downSampleHeight = textureHeight / 2;

	g_downSampleTexture = new RenderToTextureClass;
	if (!g_downSampleTexture)	return S_FALSE;
	hr = g_downSampleTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_horizontalBlurTexture = new RenderToTextureClass;
	if (!g_horizontalBlurTexture)	return S_FALSE;
	hr = g_horizontalBlurTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_verticalBlurTexture = new RenderToTextureClass;
	if (!g_verticalBlurTexture)	return S_FALSE;
	hr = g_verticalBlurTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_upSampleTexture = new RenderToTextureClass;
	if (!g_upSampleTexture)	return S_FALSE;
	hr = g_upSampleTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_smallWindow = new OrthowindowClass;
	if (!g_smallWindow)	return S_FALSE;
	hr = g_smallWindow->Initialize(g_device, downSampleWidth, downSampleHeight);
	if (FAILED(hr))	return hr;

	g_horizontalBlurShader = new HorizontalBlurShaderClass;
	if (!g_horizontalBlurShader) return S_FALSE;
	hr = g_horizontalBlurShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_verticalBlurShader = new VerticalBlurShaderClass;
	if (!g_verticalBlurShader) return S_FALSE;
	hr = g_verticalBlurShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_textureShader = new TextureShaderClass;
	if (!g_textureShader)	return S_FALSE;
	hr = g_textureShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_fullWindow = new OrthowindowClass;
	if (!g_fullWindow)	return S_FALSE;
	hr = g_fullWindow->Initialize(g_device, textureWidth, textureHeight);
	if (FAILED(hr))	return hr;

	g_camSpotLightdownSampleTexture = new RenderToTextureClass;
	if (!g_camSpotLightdownSampleTexture)	return S_FALSE;
	hr = g_camSpotLightdownSampleTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_dogLightdownSampleTexture = new RenderToTextureClass;
	if (!g_dogLightdownSampleTexture)	return S_FALSE;
	hr = g_dogLightdownSampleTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_camSpotLighthorizontalBlurTexture = new RenderToTextureClass; 
	if (!g_camSpotLighthorizontalBlurTexture)	return S_FALSE;
	hr = g_camSpotLighthorizontalBlurTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_dogLighthorizontalBlurTexture = new RenderToTextureClass;
	if (!g_dogLighthorizontalBlurTexture)	return S_FALSE;
	hr = g_dogLighthorizontalBlurTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_camSpotLightverticalBlurTexture = new RenderToTextureClass; 
	if (!g_camSpotLightverticalBlurTexture)	return S_FALSE;
	hr = g_camSpotLightverticalBlurTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_dogLightverticalBlurTexture = new RenderToTextureClass;
	if (!g_dogLightverticalBlurTexture)	return S_FALSE;
	hr = g_dogLightverticalBlurTexture->Initialize(g_device, downSampleWidth, downSampleHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_camSpotLightupSampleTexture = new RenderToTextureClass; 
	if (!g_camSpotLightupSampleTexture)	return S_FALSE;
	hr = g_camSpotLightupSampleTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_dogLightupSampleTexture = new RenderToTextureClass;
	if (!g_dogLightupSampleTexture)	return S_FALSE;
	hr = g_dogLightupSampleTexture->Initialize(g_device, textureWidth, textureHeight, 100.0f, 0.1f);
	if (FAILED(hr))	return hr;

	g_camSpotLightsmallWindow = new OrthowindowClass; 
	if (!g_camSpotLightsmallWindow)	return S_FALSE;
	hr = g_camSpotLightsmallWindow->Initialize(g_device, downSampleWidth, downSampleHeight);
	if (FAILED(hr))	return hr;

	g_dogLightsmallWindow = new OrthowindowClass;
	if (!g_dogLightsmallWindow)	return S_FALSE;
	hr = g_dogLightsmallWindow->Initialize(g_device, downSampleWidth, downSampleHeight);
	if (FAILED(hr))	return hr;

	g_camSpotLighthorizontalBlurShader = new HorizontalBlurShaderClass; 
	if (!g_camSpotLighthorizontalBlurShader) return S_FALSE;
	hr = g_camSpotLighthorizontalBlurShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_dogLighthorizontalBlurShader = new HorizontalBlurShaderClass;
	if (!g_dogLighthorizontalBlurShader) return S_FALSE;
	hr = g_dogLighthorizontalBlurShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_camSpotLightverticalBlurShader = new VerticalBlurShaderClass;
	if (!g_camSpotLightverticalBlurShader) return S_FALSE;
	hr = g_camSpotLightverticalBlurShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_dogLightverticalBlurShader = new VerticalBlurShaderClass;
	if (!g_dogLightverticalBlurShader) return S_FALSE;
	hr = g_dogLightverticalBlurShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_camSpotLighttextureShader = new TextureShaderClass; 
	if (!g_camSpotLighttextureShader)	return S_FALSE;
	hr = g_camSpotLighttextureShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_dogLighttextureShader = new TextureShaderClass;
	if (!g_dogLighttextureShader)	return S_FALSE;
	hr = g_dogLighttextureShader->Initialize(g_device, g_hWnd);
	if (FAILED(hr))	return hr;

	g_camSpotLightfullWindow = new OrthowindowClass; 
	if (!g_camSpotLightfullWindow)	return S_FALSE;
	hr = g_camSpotLightfullWindow->Initialize(g_device, textureWidth, textureHeight);
	if (FAILED(hr))	return hr;

	g_dogLightfullWindow = new OrthowindowClass;
	if (!g_dogLightfullWindow)	return S_FALSE;
	hr = g_dogLightfullWindow->Initialize(g_device, textureWidth, textureHeight);
	if (FAILED(hr))	return hr;
	
	//terrain class / terrain shader class
	g_terrainClass = new TerrainClass;
	if (!g_terrainClass) return S_FALSE;
	hr = g_terrainClass->Initialize(g_device, L"RockGround.dds", L"terrainNormalMap.png");
	if (FAILED(hr))	return hr;


	g_terrainShaderClass = new TerrainShaderClass;
	if (!g_terrainShaderClass) return S_FALSE;
	hr = g_terrainShaderClass->Initialize(g_device);
	if (FAILED(hr))	return hr;

	g_skyBoxClass = new SkyBoxClass;
	if (!g_skyBoxClass) return S_FALSE;
	hr = g_skyBoxClass->Initialize(g_device);
	if (FAILED(hr))	return hr;
	
	g_skyBoxShaderClass = new SkyBoxShaderClass;
	if (!g_skyBoxShaderClass) return S_FALSE;
	hr = g_skyBoxShaderClass->Initialize(g_device);
	if (FAILED(hr)) return hr;
	

	




	g_environmentClass = new EnvironmentClass;
	if (!g_environmentClass) return S_FALSE;
	
	//environment cube
	XMMATRIX EnvironmentCubeWorld;
	g_environmentClass->SetCubeCenter(0.0f, 3.0f, 0.0f);
	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	translation = XMMatrixTranslation(0.0f, 3.0f, 0.0f);
	EnvironmentCubeWorld = scale * translation;
	g_environmentClass->SetWorldMatrix(EnvironmentCubeWorld);

	hr = g_environmentClass->Initialize(g_device);
	if (FAILED(hr)) return hr;

	g_environmentShaderClass = new EnvironmentShaderClass;
	if (!g_environmentShaderClass) return S_FALSE;
	hr = g_environmentShaderClass->Initialize(g_device);
	if (FAILED(hr)) return hr;
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
	blendFactor[0] = 0.65;
	blendFactor[1] = 0.65;
	blendFactor[2] = 0.65;
	blendFactor[3] = 1.0f;
	///create Rasterizer
	//
	D3D11_RASTERIZER_DESC cullingModeDecs;
	ZeroMemory(&cullingModeDecs, sizeof(D3D11_RASTERIZER_DESC));
	cullingModeDecs.FillMode = D3D11_FILL_SOLID;
	cullingModeDecs.CullMode = D3D11_CULL_BACK;
	//cullingModeDecs.DepthClipEnable = true;
	cullingModeDecs.FrontCounterClockwise = true;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_CCWcullMode);
	if (FAILED(hr))	return hr;
	cullingModeDecs.FrontCounterClockwise = false;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_CWcullMode);
	if (FAILED(hr))	return hr;

	cullingModeDecs.CullMode = D3D11_CULL_NONE;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_RSCullNone);
	cullingModeDecs.FillMode = D3D11_FILL_WIREFRAME;
	cullingModeDecs.CullMode = D3D11_CULL_BACK;
	cullingModeDecs.FrontCounterClockwise = false;
	hr = g_device->CreateRasterizerState(&cullingModeDecs, &g_RSCullNoneFW);

	if (FAILED(hr))	return hr;
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
	//calculate cambaseView
	camPosition = XMVectorSet(0.0f, 0.0f, -10.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	camBaseView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	//calculate camview
	camPosition = XMVectorSet(0.0f, 2.0f, -8.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);


	g_aspectRatio = (float)screenWidth / (float)screenHeight;

	camProjection = XMMatrixPerspectiveFovLH(0.25f*XM_PI, g_aspectRatio, 0.1f, 500.0f);
	//






	///setting the Light value
	//
	float cone = 32;


	//point light
	Light.Dir = XMFLOAT4(1.1f, 2.2f, 3.3f, 0.0f);
	Light.Cone = 2;
	Light.Pos = XMFLOAT4(0.0f, 4.0f, 15.0f, 1.0f);
	Light.Attenuation = XMFLOAT3(1.0f, 0.1f, 0.0f);
	Light.Ambient = XMFLOAT4(1.f, 1.f, 1.f, 1.0f);
	Light.Diffuse = XMFLOAT4(1.0f, 0.0f, 0.7f, 1.0f);

	//direct light
	Dir_Light.Dir = XMFLOAT4(-0.5f, -1.0f, -0.5f, 0.0f);
	Dir_Light.Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	//Dir_Light.Diffuse = XMFLOAT4(209.f / 255, 135.f / 255, 0.0f, 1.0f);
	Dir_Light.Diffuse = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

	//cone light 1 spotlight for cubes
	Con_Light1.Dir = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
	Con_Light1.Pos = XMFLOAT4(0.0f, 8.0f, -24.0f, 1.0f);
	Con_Light1.Cone = cone;
	Con_Light1.Attenuation = XMFLOAT3(1.0f, 0.0f, 0.0f);
	Con_Light1.Ambient = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	Con_Light1.Diffuse = XMFLOAT4(1.0f, .1f, .3f, 1.0f);

	//cone light 2 spotlight for dog
	Con_Light2.Dir = XMFLOAT4(0.8f, 0.25f, 0.0f, 0.0f);
	Con_Light2.Pos = XMFLOAT4(18.0f, 0.1f, 0.0f, 1.0f);
	Con_Light2.Cone = cone;
	Con_Light2.Attenuation = XMFLOAT3(1.0f, 0.0f, 0.0f);
	Con_Light2.Ambient = XMFLOAT4(0.6f, 0.6f, 0.6f, 1.0f);
	Con_Light2.Diffuse = XMFLOAT4(0.0f, 1.0f, .0f, 1.0f);
	

	XMMATRIX lightView;
	XMVECTOR lightPos;
	XMMATRIX lightViewProjection;

	XMVECTOR tempDir = XMVectorSet(Con_Light2.Dir.x, Con_Light2.Dir.y, Con_Light2.Dir.z, 0.0f);

	lightPos = XMVectorSet(Con_Light2.Pos.x, Con_Light2.Pos.y, Con_Light2.Pos.z, 1.0f);
	lightView = XMMatrixLookAtLH(lightPos, tempDir + lightPos, camUp);
	lightViewProjection = XMMatrixPerspectiveFovLH(XM_PI / 2.0f, 1.0f, 1.0f, 100.0f);

	Con_Light2.lightView = lightView;
	Con_Light2.lightProj = lightViewProjection;

	//cone light 3 flashlight
	Con_Light3.Dir = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
	Con_Light3.Pos = XMFLOAT4(0.0f, 8.0f, -3.0f, 1.0f);
	Con_Light3.Cone = 81;
	Con_Light3.Attenuation = XMFLOAT3(1.0f, 0.01f, 0.001f);
	Con_Light3.Ambient = XMFLOAT4(0.78f, 0.78f, 0.78f, 1.0f);
	Con_Light3.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

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

	if (g_CWcullMode) g_CWcullMode->Release();
	if (g_CCWcullMode) g_CCWcullMode->Release();

	if (g_cubeTexture) g_cubeTexture->Release();
	if (g_lightConstantBuffer) g_lightConstantBuffer->Release();


	if (g_dogPNTModel)
	{
		g_dogPNTModel->ShutDown();
		delete g_dogPNTModel;
		g_dogPNTModel = NULL;
	}

	if (g_CubeModel)
	{
		g_CubeModel->ShutDown();
		delete g_CubeModel;
		g_CubeModel = NULL;
	}

	if (g_CubeModel2)
	{
		g_CubeModel2->ShutDown();
		delete g_CubeModel2;
		g_CubeModel2 = NULL;
	}

	if (g_spaceroomModel)
	{
		g_spaceroomModel->ShutDown();
		delete g_spaceroomModel;
		g_spaceroomModel = NULL;
	}


	if (g_flashlightModel)
	{
		g_flashlightModel->ShutDown();
		delete g_flashlightModel;
		g_flashlightModel = NULL;
	}


	if (g_baloonModel)
	{
		g_baloonModel->ShutDown();
		delete g_baloonModel;
		g_baloonModel = NULL;
	}

	if (g_arrowModel)
	{
		g_arrowModel->ShutDown();
		delete g_arrowModel;
		g_arrowModel = NULL;
	}

	if (g_ShadowShader)
	{
		g_ShadowShader->ShutDown();
		delete g_ShadowShader;
		g_ShadowShader = NULL;
	}

	if (g_PhongShader)
	{
		g_PhongShader->ShutDown();
		delete g_PhongShader;
		g_PhongShader = NULL;
	}

	if (g_dogTexture)
	{
		g_dogTexture->Release();
		g_dogTexture = NULL;
	}

	if (g_blackWhiteShadowShader)
	{
		g_blackWhiteShadowShader->ShutDown();
		delete g_blackWhiteShadowShader;
		g_blackWhiteShadowShader = NULL;
	}
	if (g_camSpotLightBWShadowShader)
	{
		g_camSpotLightBWShadowShader->ShutDown();
		delete g_camSpotLightBWShadowShader;
		g_camSpotLightBWShadowShader = NULL;
	}

	if (g_dogLightBWShadowShader)
	{
		g_dogLightBWShadowShader->ShutDown();
		delete g_dogLightBWShadowShader;
		g_dogLightBWShadowShader = NULL;
	}

	if (g_envCubesLightBWShadowShader)
	{
		g_envCubesLightBWShadowShader->ShutDown();
		delete g_envCubesLightBWShadowShader;
		g_envCubesLightBWShadowShader = NULL;
	}
	if (g_envFlashLightBWShadowShader)
	{
		g_envFlashLightBWShadowShader->ShutDown();
		delete g_envFlashLightBWShadowShader;
		g_envFlashLightBWShadowShader = NULL;
	}
	if (g_envDogLightBWShadowShader)
	{
		g_envDogLightBWShadowShader->ShutDown();
		delete g_envDogLightBWShadowShader;
		g_envDogLightBWShadowShader = NULL;
	}
	if (g_debugCube)
	{
		g_debugCube->ShutDown();
		delete g_debugCube;
		g_debugCube = NULL;
	}
	if (g_debugLine)
	{
		g_debugLine->ShutDown();
		delete g_debugLine;
		g_debugLine = NULL;
	}

	if (pickingObjectHit)
	{
		delete[] pickingObjectHit;
		pickingObjectHit = NULL;
	}


	if (g_mouse) g_mouse->Unacquire();
	if (g_keyboard) g_keyboard->Unacquire();
	if (g_directInput) g_directInput->Release();

	if (g_SLDepthTexture)
	{
		g_SLDepthTexture->ShutDown();
		delete g_SLDepthTexture;
		g_SLDepthTexture = NULL;
	}
	if (g_camSpotDepthTexture)
	{
		g_camSpotDepthTexture->ShutDown();
		delete g_camSpotDepthTexture;
		g_camSpotDepthTexture = NULL;
	}
	if (g_dogLightDepthTexture)
	{
		g_dogLightDepthTexture->ShutDown();
		delete g_dogLightDepthTexture;
		g_dogLightDepthTexture = NULL;
	}

	if (g_blackWhiteShadowTexture)
	{
		g_blackWhiteShadowTexture->ShutDown();
		delete g_blackWhiteShadowTexture;
		g_blackWhiteShadowTexture = NULL;
	}

	if (g_camSpotLightdownSampleTexture)
	{
		g_camSpotLightdownSampleTexture->ShutDown();
		delete g_camSpotLightdownSampleTexture;
		g_camSpotLightdownSampleTexture = NULL;
	}


	if (g_dogLightdownSampleTexture)
	{
		g_dogLightdownSampleTexture->ShutDown();
		delete g_dogLightdownSampleTexture;
		g_dogLightdownSampleTexture = NULL;
	}

	if (g_camSpotLighthorizontalBlurTexture)
	{
		g_camSpotLighthorizontalBlurTexture->ShutDown();
		delete g_camSpotLighthorizontalBlurTexture;
		g_camSpotLighthorizontalBlurTexture = NULL;
	}

	if (g_dogLighthorizontalBlurTexture)
	{
		g_dogLighthorizontalBlurTexture->ShutDown();
		delete g_dogLighthorizontalBlurTexture;
		g_dogLighthorizontalBlurTexture = NULL;
	}

	if (g_camSpotLightverticalBlurTexture)
	{
		g_camSpotLightverticalBlurTexture->ShutDown();
		delete g_camSpotLightverticalBlurTexture;
		g_camSpotLightverticalBlurTexture = NULL;
	}

	if (g_dogLightverticalBlurTexture)
	{
		g_dogLightverticalBlurTexture->ShutDown();
		delete g_dogLightverticalBlurTexture;
		g_dogLightverticalBlurTexture = NULL;
	}

	if (g_camSpotLightupSampleTexture)
	{
		g_camSpotLightupSampleTexture->ShutDown();
		delete g_camSpotLightupSampleTexture;
		g_camSpotLightupSampleTexture = NULL;
	}

	if (g_dogLightupSampleTexture)
	{
		g_dogLightupSampleTexture->ShutDown();
		delete g_dogLightupSampleTexture;
		g_dogLightupSampleTexture = NULL;
	}

	if (g_camSpotLightsmallWindow)
	{
		g_camSpotLightsmallWindow->ShutDown();
		delete g_camSpotLightsmallWindow;
		g_camSpotLightsmallWindow = NULL;
	}

	if (g_dogLightsmallWindow)
	{
		g_dogLightsmallWindow->ShutDown();
		delete g_dogLightsmallWindow;
		g_dogLightsmallWindow = NULL;
	}

	if (g_camSpotLightfullWindow)
	{
		g_camSpotLightfullWindow->ShutDown();
		delete g_camSpotLightfullWindow;
		g_camSpotLightfullWindow = NULL;
	}

	if (g_dogLightfullWindow)
	{
		g_dogLightfullWindow->ShutDown();
		delete g_dogLightfullWindow;
		g_dogLightfullWindow = NULL;
	}

	if (g_camSpotLighthorizontalBlurShader)
	{
		g_camSpotLighthorizontalBlurShader->ShutDown();
		delete g_camSpotLighthorizontalBlurShader;
		g_camSpotLighthorizontalBlurShader = NULL;
	}

	if (g_dogLighthorizontalBlurShader)
	{
		g_dogLighthorizontalBlurShader->ShutDown();
		delete g_dogLighthorizontalBlurShader;
		g_dogLighthorizontalBlurShader = NULL;
	}

	if (g_camSpotLightverticalBlurShader)
	{
		g_camSpotLightverticalBlurShader->ShutDown();
		delete g_camSpotLightverticalBlurShader;
		g_camSpotLightverticalBlurShader = NULL;
	}

	if (g_dogLightverticalBlurShader)
	{
		g_dogLightverticalBlurShader->ShutDown();
		delete g_dogLightverticalBlurShader;
		g_dogLightverticalBlurShader = NULL;
	}

	if (g_camSpotLighttextureShader)
	{
		g_camSpotLighttextureShader->ShutDown();
		delete g_camSpotLighttextureShader;
		g_camSpotLighttextureShader = NULL;
	}

	if (g_dogLighttextureShader)
	{
		g_dogLighttextureShader->ShutDown();
		delete g_dogLighttextureShader;
		g_dogLighttextureShader = NULL;
	}

	if (g_camSpotBWShadowTexture)
	{
		g_camSpotBWShadowTexture->ShutDown();
		delete g_camSpotBWShadowTexture;
		g_camSpotBWShadowTexture = NULL;
	}

	if (g_dogLightBWShadowTexture)
	{
		g_dogLightBWShadowTexture->ShutDown();
		delete g_dogLightBWShadowTexture;
		g_dogLightBWShadowTexture = NULL;
	}

	if (g_envCubesBWShadowTexture)
	{
		g_envCubesBWShadowTexture->ShutDown();
		delete g_envCubesBWShadowTexture;
		g_envCubesBWShadowTexture = NULL;
	}

	if (g_envFlashLightBWShadowTexture)
	{
		g_envFlashLightBWShadowTexture->ShutDown();
		delete g_envFlashLightBWShadowTexture;
		g_envFlashLightBWShadowTexture = NULL;
	}

	if (g_envDogBWShadowTexture)
	{
		g_envDogBWShadowTexture->ShutDown();
		delete g_envDogBWShadowTexture;
		g_envDogBWShadowTexture = NULL;
	}

	if (g_downSampleTexture)
	{
		g_downSampleTexture->ShutDown();
		delete g_downSampleTexture;
		g_downSampleTexture = NULL;
	}

	if (g_horizontalBlurTexture)
	{
		g_horizontalBlurTexture->ShutDown();
		delete g_horizontalBlurTexture;
		g_horizontalBlurTexture = NULL;
	}
	if (g_verticalBlurTexture)
	{
		g_verticalBlurTexture->ShutDown();
		delete g_verticalBlurTexture;
		g_verticalBlurTexture = NULL;
	}

	if (g_upSampleTexture)
	{
		g_upSampleTexture->ShutDown();
		delete g_upSampleTexture;
		g_upSampleTexture = NULL;
	}


	if (g_smallWindow)
	{
		g_smallWindow->ShutDown();
		delete g_smallWindow;
		g_smallWindow = NULL;
	}

	if (g_horizontalBlurShader)
	{
		g_horizontalBlurShader->ShutDown();
		delete g_horizontalBlurShader;
		g_horizontalBlurShader = NULL;
	}
	if (g_verticalBlurShader)
	{
		g_verticalBlurShader->ShutDown();
		delete g_verticalBlurShader;
		g_verticalBlurShader = NULL;
	}
	if (g_fullWindow)
	{
		g_fullWindow->ShutDown();
		delete g_fullWindow;
		g_fullWindow = NULL;
	}

	if (g_textureShader)
	{
		g_textureShader->ShutDown();
		delete g_textureShader;
		g_textureShader = NULL;
	}

	if (g_terrainClass)
	{
		g_terrainClass->ShutDown();
		g_terrainClass = NULL;
	}

	if (g_terrainShaderClass)
	{
		g_terrainShaderClass->ShutDown();
		g_terrainShaderClass = NULL;
	}

	if (g_skyBoxClass)
	{
		g_skyBoxClass->ShutDown();
		g_skyBoxClass = NULL;
	}

	if (g_skyBoxShaderClass)
	{
		g_skyBoxShaderClass->ShutDown();
		g_skyBoxShaderClass = NULL;
	}


	if (g_disableDepthStencilState)
	{
		g_disableDepthStencilState->Release();
		g_disableDepthStencilState = NULL;
	}
	if (g_enableDepthStencilState)
	{
		g_enableDepthStencilState->Release();
		g_enableDepthStencilState = NULL;
	}
	
	if (g_depthShader)
	{
		g_depthShader->ShutDown();
		delete g_depthShader;
		g_depthShader = NULL;
	}

	if (g_depthShader1)
	{
		g_depthShader1->ShutDown();
		delete g_depthShader1;
		g_depthShader1 = NULL;
	}
	
	if (g_depthShader2)
	{
		g_depthShader2->ShutDown();
		delete g_depthShader2;
		g_depthShader2 = NULL;
	}

	if (g_environmentClass)
	{
		g_environmentClass->ShutDown();
		delete g_environmentClass;
		g_environmentClass = NULL;
	}


	if (g_environmentShaderClass)
	{
		g_environmentShaderClass->ShutDown();
		delete g_environmentShaderClass;
		g_environmentShaderClass = NULL;
	}
	
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


	float speed = 5.0f * (float)deltaTime;
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

	if (keyboardState[DIK_F] & 0x80)
	{
		if (!isFDown)
		{
			isWireMode = !isWireMode;

			isFDown = true;
		}
	}
	if (!(keyboardState[DIK_F] & 0x80))
	{
		isFDown = false;
	}

	if (keyboardState[DIK_E] & 0x80)
	{
		if (!isEDown)
		{
			isFlahslightOff = !isFlahslightOff;

			isEDown = true;
		}
	}
	if (!(keyboardState[DIK_E] & 0x80))
	{
		isEDown = false;
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

			float mouseX = (float)mousePos.x;
			float mouseY = (float)mousePos.y;

			int hitIndex;
			float tempDist;
			float closestDist = FLT_MAX;


			XMVECTOR prwPos, prwDir;
			PickRayVector(mouseX, mouseY, g_clientWidth, g_clientHeight, camProjection, camView, prwPos, prwDir);
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
							tempDist = Pick(prwPos, prwDir, g_baloonModel->VertPosArray, g_baloonModel->VertIndexArray, pickingObjectWorld[i]);
						}
					}
					if (pickMode == 1)
						tempDist = Pick(prwPos, prwDir, objBoundingBoxVertPosArray, objBoundingBoxVertIndexArray, pickingObjectWorld[i]);

					if (pickMode == 2)
						tempDist = Pick(prwPos, prwDir, g_baloonModel->VertPosArray, g_baloonModel->VertIndexArray, pickingObjectWorld[i]);

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
	else if (g_rotX < 0.0f)
	{
		g_rotX = 6.28f + g_rotX;
	}
	if (g_rotZ > 6.28f)
	{
		g_rotZ -= 6.28f;
	}
	else if (g_rotZ < 0.0f)
	{
		g_rotZ = 6.28f + g_rotZ;
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
			<< L"Frame Time: " << mspf << L" (ms)" << L"    " << L"CamPos: ( " << XMVectorGetX(camPosition) << L", " << XMVectorGetY(camPosition) << L", " << XMVectorGetZ(camPosition) << L", " << XMVectorGetW(camPosition) << L")";
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
	g_skyBoxClass->SetWorldMatrix(skyBoxWorld);


	///point Light update
	XMVECTOR lightVector = XMVectorSet(0.0f, cosf(rotating) * 15, 0.0f, 0.0f);
	lightVector = XMVector3TransformCoord(lightVector, XMMatrixIdentity());
	//Light.Pos.y = XMVectorGetY(lightVector);


	XMMATRIX lightView;
	XMVECTOR lightPos;
	XMMATRIX lightViewProjection;
	lightPos = XMVectorSet(Con_Light1.Pos.x, Con_Light1.Pos.y, Con_Light1.Pos.z, 0.0f);
	lightView = XMMatrixLookAtLH(lightPos, XMVectorSet(Con_Light1.Pos.x, Con_Light1.Pos.y - 10.0f, Con_Light1.Pos.z, 0.0f), XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
	lightViewProjection = XMMatrixPerspectiveFovLH(XM_PI / 2.0f, 1.0f, 1.0f, 100.0f);
	Con_Light1.lightView = lightView;
	Con_Light1.lightProj = lightViewProjection;



	//

	g_rotationX = XMMatrixRotationAxis(rotXAxis, g_rotX);
	g_rotationZ = XMMatrixRotationAxis(rotZAxis, g_rotZ);
	rotation = XMMatrixRotationAxis(rotYAxis, rotating);
	translation = XMMatrixTranslation(Con_Light1.Pos.x, Con_Light1.Pos.y - 5.0f, Con_Light1.Pos.z);

	XMMATRIX cubeWorld = rotation * g_rotationX * g_rotationZ *translation;
	g_CubeModel->SetWorldMatrix(cubeWorld);

	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	rotation = XMMatrixRotationAxis(rotYAxis, -rotating);
	translation = XMMatrixTranslation(0.0f + (1.5f * cosf(rotating)), 1.0f, -24.0f + (1.5f * sinf(rotating)));
	XMMATRIX cubeWorld2 = rotation *scale * translation;
	g_CubeModel2->SetWorldMatrix(cubeWorld2);







	//g_spaceRoom world setting
	rotation = XMMatrixRotationY(XM_PI);
	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	translation = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	XMMATRIX spaceRoomWorld = scale * rotation * translation;
	g_spaceroomModel->SetWorldMatrix(spaceRoomWorld);

	//terrain world setting
	scale = XMMatrixScaling(8.0f, 6.0f, 8.0f);
	translation = XMMatrixTranslation(-1100.0f, -3.8f, -800.0f);
	XMMATRIX terrainWorld = scale * translation;
	g_terrainClass->SetWorldMatrix(terrainWorld);
	
	//dogmodel world setting
	scale = XMMatrixScaling(0.5f, 0.5f, 0.5f);
	rotation = XMMatrixRotationY(XM_PI/2.0f);
	translation = XMMatrixTranslation(25.0f, 0.0f, 0.0f);
	XMMATRIX dogWorld = scale * rotation * translation;
	g_dogPNTModel->SetWorldMatrix(dogWorld);

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

		rotation = XMMatrixRotationX(theta2) * XMMatrixRotationY(theta);
		translation = XMMatrixTranslation(XMVectorGetX(tempFlyingObjPos), XMVectorGetY(tempFlyingObjPos), XMVectorGetZ(tempFlyingObjPos));
		scale = XMMatrixScaling(1.0f, 1.5f, 1.5f);
		throwingObjWorld = scale * rotation * translation;

		CalculateAABB(throwingobjBoundingBoxVertPosArray, throwingObjWorld, throwingObjBoundingBoxMinVertex, throwingObjBoundingBoxMaxVertex);

		for (int i = 0; i < numPinckingObject; i++)
		{
			if (pickingObjectHit[i] == 0)
			{
				if (pickMode == 0)
				{
					if (BoundingSphereCollision(throwingobjBoundingSphere, throwingobjCenterOffset, throwingObjWorld, objBoundingSphere, objCenterOffset, pickingObjectWorld[i]))
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
	XMVECTOR lookDir = camTarget;

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
	camProjection = XMMatrixPerspectiveFovLH(0.25f*XM_PI, g_aspectRatio, 0.1f, 500.0f);

	XMMATRIX lightView;
	XMVECTOR lightPos;
	XMMATRIX lightViewProjection;

	Con_Light3.Pos.x = XMVectorGetX(camPosition) + XMVectorGetX(lookDir * 0.25f) - 0.03f;
	Con_Light3.Pos.y = XMVectorGetY(camPosition) + XMVectorGetY(lookDir * 0.25f) - 0.05f;
	Con_Light3.Pos.z = XMVectorGetZ(camPosition) + XMVectorGetZ(lookDir * 0.25f);

	Con_Light3.Dir.x = XMVectorGetX(camTarget) - Con_Light3.Pos.x;
	Con_Light3.Dir.y = XMVectorGetY(camTarget) - Con_Light3.Pos.y;
	Con_Light3.Dir.z = XMVectorGetZ(camTarget) - Con_Light3.Pos.z;

	XMVECTOR tempDir = XMVectorSet(Con_Light3.Dir.x, Con_Light3.Dir.y, Con_Light3.Dir.z, 0.0f);
	
	lightPos = XMVectorSet(Con_Light3.Pos.x, Con_Light3.Pos.y, Con_Light3.Pos.z, 1.0f);
	lightView = XMMatrixLookAtLH(lightPos, tempDir + lightPos, camUp);
	lightViewProjection = XMMatrixPerspectiveFovLH(XM_PI / 2.0f, 1.0f, 1.0f, 100.0f);

	Con_Light3.lightView = lightView;
	Con_Light3.lightProj = lightViewProjection;
	if (!isFlahslightOff)
		Con_Light3.Ambient = XMFLOAT4(0.48f, 0.48f, 0.48f, 1.0f);
	else
		Con_Light3.Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	XMMATRIX flashlightWorld;
	XMVECTOR flashlightDir = camTarget - camPosition;

	flashlightWorld = XMMatrixScaling(.1f, 0.1f, 0.1f) * XMMatrixRotationY(XM_PI) *camRotation* XMMatrixTranslation(Con_Light3.Pos.x, Con_Light3.Pos.y, Con_Light3.Pos.z);
	g_flashlightModel->SetWorldMatrix(flashlightWorld);

	

}

void Render()
{
	//set the RS state
	g_context->RSSetState(g_RSCullNone);
	g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_context->OMSetBlendState(NULL, NULL, 0xffffffff);

	//spot light for cubes
	RenderShadowToTexture();
	RenderBlackWhiteShadow();
	DownSampleTexture();
	HorizontalBlurToTexture();
	VerticalBlurToTexture();
	UpSampleTexture();
	
	//spot light for flash light
	RenderShadowToTexture1();
	RenderBlackWhiteShadow1();
	DownSampleTexture1();
	HorizontalBlurToTexture1();
	VerticalBlurToTexture1();
	UpSampleTexture1();
	
	//spot light for dog
	RenderShadowToTexture2();
	RenderBlackWhiteShadow2();
	DownSampleTexture2();
	HorizontalBlurToTexture2();
	VerticalBlurToTexture2();
	UpSampleTexture2();

	lightConstantBuffer.Light[0] = Light; // point light
	lightConstantBuffer.Light[1] = Dir_Light;
	lightConstantBuffer.Light[2] = Con_Light1;
	lightConstantBuffer.Light[3] = Con_Light2;
	lightConstantBuffer.Light[4] = Con_Light3;
	g_context->UpdateSubresource(g_lightConstantBuffer, 0, NULL, &lightConstantBuffer, 0, 0);
	g_context->VSSetConstantBuffers(0, 1, &g_lightConstantBuffer);
	g_context->PSSetConstantBuffers(0, 1, &g_lightConstantBuffer);

	//Clear backbuffer
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	g_context->ClearRenderTargetView(g_renderTargetView, ClearColor);
	//Refresh the Depth/Stencil view
	g_context->ClearDepthStencilView(g_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	UINT stride = sizeof(s_Vertex);
	UINT offset = 0;

	RenderEnvironmentCubeTexture();




	g_skyBoxClass->Render(g_context);
	g_skyBoxShaderClass->Render(g_context, g_skyBoxClass->GetIndexCount(), g_skyBoxClass->GetWorldMatrix(), camView, camProjection, g_skyBoxClass->GetShaderResourceView());

	g_CubeModel->Render(g_context);
	g_ShadowShader->Render(g_context, g_CubeModel, camView, camProjection, g_cubeTexture, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());

	g_CubeModel2->Render(g_context);
	g_ShadowShader->Render(g_context, g_CubeModel2, camView, camProjection, g_cubeTexture, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());

	
	
	g_spaceroomModel->Render(g_context);
	g_ShadowShader->Render(g_context, g_spaceroomModel, camView, camProjection, NULL, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());

	g_flashlightModel->Render(g_context);
	g_ShadowShader->Render(g_context, g_flashlightModel, camView, camProjection, NULL, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());


	if (objFlying)
	{
		g_arrowModel->Render(g_context);
		g_arrowModel->SetWorldMatrix(throwingObjWorld);
		g_ShadowShader->Render(g_context, g_arrowModel, camView, camProjection, g_arrowTexture, NULL, NULL, NULL);
	}



	XMFLOAT4 tempCamPos;
	XMStoreFloat4(&tempCamPos, camPosition);

	g_environmentClass->Render(g_context);
	g_environmentShaderClass->Render(g_context, g_environmentClass->GetIndexCount(), g_environmentClass->GetWorldMatrix(), camView, camProjection, NULL, NULL, g_environmentClass->GetShaderResourceView(), false, false, tempCamPos);


	if (isWireMode)
		g_context->RSSetState(g_RSCullNoneFW);


	g_terrainClass->Render(g_context);
	g_terrainShaderClass->Render(g_context, g_terrainClass->GetIndexCount(), g_terrainClass->GetWorldMatrix(), camView, camProjection, g_terrainClass->GetTexture(), g_terrainClass->GetNormalMap(), true, true, tempCamPos);

	g_dogPNTModel->Render(g_context);
	

	g_PhongShader->Render(g_context, g_dogPNTModel, camView, camProjection, g_dogTexture, g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView(), true, false, isPhongTessel);

	g_context->RSSetState(g_RSCullNone);


	//render transparncy objects
	g_context->OMSetBlendState(g_transparency, blendFactor, 0xffffffff);

	
	XMVECTOR baloon0 = XMVectorZero();
	XMVECTOR baloon1 = XMVectorZero();
	XMVECTOR baloon2 = XMVectorZero();

	baloon0 = XMVector3TransformCoord(baloon0, baloonWorld0);
	float distX = XMVectorGetX(baloon0) - XMVectorGetX(camPosition);
	float distY = XMVectorGetY(baloon0) - XMVectorGetY(camPosition);
	float distZ = XMVectorGetZ(baloon0) - XMVectorGetZ(camPosition);
	float baloon0Dist = distX*distX + distY*distY + distZ*distZ;
	
	baloon1 = XMVector3TransformCoord(baloon1, baloonWorld1);
	distX = XMVectorGetX(baloon1) - XMVectorGetX(camPosition);
	distY = XMVectorGetY(baloon1) - XMVectorGetY(camPosition);
	distZ = XMVectorGetZ(baloon1) - XMVectorGetZ(camPosition);
	float baloon1Dist = distX*distX + distY*distY + distZ*distZ;

	baloon2 = XMVector3TransformCoord(baloon2, baloonWorld2);
	distX = XMVectorGetX(baloon2) - XMVectorGetX(camPosition);
	distY = XMVectorGetY(baloon2) - XMVectorGetY(camPosition);
	distZ = XMVectorGetZ(baloon2) - XMVectorGetZ(camPosition);
	float baloon2Dist = distX*distX + distY*distY + distZ*distZ;


	XMMATRIX closest;
	XMMATRIX seconedclose;
	XMMATRIX farest;

	if (baloon0Dist > baloon1Dist)
	{
		if (baloon0Dist > baloon2Dist)
		{
			if (baloon1Dist > baloon2Dist)
			{
				farest = baloonWorld0;
				g_baloonTexture0 = g_TextureR;

				seconedclose = baloonWorld1;
				g_baloonTexture1 = g_TextureG;

				closest = baloonWorld2;
				g_baloonTexture2 = g_TextureB;

				isAlive1st = pickingObjectHit[0];
				isAlive2rd = pickingObjectHit[1];
				isAlive3th = pickingObjectHit[2];

			}
			else
			{
				farest = baloonWorld0;
				g_baloonTexture0 = g_TextureR;
				seconedclose = baloonWorld2;
				g_baloonTexture1 = g_TextureB;
				closest = baloonWorld1;
				g_baloonTexture2 = g_TextureG;
				isAlive1st = pickingObjectHit[0];
				isAlive2rd = pickingObjectHit[2];
				isAlive3th = pickingObjectHit[1];
			}
		}
		else
		{
			farest = baloonWorld2;
			g_baloonTexture0 = g_TextureB;
			seconedclose = baloonWorld0;
			g_baloonTexture1 = g_TextureR;
			closest = baloonWorld1;
			g_baloonTexture2 = g_TextureG;
			isAlive1st = pickingObjectHit[2];
			isAlive2rd = pickingObjectHit[0];
			isAlive3th = pickingObjectHit[1];
		}
	}
	else
	{
		if (baloon0Dist > baloon2Dist)
		{
			farest = baloonWorld1;
			g_baloonTexture0 = g_TextureG;
			seconedclose = baloonWorld0;
			g_baloonTexture1 = g_TextureR;
			closest = baloonWorld2;
			g_baloonTexture2 = g_TextureB;
			isAlive1st = pickingObjectHit[1];
			isAlive2rd = pickingObjectHit[0];
			isAlive3th = pickingObjectHit[2];
		}
		else
		{
			if (baloon2Dist > baloon1Dist)
			{
				farest = baloonWorld2;
				g_baloonTexture0 = g_TextureB;
				seconedclose = baloonWorld1;
				g_baloonTexture1 = g_TextureG;
				closest = baloonWorld0;
				g_baloonTexture2 = g_TextureR;
				isAlive1st = pickingObjectHit[2];
				isAlive2rd = pickingObjectHit[1];
				isAlive3th = pickingObjectHit[0];
			}
			else
			{
				farest = baloonWorld1;
				g_baloonTexture0 = g_TextureG;
				seconedclose = baloonWorld2;
				g_baloonTexture1 = g_TextureB;
				closest = baloonWorld0;
				g_baloonTexture2 = g_TextureR;
				isAlive1st = pickingObjectHit[1];
				isAlive2rd = pickingObjectHit[2];
				isAlive3th = pickingObjectHit[0];
			}
		}
	}



	g_baloonModel->Render(g_context);
	if (isAlive1st == 0)
	{
		g_baloonModel->SetWorldMatrix(farest);
		g_context->RSSetState(g_CCWcullMode);
		g_ShadowShader->Render(g_context, g_baloonModel, camView, camProjection, g_baloonTexture0, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());
		g_context->RSSetState(g_CWcullMode);
		g_ShadowShader->Render(g_context, g_baloonModel, camView, camProjection, g_baloonTexture0, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());
	}

	if (isAlive2rd == 0)
	{
		g_baloonModel->SetWorldMatrix(seconedclose);
		g_context->RSSetState(g_CCWcullMode);
		g_ShadowShader->Render(g_context, g_baloonModel, camView, camProjection, g_baloonTexture1, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());
		g_context->RSSetState(g_CWcullMode);
		g_ShadowShader->Render(g_context, g_baloonModel, camView, camProjection, g_baloonTexture1, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());
	}

	if (isAlive3th == 0)
	{
		g_baloonModel->SetWorldMatrix(closest);
		g_context->RSSetState(g_CCWcullMode);
		g_ShadowShader->Render(g_context, g_baloonModel, camView, camProjection, g_baloonTexture2, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());
		g_context->RSSetState(g_CWcullMode);
		g_ShadowShader->Render(g_context, g_baloonModel, camView, camProjection, g_baloonTexture2, g_upSampleTexture->GetShaderResourceView(), g_camSpotLightupSampleTexture->GetShaderResourceView(), g_dogLightupSampleTexture->GetShaderResourceView());
	}
	g_debugCube->Render(g_context, g_CubeModel, camView, camProjection);
	//g_debugLine->Render(g_context, g_dogPNTModel, camView, camProjection);


	//Present the backbuffer to the screen
	g_swapChain->Present(0, 0);
}

void RenderShadowToTexture()
{
	g_SLDepthTexture->SetRenderTarget(g_context);

	g_SLDepthTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);


	g_CubeModel->Render(g_context);
	g_depthShader->Render(g_context, g_CubeModel, Con_Light1.lightView, Con_Light1.lightProj);


	g_CubeModel2->Render(g_context);
	g_depthShader->Render(g_context, g_CubeModel2, Con_Light1.lightView, Con_Light1.lightProj);

	g_spaceroomModel->Render(g_context);
	g_depthShader->Render(g_context, g_spaceroomModel, Con_Light1.lightView, Con_Light1.lightProj);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);


}

void RenderBlackWhiteShadow()
{
	g_blackWhiteShadowTexture->SetRenderTarget(g_context);
	g_blackWhiteShadowTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	g_CubeModel->Render(g_context);
	g_blackWhiteShadowShader->Render(g_context, g_CubeModel, camView, camProjection, Con_Light1.lightView, Con_Light1.lightProj, g_SLDepthTexture->GetShaderResourceView(), Con_Light1.Pos);

	g_CubeModel2->Render(g_context);
	g_blackWhiteShadowShader->Render(g_context, g_CubeModel2, camView, camProjection, Con_Light1.lightView, Con_Light1.lightProj, g_SLDepthTexture->GetShaderResourceView(), Con_Light1.Pos);

	g_spaceroomModel->Render(g_context);
	g_blackWhiteShadowShader->Render(g_context, g_spaceroomModel, camView, camProjection, Con_Light1.lightView, Con_Light1.lightProj, g_SLDepthTexture->GetShaderResourceView(), Con_Light1.Pos);
	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void DownSampleTexture()
{
	g_downSampleTexture->SetRenderTarget(g_context);

	g_downSampleTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);
	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_smallWindow->Render(g_context);

	g_textureShader->Render(g_context, g_smallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_downSampleTexture->GetOthroMatrix(), g_blackWhiteShadowTexture->GetShaderResourceView());

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);
	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void HorizontalBlurToTexture()
{
	float screenSizeX = (float)(textureWidth / 2);
	g_horizontalBlurTexture->SetRenderTarget(g_context);
	g_horizontalBlurTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_smallWindow->Render(g_context);

	g_horizontalBlurShader->Render(g_context, g_smallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_horizontalBlurTexture->GetOthroMatrix(), g_downSampleTexture->GetShaderResourceView(), screenSizeX);

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);

}

void VerticalBlurToTexture()
{
	float screenSizeY = (float)(textureHeight / 2);
	g_verticalBlurTexture->SetRenderTarget(g_context);
	g_verticalBlurTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_smallWindow->Render(g_context);

	g_verticalBlurShader->Render(g_context, g_smallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_verticalBlurTexture->GetOthroMatrix(), g_horizontalBlurTexture->GetShaderResourceView(), screenSizeY);

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void UpSampleTexture()
{
	g_upSampleTexture->SetRenderTarget(g_context);
	g_upSampleTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the full screen ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_fullWindow->Render(g_context);

	g_textureShader->Render(g_context, g_fullWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_upSampleTexture->GetOthroMatrix(), g_verticalBlurTexture->GetShaderResourceView());

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void RenderShadowToTexture1()
{
	g_camSpotDepthTexture->SetRenderTarget(g_context);

	g_camSpotDepthTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);


	g_CubeModel->Render(g_context);
	g_depthShader1->Render(g_context, g_CubeModel, Con_Light3.lightView, Con_Light3.lightProj);


	g_CubeModel2->Render(g_context);
	g_depthShader1->Render(g_context, g_CubeModel2, Con_Light3.lightView, Con_Light3.lightProj);

	g_spaceroomModel->Render(g_context);
	g_depthShader1->Render(g_context, g_spaceroomModel, Con_Light3.lightView, Con_Light3.lightProj);

	g_dogPNTModel->Render(g_context);
	g_depthShader1->Render(g_context, g_dogPNTModel, Con_Light3.lightView, Con_Light3.lightProj);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);


}

void RenderBlackWhiteShadow1()
{
	g_camSpotBWShadowTexture->SetRenderTarget(g_context);
	g_camSpotBWShadowTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	g_CubeModel->Render(g_context);
	g_camSpotLightBWShadowShader->Render(g_context, g_CubeModel, camView, camProjection, Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);

	g_CubeModel2->Render(g_context);
	g_camSpotLightBWShadowShader->Render(g_context, g_CubeModel2, camView, camProjection, Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);

	g_spaceroomModel->Render(g_context);
	g_camSpotLightBWShadowShader->Render(g_context, g_spaceroomModel, camView, camProjection, Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);

	g_dogPNTModel->Render(g_context);
	g_camSpotLightBWShadowShader->Render(g_context, g_dogPNTModel, camView, camProjection, Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);
	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void DownSampleTexture1()
{
	g_camSpotLightdownSampleTexture->SetRenderTarget(g_context);

	g_camSpotLightdownSampleTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);
	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_camSpotLightsmallWindow->Render(g_context);

	g_camSpotLighttextureShader->Render(g_context, g_camSpotLightsmallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_camSpotLightdownSampleTexture->GetOthroMatrix(), g_camSpotBWShadowTexture->GetShaderResourceView());

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);
	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void HorizontalBlurToTexture1()
{
	float screenSizeX = (float)(textureWidth / 2);
	g_camSpotLighthorizontalBlurTexture->SetRenderTarget(g_context);
	g_camSpotLighthorizontalBlurTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_camSpotLightsmallWindow->Render(g_context);

	g_camSpotLighthorizontalBlurShader->Render(g_context, g_camSpotLightsmallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_camSpotLighthorizontalBlurTexture->GetOthroMatrix(), g_camSpotLightdownSampleTexture->GetShaderResourceView(), screenSizeX);

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void VerticalBlurToTexture1()
{
	float screenSizeY = (float)(textureHeight / 2);
	g_camSpotLightverticalBlurTexture->SetRenderTarget(g_context);
	g_camSpotLightverticalBlurTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_camSpotLightsmallWindow->Render(g_context);

	g_camSpotLightverticalBlurShader->Render(g_context, g_camSpotLightsmallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_camSpotLightverticalBlurTexture->GetOthroMatrix(), g_camSpotLighthorizontalBlurTexture->GetShaderResourceView(), screenSizeY);

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void UpSampleTexture1()
{
	g_camSpotLightupSampleTexture->SetRenderTarget(g_context);
	g_camSpotLightupSampleTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the full screen ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_camSpotLightfullWindow->Render(g_context);

	g_camSpotLighttextureShader->Render(g_context, g_camSpotLightfullWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_camSpotLightupSampleTexture->GetOthroMatrix(), g_camSpotLightverticalBlurTexture->GetShaderResourceView());

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);

}

void RenderShadowToTexture2()
{
	g_dogLightDepthTexture->SetRenderTarget(g_context);

	g_dogLightDepthTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	g_spaceroomModel->Render(g_context);
	g_depthShader2->Render(g_context, g_spaceroomModel, Con_Light2.lightView, Con_Light2.lightProj);

	g_dogPNTModel->Render(g_context);
	g_depthShader2->Render(g_context, g_dogPNTModel, Con_Light2.lightView, Con_Light2.lightProj);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);


}

void RenderBlackWhiteShadow2()
{
	g_dogLightBWShadowTexture->SetRenderTarget(g_context);
	g_dogLightBWShadowTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	g_dogPNTModel->Render(g_context);
	g_dogLightBWShadowShader->Render(g_context, g_dogPNTModel, camView, camProjection, Con_Light2.lightView, Con_Light2.lightProj, g_dogLightDepthTexture->GetShaderResourceView(), Con_Light2.Pos);
	
	g_spaceroomModel->Render(g_context);
	g_dogLightBWShadowShader->Render(g_context, g_spaceroomModel, camView, camProjection, Con_Light2.lightView, Con_Light2.lightProj, g_dogLightDepthTexture->GetShaderResourceView(), Con_Light2.Pos);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void DownSampleTexture2()
{
	g_dogLightdownSampleTexture->SetRenderTarget(g_context);

	g_dogLightdownSampleTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);
	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_dogLightsmallWindow->Render(g_context);

	g_dogLighttextureShader->Render(g_context, g_dogLightsmallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_dogLightdownSampleTexture->GetOthroMatrix(), g_dogLightBWShadowTexture->GetShaderResourceView());

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);
	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void HorizontalBlurToTexture2()
{
	float screenSizeX = (float)(textureWidth / 2);
	g_dogLighthorizontalBlurTexture->SetRenderTarget(g_context);
	g_dogLighthorizontalBlurTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_dogLightsmallWindow->Render(g_context);

	g_dogLighthorizontalBlurShader->Render(g_context, g_dogLightsmallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_dogLighthorizontalBlurTexture->GetOthroMatrix(), g_dogLightdownSampleTexture->GetShaderResourceView(), screenSizeX);

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);

}

void VerticalBlurToTexture2()
{
	float screenSizeY = (float)(textureHeight / 2);
	g_dogLightverticalBlurTexture->SetRenderTarget(g_context);
	g_dogLightverticalBlurTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the small ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_dogLightsmallWindow->Render(g_context);

	g_dogLightverticalBlurShader->Render(g_context, g_dogLightsmallWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_dogLightverticalBlurTexture->GetOthroMatrix(), g_dogLighthorizontalBlurTexture->GetShaderResourceView(), screenSizeY);

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

void UpSampleTexture2()
{
	g_dogLightupSampleTexture->SetRenderTarget(g_context);
	g_dogLightupSampleTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

	// turn off z buffe;
	g_context->OMSetDepthStencilState(g_disableDepthStencilState, 1);

	//put the full screen ortho window vertex and index buffers on graphics pipeline to prepare them for drawing
	g_dogLightfullWindow->Render(g_context);

	g_dogLighttextureShader->Render(g_context, g_dogLightfullWindow->GetIndexCount(), XMMatrixIdentity(), camBaseView, g_dogLightupSampleTexture->GetOthroMatrix(), g_dogLightverticalBlurTexture->GetShaderResourceView());

	// turn on z buffe;
	g_context->OMSetDepthStencilState(g_enableDepthStencilState, 1);

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);

}

void RenderEnvironmentCubeTexture()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		//render shadows from environment camera
		//dog shadow
		g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		g_envDogBWShadowTexture->SetRenderTarget(g_context);
		g_envDogBWShadowTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

		g_dogPNTModel->Render(g_context);
		g_envDogLightBWShadowShader->Render(g_context, g_dogPNTModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light2.lightView, Con_Light2.lightProj, g_dogLightDepthTexture->GetShaderResourceView(), Con_Light2.Pos);

		g_spaceroomModel->Render(g_context);
		g_envDogLightBWShadowShader->Render(g_context, g_spaceroomModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light2.lightView, Con_Light2.lightProj, g_dogLightDepthTexture->GetShaderResourceView(), Con_Light2.Pos);

		
		//flashlight shadows
		g_envFlashLightBWShadowTexture->SetRenderTarget(g_context);
		g_envFlashLightBWShadowTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

		g_CubeModel->Render(g_context);
		g_envFlashLightBWShadowShader->Render(g_context, g_CubeModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);

		g_CubeModel2->Render(g_context);
		g_envFlashLightBWShadowShader->Render(g_context, g_CubeModel2, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);

		g_spaceroomModel->Render(g_context);
		g_envFlashLightBWShadowShader->Render(g_context, g_spaceroomModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);

		g_dogPNTModel->Render(g_context);
		g_envFlashLightBWShadowShader->Render(g_context, g_dogPNTModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light3.lightView, Con_Light3.lightProj, g_camSpotDepthTexture->GetShaderResourceView(), Con_Light3.Pos);

		//cubes shadows
		g_envCubesBWShadowTexture->SetRenderTarget(g_context);
		g_envCubesBWShadowTexture->ClearRenderTarget(g_context, 0.0f, 0.0f, 0.0f, 1.0f);

		g_CubeModel->Render(g_context);
		g_envCubesLightBWShadowShader->Render(g_context, g_CubeModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light1.lightView, Con_Light1.lightProj, g_SLDepthTexture->GetShaderResourceView(), Con_Light1.Pos);

		g_CubeModel2->Render(g_context);
		g_envCubesLightBWShadowShader->Render(g_context, g_CubeModel2, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light1.lightView, Con_Light1.lightProj, g_SLDepthTexture->GetShaderResourceView(), Con_Light1.Pos);

		g_spaceroomModel->Render(g_context);
		g_envCubesLightBWShadowShader->Render(g_context, g_spaceroomModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), Con_Light1.lightView, Con_Light1.lightProj, g_SLDepthTexture->GetShaderResourceView(), Con_Light1.Pos);

		//draw the scene
		g_environmentClass->SetRenderTarget(g_context, g_environmentClass->GetRenderTargetView()[i]);
		g_environmentClass->ClearRenderTarget(g_context, g_environmentClass->GetRenderTargetView()[i], 0.75f, 0.75f, 0.75f, 1.0f);

		g_skyBoxClass->Render(g_context);
		g_skyBoxShaderClass->Render(g_context, g_skyBoxClass->GetIndexCount(), g_skyBoxClass->GetWorldMatrix(), g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_skyBoxClass->GetShaderResourceView());

		g_CubeModel->Render(g_context);
		g_ShadowShader->Render(g_context, g_CubeModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_cubeTexture, g_envCubesBWShadowTexture->GetShaderResourceView(), g_envFlashLightBWShadowTexture->GetShaderResourceView(), g_envDogBWShadowTexture->GetShaderResourceView());

		g_CubeModel2->Render(g_context);
		g_ShadowShader->Render(g_context, g_CubeModel2, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_cubeTexture, g_envCubesBWShadowTexture->GetShaderResourceView(), g_envFlashLightBWShadowTexture->GetShaderResourceView(), g_envDogBWShadowTexture->GetShaderResourceView());

		//
		g_spaceroomModel->Render(g_context);
		g_ShadowShader->Render(g_context, g_spaceroomModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), NULL, g_envCubesBWShadowTexture->GetShaderResourceView(), g_envFlashLightBWShadowTexture->GetShaderResourceView(), g_envDogBWShadowTexture->GetShaderResourceView());

		g_flashlightModel->Render(g_context);
		g_ShadowShader->Render(g_context, g_flashlightModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), NULL, g_envCubesBWShadowTexture->GetShaderResourceView(), g_envFlashLightBWShadowTexture->GetShaderResourceView(), g_envDogBWShadowTexture->GetShaderResourceView());

		g_dogPNTModel->Render(g_context);
		if (isWireMode)
			g_context->RSSetState(g_RSCullNoneFW);
		g_PhongShader->Render(g_context, g_dogPNTModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_dogTexture, g_envFlashLightBWShadowTexture->GetShaderResourceView(), g_envDogBWShadowTexture->GetShaderResourceView(), true, false, isPhongTessel);

		XMFLOAT4 tempCamPos;
		XMStoreFloat4(&tempCamPos, camPosition);

		g_terrainClass->Render(g_context);
		g_terrainShaderClass->Render(g_context, g_terrainClass->GetIndexCount(), g_terrainClass->GetWorldMatrix(), g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_terrainClass->GetTexture(), g_terrainClass->GetNormalMap(), true, true, tempCamPos);
		g_context->RSSetState(g_RSCullNone);


		g_context->OMSetBlendState(g_transparency, blendFactor, 0xffffffff);

		XMVECTOR baloon0 = XMVectorZero();
		XMVECTOR baloon1 = XMVectorZero();
		XMVECTOR baloon2 = XMVectorZero();
		XMVECTOR cubeCamPos = XMLoadFloat3(&g_environmentClass->GetCubeCenter());

		baloon0 = XMVector3TransformCoord(baloon0, baloonWorld0);
		float distX = XMVectorGetX(baloon0) - XMVectorGetX(cubeCamPos);
		float distY = XMVectorGetY(baloon0) - XMVectorGetY(cubeCamPos);
		float distZ = XMVectorGetZ(baloon0) - XMVectorGetZ(cubeCamPos);
		float baloon0Dist = distX*distX + distY*distY + distZ*distZ;

		baloon1 = XMVector3TransformCoord(baloon1, baloonWorld1);
		distX = XMVectorGetX(baloon1) - XMVectorGetX(cubeCamPos);
		distY = XMVectorGetY(baloon1) - XMVectorGetY(cubeCamPos);
		distZ = XMVectorGetZ(baloon1) - XMVectorGetZ(cubeCamPos);
		float baloon1Dist = distX*distX + distY*distY + distZ*distZ;

		baloon2 = XMVector3TransformCoord(baloon2, baloonWorld2);
		distX = XMVectorGetX(baloon2) - XMVectorGetX(cubeCamPos);
		distY = XMVectorGetY(baloon2) - XMVectorGetY(cubeCamPos);
		distZ = XMVectorGetZ(baloon2) - XMVectorGetZ(cubeCamPos);
		float baloon2Dist = distX*distX + distY*distY + distZ*distZ;


		XMMATRIX closest;
		XMMATRIX seconedclose;
		XMMATRIX farest;

		if (baloon0Dist > baloon1Dist)
		{
			if (baloon0Dist > baloon2Dist)
			{
				if (baloon1Dist > baloon2Dist)
				{
					farest = baloonWorld0;
					g_baloonTexture0 = g_TextureR;

					seconedclose = baloonWorld1;
					g_baloonTexture1 = g_TextureG;

					closest = baloonWorld2;
					g_baloonTexture2 = g_TextureB;

					isAlive1st = pickingObjectHit[0];
					isAlive2rd = pickingObjectHit[1];
					isAlive3th = pickingObjectHit[2];

				}
				else
				{
					farest = baloonWorld0;
					g_baloonTexture0 = g_TextureR;
					seconedclose = baloonWorld2;
					g_baloonTexture1 = g_TextureB;
					closest = baloonWorld1;
					g_baloonTexture2 = g_TextureG;
					isAlive1st = pickingObjectHit[0];
					isAlive2rd = pickingObjectHit[2];
					isAlive3th = pickingObjectHit[1];
				}
			}
			else
			{
				farest = baloonWorld2;
				g_baloonTexture0 = g_TextureB;
				seconedclose = baloonWorld0;
				g_baloonTexture1 = g_TextureR;
				closest = baloonWorld1;
				g_baloonTexture2 = g_TextureG;
				isAlive1st = pickingObjectHit[2];
				isAlive2rd = pickingObjectHit[0];
				isAlive3th = pickingObjectHit[1];
			}
		}
		else
		{
			if (baloon0Dist > baloon2Dist)
			{
				farest = baloonWorld1;
				g_baloonTexture0 = g_TextureG;
				seconedclose = baloonWorld0;
				g_baloonTexture1 = g_TextureR;
				closest = baloonWorld2;
				g_baloonTexture2 = g_TextureB;
				isAlive1st = pickingObjectHit[1];
				isAlive2rd = pickingObjectHit[0];
				isAlive3th = pickingObjectHit[2];
			}
			else
			{
				if (baloon2Dist > baloon1Dist)
				{
					farest = baloonWorld2;
					g_baloonTexture0 = g_TextureB;
					seconedclose = baloonWorld1;
					g_baloonTexture1 = g_TextureG;
					closest = baloonWorld0;
					g_baloonTexture2 = g_TextureR;
					isAlive1st = pickingObjectHit[2];
					isAlive2rd = pickingObjectHit[1];
					isAlive3th = pickingObjectHit[0];
				}
				else
				{
					farest = baloonWorld1;
					g_baloonTexture0 = g_TextureG;
					seconedclose = baloonWorld2;
					g_baloonTexture1 = g_TextureB;
					closest = baloonWorld0;
					g_baloonTexture2 = g_TextureR;
					isAlive1st = pickingObjectHit[1];
					isAlive2rd = pickingObjectHit[2];
					isAlive3th = pickingObjectHit[0];
				}
			}
		}

		g_baloonModel->Render(g_context);
		if (isAlive1st == 0)
		{
			g_baloonModel->SetWorldMatrix(farest);
			g_context->RSSetState(g_CCWcullMode);
			g_ShadowShader->Render(g_context, g_baloonModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_baloonTexture0, NULL, NULL, NULL);
			g_context->RSSetState(g_CWcullMode);
			g_ShadowShader->Render(g_context, g_baloonModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_baloonTexture0, NULL, NULL, NULL);

		}
		if (isAlive2rd == 0)
		{
			g_baloonModel->SetWorldMatrix(seconedclose);
			g_context->RSSetState(g_CCWcullMode);
			g_ShadowShader->Render(g_context, g_baloonModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_baloonTexture1, NULL, NULL, NULL);
			g_context->RSSetState(g_CWcullMode);
			g_ShadowShader->Render(g_context, g_baloonModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_baloonTexture1, NULL, NULL, NULL);
		}
		if (isAlive3th == 0)
		{
			g_baloonModel->SetWorldMatrix(closest);
			g_context->RSSetState(g_CCWcullMode);
			g_ShadowShader->Render(g_context, g_baloonModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_baloonTexture2, NULL, NULL, NULL);
			g_context->RSSetState(g_CWcullMode);
			g_ShadowShader->Render(g_context, g_baloonModel, g_environmentClass->GetViewMatrix()[i], g_environmentClass->GetProjectionMatrix(), g_baloonTexture2, NULL, NULL, NULL);
		}
		g_context->OMSetBlendState(NULL, NULL, 0xffffffff);
		g_context->RSSetState(g_RSCullNone);
	}

	//set the render target back
	g_context->OMSetRenderTargets(1, &g_renderTargetView, g_DepthStencilView);

	//set the viewport back
	D3D11_VIEWPORT vp = { 0 };
	vp.Width = (FLOAT)screenWidth;
	vp.Height = (FLOAT)screenHeight;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_context->RSSetViewports(1, &vp);
}

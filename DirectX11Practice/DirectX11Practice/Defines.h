#pragma once
#include <DirectXMath.h>
#include <Windows.h>
#include <sstream>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx11async.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include "GameTimer.h"
#include <dinput.h>
#include <vector>
#include <fstream>
#include <istream>


using namespace DirectX;

//vertex struct
struct s_Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT2 texCoord; //UV
	XMFLOAT3 Normal;  // z-axis
	XMFLOAT3 Tangent;  // x-axis (V-axis)
	XMFLOAT3 BiTangent; // y-axis
};


//Light struct
struct s_Light
{
	s_Light() { ZeroMemory(this, sizeof(this)); }
	XMFLOAT4 Dir;
	XMFLOAT3 Attenuation;
	float Cone;
	XMFLOAT4 Pos;
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMMATRIX lightView;
	XMMATRIX lightProj;
};

//constant buffer struct
struct s_ConstantBuffer
{
	s_ConstantBuffer() { ZeroMemory(this, sizeof(this)); }
	XMMATRIX WVP;
	XMMATRIX World;
	XMMATRIX lightView;
	XMMATRIX lightProjection;
	XMFLOAT4 Diffuse;
	XMVECTOR CamPos;
	BOOL HasTexture = false;
	BOOL HasNormalMap = false;
	BOOL IsPhongTessel = false;
};

//Light constant buffer struct
struct s_LightConstantBuffer
{
	s_Light Light[5];
};


struct s_MeshData
{
	std::vector<s_Vertex> Vertices;
	std::vector<UINT> Indices;
};

struct s_SurfaceMaterial
{
	std::wstring MatName;
	XMFLOAT4 Diffuse;
	int TexArrayIndex;
	int NormalMapTexArrayIndex;
	bool HasNormalMap;
	bool HasTexture;
	bool Transparent;
};


struct s_OBJModel
{
	std::vector<int> SubsetsIndexStart;
	std::vector<int> SubsetsTexture;
	std::vector<std::wstring> TextureNameArray;
	std::vector<ID3D11ShaderResourceView*>	SRV;
	std::vector<s_SurfaceMaterial>	Material;
	XMMATRIX			World = XMMatrixIdentity();
	ID3D11Buffer*		VB = NULL;
	ID3D11Buffer*		IB = NULL;
	ID3D11BlendState*	Transparency = NULL;
	int					Subsets = 0;
	//optional vector for picking objcet; for CPU calculating
	std::vector<XMFLOAT3> VertPosArray;
	std::vector<DWORD> VertIndexArray;
};

struct s_HeightMapInfo
{
	int TerrainWidth;
	int TerrainHeight;
	XMFLOAT3* HieghtMap; //Array to store terrain's vertices positions 
	XMFLOAT3* HieghtMapNormal; //Array to store terrain's normal vector 
};

struct s_InstanceType
{
	XMFLOAT3 position;
};
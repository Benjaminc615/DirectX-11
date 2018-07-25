#pragma once
#include "Defines.h"

class SpotLightClass
{
private:

	XMMATRIX m_viewMatrix;
	XMMATRIX m_projectMatrix;

	XMFLOAT4 m_position;
	XMFLOAT4 m_lookAt;  //direct
	XMFLOAT4 m_direction;
	XMFLOAT4 m_ambient;
	XMFLOAT4 m_diffuse;
	XMFLOAT3 m_attenuation;
	float m_cone;

public:
	SpotLightClass();
	~SpotLightClass();

	void SetAmbientColor(float r, float g, float b, float a);
	void SetDiffuseColor(float r, float g, float b, float a);
	void SetPosition(float x, float y, float z, float w);
	void SetLookAt(float x, float y, float z, float w);
	void SetAttenuation(float d, float d2, float d3);
	void SetCone(float cone);

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();
	XMFLOAT4 GetPosition();

	XMFLOAT3 GetAttenuation();
	float GetCone();

	void GenerateViewMatrix();
	void GenerateProjectMatrix(float screenDepth, float screenNear);

	XMMATRIX GetViewMatrix();
	XMMATRIX GetPorjectMatrix();


};

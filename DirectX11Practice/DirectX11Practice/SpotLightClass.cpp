#include "SpotLightClass.h"

SpotLightClass::SpotLightClass()
{
}

SpotLightClass::~SpotLightClass()
{
}

void SpotLightClass::SetAmbientColor(float r, float g, float b, float a)
{
	m_ambient = XMFLOAT4(r, g, b, a);
}

void SpotLightClass::SetDiffuseColor(float r, float g, float b, float a)
{
	m_diffuse = XMFLOAT4(r, g, b, a);
}

void SpotLightClass::SetPosition(float x, float y, float z, float w)
{
	m_position = XMFLOAT4(x, y, z, w);
}

void SpotLightClass::SetLookAt(float x, float y, float z, float w)
{
	m_lookAt = XMFLOAT4(x, y, z, w);
}

void SpotLightClass::SetAttenuation(float d, float d2, float d3)
{
	m_attenuation = XMFLOAT3(d, d2, d3);
}

void SpotLightClass::SetCone(float cone)
{
	m_cone = cone;
}

XMFLOAT4 SpotLightClass::GetAmbientColor()
{
	return m_ambient;
}

XMFLOAT4 SpotLightClass::GetDiffuseColor()
{
	return m_diffuse;
}

XMFLOAT4 SpotLightClass::GetPosition()
{
	return m_position;
}

XMFLOAT3 SpotLightClass::GetAttenuation()
{
	return m_attenuation;
}

float SpotLightClass::GetCone()
{
	return m_cone;
}

void SpotLightClass::GenerateViewMatrix()
{
	XMVECTOR up;
	XMVECTOR pos;
	XMVECTOR at;

	up.m128_f32[0] = 0.0f;
	up.m128_f32[1] = 1.0f;
	up.m128_f32[2] = 0.0f;
	up.m128_f32[3] = 0.0f;
	
	pos = XMVectorSet(m_position.x, m_position.y, m_position.z, m_position.w);
	at = XMVectorSet(m_lookAt.x, m_lookAt.y, m_lookAt.z, m_position.w);

	m_viewMatrix= XMMatrixLookAtLH(pos, at, up);
}

void SpotLightClass::GenerateProjectMatrix(float screenDepth, float screenNear)
{
	float fieldOfView, screenAspect;
	fieldOfView = (float)XM_PI / 2.0f;
	screenAspect = 1.0f;

	XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenNear);
}

XMMATRIX SpotLightClass::GetViewMatrix()
{
	return m_viewMatrix;
}

XMMATRIX SpotLightClass::GetPorjectMatrix()
{
	return m_projectMatrix;
}
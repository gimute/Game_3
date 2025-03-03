#include "stdafx.h"
#include "LightManager.h"

//ライトを管理するクラス

void LightManager::NewPointLight(const Vector3 pos, const Vector3 color, const float range)
{
	m_pointLights.push_back(std::make_unique<PointLight>());
	m_pointLights.back()->Init();
	m_pointLights.back()->SetPosition(pos * 0.4f);
	m_pointLights.back()->SetColor(color);
	m_pointLights.back()->SetRange(range);
	m_pointLights.back()->SetAffectPowParam(2.0f);
	m_pointLights.back()->Update();
	
}

void LightManager::Update()
{
	for (int i = 0; i < m_pointLights.size(); i++)
	{
		m_pointLights[i]->Update();
	}
}

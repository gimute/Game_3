#pragma once


//ライトを管理するクラス

class LightManager
{
public:
	void NewPointLight(const Vector3 pos, const Vector3 color, const float range);

	void Update();

private:
	std::vector<std::unique_ptr<PointLight>> m_pointLights;
};


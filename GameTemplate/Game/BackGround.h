#pragma once

//バックグラウンドクラス
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	void SetScale(const Vector3 scale)
	{
		m_scale = scale;
	}

	void SetPosition(const Vector3 pos)
	{
		m_position = pos;
	}

private:
	ModelRender m_bgModel;
	PhysicsStaticObject m_PhysicsStaticObject;
	Vector3 m_scale = Vector3::One;
	Vector3 m_position = Vector3::Zero;
};


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

private:
	ModelRender m_bgModel;
	PhysicsStaticObject m_PhysicsStaticObject;
};


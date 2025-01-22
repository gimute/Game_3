#pragma once

//�o�b�N�O���E���h�N���X
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


#pragma once

//�o�b�N�O���E���h�N���X
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	ModelRender m_bgModel;

};


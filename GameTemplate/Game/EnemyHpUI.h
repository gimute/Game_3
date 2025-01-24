#pragma once

//hpUI

namespace {
	const float ENEMY_HP_UI_SPRITE_WIGHT = 400;
	const float ENEMY_HP_UI_SPRITE_HEIGHT = 50;
	const Vector3 ENEMY_HP_UI_SCALE = { 0.2f,0.2f,1.0f };
}

class Enemy;

class EnemyHpUI : public IGameObject
{
public:
	EnemyHpUI();
	~EnemyHpUI();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void Init(Enemy* enemy, float maxHP);

	/// <summary>
	/// �_���[�W
	/// </summary>
	/// <param name="damageAmount"></param>
	void Damage(float damageAmount)
	{
		m_nowHp -= damageAmount;
	}

	/// <summary>
	/// ����HP��ݒ�
	/// </summary>
	/// <returns></returns>
	float GetNowHp()
	{
		return m_nowHp;
	}

private:
	SpriteRender m_hpBarSp;
	SpriteRender m_backHpBarSp;

	Enemy* m_enemy;

	float m_maxHp = 0.0f;	//�ő�HP
	float m_nowHp = 0.0f;	//����HP

	float m_RemainingHPProportion = 1.0f;	//�c��HP����

	Vector3 m_screenPos;

};


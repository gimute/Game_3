#pragma once

//�v���C���[��HPUI

namespace {
	const float PLAYER_HP_UI_SPRITE_WIGHT = 400;
	const float PLAYER_HP_UI_SPRITE_HEIGHT = 50;
}

class Player;

class PlayerHpUI : public IGameObject
{
public:
	PlayerHpUI() {};
	~PlayerHpUI() {};
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="maxHP">�ő�HP</param>
	void Init(float maxHP);

	/// <summary>
	/// �ő�HP��ݒ�
	/// </summary>
	/// <param name="maxHp"></param>
	void SetMaxHp(float maxHp)
	{
		m_maxHp = maxHp;
	}

	/// <summary>
	/// ����HP��ݒ�
	/// </summary>
	/// <returns></returns>
	float GetNowHp()
	{
		return m_nowHp;
	}

	/// <summary>
	/// ��
	/// </summary>
	/// <param name="healAmount"></param>
	void Heal(float healAmount)
	{
		m_nowHp += healAmount;
	}

	/// <summary>
	/// �_���[�W
	/// </summary>
	/// <param name="damageAmount"></param>
	void Damage(float damageAmount)
	{
		m_nowHp -= damageAmount;
	}

private:
	Player* m_player = nullptr;	//�v���C���[
	SpriteRender m_hpSprite;	//HP�̃X�v���C�g
	SpriteRender m_backHpBarSp;

	float m_maxHp = 0.0f;	//�ő�HP
	float m_nowHp = 0.0f;	//����HP

	float RemainingHPProportion = 1.0f;	//�c��HP����
};


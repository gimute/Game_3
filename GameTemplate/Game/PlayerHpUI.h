#pragma once

//プレイヤーのHPUI

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
	/// 初期化
	/// </summary>
	/// <param name="maxHP">最大HP</param>
	void Init(float maxHP);

	/// <summary>
	/// 最大HPを設定
	/// </summary>
	/// <param name="maxHp"></param>
	void SetMaxHp(float maxHp)
	{
		m_maxHp = maxHp;
	}

	/// <summary>
	/// 現在HPを設定
	/// </summary>
	/// <returns></returns>
	float GetNowHp()
	{
		return m_nowHp;
	}

	/// <summary>
	/// 回復
	/// </summary>
	/// <param name="healAmount"></param>
	void Heal(float healAmount)
	{
		m_nowHp += healAmount;
	}

	/// <summary>
	/// ダメージ
	/// </summary>
	/// <param name="damageAmount"></param>
	void Damage(float damageAmount)
	{
		m_nowHp -= damageAmount;
	}

private:
	Player* m_player = nullptr;	//プレイヤー
	SpriteRender m_hpSprite;	//HPのスプライト
	SpriteRender m_backHpBarSp;

	float m_maxHp = 0.0f;	//最大HP
	float m_nowHp = 0.0f;	//現在HP

	float RemainingHPProportion = 1.0f;	//残りHP割合
};


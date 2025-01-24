#include "stdafx.h"
#include "PlayerHpUI.h"

#include "Player.h"

//プレイヤーのHPUI

bool PlayerHpUI::Start()
{
	m_player = FindGO<Player>("player");

	m_hpSprite.Init("Assets/sprite/hpBar_2.DDS", PLAYER_HP_UI_SPRITE_WIGHT, PLAYER_HP_UI_SPRITE_HEIGHT);

	m_backHpBarSp.Init("Assets/sprite/hpBar_2.DDS", PLAYER_HP_UI_SPRITE_WIGHT, PLAYER_HP_UI_SPRITE_HEIGHT);
	m_backHpBarSp.SetMulColor({ 0.0f,0.0f,0.0f,1.0f });

	m_hpSprite.SetPivot({ 0.0f,1.0f });
	m_hpSprite.SetPosition({ -780.0f,430.0f,0.0f });
	m_hpSprite.Update();

	m_backHpBarSp.SetPivot({ 0.0f,1.0f });
	m_backHpBarSp.SetPosition({ -780.0f,430.0f,0.0f });
	m_backHpBarSp.Update();


	return true;
}

void PlayerHpUI::Init(float maxHP)
{
	//HPの設定
	m_maxHp = maxHP;
	m_nowHp = maxHP;

	//残りHP%
	RemainingHPProportion = 1.0f;
}

void PlayerHpUI::Update()
{
	RemainingHPProportion = m_nowHp / m_maxHp;

	m_hpSprite.SetScale({ RemainingHPProportion,1.0f,1.0f });
	m_hpSprite.Update();

}

void PlayerHpUI::Render(RenderContext& rc)
{
	m_backHpBarSp.Draw(rc);
	m_hpSprite.Draw(rc);
}



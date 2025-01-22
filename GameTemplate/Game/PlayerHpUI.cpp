#include "stdafx.h"
#include "PlayerHpUI.h"

#include "Player.h"

//プレイヤーのHPUI

bool PlayerHpUI::Start()
{
	m_player = FindGO<Player>("player");

	m_hpSprite.Init("Assets/sprite/hpBar_1.DDS", HP_UI_SPRITE_WIGHT, HP_UI_SPRITE_HEIGHT);

	/*m_hpSprite.Init(spInitData);

	m_hpSprite.SetScale({ 0.5f, 0.5f, 0.5f });*/
	m_hpSprite.SetPivot({ 0.0f,1.0f });
	m_hpSprite.SetPosition({ -780.0f,430.0f,0.0f });
	m_hpSprite.Update();

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
	m_hpSprite.Draw(rc);
}



#include "stdafx.h"
#include "EnemyHpUI.h"

#include "Enemy.h"
//hpui

EnemyHpUI::EnemyHpUI()
{
}

EnemyHpUI::~EnemyHpUI()
{
}

bool EnemyHpUI::Start()
{
	m_hpBarSp.Init("Assets/sprite/hpBar_2.DDS", ENEMY_HP_UI_SPRITE_WIGHT, ENEMY_HP_UI_SPRITE_HEIGHT);
	m_backHpBarSp.Init("Assets/sprite/hpBar_2.DDS", ENEMY_HP_UI_SPRITE_WIGHT, ENEMY_HP_UI_SPRITE_HEIGHT);
	m_backHpBarSp.SetMulColor({ 0.0f,0.0f,0.0f,1.0f });

	m_hpBarSp.SetPivot({ 0.0f,1.0f });
	m_hpBarSp.SetScale(ENEMY_HP_UI_SCALE);
	m_backHpBarSp.SetPivot({ 0.0f,1.0f });
	m_backHpBarSp.SetScale(ENEMY_HP_UI_SCALE);

	return true;
}

void EnemyHpUI::Update()
{
	//HPバーをエネミーの上に表示する処理
	Vector3 uiPos;
	uiPos = m_enemy->GetPosition();
	uiPos.y += 150.0f;

	g_camera3D->CalcScreenPositionFromWorldPosition(m_screenPos, uiPos);

	m_screenPos.x -= ENEMY_HP_UI_SPRITE_WIGHT * ENEMY_HP_UI_SCALE.x / 2.0f;
	m_screenPos.y -= ENEMY_HP_UI_SPRITE_HEIGHT * ENEMY_HP_UI_SCALE.y / 2.0f;

	m_hpBarSp.SetPosition({ m_screenPos.x, m_screenPos.y });
	m_backHpBarSp.SetPosition({ m_screenPos.x, m_screenPos.y });

	//残りHP割合によってバーを縮める処理
	m_RemainingHPProportion = m_nowHp / m_maxHp;
	
	float spriteXScale = ENEMY_HP_UI_SCALE.x * m_RemainingHPProportion;

	m_hpBarSp.SetScale({ spriteXScale,ENEMY_HP_UI_SCALE.y,ENEMY_HP_UI_SCALE.z });

	m_hpBarSp.Update();
	m_backHpBarSp.Update();
}

void EnemyHpUI::Init(Enemy* enemy, float maxHP)
{
	m_enemy = enemy;

	//HPの設定
	m_maxHp = maxHP;
	m_nowHp = maxHP;

	//残りHP%
	m_RemainingHPProportion = 1.0f;
}

void EnemyHpUI::Render(RenderContext& rc)
{
	//カメラより前にあれば描画する
	if (m_screenPos.z >= 0.0f)
	{
		m_backHpBarSp.Draw(rc);
		m_hpBarSp.Draw(rc);
	}
	
}

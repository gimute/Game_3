#pragma once

//エネミーの移動速度などのパラメーターの定数まとめ

namespace {
	const float ENEMY_WALK_SPEED = 100.0f;
	const float ENEMY_DASH_SPEED = 200.0f;
	const float ENEMY_GUARDWALK_SPEED = 75.0f;

	const char* ENEMY_ATTACK_COLLISION_NAME = { "enemy_attack" };			//エネミーの攻撃コリジョンの名前
	const char* ENEMY_SIDE_ATTACK_NAME = { "enemy_SideAttack" };			//エネミーの横攻撃を示す文字列
	const char* ENEMY_VERTICAL_ATTACK_NAME = { "enemy_VerticalAttack" };	//エネミーの縦攻撃を示す文字列
	const wchar_t* ENEMY_ATTACK_COLLISION_BONE_NAME = L"mixamorig_Sword_joint"; //攻撃判定コリジョンを生成するボーンの名前

}

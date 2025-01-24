#pragma once
//定数まとめ

namespace {
	const wchar_t* PLAYER_ATTACK_COLLISION_BONE_NAME = L"mixamorig_Sword_joint"; //攻撃判定コリジョンを生成するボーンの名前
	const char* PLAYER_ATTACK_COLLISION_NAME = { "player_attack" };			//エネミーの攻撃コリジョンの名前

	//剣のサイズ
	//zが剣の長さにあたる
	const Vector3 PLAYER_SOWLD_SIZE = { 10.0f,10.0f,50.0f };
}

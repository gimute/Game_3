#pragma once
//プレイヤー関係の定数まとめ

namespace {
	const wchar_t* PLAYER_ATTACK_COLLISION_BONE_NAME = L"mixamorig_Sword_joint"; //攻撃判定コリジョンを生成するボーンの名前
	const char* PLAYER_ATTACK_COLLISION_NAME = { "player_attack" };			//エネミーの攻撃コリジョンの名前
	const char* PLAYER_JUSTDODGE_ATTACK_COLLISION_INFORMATION = { "rush_attack" };	//ジャスト回避攻撃コリジョンに付与する追加情報

	//歩きのスピード
	const float WALK_SPEED = 150.0f;

	//剣のサイズ
	//zが剣の長さにあたる
	const Vector3 PLAYER_SOWLD_SIZE = { 10.0f,10.0f,50.0f };

	//ガードコリジョンのプレイヤーからずらす量、zはプレイヤーの正面方向にどれくらいずらすかの量
	const Vector3 PLAYER_GUARD_COLLISION_POS = { 0.0f, 70.0f, 30.0f };

	//キーバインド
	const EnButton PLAYER_GUARD_BUTTON = enButtonLB1;	//ガードボタン
	const EnButton PLAYER_ATTACK_BUTTON = enButtonX;	//攻撃ボタン
	const EnButton PLAYER_JUMP_BUTTON = enButtonB;	//ジャンプボタン
	const EnButton PLAYER_RUN_BUTTON = enButtonA;	//ダッシュボタン

}

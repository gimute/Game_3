#pragma once

//プレイヤーステート

enum EnPlayerState {
	enPlayerIdle,		//待機
	enPlayerWalk,		//歩き
	enPlayerAttack,	//攻撃
	enPlayerGuard,	//ガード
	enPlayerDodge,		//回避
	enPlayerReceiveDamage,	//被ダメージ
	enPlayerJustDodgeAttack,	//ジャスト回避後のラッシュ攻撃
	enPlayerDie,		//しぼう
};

//アニメーションイベント
enum EnPlayerAnimationEvent {
	enPlayerAnimationEvent_AttackStart,
	enPlayerAnimationEvent_AttackEnd,
	enPlayerAnimationEvent_MoveEnd,
	enPlayerAnimationEvent_None
};
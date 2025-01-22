#pragma once

//プレイヤーステート

enum EnPlayerState {
	enIdle,		//待機
	enWalk,		//歩き
	enAttack,	//攻撃
	enGuard,	//ガード
	enDodge,		//回避
	enReceiveDamage,	//被ダメージ
	enJustDodgeAttack,	//ジャスト回避後のラッシュ攻撃
	enDie,		//しぼう
};

//アニメーションイベント
enum EnPlayerAnimationEvent {
	enPlayerAnimationEvent_AttackStart,
	enPlayerAnimationEvent_AttackEnd,
	enPlayerAnimationEvent_None
};
#pragma once

//エネミーステート

enum EnEnemyState
{
	enContinue,		//ステートを継続
	enEnemyIdle,	//待機
	enEnemyWiteAndSee,	//様子見
	enEnemyAttackPrepare, //攻撃準備
	enEnemyJumpSlash,	//ジャンプ切り
	enEnemySideSlash,	//横切り
	enEnemyReceiveDamage,	//被ダメージ
	enEnemyDie,			//死亡
};

//アニメーションイベント
enum EnEnemyAnimationEvent {
	enEnemyAnimationEvent_AttackStart,
	enEnemyAnimationEvent_AttackEnd,
	enEnemyAnimationEvent_None
};
#pragma once

//エネミーステート

enum EnEnemyState
{
	enEnemyIdle,	//待機
	enEnemyWiteAndSee,	//様子見
	enEnemyAttackPrepare, //攻撃準備
	enEnemyJumpSlash,	//ジャンプ切り
	enEnemySideSlash,	//横切り
};
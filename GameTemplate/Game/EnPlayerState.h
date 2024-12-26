#pragma once

//プレイヤーステート

enum EnPlayerState {
	enIdle,		//待機
	enWalk,		//歩き
	enAttack,	//攻撃
	enGuard,	//ガード
	enDodge		//回避
};
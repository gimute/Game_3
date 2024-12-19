#pragma once

//ステート

enum EnPlayerState {
	enIdle,		//待機
	enWalk,		//歩き
	enAttack,	//攻撃
	enGuard,	//ガード
	enBackflip		//後ろ回避
};
#pragma once

#include "EnPlayerState.h"


//プレイヤーステートの基底クラス

// ステートパターン？をやってみる
// 自分の理解だと、ステートを持つ何らかのオブジェクト(今回はプレイヤー)の処理をステートごとにクラスにして分けて、
// その処理をポリモーフィズム的なあれで、オブジェクトに持たせるステートクラスをとっかえひっかえ入れ替える形でコードを書くこと、みたいなイメージ
//  
// ステートごとの処理を分けて書くのでそれぞれのステートでどういう処理をしてるのか把握しやすく
// 新しくステートを追加する時に他のステートの処理とごっちゃになったりせず追加しやすい(if文とかの分岐処理で制御するとめっちゃわかりにくくなる)

class Player;

class IPlayerState
{
public:
	//ステートに遷移するときに行う処理
	virtual void Start(Player* player) {};
	//他のステートに遷移するときに行う処理
	virtual void End(Player* player) {};

	//移動処理
	virtual void Move(Vector3& position, CharacterController& charaCon) {};
	//回転処理
	virtual void Rotation(Quaternion& rotation) {};
	//アニメーションの再生
	virtual void AnimationPlay(ModelRender& model) {};
	//ステート遷移
	virtual EnPlayerState StateTransition() { return enIdle; };
	//当たり判定処理
	virtual void Collision(const Vector3& position, ModelRender& model) {};

};


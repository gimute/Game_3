#include "stdafx.h"
#include "PlayerStateJustDodgeAttack.h"

#include "Player.h"
#include "Enemy.h"

#include "PlayerParameter.h"

//�X�e�[�g

void PlayerStateJustDodgeAttack::Start(Player* player)
{
	g_gameTime->SetTimeMulValue(0.5f);

	player->GetModel()->PlayAnimation(Player::enAnimationClip_Walk, 0.1f);


	m_attackFlowState = enEnemyApproach;

	//�U���R���W�����𐶐�����{�[����ID���擾
	m_attackBoneID = player->GetModel()->FindBoneID(PLAYER_ATTACK_COLLISION_BONE_NAME);

	//�U���R���W��������
	m_attackCollision = NewGO<CollisionObject>(0, "playerattack");
	m_attackCollision->CreateBox(player->GetPosition(), Quaternion::Identity, PLAYER_SOWLD_SIZE);
	m_attackCollision->SetName(PLAYER_ATTACK_COLLISION_NAME);
	m_attackCollision->SetAdditionalInformation(PLAYER_JUSTDODGE_ATTACK_COLLISION_INFORMATION);
	m_attackCollision->SetIsEnableAutoDelete(false);

	m_enemy = player->GetTargetEnemy();
}

void PlayerStateJustDodgeAttack::End(Player* player)
{
	DeleteGO(m_attackCollision);

	g_gameTime->SetTimeMulValue(1.0f);

	g_renderingEngine->DisableCenterBlur();

}

void PlayerStateJustDodgeAttack::Move(Vector3& position, CharacterController& charaCon)
{
	if (m_enemy->IsDead() || m_enemy == nullptr)
	{
		m_enemy = nullptr;
		m_attackFlowState = enEnd;
	}
	else
	{
		playerToEnemyVec = m_enemy->GetPosition() - position;
	}

	if (!m_attackFlowState == enEnemyApproach)
	{
		return;
	}

	
	if (playerToEnemyVec.Length() < 110.0f)
	{
		m_attackFlowState = enAttack1;
	}

	playerToEnemyVec.Normalize();
	playerToEnemyVec *= 1000.0f;

	position = charaCon.Execute(playerToEnemyVec, g_gameTime->GetTrueFrameDeltaTime());

	
}

void PlayerStateJustDodgeAttack::Rotation(Quaternion& rotation, const Vector3& position)
{
	//�X�e�B�b�N�̓��͂����]�����߂�
	playerToEnemyVec.Normalize();
	rotation.SetRotationY(atan2(playerToEnemyVec.x, playerToEnemyVec.z));
}

void PlayerStateJustDodgeAttack::Animation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	if (!model.IsPlayingAnimation())
	{
		StateOenStep();
	}

	switch (m_attackFlowState)
	{
	case PlayerStateJustDodgeAttack::enEnemyApproach:
		model.PlayAnimation(Player::enAnimationClip_Walk, 0.1f);
		break;

	case PlayerStateJustDodgeAttack::enAttack1:
		model.SetAnimationSpeed(4.0f);
		model.PlayAnimation(Player::enAnimationClip_Slash, 0.1f);
		break;

	case PlayerStateJustDodgeAttack::enAttack2:
		model.SetAnimationSpeed(5.0f);
		model.PlayAnimation(Player::enAnimationClip_JumpSlash, 0.1f);
		break;

	case PlayerStateJustDodgeAttack::enAttack3:
		model.SetAnimationSpeed(4.0f);
		model.PlayAnimation(Player::enAnimationClip_Slash, 0.1f);
		break;

	default:
		break;
	}

	switch (animeEvent)
	{
	case enPlayerAnimationEvent_AttackEnd:
		animeEvent = enPlayerAnimationEvent_None;
		//�U���R���W�������~
		m_attackCollision->SetIsEnable(false);
		break;

	case enPlayerAnimationEvent_AttackStart:
		animeEvent = enPlayerAnimationEvent_None;
		//�U���R���W�����𕜊�
		m_attackCollision->SetIsEnable(true);
		break;

	default:
		animeEvent = enPlayerAnimationEvent_None;
		break;
	}
}

void PlayerStateJustDodgeAttack::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
{
	//�U���R���W�����������ĂȂ��Ȃ珈�����΂�
	if (m_attackCollision == nullptr || m_attackCollision->IsDead())
	{
		return;
	}
	//�U���R���W�����̍��W�ݒ�
	//�U���R���W�������o���{�[���̃��[���h�s����󂯎��
	Matrix matrix = model.GetBone(m_attackBoneID)->GetWorldMatrix();

	//�s������̂܂܃R���W�����ɓK������Ǝ�𒆐S�ɃR���W�������o�Ă���̂ł��炷
	//�s�񂩂��]���擾
	Quaternion rotation;
	rotation.SetRotation(matrix);
	//z��1�����L�т��x�N�g���ɉ�]��K�p����
	Vector3 test = Vector3::AxisZ;
	rotation.Apply(test);
	//���̃x�N�g�������̒����̔����{�ɂ���
	test *= PLAYER_SOWLD_SIZE.z / 2.0f;
	//�p�ӂ����x�N�g���ōs��̍��W�ɂ����鐔�l�����炷
	matrix.m[3][0] += test.x;
	matrix.m[3][1] += test.y;
	matrix.m[3][2] += test.z;

	//���������s����R���W�����ɓK�p
	m_attackCollision->SetWorldMatrix(matrix);
}

void PlayerStateJustDodgeAttack::StateOenStep()
{
	switch (m_attackFlowState)
	{
	case PlayerStateJustDodgeAttack::enEnemyApproach:
		break;
	case PlayerStateJustDodgeAttack::enAttack1:
		m_attackFlowState = enAttack2;
		//�U���R���W��������U�@�\��~
		m_attackCollision->SetIsEnable(false);
		break;
	case PlayerStateJustDodgeAttack::enAttack2:
		m_attackFlowState = enAttack3;
		//�U���R���W�����𕜊�
		m_attackCollision->SetIsEnable(true);
		break;
	case PlayerStateJustDodgeAttack::enAttack3:
		m_attackFlowState = enEnd;
		break;
	case PlayerStateJustDodgeAttack::enEnd:
		break;
	default:
		break;
	}

}

EnPlayerState PlayerStateJustDodgeAttack::StateTransition()
{
	if (m_attackFlowState == enEnd)
	{
		return enPlayerIdle;
	}
	else
	{
		return enPlayerJustDodgeAttack;
	}
}

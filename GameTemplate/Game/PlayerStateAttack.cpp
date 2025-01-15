#include "stdafx.h"
#include "PlayerStateAttack.h"
#include "Player.h"

#include "PlayerParameter.h"

void PlayerStateAttack::Start(Player* player)
{
	//�A�j���[�V�����Đ����t���O��������
	m_animationPlay = true;

	//�U������R���W�����𐶐�����{�[����ID���擾
	m_attackBoneID = player->GetModel()->FindBoneID(PLAYER_ATTACK_COLLISION_BONE_NAME);

	
}

void PlayerStateAttack::End(Player* player)
{
	
	bool IsCollisionNull = m_attackCollision == nullptr;
	//�U���R���W����������łȂ�������A�j������
	if (!IsCollisionNull || !m_attackCollision->IsDead())
	{
		DeleteGO(m_attackCollision);
	}
}

void PlayerStateAttack::PlayAnimation(ModelRender& model, EnPlayerAnimationEvent& animeEvent)
{
	if (model.IsPlayingAnimation())
	{
		model.SetAnimationSpeed(1.0f);

		model.PlayAnimation(Player::enAnimationClip_Slash, 0.1f);
	}
	else
	{
		m_animationPlay = false;
	}

	switch (animeEvent)
	{
	case enPlayerAnimationEvent_AttackEnd:
		animeEvent = enPlayerAnimationEvent_None;
		//�U���R���W������j��
		DeleteGO(m_attackCollision);
		break;

	case enPlayerAnimationEvent_AttackStart:
		animeEvent = enPlayerAnimationEvent_None;
		//�U���R���W������p��
		m_attackCollision = NewGO<CollisionObject>(0, "playerattack");
		m_attackCollision->CreateBox(Vector3::Zero, Quaternion::Identity, PLAYER_SOWLD_SIZE);
		m_attackCollision->SetName("player_attack");
		m_attackCollision->SetIsEnableAutoDelete(false);
		break;

	default:
		break;
	}
}

EnPlayerState PlayerStateAttack::StateTransition()
{

	
	if (m_animationPlay)
	{
		return enAttack;	
	}
	else
	{
		return enIdle;
	}
	
}

void PlayerStateAttack::Collision(const Vector3& pos, ModelRender& model, CharacterController& characon)
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
#pragma once
//�萔�܂Ƃ�

namespace {
	const wchar_t* PLAYER_ATTACK_COLLISION_BONE_NAME = L"mixamorig_Sword_joint"; //�U������R���W�����𐶐�����{�[���̖��O
	const char* PLAYER_ATTACK_COLLISION_NAME = { "player_attack" };			//�G�l�~�[�̍U���R���W�����̖��O

	//���̃T�C�Y
	//z�����̒����ɂ�����
	const Vector3 PLAYER_SOWLD_SIZE = { 10.0f,10.0f,50.0f };

	//�K�[�h�R���W�����̃v���C���[���炸�炷�ʁAz�̓v���C���[�̐��ʕ����ɂǂꂭ�炢���炷���̗�
	const Vector3 PLAYER_GUARD_COLLISION_POS = { 0.0f, 70.0f, 30.0f };

}

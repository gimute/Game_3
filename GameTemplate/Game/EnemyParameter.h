#pragma once

//�G�l�~�[�̈ړ����x�Ȃǂ̃p�����[�^�[�̒萔�܂Ƃ�

namespace {
	const float ENEMY_WALK_SPEED = 100.0f;
	const float ENEMY_DASH_SPEED = 200.0f;
	const float ENEMY_GUARDWALK_SPEED = 75.0f;

	const char* ENEMY_ATTACK_COLLISION_NAME = { "enemy_attack" };			//�G�l�~�[�̍U���R���W�����̖��O
	const char* ENEMY_SIDE_ATTACK_NAME = { "enemy_SideAttack" };			//�G�l�~�[�̉��U��������������
	const char* ENEMY_VERTICAL_ATTACK_NAME = { "enemy_VerticalAttack" };	//�G�l�~�[�̏c�U��������������
	const wchar_t* ENEMY_ATTACK_COLLISION_BONE_NAME = L"mixamorig_Sword_joint"; //�U������R���W�����𐶐�����{�[���̖��O

}

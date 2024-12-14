#pragma once

//�`����Ŏg���萔���܂Ƃ߂��w�b�_�[�t�@�C���A�Ȃ͂�

namespace nsK2EngineLow {

	//�|�C���g���C�g�̍ő吔
	const int MAX_POINT_LIGHT = 250;
	const int MAX_SPOT_LIGHT = 250;

	// TBR�p�̃p�����[�^�B
	const int TILE_WIDTH = 16;  // �^�C���̕�
	const int TILE_HEIGHT = 16; // �^�C���̍���
	const int NUM_TILE = (FRAME_BUFFER_W / TILE_WIDTH) * (FRAME_BUFFER_H / TILE_HEIGHT); // �^�C���̐�

	//�����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���܂Ƃ߂�\����
	struct RenderTargetFormat {
		DXGI_FORMAT colorBufferFormat;	//�J���[�o�b�t�@�[�̃t�H�[�}�b�g
		DXGI_FORMAT depthBufferFormat;	//�[�x�o�b�t�@�̃t�H�[�}�b�g
	};

	//�V���h�E�}�b�v�̃t�H�[�}�b�g
	const RenderTargetFormat g_ShadowMapFormat = {
		DXGI_FORMAT_R32G32_FLOAT,	//�J���[�o�b�t�@
		DXGI_FORMAT_D32_FLOAT		//�[�x�o�b�t�@
	};
	
	//���C�������_�����O�^�[�Q�b�g�̃t�H�[�}�b�g
	const RenderTargetFormat g_mainRenderTargetFormat{
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	};

	//�{�����[�����C�g�}�b�v�̃t�H�[�}�b�g
	const RenderTargetFormat g_drawVolumeLightMapFormat = {
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	};

	//G-Buffer�̃J���[�o�b�t�@�[�t�H�[�}�b�g
	const DXGI_FORMAT g_albedColorBuffer = DXGI_FORMAT_R8G8B8A8_UNORM;	//�A���x�h�J���[��G-Buffer
	const DXGI_FORMAT g_normalSpecBuffer = DXGI_FORMAT_R8G8B8A8_UNORM;	//�@���ƃX�y�L�����p���[��G-Buffer
	const DXGI_FORMAT g_depthBuffer = DXGI_FORMAT_R32_FLOAT;				//�[�x�l��G-Buffer

}
#include "k2EngineLowPreCompile.h"
#include "LightCulling.h"
//���C�g�J�����O
namespace nsK2EngineLow {
	void LightCulling::Init(
		Texture& depthTexture,
		ConstantBuffer& lightCB,
		RWStructuredBuffer& pointLightNoListInTileUAV,
		RWStructuredBuffer& spotLightNoListInTileUAV
	) {
		m_pointLightNoListInTileUAV = &pointLightNoListInTileUAV;
		m_spotLightNoListInTileUAV = &spotLightNoListInTileUAV;

		m_shader.LoadCS("Assets/shader/preProcess/lightCulling.fx", "CSMain");

		//���C�g�J�����O�̃J�������p�̒萔�o�b�t�@�[���쐬
		m_cameraDataCB.Init(sizeof(CameraData), nullptr);

		//�f�B�X�N���v�^�q�[�v��������
		//�v����ɂ��ڂ�ɏ悹����̂�ݒ肷��
		//�V�F�[�_�[���\�[�X
		m_descriptorHeap.RegistShaderResource(0, depthTexture);
		//�A���I�[�_�[�A�N�Z�X���\�[�X�A�S�R�킩���
		m_descriptorHeap.RegistUnorderAccessResource(0, pointLightNoListInTileUAV);
		m_descriptorHeap.RegistUnorderAccessResource(1, spotLightNoListInTileUAV);
		//�萔�o�b�t�@�[
		m_descriptorHeap.RegistConstantBuffer(0, m_cameraDataCB);
		m_descriptorHeap.RegistConstantBuffer(1, lightCB);
		//�o�^���m�肳����
		//���ڂ�ɏ悹��M�����܂����C���[�W�A���g�͌ォ������
		m_descriptorHeap.Commit();


		//���[�g�V�O�l�`�����쐬
		//�V�F�[�_�[�ɗ����f�[�^�̎�ނƐ������炩���ߒ�`���镨
		m_rootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP
		);

		//�p�C�v���C���X�e�[�g��������
		//���̓X�g���[���A�V�F�[�_�A�X�e�[�g�������ׂĂЂƂ̃I�u�W�F�N�g�̂܂Ƃ߂����́A�炵��
		D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = { 0 };
		//���[�g�V�O�l�`��
		psoDesc.pRootSignature = m_rootSignature.Get();
		//�R���s���[�g�V�F�[�_�[
		psoDesc.CS = CD3DX12_SHADER_BYTECODE(m_shader.GetCompiledBlob());
		//�����͉����킩���
		psoDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
		psoDesc.NodeMask = 0;
		m_pipelineState.Init(psoDesc);
	}


	void LightCulling::Execute(RenderContext& rc)
	{
		//�J�����O�Ɏg���J�����̏����擾����
		CameraData cameraData;
		//�v���W�F�N�V�����s��
		cameraData.mProj = g_camera3D->GetProjectionMatrix();
		//�v���W�F�N�V�����s��̋t�s��
		//�֐��Œ��ɋt�s���ꂽ�C�����邯�ǂƂ肠�����͂��̂܂܂�
		cameraData.mProjInv.Inverse(g_camera3D->GetProjectionMatrix());
		//�J�����̉�]�s��
		cameraData.mCameraRot = g_camera3D->GetCameraRotation();
		//�J�����̕`��͈͂ƃt���[���o�b�t�@�[�̏c��
		cameraData.screenParam.x = g_camera3D->GetNear();
		cameraData.screenParam.y = g_camera3D->GetFar();
		cameraData.screenParam.z = FRAME_BUFFER_W;
		cameraData.screenParam.w = FRAME_BUFFER_H;
		//�J�����f�[�^�萔�o�b�t�@�ɓo�^(�R�s�[)
		m_cameraDataCB.CopyToVRAM(cameraData);

		//���C�g�J�����O�̃R���s���[�g�V�F�[�_�[���f�B�X�p�b�`
		//�܂��p�ӂ������[�g�V�O�l�`���A�f�B�X�N���v�^�q�[�v�A�p�C�v���C���X�e�[�g��ݒ肷��
		rc.SetComputeRootSignature(m_rootSignature);
		rc.SetComputeDescriptorHeap(m_descriptorHeap);
		rc.SetPipelineState(m_pipelineState);

		//�t���[���o�b�t�@�[�̕��ƍ�����TILE_WIDTH�ATILE_HEIGHT�̔{���ɐ؂�グ��
		//���Ɏg���Ă���ϐ����S�Đ����^�Ȃ̂ŁA�؂�̂Ă𗘗p���ď�肢���Ƃ���Ă�
		UINT FRAME_BUFFER_W_ROUNDUP = ((FRAME_BUFFER_W + TILE_WIDTH - 1) / TILE_WIDTH) * TILE_WIDTH;
		UINT FRAME_BUFFER_H_ROUNDUP = ((FRAME_BUFFER_H + TILE_HEIGHT - 1) / TILE_HEIGHT) * TILE_HEIGHT;

		//�O���[�v�̐���ݒ肵�ăf�B�X�p�b�`
		//�O���[�v�̐��̓^�C���̐�
		rc.Dispatch(
			FRAME_BUFFER_W_ROUNDUP / TILE_WIDTH,
			FRAME_BUFFER_H_ROUNDUP / TILE_HEIGHT,
			1);

		//���\�[�X�o���A
		//�Ȃ񂩃��\�[�X�X�e�[�g��J�ڂ���Ƃ������Ă邯�ǂ悭�킪���
		rc.TransitionResourceState(
			m_pointLightNoListInTileUAV->GetD3DResoruce(),
			D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
		);
	}
}
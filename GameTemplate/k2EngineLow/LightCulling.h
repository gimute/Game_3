#pragma once
//���C�g�J�����O
namespace nsK2EngineLow {
	class LightCulling : public Noncopyable
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="depthTexture">�V�[���̐[�x�l���������܂ꂽ�e�N�X�`��</param>
		/// <param name="lightCB">���C�g�f�[�^�̒萔�o�b�t�@�[</param>
		/// <param name="pointLightNoListInTileUAV">�^�C�����Ƃ̃|�C���g���C�g�̃��X�g���o�͂��邽�߂�UAV</param>
		/// <param name="spotLightNoListInTileUAV">�^�C�����Ƃ̃X�|�b�g���C�g�̃��X�g���o�͂��邽�߂�UAV</param>
		void Init(
			Texture& depthTexture,
			ConstantBuffer& lightCB,
			RWStructuredBuffer& pointLightNoListInTileUAV,
			RWStructuredBuffer& spotLightNoListInTileUAV
		);

		/// <summary>
		/// ���C�g�J�����O���s
		/// </summary>
		/// <param name="rc"></param>
		void Execute(RenderContext& rc);

	private:
		//���C�g�J�����O�Ŏg�p����J�������
		struct CameraData
		{
			Matrix mProj;		//�v���W�F�N�V�����s��
			Matrix mProjInv;	//�v���W�F�N�V�����s��̋t�s��
			Matrix mCameraRot;	//�J�����̉�]�s��
			Vector4 screenParam;	//�X�N���[�����
		};

		RootSignature m_rootSignature;		//���[�g�V�O�l�`��
		ConstantBuffer m_cameraDataCB;		//�J�����f�[�^�̒萔�o�b�t�@
		PipelineState m_pipelineState;		//�p�C�v���C���X�e�[�g

		Shader m_shader;					//���C�g�J�����O�V�F�[�_�[

		DescriptorHeap m_descriptorHeap;	//�f�B�X�N���v�^�q�[�v

		RWStructuredBuffer* m_pointLightNoListInTileUAV = nullptr;	//�^�C�����Ƃ̃|�C���g���C�g�̃��X�g��UAV
		RWStructuredBuffer* m_spotLightNoListInTileUAV = nullptr;	//�^�C�����Ƃ̃X�|�b�g���C�g�̃��X�g��UAV

	};
}




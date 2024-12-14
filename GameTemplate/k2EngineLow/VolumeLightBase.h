#pragma once


namespace nsK2EngineLow {
	class VolumeLightBase : Noncopyable
	{
	public:
		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~VolumeLightBase();

		/// <summary>
		/// �X�V����
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="lightData">���C�g�f�[�^</param>
		/// <param name="tkmFilePath">tkm�t�@�C���p�X</param>
		/// <param name="psFinalEntryFunc">�ŏI�o�X�̃s�N�Z���V�F�[�_�̃G���g���[�|�C���g</param>
		void Init(
			const void* lightData,
			const char* tkmFilePath,
			const char* psFinalEntryFunc
		);

		/// <summary>
		/// �{�����[�����C�g�̑O�ʂ�`��
		/// </summary>
		/// <param name="rc"></param>
		void DrawToVolumeLightMapFront(RenderContext& rc);

		/// <summary>
		/// �{�����[�����C�g�̔w�ʂ�`��
		/// </summary>
		/// <param name="rc"></param>
		void DrawToVolumeLightMapBack(RenderContext& rc);

		/// <summary>
		/// �ŏI�`��
		/// </summary>
		/// <param name="rc"></param>
		void DrawFinal(RenderContext& rc);

	private:
		/// <summary>
		/// ���C�g�f�[�^��ݒ�
		/// </summary>
		/// <param name="lightData">���C�g�f�[�^</param>
		virtual void SetLightData(const void* lightData) = 0;
		//�ŏI�`��O�ɍs������
		virtual void PreDrawFinal(RenderContext& rc) = 0;

		virtual void* GetFinalCB() = 0;
		virtual int GetFinalCBSize() const = 0;

	private:
		Sprite m_final;		//�ŏI�`��

	protected:
		Model m_modelFront;	//�{�����[�����C�g�̑O�ʕ`��p�̃��f��
		Model m_modelBack;	//�{�����[�����C�g�̔w�ʕ`��p�̃��f��
	};

	template<class TLightData, class TLightDataRaw>
	class VolumeLight : public VolumeLightBase {
	private:
		/// <summary>
		/// ���C�g�f�[�^���Z�b�g
		/// </summary>
		/// <param name="lightData"></param>
		void SetLightData(const void* lightData) override
		{
			m_lightData = static_cast<const TLightData*>(lightData);
		}

		/// <summary>
		/// �ŏI�`��̒萔�o�b�t�@�ɑ���f�[�^���擾
		/// </summary>
		void* GetFinalCB() override
		{
			return &m_finalCB;
		}
		int GetFinalCBSize() const override
		{
			return sizeof(m_finalCB);
		}

		/// <summary>
		/// �ŏI�`��O�ɍs������
		/// </summary>
		/// <param name="rc"></param>
		void PreDrawFinal(RenderContext& rc) override
		{
			//�ŏI�`��̒萔�o�b�t�@���X�V����
			m_finalCB.lightDataRaw = m_lightData->GetRawData();
			//�J�����֌W�̃f�[�^��Draw�̃p�X�ŃR�s�[���Ȃ��ƁAUpdate�̏��Ԃ�
			//1�t���[���O�̃J�������ɂȂ��Ă��܂�
			m_finalCB.mViewProjInv = g_camera3D->GetViewProjectionMatrixInv();
			m_finalCB.randomSeed = rand() % 100;
		}

	private:
		/// <summary>
		/// �ŏI�`��p�X�̒萔�o�b�t�@�ɑ���f�[�^
		/// </summary>
		struct FinalCB {
			TLightDataRaw lightDataRaw;	//���̃��C�g�f�[�^
			Matrix mViewProjInv;		//�r���[�v���W�F�N�V�����s��̋t�s��
			float randomSeed;			//�����̎�
		};
		
		FinalCB m_finalCB;		//�ŏI�`��̒萔�o�b�t�@

	protected:
		const TLightData* m_lightData = nullptr;	//�{�����[�����C�g���O�t�����郉�C�g
	};
}



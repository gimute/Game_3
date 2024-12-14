#pragma once

namespace nsK2EngineLow {
	class PostEffectComponentBase : public Noncopyable
	{
	public:
		void Init(RenderTarget& mainRenderTarget);

		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);

		/// <summary>
		/// �|�X�g�G�t�F�N�g�𖳌��ɂ���
		/// </summary>
		void Disable()
		{
			m_isEnable = false;
		}
		/// <summary>
		/// �|�X�g�G�t�F�N�g��L���ɂ���B
		/// </summary>
		void Enable()
		{
			m_isEnable = true;
		}
		/// <summary>
		/// �|�X�g�G�t�F�N�g���L��������B
		/// </summary>
		/// <returns></returns>
		bool IsEnable() const
		{
			return m_isEnable;
		}

		//���̃N���X���p�������q�N���X�̓Ǝ����������鏃�����z�֐�
		// �q�N���X�̏���������
		virtual void OnInit(RenderTarget& mainRenderTarget) = 0;
		// �q�N���X�̕`�揈��
		virtual void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) = 0;

		virtual Texture& GetResultTexture()
		{
			static Texture nullTexture;
			return nullTexture;
		}

		/// <summary>
		/// �|�X�g�̌��ʂ����C�������_�����O�^�[�Q�b�g�ɃR�s�[���邩�ǂ���
		/// </summary>
		/// <returns></returns>
		virtual bool IsCopyResultTextureToMainRenderTarget() const
		{
			return false;
		}


	private:
		bool m_isEnable = true;		//�|�X�g�G�t�F�N�g��L���ɂ��邩
		Sprite m_copyMainRtSprite;	//���C�������_�����O�^�[�Q�b�g�ɕ`�悷�邽�߂̃X�v���C�g�B
	};
}



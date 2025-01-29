#pragma once

namespace nsK2EngineLow {
	class ShadowMapRender : public Noncopyable
	{
	public:
		void Init();

		void Render(
			RenderContext& rc,
			const Vector3& ligDirection,
			std::vector<IRenderer*>& renderObject
			);

		//�V���h�E�}�b�v���擾
		Texture& GetShadowMap()
		{
			return m_blur.GetBokeTexture();
			//return m_shadowMapRT.GetRenderTargetTexture();
		}

		const Matrix& GetLVPMatrix() const
		{
			return m_lvp;
		}

		const Vector3& GetLigCameraPos() const
		{
			return m_ligCameraPos;
		}

	private:
		RenderTarget m_shadowMapRT;	//�V���h�E�}�b�v�����_�[�^�[�Q�b�g

		Matrix m_lvp;			//���C�g�r���[�v���W�F�N�V�����s��

		GaussianBlur m_blur;	//�\�t�g�V���h�E�����邽�߂̃u���[����

		Vector3 m_ligCameraPos = Vector3::Zero;	//���C�g�J�����̃|�W�V�����ۑ��p�ϐ�
	};

}


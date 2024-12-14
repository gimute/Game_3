#pragma once

namespace nsK2EngineLow {
	/// <summary>
	/// �����_�[���[�̊��N���X�B
	/// </summary>
	class IRenderer : public Noncopyable
	{
	public:

		//2D�`��
		virtual void OnRender2D(RenderContext& rc)
		{

		}

		//G-Buffer�`��
		virtual void OnRenderToGBuffer(RenderContext& rc)
		{

		}

		/// <summary>
		/// �V���h�E�}�b�v�ւ̕`��p�X����Ă΂�鏈��
		/// </summary>
		/// <param name="rc">�����_�����O�R���e�L�X�g</param>
		/// <param name="LigViewMatrix">���C�g�̃r���[�s��</param>
		/// <param name="LigProjMatrix">���C�g�̃v���W�F�N�V�����s��</param>
		/// <param name="lightPos">���C�g�̃|�W�V����</param>
		virtual void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& LigViewMatrix,
			const Matrix& LigProjMatrix,
			Vector3& lightPos
		)
		{

		}
	};
}

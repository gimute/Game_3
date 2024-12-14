#pragma once

#include "Bloom.h"
#include "CenterBlur.h"

namespace nsK2EngineLow {
	/// <summary>
	/// �|�X�g�G�t�F�N�g
	/// </summary>
	class PostEffect : public Noncopyable
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="mainRenderTarget">�����_�����O�^�[�Q�b�g</param>
		void Init(RenderTarget& mainRenderTarget);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		/// <param name="mainRenderTarget">���C�������_�[�^�[�Q�b�g</param>
		void Render(RenderContext& rc, RenderTarget& mainRenderTarget);


		void DisableCenterBlur()
		{
			m_centeBlur.Disable();
		}

		void EnableCenterBlur()
		{
			m_centeBlur.Enable();
		}

	private:
		Bloom m_bloom;	    //�u���[��
		CenterBlur m_centeBlur;
	};
}



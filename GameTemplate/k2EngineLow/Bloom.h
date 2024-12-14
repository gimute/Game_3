#pragma once

#include "PostEffectComponentBase.h"

namespace nsK2EngineLow {
	/// <summary>
	/// �u���[��
	/// </summary>
	class Bloom : public PostEffectComponentBase
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="mainRenderTarget">���C�������_�[�^�[�Q�b�g</param>
		void OnInit(RenderTarget& mainRenderTarget) override;
		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc">�����_�[�R���e�L�X�g</param>
		/// <param name="mainRenderTarget">���C�������_�[�^�[�Q�b�g</param>
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) override;


		//���ʂ�Ԃ������Ȋ����ŏ����Ă邯�ǑS�R�R����Ȃ��H
		Texture& GetResultTexture() override
		{
			return m_luminanceRenderTarget.GetRenderTargetTexture();
		};

	private:
		RenderTarget m_luminanceRenderTarget;	//�P�x���o�p�̃����_�����O�^�[�Q�b�g
		Sprite m_luminanceSprite;				//�P�x���o�p�̃X�v���C�g
		GaussianBlur m_gaussianBlur[4];			//�K�E�V�A���u���[
		Sprite m_finalSprite;					//�ŏI�����p�̃X�v���C�g
	};


}



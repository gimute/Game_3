#pragma once

#include "PostEffectComponentBase.h"

//�����u���[
namespace nsK2EngineLow {
	
	/// <summary>
	/// ��������O�Ɍ������u���[
	/// </summary>
	class CenterBlur : public PostEffectComponentBase
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="mainRenderTarget"></param>
		void OnInit(RenderTarget& mainRenderTarget) override;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="mainRenderTarget"></param>
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) override;

	private:
		Sprite m_centerBlur;

		RenderTarget m_tsts;
		Sprite m_keka;
	};

}




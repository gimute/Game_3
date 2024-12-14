#include "k2EngineLowPreCompile.h"
#include "PostEffect.h"

namespace nsK2EngineLow {
	void PostEffect::Init(RenderTarget& mainRenderTarget)
	{
		//ブルームの初期化
		m_bloom.Init(mainRenderTarget);

		//
		m_centeBlur.Init(mainRenderTarget);
	}

	void PostEffect::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//ブルーム
		m_bloom.Render(rc, mainRenderTarget);

		//
		m_centeBlur.Render(rc, mainRenderTarget);
	}

}

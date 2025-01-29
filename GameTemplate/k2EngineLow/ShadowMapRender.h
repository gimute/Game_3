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

		//シャドウマップを取得
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
		RenderTarget m_shadowMapRT;	//シャドウマップレンダーターゲット

		Matrix m_lvp;			//ライトビュープロジェクション行列

		GaussianBlur m_blur;	//ソフトシャドウをするためのブラー処理

		Vector3 m_ligCameraPos = Vector3::Zero;	//ライトカメラのポジション保存用変数
	};

}


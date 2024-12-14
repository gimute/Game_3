#pragma once

namespace nsK2EngineLow {
	/// <summary>
	/// レンダーラーの基底クラス。
	/// </summary>
	class IRenderer : public Noncopyable
	{
	public:

		//2D描画
		virtual void OnRender2D(RenderContext& rc)
		{

		}

		//G-Buffer描画
		virtual void OnRenderToGBuffer(RenderContext& rc)
		{

		}

		/// <summary>
		/// シャドウマップへの描画パスから呼ばれる処理
		/// </summary>
		/// <param name="rc">レンダリングコンテキスト</param>
		/// <param name="LigViewMatrix">ライトのビュー行列</param>
		/// <param name="LigProjMatrix">ライトのプロジェクション行列</param>
		/// <param name="lightPos">ライトのポジション</param>
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

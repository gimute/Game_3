#pragma once

#include "myRenderer.h"
#include "PostEffect.h"
#include "ShadowMapRender.h"
#include "LightCulling.h"
#include "VolumeLightRender.h"

namespace nsK2EngineLow {
	/// <summary>
	/// レンダリングエンジン
	/// </summary>
	class RenderingEngine : public Noncopyable
	{
	public:
		struct SDeferredLightingCB
		{
			Light m_light;		//ライト
			Matrix m_viewProjIn;	//ゲームカメラビュープロジェクション行列の逆行列
			Matrix m_lvp;		//シャドウ用ライトカメラのビュープロジェクション行列
			Vector3 m_shadowLightPos;	//シャドウマップ用のライトカメラのポジション
		};


		RenderingEngine();
		~RenderingEngine();

		//初期化
		void Init();

		//実行
		void Execute(RenderContext& rc);

		//描画オブジェクトを追加
		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		/// <summary>
		/// ボリュームライトをシーンに追加
		/// </summary>
		/// <param name="lig"></param>
		void AddVolumeSpotLight(VolumeLightBase& lig)
		{
			m_volumeLightRender.AddVolumeLight(lig);
		}

		/// <summary>
		/// ボリュームライトをシーンから削除
		/// </summary>
		/// <param name="lig"></param>
		void RemoveVolumeLight(VolumeLightBase& lig)
		{
			m_volumeLightRender.RemoveVolumeSpotLight(lig);
		}
		
		/// <summary>
		/// ボリュームライトレンダラーを取得
		/// </summary>
		/// <returns></returns>
		VolumeLightRender& GetVolumeLightRender()
		{
			return m_volumeLightRender;
		}

		/// <summary>
		/// GBufferの深度値テクスチャを取得
		/// </summary>
		/// <returns></returns>
		Texture& GetGBufferDepthTexture()
		{
			return m_depthRT.GetRenderTargetTexture();
		}

		Texture& GetGBufferAlbedoTexture()
		{
			return m_albedRT.GetRenderTargetTexture();
		}

		void DisableCenterBlur()
		{
			m_postEffect.DisableCenterBlur();
		}

		void EnableCenterBlur()
		{
			
			m_postEffect.EnableCenterBlur();
		}


	private:
		/// <summary>
		/// メインレンダーターゲットの初期化
		/// </summary>
		void InitMainRenderTarget();
		
		/// <summary>
		/// G-Buffer用のレンダリングターゲットの初期化
		/// </summary>
		void InitGBuffer();

		/// <summary>
		/// ディファードライティングの初期化
		/// </summary>
		void InitDeferredLighting();
		/// <summary>
		/// ディファードライティングで使用するスプライトの初期化
		/// </summary>
		void InitDiferrdLightingSprite();

		/// <summary>
		/// メインレンダリングターゲットをフレームバッファにコピーするためのスプライト初期化
		/// </summary>
		void InitCopyMainRenderTargetToFrameBufferSprite();


		//G-Bufferへの描画
		void RenderToGBuffer(RenderContext& rc);

		//ディファードライティング
		void DeferredLighting(RenderContext& rc);

		//フォワードレンダリング
		void ForwardRendering(RenderContext& rc);

	private:
		std::vector<IRenderer*> m_renderObjects;	//描画オブジェクトのリスト

		RenderTarget m_albedRT;				//アルベドカラー書き込み用のレンダリングターゲット
		RenderTarget m_normalSpecRT;			//法線書き込み用のレンダリングターゲット
		RenderTarget m_depthRT;			//深度値書き込み用のレンダリングターゲット
		RenderTarget* rts[3] = {			//G-Buffer用のレンダータリングターゲットをまとめる配列
			&m_albedRT,
			&m_normalSpecRT,
			&m_depthRT
		};
		RenderTarget m_mainRenderTarget;			//メインレンダリングターゲット
		
		ShadowMapRender m_shadowMapRender;			//シャドウマップレンダー
		PostEffect m_postEffect;					//ポストエフェクト

		Sprite m_copyMainRtToFrameBufferSprite;		//メインレンダリングターゲットをフレームバッファにコピーするためのスプライト
		Sprite m_GBufferTest;						//G-Bufferの様子を見るためのテストスプライト

		Sprite m_diferredLightingSprite;			//ディファードライティング用のスプライト
		SDeferredLightingCB m_deferredLightingCB;	//ディファードライティング用の定数バッファ


		LightCulling m_lightCulling;

		RWStructuredBuffer m_pointLightNoListInTileUAV;		// タイルごとのポイントライトのリストのUAV
		RWStructuredBuffer m_spotLightNoListInTileUAV;		// タイルごとのスポットライトのリストのUAV

		VolumeLightRender m_volumeLightRender;		//ボリュームライトレンダー
	};
}

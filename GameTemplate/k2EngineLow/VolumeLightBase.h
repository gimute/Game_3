#pragma once


namespace nsK2EngineLow {
	class VolumeLightBase : Noncopyable
	{
	public:
		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~VolumeLightBase();

		/// <summary>
		/// 更新処理
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="lightData">ライトデータ</param>
		/// <param name="tkmFilePath">tkmファイルパス</param>
		/// <param name="psFinalEntryFunc">最終バスのピクセルシェーダのエントリーポイント</param>
		void Init(
			const void* lightData,
			const char* tkmFilePath,
			const char* psFinalEntryFunc
		);

		/// <summary>
		/// ボリュームライトの前面を描画
		/// </summary>
		/// <param name="rc"></param>
		void DrawToVolumeLightMapFront(RenderContext& rc);

		/// <summary>
		/// ボリュームライトの背面を描画
		/// </summary>
		/// <param name="rc"></param>
		void DrawToVolumeLightMapBack(RenderContext& rc);

		/// <summary>
		/// 最終描画
		/// </summary>
		/// <param name="rc"></param>
		void DrawFinal(RenderContext& rc);

	private:
		/// <summary>
		/// ライトデータを設定
		/// </summary>
		/// <param name="lightData">ライトデータ</param>
		virtual void SetLightData(const void* lightData) = 0;
		//最終描画前に行う処理
		virtual void PreDrawFinal(RenderContext& rc) = 0;

		virtual void* GetFinalCB() = 0;
		virtual int GetFinalCBSize() const = 0;

	private:
		Sprite m_final;		//最終描画

	protected:
		Model m_modelFront;	//ボリュームライトの前面描画用のモデル
		Model m_modelBack;	//ボリュームライトの背面描画用のモデル
	};

	template<class TLightData, class TLightDataRaw>
	class VolumeLight : public VolumeLightBase {
	private:
		/// <summary>
		/// ライトデータをセット
		/// </summary>
		/// <param name="lightData"></param>
		void SetLightData(const void* lightData) override
		{
			m_lightData = static_cast<const TLightData*>(lightData);
		}

		/// <summary>
		/// 最終描画の定数バッファに送るデータを取得
		/// </summary>
		void* GetFinalCB() override
		{
			return &m_finalCB;
		}
		int GetFinalCBSize() const override
		{
			return sizeof(m_finalCB);
		}

		/// <summary>
		/// 最終描画前に行う処理
		/// </summary>
		/// <param name="rc"></param>
		void PreDrawFinal(RenderContext& rc) override
		{
			//最終描画の定数バッファを更新する
			m_finalCB.lightDataRaw = m_lightData->GetRawData();
			//カメラ関係のデータはDrawのパスでコピーしないと、Updateの順番で
			//1フレーム前のカメラ情報になってしまう
			m_finalCB.mViewProjInv = g_camera3D->GetViewProjectionMatrixInv();
			m_finalCB.randomSeed = rand() % 100;
		}

	private:
		/// <summary>
		/// 最終描画パスの定数バッファに送るデータ
		/// </summary>
		struct FinalCB {
			TLightDataRaw lightDataRaw;	//生のライトデータ
			Matrix mViewProjInv;		//ビュープロジェクション行列の逆行列
			float randomSeed;			//乱数の種
		};
		
		FinalCB m_finalCB;		//最終描画の定数バッファ

	protected:
		const TLightData* m_lightData = nullptr;	//ボリュームライトを外付けするライト
	};
}



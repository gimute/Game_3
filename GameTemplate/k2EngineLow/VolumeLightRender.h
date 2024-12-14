#pragma once
//レンダー

namespace nsK2EngineLow {
	class VolumeLightBase;

	//ボリュームライトレンダラー
	class VolumeLightRender : Noncopyable
	{
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		void Init();

		/// <summary>
		/// ボリュームライトを描画する
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rtvHandle"></param>
		/// <param name="dsvHandle"></param>
		void Render(RenderContext& rc, D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle, D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);

		/// <summary>
		/// ボリュームライトをレンダラーに追加
		/// </summary>
		/// <param name="lig"></param>
		void AddVolumeLight(VolumeLightBase& lig)
		{
			m_volumeLightArray.emplace_back(&lig);
		}

		/// <summary>
		/// ボリュームライトをレンダラーから削除
		/// </summary>
		/// <param name="lig"></param>
		void RemoveVolumeSpotLight(VolumeLightBase& lig)
		{
			//引数で渡されたボリュームライトを探す
			auto it = std::find(m_volumeLightArray.begin(), m_volumeLightArray.end(), &lig);
			//見つかればそれを削除
			if (it != m_volumeLightArray.end())
			{
				m_volumeLightArray.erase(it);
			}
		}

		Texture& GetVolumeLightMapFrontTexture()
		{
			return m_volumeLightMapFront.GetRenderTargetTexture();
		}

		Texture& GetVolumeLightMapBackTexture()
		{
			return m_volumeLightMapBack.GetRenderTargetTexture();
		}

	private:
		RenderTarget m_volumeLightMapFront;
		RenderTarget m_volumeLightMapBack;

		std::list< VolumeLightBase* > m_volumeLightArray;   // ボリュームライトの配列


	};

}



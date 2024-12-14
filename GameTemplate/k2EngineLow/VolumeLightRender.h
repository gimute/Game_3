#pragma once
//�����_�[

namespace nsK2EngineLow {
	class VolumeLightBase;

	//�{�����[�����C�g�����_���[
	class VolumeLightRender : Noncopyable
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		void Init();

		/// <summary>
		/// �{�����[�����C�g��`�悷��
		/// </summary>
		/// <param name="rc"></param>
		/// <param name="rtvHandle"></param>
		/// <param name="dsvHandle"></param>
		void Render(RenderContext& rc, D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle, D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle);

		/// <summary>
		/// �{�����[�����C�g�������_���[�ɒǉ�
		/// </summary>
		/// <param name="lig"></param>
		void AddVolumeLight(VolumeLightBase& lig)
		{
			m_volumeLightArray.emplace_back(&lig);
		}

		/// <summary>
		/// �{�����[�����C�g�������_���[����폜
		/// </summary>
		/// <param name="lig"></param>
		void RemoveVolumeSpotLight(VolumeLightBase& lig)
		{
			//�����œn���ꂽ�{�����[�����C�g��T��
			auto it = std::find(m_volumeLightArray.begin(), m_volumeLightArray.end(), &lig);
			//������΂�����폜
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

		std::list< VolumeLightBase* > m_volumeLightArray;   // �{�����[�����C�g�̔z��


	};

}



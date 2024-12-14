#pragma once

#include "myRenderer.h"
#include "PostEffect.h"
#include "ShadowMapRender.h"
#include "LightCulling.h"
#include "VolumeLightRender.h"

namespace nsK2EngineLow {
	/// <summary>
	/// �����_�����O�G���W��
	/// </summary>
	class RenderingEngine : public Noncopyable
	{
	public:
		struct SDeferredLightingCB
		{
			Light m_light;		//���C�g
			Matrix m_viewProjIn;	//�Q�[���J�����r���[�v���W�F�N�V�����s��̋t�s��
			Matrix m_lvp;		//�V���h�E�p���C�g�J�����̃r���[�v���W�F�N�V�����s��
			Vector3 m_shadowLightPos;	//�V���h�E�}�b�v�p�̃��C�g�J�����̃|�W�V����
		};


		RenderingEngine();
		~RenderingEngine();

		//������
		void Init();

		//���s
		void Execute(RenderContext& rc);

		//�`��I�u�W�F�N�g��ǉ�
		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.push_back(renderObject);
		}

		/// <summary>
		/// �{�����[�����C�g���V�[���ɒǉ�
		/// </summary>
		/// <param name="lig"></param>
		void AddVolumeSpotLight(VolumeLightBase& lig)
		{
			m_volumeLightRender.AddVolumeLight(lig);
		}

		/// <summary>
		/// �{�����[�����C�g���V�[������폜
		/// </summary>
		/// <param name="lig"></param>
		void RemoveVolumeLight(VolumeLightBase& lig)
		{
			m_volumeLightRender.RemoveVolumeSpotLight(lig);
		}
		
		/// <summary>
		/// �{�����[�����C�g�����_���[���擾
		/// </summary>
		/// <returns></returns>
		VolumeLightRender& GetVolumeLightRender()
		{
			return m_volumeLightRender;
		}

		/// <summary>
		/// GBuffer�̐[�x�l�e�N�X�`�����擾
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
		/// ���C�������_�[�^�[�Q�b�g�̏�����
		/// </summary>
		void InitMainRenderTarget();
		
		/// <summary>
		/// G-Buffer�p�̃����_�����O�^�[�Q�b�g�̏�����
		/// </summary>
		void InitGBuffer();

		/// <summary>
		/// �f�B�t�@�[�h���C�e�B���O�̏�����
		/// </summary>
		void InitDeferredLighting();
		/// <summary>
		/// �f�B�t�@�[�h���C�e�B���O�Ŏg�p����X�v���C�g�̏�����
		/// </summary>
		void InitDiferrdLightingSprite();

		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g������
		/// </summary>
		void InitCopyMainRenderTargetToFrameBufferSprite();


		//G-Buffer�ւ̕`��
		void RenderToGBuffer(RenderContext& rc);

		//�f�B�t�@�[�h���C�e�B���O
		void DeferredLighting(RenderContext& rc);

		//�t�H���[�h�����_�����O
		void ForwardRendering(RenderContext& rc);

	private:
		std::vector<IRenderer*> m_renderObjects;	//�`��I�u�W�F�N�g�̃��X�g

		RenderTarget m_albedRT;				//�A���x�h�J���[�������ݗp�̃����_�����O�^�[�Q�b�g
		RenderTarget m_normalSpecRT;			//�@���������ݗp�̃����_�����O�^�[�Q�b�g
		RenderTarget m_depthRT;			//�[�x�l�������ݗp�̃����_�����O�^�[�Q�b�g
		RenderTarget* rts[3] = {			//G-Buffer�p�̃����_�[�^�����O�^�[�Q�b�g���܂Ƃ߂�z��
			&m_albedRT,
			&m_normalSpecRT,
			&m_depthRT
		};
		RenderTarget m_mainRenderTarget;			//���C�������_�����O�^�[�Q�b�g
		
		ShadowMapRender m_shadowMapRender;			//�V���h�E�}�b�v�����_�[
		PostEffect m_postEffect;					//�|�X�g�G�t�F�N�g

		Sprite m_copyMainRtToFrameBufferSprite;		//���C�������_�����O�^�[�Q�b�g���t���[���o�b�t�@�ɃR�s�[���邽�߂̃X�v���C�g
		Sprite m_GBufferTest;						//G-Buffer�̗l�q�����邽�߂̃e�X�g�X�v���C�g

		Sprite m_diferredLightingSprite;			//�f�B�t�@�[�h���C�e�B���O�p�̃X�v���C�g
		SDeferredLightingCB m_deferredLightingCB;	//�f�B�t�@�[�h���C�e�B���O�p�̒萔�o�b�t�@


		LightCulling m_lightCulling;

		RWStructuredBuffer m_pointLightNoListInTileUAV;		// �^�C�����Ƃ̃|�C���g���C�g�̃��X�g��UAV
		RWStructuredBuffer m_spotLightNoListInTileUAV;		// �^�C�����Ƃ̃X�|�b�g���C�g�̃��X�g��UAV

		VolumeLightRender m_volumeLightRender;		//�{�����[�����C�g�����_�[
	};
}

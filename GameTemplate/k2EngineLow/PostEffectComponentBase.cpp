#include "k2EngineLowPreCompile.h"
#include "PostEffectComponentBase.h"

namespace nsK2EngineLow {
	void PostEffectComponentBase::Init(RenderTarget& mainRenderTarget)
	{
		OnInit(mainRenderTarget);

		// ���̃��C�������_�[�^�[�Q�b�g�փR�s�[����t���Ooff�ŏ�������������
		// ���C�������_�[�^�[�Q�b�g�փR�s�[����t���Oon�ɂ�����G���[�f����邭�ˁH
		if (IsCopyResultTextureToMainRenderTarget()) {
			SpriteInitData initData;
			initData.m_width = mainRenderTarget.GetWidth();
			initData.m_height = mainRenderTarget.GetHeight();
			initData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();
			initData.m_fxFilePath = "Assets/shader/Sprite.fx";
			//����u���[�����ƋP�x���o�e�N�X�`�����g���Ă邩�琳�����@�\���Ȃ�
			initData.m_textures[0] = &GetResultTexture();
			m_copyMainRtSprite.Init(initData);
		}
	}

	void PostEffectComponentBase::Render(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//�|�X�g�G�t�F�N�g�������Ȃ牽�������ɕԂ�
		if (!m_isEnable) {
			return;
		}


		
		//�Ǝ�����
		OnRender(rc, mainRenderTarget);

		//���C�������_�����O�^�[�Q�b�g�ɃR�s�[���鏈���A�����������C�������_�����O�^�[�Q�b�g�ɕ`�悵�Ă邩��Ӗ��킩���
		if (IsCopyResultTextureToMainRenderTarget()) {
			// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
			rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
			// �����_�����O�^�[�Q�b�g��ݒ�
			rc.SetRenderTargetAndViewport(mainRenderTarget);
			// �|�X�g�G�t�F�N�g�̌��ʂ����C�������_�����O�^�[�Q�b�g�ɔ��f�B
			m_copyMainRtSprite.Draw(rc);
			// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
			rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
		}
	}

}

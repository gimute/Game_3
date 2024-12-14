#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow {
	void Bloom::OnInit(RenderTarget& mainRenderTarget)
	{
		m_luminanceRenderTarget.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			DXGI_FORMAT_UNKNOWN
		);

		//�P�x���o�p�̃X�v���C�g��������
		//�����������쐬����
		SpriteInitData luminanceSpriteInitData;
		//�P�x���o�p�̃V�F�[�_�[�t�@�C���p�X���w�肷��
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/postEffect/bloom.fx";
		//���_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		//���̂Ƃ��둗�肽����񂪖����̂Ń��[�U�[�g���R���X�^���g�o�b�t�@�[�̓X���[
		//luminanceSpriteInitData.m_expandConstantBuffer = ;
		//luminanceSpriteInitData.m_expandConstantBufferSize = sizeof();
		
		//�X�v���C�g�̕��ƍ�����luminnceRenderTarget�Ɠ���
		luminanceSpriteInitData.m_width = mainRenderTarget.GetWidth();
		luminanceSpriteInitData.m_height = mainRenderTarget.GetHeight();

		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
		luminanceSpriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		// �`�����ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���w�肷��
		luminanceSpriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

		//�X�v���C�g��������
		m_luminanceSprite.Init(luminanceSpriteInitData);


		//�K�E�V�A���u���[��������
		//gaussianBlur[0]�͋P�x�e�N�X�`���ɃK�E�V�A���u���[��������
		//[1][2][3]�͂��ꂼ��ЂƂO�̃K�E�V�A���u���[�̃e�N�X�`���ɃK�E�V�A���u���[��������
		m_gaussianBlur[0].Init(&m_luminanceRenderTarget.GetRenderTargetTexture());
		m_gaussianBlur[1].Init(&m_gaussianBlur[0].GetBokeTexture());
		m_gaussianBlur[2].Init(&m_gaussianBlur[1].GetBokeTexture());
		m_gaussianBlur[3].Init(&m_gaussianBlur[2].GetBokeTexture());

		// �ŏI�����p�̃X�v���C�g������������
		SpriteInitData finalSpriteInitData;
		// �{�P�e�N�X�`����4���w�肷��
		finalSpriteInitData.m_textures[0] = &m_gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &m_gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &m_gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &m_gaussianBlur[3].GetBokeTexture();
		// �𑜓x��mainRenderTarget�̕��ƍ���
		finalSpriteInitData.m_width = mainRenderTarget.GetWidth();
		finalSpriteInitData.m_height = mainRenderTarget.GetHeight();
		// �ڂ������摜���A�ʏ��2D�Ƃ��ă��C�������_�����O�^�[�Q�b�g�ɕ`�悷��̂ŁA
		// 2D�p�̃V�F�[�_�[���g�p����
		finalSpriteInitData.m_fxFilePath = "Assets/shader/postEffect/bloom.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		// �������A���Z�����ŕ`�悷��̂ŁA�A���t�@�u�����f�B���O���[�h�����Z�ɂ���
		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		finalSpriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

		m_finalSprite.Init(finalSpriteInitData);

	}

	void Bloom::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		//�P�x���o
		// �P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX
		rc.WaitUntilToPossibleSetRenderTarget(m_luminanceRenderTarget);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_luminanceRenderTarget);
		// �����_�����O�^�[�Q�b�g���N���A
		rc.ClearRenderTargetView(m_luminanceRenderTarget);
		// �P�x���o���s��
		m_luminanceSprite.Draw(rc);
		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_luminanceRenderTarget);

		// �K�E�V�A���u���[��4����s����
		m_gaussianBlur[0].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[1].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[2].ExecuteOnGPU(rc, 10);
		m_gaussianBlur[3].ExecuteOnGPU(rc, 10);

		// 4���̃{�P�摜���������ă��C�������_�����O�^�[�Q�b�g�ɉ��Z����
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(mainRenderTarget);
		// �ŏI����
		m_finalSprite.Draw(rc);
		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	}
}
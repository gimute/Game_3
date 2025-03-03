#include "k2EngineLowPreCompile.h"
#include "CenterBlur.h"

//�Z���^�[�u���[
namespace nsK2EngineLow {
	void CenterBlur::OnInit(RenderTarget& mainRenderTarget)
	{
		m_tsts.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			g_mainRenderTargetFormat.depthBufferFormat
		);

		//�u���[��K�p���邽�߂̃X�v���C�g��������
		SpriteInitData spriteInitDate;
		//�V�F�[�_�[�t�@�C���p�X���w��
		spriteInitDate.m_fxFilePath = "Assets/shader/postEffect/centerBlur.fx";
		//���ƍ�����mainRenderTarget�Ɠ���
		spriteInitDate.m_width = mainRenderTarget.GetWidth();
		spriteInitDate.m_height = mainRenderTarget.GetHeight();
		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
		spriteInitDate.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		//�������ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���擾
		spriteInitDate.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();
		//�u���[�̋�����ݒ肷�邽�߂̒l������萔�o�b�t�@�[
		spriteInitDate.m_expandConstantBuffer = &m_blurPower;
		spriteInitDate.m_expandConstantBufferSize = sizeof(m_blurPower);

		//�p�ӂ����f�[�^�ŃX�v���C�g��������
		m_centerBlur.Init(spriteInitDate);

		//�u���[��K�p���邽�߂̃X�v���C�g��������
		SpriteInitData spriteInitDatea;
		//�V�F�[�_�[�t�@�C���p�X���w��
		spriteInitDatea.m_fxFilePath = "Assets/shader/sprite.fx";
		//���ƍ�����mainRenderTarget�Ɠ���
		spriteInitDatea.m_width = m_tsts.GetWidth();
		spriteInitDatea.m_height = m_tsts.GetHeight();
		//�e�N�X�`���̓��C�������_�����O�^�[�Q�b�g�̃J���[�o�b�t�@�[
		spriteInitDatea.m_textures[0] = &m_tsts.GetRenderTargetTexture();
		//�������ރ����_�����O�^�[�Q�b�g�̃t�H�[�}�b�g���擾
		spriteInitDatea.m_colorBufferFormat[0] = m_tsts.GetColorBufferFormat();

		//�p�ӂ����f�[�^�ŃX�v���C�g��������
		m_keka.Init(spriteInitDatea);
	}

	void CenterBlur::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		switch (m_fadeState)
		{
		case nsK2EngineLow::enCenterBlureIn:
			m_blurPower += g_gameTime->GetTrueFrameDeltaTime() * 2.0f;
			if (m_blurPower >= 1.0f)
			{
				m_blurPower = 1.0f;
				m_fadeState = enCenterBlureIdle;
			}
			break;

		case nsK2EngineLow::enCenterBlureOut:
			m_blurPower -= g_gameTime->GetTrueFrameDeltaTime() * 2.0f;
			if (m_blurPower <= 0.0f)
			{
				m_blurPower = 0.0f;
				m_fadeState = enCenterBlureIdle;
				Disable();
			}
			break;

		case nsK2EngineLow::enCenterBlureIdle:
			break;
		default:
			break;
		}

		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(m_tsts);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(m_tsts);
		// �u���[��K�p
		m_centerBlur.Draw(rc);
		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(m_tsts);


		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		// �����_�����O�^�[�Q�b�g��ݒ�
		rc.SetRenderTargetAndViewport(mainRenderTarget);
		// �u���[��K�p
		m_keka.Draw(rc);
		// �����_�����O�^�[�Q�b�g�ւ̏������ݏI���҂�
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);
	}

}
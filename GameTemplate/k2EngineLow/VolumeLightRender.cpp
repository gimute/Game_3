#include "k2EngineLowPreCompile.h"
#include "VolumeLightRender.h"

namespace nsK2EngineLow {
	void VolumeLightRender::Init()
	{
		//�����_�����O�^�[�Q�b�g�̏�����
		m_volumeLightMapFront.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			g_drawVolumeLightMapFormat.colorBufferFormat,
			g_drawVolumeLightMapFormat.depthBufferFormat
		);

		m_volumeLightMapBack.Create(
			FRAME_BUFFER_W,
			FRAME_BUFFER_H,
			1,
			1,
			g_drawVolumeLightMapFormat.colorBufferFormat,
			g_drawVolumeLightMapFormat.depthBufferFormat
		);
	}

	void VolumeLightRender::Render(RenderContext& rc, D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle, D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle)
	{
		//�{�����[�����C�g�`��
		for (auto& volumeLig : m_volumeLightArray) {
			//1�p�X�A�O�ʂ�`��
			rc.WaitUntilToPossibleSetRenderTarget(m_volumeLightMapFront);
			rc.SetRenderTargetAndViewport(m_volumeLightMapFront);
			rc.ClearRenderTargetView(m_volumeLightMapFront);
			volumeLig->DrawToVolumeLightMapFront(rc);

			//2�p�X�A�w�ʂ�`��
			rc.WaitUntilToPossibleSetRenderTarget(m_volumeLightMapBack);
			rc.SetRenderTargetAndViewport(m_volumeLightMapBack);
			rc.ClearRenderTargetView(m_volumeLightMapBack);
			volumeLig->DrawToVolumeLightMapBack(rc);

			//���Ǝ�O�̏������݊����҂�
			rc.WaitUntilFinishDrawingToRenderTarget(m_volumeLightMapFront);
			rc.WaitUntilFinishDrawingToRenderTarget(m_volumeLightMapBack);

			//3�p�X�A�ŏI�`��
			rc.SetRenderTarget(rtvHandle, dsvHandle);
			rc.SetViewportAndScissor(g_graphicsEngine->GetFrameBufferViewport());
			volumeLig->DrawFinal(rc);
		}
	}
}

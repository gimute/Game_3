#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"

namespace nsK2EngineLow{
	void ShadowMapRender::Init()
	{
		float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

		m_shadowMapRT.Create(
			2048,
			2048,
			1,
			1,
			g_ShadowMapFormat.colorBufferFormat,
			g_ShadowMapFormat.depthBufferFormat,
			clearColor
		);

		m_blur.Init(&m_shadowMapRT.GetRenderTargetTexture());
	}

	void ShadowMapRender::Render(
		RenderContext& rc,
		const Vector3& ligDirection,
		std::vector<IRenderer*>& renderObjects)
	{
		Camera lightCamera;

		m_ligCameraPos = ligDirection * -1.0f;
		m_ligCameraPos.Normalize();

		
		m_ligCameraPos *= 700.0f;

		lightCamera.SetViewAngle(Math::DegToRad(135.0f));
		lightCamera.SetTarget({0.0f,0.0f,0.0f});
		lightCamera.SetPosition(m_ligCameraPos);
		lightCamera.SetNear(1.0f);
		lightCamera.SetFar(5000.0f);

		Vector3 test = g_camera3D->GetTarget() - m_ligCameraPos;
		test.Normalize();

		if (fabsf(test.y) > 0.9999f)
		{
		}
		lightCamera.SetUp(g_vec3AxisZ);

		lightCamera.Update();


		m_lvp = lightCamera.GetViewProjectionMatrix();

		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMapRT);
		rc.SetRenderTargetAndViewport(m_shadowMapRT);
		rc.ClearRenderTargetView(m_shadowMapRT);

		for (auto& renderer : renderObjects)
		{
			renderer->OnRenderShadowMap(
				rc,
				lightCamera.GetViewMatrix(),
				lightCamera.GetProjectionMatrix(),
				m_ligCameraPos
			);
		}

		rc.WaitUntilFinishDrawingToRenderTarget(m_shadowMapRT);

		m_blur.ExecuteOnGPU(rc, 1.0f);
	}

}

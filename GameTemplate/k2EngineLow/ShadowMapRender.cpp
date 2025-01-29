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
		Matrix viewMatrix;
		Vector3 lightTarget = g_camera3D->GetTarget();
		Vector3 lightPos = { 0.0f,400.0f,0.0f };

		/*Vector3 lightTarget = g_camera3D->GetPosition();
		Vector3 lightPos = lightTarget;

		lightPos += (ligDirection) * (500.0f / ligDirection.y);*/

		/*if (fabsf(ligDirection.y) > 0.9999f)
		{
			viewMatrix.MakeLookAt(lightPos, lightTarget, g_vec3AxisX);
		}
		else*/
		/*{
			viewMatrix.MakeLookAt(lightPos, lightTarget, g_vec3AxisY);
		}

		Matrix projMatrix;
		projMatrix.MakeOrthoProjectionMatrix(
			5000.0f,
			5000.0f,
			1.0f,
			g_camera3D->GetFar()
			);

		m_lvp = viewMatrix * projMatrix;

		rc.WaitUntilToPossibleSetRenderTarget(m_shadowMapRT);
		rc.SetRenderTargetAndViewport(m_shadowMapRT);
		rc.ClearRenderTargetView(m_shadowMapRT);

		for (auto& renderer : renderObjects)
		{
			renderer->OnRenderShadowMap(
				rc,
				viewMatrix,
				projMatrix,
				lightPos
			);
		}*/

		Camera lightCamera;

		m_ligCameraPos = ligDirection * -1.0f;
		m_ligCameraPos.Normalize();

		
		m_ligCameraPos *= 1000.0f;

		lightCamera.SetViewAngle(Math::DegToRad(90.0f));
		lightCamera.SetTarget(g_camera3D->GetTarget());
		lightCamera.SetPosition(m_ligCameraPos);
		lightCamera.SetNear(1.0f);
		lightCamera.SetFar(5000.0f);

		Vector3 test = g_camera3D->GetTarget() - m_ligCameraPos;
		test.Normalize();

		if (fabsf(test.y) > 0.9999f)
		{
			lightCamera.SetUp(g_vec3AxisX);
		}
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

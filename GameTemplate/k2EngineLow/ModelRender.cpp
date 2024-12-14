#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {
	ModelRender::ModelRender()
	{

	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Init(
		const char* tkmfilepath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis
	)
	{
		//スケルトンを初期化
		InitSkeleton(tkmfilepath);
		//アニメーションを初期化
		InitAnimation(animationClips, numAnimationClips);
		//G-Buffer描画用のモデルの初期化
		InitModelOnRenderGBuffer(tkmfilepath, enModelUpAxis);
		//シャドウマップ描画用モデルの初期化
		InitShadowModel(tkmfilepath, enModelUpAxis);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み
		//モデルのファイルパスの末尾の.tkmを.tksにしてそれを読み込む、
		//そのためスケルトンとモデルのファイルは同じファイル内に無いとこの処理は機能しない。
		//それぞれ別で指定させてもいいが2個もファイルパス書くのはめんどいのでこのままで。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		//作ったファイルパスからスケルトンを読み込む
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
	{
		//引数をそれぞれメンバ変数に代入
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;

		if (m_animationClips != nullptr) 
		{
			//アニメーション初期化
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				m_numAnimationClips
			);
		}
	}

	void ModelRender::InitModelOnRenderGBuffer(
		const char* tkmFilePath,
		EnModelUpAxis enModelUpAxis
	)
	{
		ModelInitData initData;
		initData.m_fxFilePath = "Assets/shader/renderToGBuffer3DModel.fx";
		initData.m_tkmFilePath = tkmFilePath;
		initData.m_modelUpAxis = enModelUpAxis;

		//スケルトンが初期化されていたら
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}
		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		initData.m_colorBufferFormat[0] = g_albedColorBuffer;
		initData.m_colorBufferFormat[1] = g_normalSpecBuffer;
		initData.m_colorBufferFormat[2] = g_depthBuffer;

		m_renderToGBufferModel.Init(initData);
	}

	void ModelRender::InitShadowModel(
		const char* tkmFilePath,
		EnModelUpAxis enModelUpAxis
	)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = tkmFilePath;
		initData.m_fxFilePath = "Assets/shader/preProcess/drawShadowMap.fx";
		initData.m_modelUpAxis = enModelUpAxis;

		//定数バッファーにライトのポジションを入れる準備、実際のライトの値はシャドウを描画するときに受け取る
		initData.m_expandConstantBuffer = &m_lightPos;
		initData.m_expandConstantBufferSize = sizeof(m_lightPos);

		initData.m_colorBufferFormat[0] = g_ShadowMapFormat.colorBufferFormat;

		//スケルトンが初期化されていたら
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}
		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		//if (m_animationClips != nullptr) {
		//	//スケルトンを指定
		//	initData.m_skeleton = &m_skeleton;
		//}

		m_shadowModel.Init(initData);
	}

	void ModelRender::Update()
	{
		//ワールド座標更新
		m_renderToGBufferModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//スケルトンが初期化済みの場合
		if (m_skeleton.IsInited())
		{
			//スケルトン更新
			m_skeleton.Update(m_renderToGBufferModel.GetWorldMatrix());

			//アニメーションを進める
			m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
		}

	}

	void ModelRender::OnRenderToGBuffer(RenderContext& rc)
	{
		if (m_renderToGBufferModel.IsInited()) {
			m_renderToGBufferModel.Draw(rc, 1);
		}
	}

	void ModelRender::OnRenderShadowMap(
		RenderContext& rc,
		const Matrix& LigViewMatrix,
		const Matrix& LigProjMatrix,
		Vector3& lightPos)
	{
		m_lightPos = lightPos;
		if (m_isShadowCaster)
		{
			m_shadowModel.Draw(
				rc,
				LigViewMatrix,
				LigProjMatrix,
				1
			);
		}
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}
}
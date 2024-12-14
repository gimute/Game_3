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
		//�X�P���g����������
		InitSkeleton(tkmfilepath);
		//�A�j���[�V������������
		InitAnimation(animationClips, numAnimationClips);
		//G-Buffer�`��p�̃��f���̏�����
		InitModelOnRenderGBuffer(tkmfilepath, enModelUpAxis);
		//�V���h�E�}�b�v�`��p���f���̏�����
		InitShadowModel(tkmfilepath, enModelUpAxis);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//�X�P���g���̃f�[�^��ǂݍ���
		//���f���̃t�@�C���p�X�̖�����.tkm��.tks�ɂ��Ă����ǂݍ��ށA
		//���̂��߃X�P���g���ƃ��f���̃t�@�C���͓����t�@�C�����ɖ����Ƃ��̏����͋@�\���Ȃ��B
		//���ꂼ��ʂŎw�肳���Ă�������2���t�@�C���p�X�����̂͂߂�ǂ��̂ł��̂܂܂ŁB
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		//������t�@�C���p�X����X�P���g����ǂݍ���
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips)
	{
		//���������ꂼ�ꃁ���o�ϐ��ɑ��
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;

		if (m_animationClips != nullptr) 
		{
			//�A�j���[�V����������
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

		//�X�P���g��������������Ă�����
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}
		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
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

		//�萔�o�b�t�@�[�Ƀ��C�g�̃|�W�V���������鏀���A���ۂ̃��C�g�̒l�̓V���h�E��`�悷��Ƃ��Ɏ󂯎��
		initData.m_expandConstantBuffer = &m_lightPos;
		initData.m_expandConstantBufferSize = sizeof(m_lightPos);

		initData.m_colorBufferFormat[0] = g_ShadowMapFormat.colorBufferFormat;

		//�X�P���g��������������Ă�����
		if (m_skeleton.IsInited())
		{
			initData.m_skeleton = &m_skeleton;
		}
		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��B
		initData.m_vsEntryPointFunc = "VSMain";
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";

		//if (m_animationClips != nullptr) {
		//	//�X�P���g�����w��
		//	initData.m_skeleton = &m_skeleton;
		//}

		m_shadowModel.Init(initData);
	}

	void ModelRender::Update()
	{
		//���[���h���W�X�V
		m_renderToGBufferModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);

		//�X�P���g�����������ς݂̏ꍇ
		if (m_skeleton.IsInited())
		{
			//�X�P���g���X�V
			m_skeleton.Update(m_renderToGBufferModel.GetWorldMatrix());

			//�A�j���[�V������i�߂�
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
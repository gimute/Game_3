#pragma once

#include "myRenderer.h"

namespace nsK2EngineLow {
	class ModelRender : public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="tkmfilePath">tkm�t�@�C���p�X</param>
		void Init(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimarionClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		);

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();

		/// <summary>
		/// �`�揈��
		/// </summary>
		void Draw(RenderContext& rc);

		/// <summary>
		/// G-Buffer�`��p�X����Ă΂�鏈��
		/// </summary>
		void OnRenderToGBuffer(RenderContext& rc) override;

		void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& LigViewMatrix,
			const Matrix& LigProjMatrix,
			Vector3& lightPos) override;

		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="pos">���W</param>
		void SetPosition(Vector3 pos)
		{
			m_position = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rot">��]</param>
		void SetRotation(Quaternion rot)
		{
			m_rotation = rot;
		}


		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns>�N�I�[�^�j�I��</returns>
		Quaternion GetRotation()
		{
			return m_rotation;
		}

		/// <summary>
		/// �g���ݒ�
		/// </summary>
		/// <param name="scale">�g��</param>
		void SetScale(Vector3 scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}

		/// <summary>
		/// �V���h�E��X�^�[�t���O��ݒ肷��
		/// </summary>
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		/// <summary>
		/// �A�j���[�V�����Đ�
		/// </summary>
		/// <param name="animNo">�A�j���[�V�����̔ԍ�</param>
		/// <param name="interpolateTime">�⊮����</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		
		/// <summary>
		/// �A�j���[�V�����̍Đ����x��ݒ�
		/// </summary>
		/// <param name="animationSpeed">�Đ����x</param>
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		/// <summary>
		/// �A�j���[�V�����̍Đ����H
		/// </summary>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// <summary>
		/// �{�[���̖��O����{�[���ԍ��������B
		/// </summary>
		/// <param name="boneName">�{�[���̖��O</param>
		/// <returns>�{�[���ԍ��A������Ȃ������ꍇ��-1���Ԃ��Ă���</returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// �{�[���ԍ�����{�[�����擾�B
		/// </summary>
		/// <param name="boneNo">�{�[���ԍ�</param>
		/// <returns>�{�[��</returns>
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
		}

		//�A�j���[�V�����C�x���g
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}


		/// <summary>
		/// ���f�����擾
		/// </summary>
		/// <returns></returns>
		Model& GetModel()
		{
			return m_renderToGBufferModel;
		}

	private:
		/// <summary>
		/// �X�P���g���̏�����
		/// </summary>
		/// <param name="filePath">���f���̃t�@�C���p�X</param>
		void InitSkeleton(const char* filePath);

		/// <summary>
		/// G-Buffer�`��p���f���̏�����
		/// </summary>
		/// <param name="tkmfilepath">���f���̃t�@�C���p�X</param>
		void InitModelOnRenderGBuffer(
			const char* tkmfilepath,
			EnModelUpAxis enModelUpAxis
		);

		/// <summary>
		/// �V���h�E�}�b�v�p���f���̏�����
		/// </summary>
		/// <param name="tkmfilepath"></param>
		/// <param name="enModelUpAxis"></param>
		void InitShadowModel(
			const char* tkmfilepath,
			EnModelUpAxis enModelUpAxis
		);

		/// <summary>
		/// �A�j���[�V�����̏�����
		/// </summary>
		/// <param name="animationClips">�A�j���[�V�����N���b�v</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐�</param>
		/// <param name="enModelUpAxis">���f���̏����</param>
		void InitAnimation(
			AnimationClip* animationClips,
			int numAnimationClips
			);

	private:

		Model m_model;

		Skeleton m_skeleton;			//�{�[��
		AnimationClip* m_animationClips = nullptr;	//�A�j���[�V�����N���b�v
		int m_numAnimationClips = 0;	//�A�j���[�V�����N���b�v�̐�
		Animation m_animation;			//�A�j���[�V����
		float m_animationSpeed = 1.0f;	//�A�j���[�V�����̍Đ��X�s�[�h

		bool m_isShadowCaster = true;	//�V���h�E�L���X�^�[

		Model m_renderToGBufferModel;	//RenderToGBuffer�ŕ`�悳��郂�f��
		Model m_shadowModel;
		Vector3 m_lightPos = Vector3::Zero;	//�V���h�E�}�b�v�Ɏg�����C�g�̃|�W�V����

		Vector3 m_position = Vector3::Zero;	//���W
		Quaternion m_rotation = Quaternion::Identity;	//��]
		Vector3 m_scale = Vector3::One;	//�g�嗦
	};
}



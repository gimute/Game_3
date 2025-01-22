#pragma once

#include "myRenderer.h"

namespace nsK2EngineLow {
	class ModelRender : public IRenderer
	{
	public:
		ModelRender();
		~ModelRender();

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="tkmfilePath">tkmファイルパス</param>
		void Init(
			const char* tkmfilePath,
			AnimationClip* animationClips = nullptr,
			int numAnimarionClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ
		);

		/// <summary>
		/// 更新処理
		/// </summary>
		void Update();

		/// <summary>
		/// 描画処理
		/// </summary>
		void Draw(RenderContext& rc);

		/// <summary>
		/// G-Buffer描画パスから呼ばれる処理
		/// </summary>
		void OnRenderToGBuffer(RenderContext& rc) override;

		void OnRenderShadowMap(
			RenderContext& rc,
			const Matrix& LigViewMatrix,
			const Matrix& LigProjMatrix,
			Vector3& lightPos) override;

		/// <summary>
		/// 座標を設定
		/// </summary>
		/// <param name="pos">座標</param>
		void SetPosition(Vector3 pos)
		{
			m_position = pos;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}

		/// <summary>
		/// 回転を設定
		/// </summary>
		/// <param name="rot">回転</param>
		void SetRotation(Quaternion rot)
		{
			m_rotation = rot;
		}


		/// <summary>
		/// 回転を取得
		/// </summary>
		/// <returns>クオータニオン</returns>
		Quaternion GetRotation()
		{
			return m_rotation;
		}

		/// <summary>
		/// 拡大を設定
		/// </summary>
		/// <param name="scale">拡大</param>
		void SetScale(Vector3 scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}

		/// <summary>
		/// シャドウやスターフラグを設定する
		/// </summary>
		void SetShadowCasterFlag(bool flag)
		{
			m_isShadowCaster = flag;
		}

		/// <summary>
		/// アニメーション再生
		/// </summary>
		/// <param name="animNo">アニメーションの番号</param>
		/// <param name="interpolateTime">補完時間</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		
		/// <summary>
		/// アニメーションの再生速度を設定
		/// </summary>
		/// <param name="animationSpeed">再生速度</param>
		void SetAnimationSpeed(const float animationSpeed)
		{
			m_animationSpeed = animationSpeed;
		}

		/// <summary>
		/// アニメーションの再生中？
		/// </summary>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}

		/// <summary>
		/// ボーンの名前からボーン番号を検索。
		/// </summary>
		/// <param name="boneName">ボーンの名前</param>
		/// <returns>ボーン番号、見つからなかった場合は-1が返ってくる</returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// ボーン番号からボーンを取得。
		/// </summary>
		/// <param name="boneNo">ボーン番号</param>
		/// <returns>ボーン</returns>
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
		}

		//アニメーションイベント
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}


		/// <summary>
		/// モデルを取得
		/// </summary>
		/// <returns></returns>
		Model& GetModel()
		{
			return m_renderToGBufferModel;
		}

	private:
		/// <summary>
		/// スケルトンの初期化
		/// </summary>
		/// <param name="filePath">モデルのファイルパス</param>
		void InitSkeleton(const char* filePath);

		/// <summary>
		/// G-Buffer描画用モデルの初期化
		/// </summary>
		/// <param name="tkmfilepath">モデルのファイルパス</param>
		void InitModelOnRenderGBuffer(
			const char* tkmfilepath,
			EnModelUpAxis enModelUpAxis
		);

		/// <summary>
		/// シャドウマップ用モデルの初期化
		/// </summary>
		/// <param name="tkmfilepath"></param>
		/// <param name="enModelUpAxis"></param>
		void InitShadowModel(
			const char* tkmfilepath,
			EnModelUpAxis enModelUpAxis
		);

		/// <summary>
		/// アニメーションの初期化
		/// </summary>
		/// <param name="animationClips">アニメーションクリップ</param>
		/// <param name="numAnimationClips">アニメーションクリップの数</param>
		/// <param name="enModelUpAxis">モデルの上方向</param>
		void InitAnimation(
			AnimationClip* animationClips,
			int numAnimationClips
			);

	private:

		Model m_model;

		Skeleton m_skeleton;			//ボーン
		AnimationClip* m_animationClips = nullptr;	//アニメーションクリップ
		int m_numAnimationClips = 0;	//アニメーションクリップの数
		Animation m_animation;			//アニメーション
		float m_animationSpeed = 1.0f;	//アニメーションの再生スピード

		bool m_isShadowCaster = true;	//シャドウキャスター

		Model m_renderToGBufferModel;	//RenderToGBufferで描画されるモデル
		Model m_shadowModel;
		Vector3 m_lightPos = Vector3::Zero;	//シャドウマップに使うライトのポジション

		Vector3 m_position = Vector3::Zero;	//座標
		Quaternion m_rotation = Quaternion::Identity;	//回転
		Vector3 m_scale = Vector3::One;	//拡大率
	};
}



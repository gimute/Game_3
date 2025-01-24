#pragma once
namespace nsK2EngineLow {
	class SpriteRender : public IRenderer
	{
	public:
		SpriteRender() {};
		~SpriteRender() {};

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="filePath">�摜�̃t�@�C���p�X</param>
		/// <param name="w">����</param>
		/// <param name="h">�c��</param>
		/// <param name="alphaBlendMode">�A���t�@�u�����f�B���O���[�h</param>
		void Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="initData">�X�v���C�g�̏������f�[�^</param>
		void Init(SpriteInitData initData)
		{
			m_sprite.Init(initData);
		}

		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector2& pos)
		{
			m_position = { pos.x,pos.y,0.0f };
		}
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// �X�P�[����ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		/// <summary>
		/// �X�P�[�����擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rot"></param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}
		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// �s�{�b�g��ݒ�
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// �s�{�b�g���擾
		/// </summary>
		/// <returns></returns>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// ��Z�J���[��ݒ�
		/// </summary>
		/// <param name="mulColor"></param>
		void SetMulColor(const Vector4& mulColor)
		{
			m_sprite.SetMulColor(mulColor);
		}
		/// <summary>
		/// ��Z�J���[���擾
		/// </summary>
		/// <returns></returns>
		const Vector4& GetMulColor() const
		{
			return m_sprite.GetMulColor();
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update()
		{
			m_sprite.Update(
				m_position,
				m_rotation,
				m_scale,
				m_pivot);
		}

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc"></param>
		/// <remarks>
		/// �����_�����O�G���W���ɓo�^���鏈��
		/// </remarks>
		void Draw(RenderContext& rc);

		//2D�`��p�X����Ă΂�鏈��
		void OnRender2D(RenderContext& rc) override
		{
			m_sprite.Draw(rc);
		}

	private:
		Sprite		m_sprite;							//�X�v���C�g
		Vector3		m_position = Vector3::Zero;			//���W
		Quaternion	m_rotation = Quaternion::Identity;	//��]
		Vector3		m_scale = Vector3::One;				//�X�P�[��
		Vector2		m_pivot = Sprite::DEFAULT_PIVOT;	//�s�{�b�g
	};

}




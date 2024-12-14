#pragma once

namespace nsK2EngineLow {
	class SpotLight : public Noncopyable
	{
	public:
		~SpotLight();

		//������
		void Init();

		/// <summary>
		/// ���C�g�̍��W��ݒ�
		/// </summary>
		/// <param name="position">���C�g�̍��W</param>
		void SetPosition(const Vector3& position)
		{
			m_spotLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_spotLight->SetPosition(x, y, z);
		}
		/// <summary>
		/// ���C�g�̍��W���擾
		/// </summary>
		/// <returns>���C�g�̍��W</returns>
		const Vector3& GetPosition() const
		{
			return m_spotLight->GetPosition();
		}

		/// <summary>
		/// ���C�g�̃J���[��ݒ�
		/// </summary>
		/// <param name="color">���C�g�̃J���[</param>
		void SetColor(const Vector3& color)
		{
			m_spotLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_spotLight->SetColor(r, g, b);
		}
		/// <summary>
		/// ���C�g�̃J���[�̎擾
		/// </summary>
		/// <returns>���C�g�̃J���[</returns>
		const Vector3& GetColor() const
		{
			return m_spotLight->GetColor();
		}

		/// <summary>
		/// �ˏo������ݒ�
		/// </summary>
		/// <param name="direction"></param>
		void SetDirection(const Vector3& direction)
		{
			m_spotLight->SetDirection(direction);
		}
		void SetDirection(float x, float y, float z)
		{
			m_spotLight->SetDirection(x, y, z);
		}
		/// <summary>
		/// �ˏo�������擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetDirection() const
		{
			return m_spotLight->GetDirection();
		}

		/// <summary>
		/// �e���͈͂�ݒ�
		/// </summary>
		/// <param name="range"></param>
		void SetRange(float range)
		{
			m_spotLight->SetRange(range);
		}
		/// <summary>
		/// �e���͈͂��擾
		/// </summary>
		/// <returns></returns>
		float GetRange() const
		{
			return m_spotLight->GetRange();
		}

		/// <summary>
		/// �ˏo�͈͂�ݒ�
		/// </summary>
		/// <param name="angle">�ˏo�͈�(Degree)</param>
		void SetAngle_Deg(float angle)
		{
			//Deg��Rad�ɕϊ�
			angle = Math::DegToRad(angle);
			m_spotLight->SetAngle(angle);
		}
		/// <summary>
		/// �ˏo�͈͂��擾
		/// </summary>
		/// <returns>�ˏo�͈�</returns>
		const float GetAngle()const
		{
			return m_spotLight->GetAngle();
		}
		/// <summary>
		/// �ˏo�͈͂��擾
		/// </summary>
		/// <returns>�ˏo�͈�(Degree)</returns>
		const float GetAngle_Deg()const
		{
			//Rad��Deg�ɕϊ����Ă���n��
			return Math::RadToDeg(m_spotLight->GetAngle());
		}


		/// <summary>
		/// �����ɂ��e�����̗ݏ搔��ݒ�
		/// </summary>
		/// <param name="powParam"></param>
		void SetRangeAffectPowParam(float powParam)
		{
			m_spotLight->SetRangeAffectPowParam(powParam);
		}

		/// <summary>
		/// �p�x�ɂ��ݏ搔��ݒ�
		/// </summary>
		/// <param name="powParam"></param>
		void SetAngleAffectPowParam(float powParam)
		{
			m_spotLight->SetAngleAffectPowParam(powParam);
		}

		/// <summary>
		/// ���f�[�^���擾
		/// </summary>
		/// <returns></returns>
		const SSpotLight& GetRawData() const
		{
			return *m_spotLight;
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update()
		{
			m_spotLight->Update();
		}

		

	private:
		SSpotLight* m_spotLight = nullptr;	//�g�p���郉�C�g�̃|�C���^

	};
}


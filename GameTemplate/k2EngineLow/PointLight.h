#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// �|�C���g���C�g
	/// </summary>
	class PointLight : public Noncopyable
	{
	public:
		~PointLight();

		//������
		void Init();

		/// <summary>
		/// ���C�g�̍��W��ݒ�
		/// </summary>
		/// <param name="position">���C�g�̍��W</param>
		void SetPosition(const Vector3& position)
		{
			m_pointLight->SetPosition(position);
		}
		void SetPosition(float x, float y, float z)
		{
			m_pointLight->SetPosition(x, y, z);
		}
		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns>���C�g�̍��W</returns>
		const Vector3& GetPosition() const
		{
			return m_pointLight->GetPosition();
		}

		/// <summary>
		/// ���C�g�̃J���[��ݒ�
		/// </summary>
		/// <param name="color">���C�g�̃J���[</param>
		void SetColor(const Vector3& color)
		{
			m_pointLight->SetColor(color);
		}
		void SetColor(float r, float g, float b)
		{
			m_pointLight->SetColor(r, g, b);
		}
		/// <summary>
		/// ���C�g�̃J���[���擾
		/// </summary>
		/// <returns>���C�g�̃J���[</returns>
		const Vector3& GetColor() const
		{
			return m_pointLight->GetColor();
		}

		/// <summary>
		/// �e���͈͂�ݒ�
		/// </summary>
		/// <param name="range"></param>
		void SetRange(float range)
		{
			m_pointLight->SetRange(range);
		}
		/// <summary>
		/// �e���͈͂��擾
		/// </summary>
		/// <returns></returns>
		float GetRange() const
		{
			return m_pointLight->GetRange();
		}

		/// <summary>
		/// �e�����̗ݏ搔��ݒ�
		/// </summary>
		/// <param name="powParam"></param>
		void SetAffectPowParam(float powParam)
		{
			m_pointLight->SetAffectPowParam(powParam);
		}

		/// <summary>
		/// ���f�[�^���擾
		/// </summary>
		/// <returns></returns>
		const SPointLight& GetRawData() const
		{
			return *m_pointLight;
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update()
		{
			m_pointLight->Updata();
		}
		
		
		

	private:
		SPointLight* m_pointLight = nullptr;	//�g�p���郉�C�g�̃|�C���^
	};
}


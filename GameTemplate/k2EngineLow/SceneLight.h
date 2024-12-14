#pragma once

namespace nsK2EngineLow {

	//�f�B���N�V�������C�g�\����
	struct DirectionLight
	{
		Vector3 direction = Vector3::Zero;
		int castShadow = true;
		Vector3 color = Vector3::Zero;
		float pad;
	};

	//�|�C���g���C�g�̍\����
	struct SPointLight
	{
	private:
		Vector3 position = g_vec3Zero;		//���W
		int isUse = false;					//�g�p���t���O
		Vector3 color = g_vec3One;			//���C�g�̃J���[
		float range;						//�e���͈�
		Vector3 positionInView;				//�J������Ԃł̍��W
		int pow;							//�e�����̗ݏ搔

		//Vector3 position = g_vec3Zero;		//���W
		//int isUse = false;					//�g�p���t���O
		//Vector3 color = g_vec3One;			//���C�g�̃J���[
		//float pad1;
		//Vector3 attn = { 1.0f,1.0f,0.0f };	//�����p�����[�^�Bx�ɉe���͈́Ay�ɂ͉e�����ɗݏ悷��p�����[�^
		//float pad2;
	public:
		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			this->position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		//���W���擾
		const Vector3& GetPosition() const
		{
			return position;
		}

		//�J���[��ݒ�
		void SetColor(const Vector3& color)
		{
			this->color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r, g, b });
		}
		//�J���[���擾
		const Vector3& GetColor() const
		{
			return color;
		}

		//�͈͂�ݒ�
		void SetRange(float range)
		{
			this->range = range;
		}
		//�e���͈͂��擾
		float GetRange() const
		{
			return range;
		}

		//�e�����̗ݏ搔��ݒ�B
		void SetAffectPowParam(float powParam)
		{
			pow = powParam;
		}

		//�|�C���g���C�g���g�p���ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void Use()
		{
			isUse = true;
		}
		//�|�C���g���C�g�𖢎g�p�ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void UnUse()
		{
			isUse = false;
		}
		//�|�C���g���C�g���g�p�������ׂ�
		const int GetUse() const
		{
			return isUse;
		}

		//�X�V����
		void Updata();
	};

	//�X�|�b�g���C�g�̍\����
	struct SSpotLight
	{
	private:
		Vector3 position = g_vec3Zero;	//���W
		int isUse = false;				//�g�p���t���O
		Vector3 color = g_vec3One;		//���C�g�̃J���[
		float range = 0.0f;					//�e���͈�
		Vector3 direction = g_vec3Down;	//�ˏo����
		float angle = 0.0f;					//�ˏo�͈�
		Vector3 positionInView;			//�J������Ԃł̍��W
		float rangePow;					//�����ɂ��e�����̗ݏ搔
		Vector3 directionInView;            // �J������Ԃł̎ˏo�����B
		float anglePow;					//�p�x�ɂ��e�����̗ݏ搔

	public:
		//���W��ݒ�
		void SetPosition(const Vector3& position)
		{
			this->position = position;
		}
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		//���W���擾
		const Vector3& GetPosition() const
		{
			return position;
		}

		//���C�g�̃J���[��ݒ�
		void SetColor(const Vector3 color)
		{
			this->color = color;
		}
		void SetColor(float r, float g, float b)
		{
			SetColor({ r, g, b });
		}
		//���C�g�̃J���[���擾
		const Vector3& GetColor() const
		{
			return color;
		}

		//�ˏo������ݒ�
		void SetDirection(const Vector3& direction)
		{
			this->direction = direction;
			this->direction.Normalize();
		}
		void SetDirection(float x, float y, float z)
		{
			direction.Set(x, y, z);
			direction.Normalize();
		}
		//�ˏo�������擾
		const Vector3& GetDirection() const
		{
			return direction;
		}

		//�X�|�b�g���C�g���g�p���ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void Use()
		{
			isUse = true;
		}
		//�X�|�b�g���C�g�𖢎g�p�ɂ���
		//�G���W���Ŏg�p���邽�߂̊֐��Ȃ̂ŃQ�[��������Ăяo���Ȃ��悤����
		void UnUse()
		{
			isUse = false;
		}
		//�X�|�b�g���C�g���g�p�������ׂ�
		const int GetUse() const
		{
			return isUse;
		}


		//�e���͈͂�ݒ�
		void SetRange(float range)
		{
			this->range = range;
		}
		//�e���͈͂��擾
		const float GetRange() const
		{
			return range;
		}

		//�ˏo�͈͂�ݒ�
		void SetAngle(float angle)
		{
			this->angle = angle;
		}
		//�ˏo�͈͂��擾
		const float GetAngle() const
		{
			return angle;
		}

		//���̋����ɂ��e�����ɗݏ悷��l��ݒ�
		void SetRangeAffectPowParam(float powParam)
		{
			rangePow = powParam;
		}

		//���̊p�x�ɂ��e�����ɗݏ悷��l��ݒ�
		void SetAngleAffectPowParam(float powParam)
		{
			anglePow = powParam;
		}

		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
	};

	//���C�g�\����
	struct Light
	{
		DirectionLight directionalLight;	// �f�B���N�V�������C�g�\����
		SPointLight pointLights[MAX_POINT_LIGHT];	//�|�C���g���C�g�̔z��
		SSpotLight spotLights[MAX_SPOT_LIGHT];	//�X�|�b�g���C�g�̔z��
		Vector3 eyePos = Vector3::Zero;		// ���_�̈ʒu
		int numPointLight;					//�|�C���g���C�g�̐�
		Vector3 ambientLight = Vector3::Zero;	//����
		int numSpotLight;					//�X�|�b�g���C�g�̐�
		Vector3 eyeDir = Vector3::Zero;		//�����̕���
		float pad3;
	};

	class SceneLight : public Noncopyable
	{
	private:

	public:
		SceneLight();
		~SceneLight();

		//������
		void Init();

		//�X�V����
		void Update();

		//�V�[�����C�g���擾
		Light& GetSceneLight()
		{
			return m_light;
		}

		//�f�B���N�V�������C�g�̃p�����[�^��ݒ�
		void SetDirectionLight(int lightNo, Vector3 direction, Vector3 color)
		{
			direction.Normalize();
			m_light.directionalLight.direction = direction;
			m_light.directionalLight.color = color;
		}

		//������ݒ�
		void SetAmbient(Vector3 ambientcolor)
		{
			m_light.ambientLight = ambientcolor;
		}

		/// <summary>
		/// �V�[���Ƀ|�C���g���C�g��ǉ�
		/// </summary>
		/// <remark>
		/// ���̊֐��Œǉ������|�C���g���C�g��
		/// �s�v�ɂȂ�����DeletePointLight�֐����g�p���č폜���Ă�������
		/// </remark>
		/// <returns>�ǉ����ꂽ�|�C���g���C�g�̃A�h���X</returns>
		SPointLight* NewPointLight()
		{
			return NewDynamicLight<SPointLight>(m_unusePointLightQueue);
		}

		/// <summary>
		/// �V�[���ɃX�|�b�g���C�g��ǉ�
		/// </summary>
		/// <remark>
		/// ���̊֐��Œǉ������X�|�b�g���C�g��
		/// �s�v�ɂȂ�����DeletePointLight�֐����g�p���č폜���Ă�������
		/// </remark>
		/// <returns>�ǉ����ꂽ�X�|�b�g���C�g�̃A�h���X</returns>
		SSpotLight* NewSpotLight()
		{
			return NewDynamicLight<SSpotLight>(m_unuseSpotLightQueue);
		}

		/// <summary>
		/// �V�[������|�C���g���C�g���폜
		/// </summary>
		/// <param name="pointLight">�폜����|�C���g���C�g</param>
		void DeletePointLight(SPointLight* pointLight)
		{
			DeleteDynamicLight<SPointLight>(pointLight, m_unusePointLightQueue);
		}


		/// <summary>
		/// �V�[������X�|�b�g���C�g���폜
		/// </summary>
		/// <param name="spotLight">�폜����X�|�b�g���C�g</param>
		void DeleteSpotLight(SSpotLight* spotLight)
		{
			DeleteDynamicLight<SSpotLight>(spotLight, m_unuseSpotLightQueue);
		}

	private:
		/// <summary>
		/// �V�������I���C�g��ǉ��B
		/// </summary>
		/// <typeparam name="TDynamicLight">�ǉ����铮�I���C�g�̎��</typeparam>
		/// <typeparam name="TQue">�g�p���関�g�p���C�g�̃L���[�̌^</typeparam>
		/// <param name="que">�g�p���関�g�p���C�g�̃L���[</param>
		/// <returns>���C�g�̒ǉ����ł��Ȃ����nullptr���A�ǉ��ł�����ǉ��������C�g�̃|�C���^��Ԃ�</returns>
		template<class TDynamicLight>
		TDynamicLight* NewDynamicLight(std::deque<TDynamicLight*>& que)
		{
			if (que.empty()) {
				//���g�p�̃��C�g���Ȃ�
				return nullptr;
			}
			//���g�p�̃��C�g���L���[������o��
			TDynamicLight* newPt = que.front();
			//�g�p���ɂ���
			newPt->Use();
			//���o�����v�f��擪���珜��
			que.pop_front();
			return newPt;
		}

		/// <summary>
		/// �V�[�����瓮�I���C�g���폜
		/// </summary>
		/// <param name="pointLight">�폜����|�C���g���C�g</param>
		template<class TDynamicLight>
		void DeleteDynamicLight(TDynamicLight* light, std::deque<TDynamicLight*>& que)
		{
			if (light != nullptr) {
				//�t���O�𖢎g�p�ɕύX����
				light->UnUse();
				//���g�p���X�g�ɒǉ�����
				que.push_back(light);
			}
		}

	private:
		Light m_light;	//�V�[�����C�g
		std::deque<SPointLight*> m_unusePointLightQueue;	//���g�p�̃|�C���g���C�g�̃|�C���^�̃L���[
		std::deque<SSpotLight*> m_unuseSpotLightQueue;		//���g�p�̃X�|�b�g���C�g�̃|�C���^�̃L���[
	};
}

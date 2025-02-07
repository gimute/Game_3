#pragma once


namespace {
	static const int MAX_TEXT_SIZE = 256;
}

namespace nsK2EngineLow {
	//�t�H���g�����_�[
	class FontRender : public IRenderer
	{
	public:
		FontRender() {};
		~FontRender() {};

		//�\�����镶����ݒ�
		void SetText(const wchar_t* text)
		{
			swprintf_s(m_text, text);
		}
		//�\�����镶�����擾
		const wchar_t* GetText() const
		{
			return m_text;
		}

		/// <summary>
		/// ���W��ݒ�
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(Vector2 pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// ���W���擾
		/// </summary>
		/// <returns></returns>
		const Vector2& GetPosition() const
		{
			return m_position;
		}

		/// <summary>
		/// �g�嗦��ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const float scale)
		{
			m_scale = scale;
		}
		
		/// <summary>
		/// �g�嗦���擾
		/// </summary>
		/// <returns></returns>
		const float& GetScale() const
		{
			return m_scale;
		}

		/// <summary>
		/// ��]��ݒ�
		/// </summary>
		/// <param name="rotation">��]�ʁA������������Ɣ����v���A����������Ǝ��v���</param>
		void SetRotation(const float rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// ��]���擾
		/// </summary>
		/// <returns></returns>
		const float& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// �F��ݒ�
		/// </summary>
		/// <param name="color"></param>
		void SetColor(const Vector4& color)
		{
			m_color = color;
		}
		void SetColor(float r, float g, float b, float a)
		{
			SetColor({ r,g,b,a });
		}

		/// <summary>
		/// �F���擾
		/// </summary>
		/// <returns></returns>
		const Vector4& GetColor() const
		{
			return m_color;
		}

		/// <summary>
		/// �e�̃p�����[�^��ݒ�B
		/// </summary>
		/// <param name="isDrawShadow">�e��`�悷��H</param>
		/// <param name="shadowOffset">�e��`�悷��Ƃ��̃s�N�Z���̃I�t�Z�b�g�ʁB</param>
		/// <param name="shadowColor">�e�̐F�B</param>
		void SetShadowParam(bool isDrawShadow, float shadowOffset, const Vector4& shadowColor)
		{
			m_font.SetShadowParam(isDrawShadow, shadowOffset, shadowColor);
		}

		/// <summary>
		/// �s�{�b�g��ݒ�
		/// </summary>
		/// <param name="pivot"></param>
		void SetPivot(Vector2 pivot)
		{
			m_pivot = pivot;
		}
		
		/// <summary>
		/// �s�{�b�g���擾
		/// </summary>
		const Vector2& GetPivot() const
		{
			return m_pivot;
		}


		//�`�揈���B
		void Draw(RenderContext& rc);

		//2D�̕`�揈��
		void OnRender2D(RenderContext& rc) override;


	private:
		Vector2 m_position = Vector2::Zero;
		float m_rotation = 0.0f;
		float m_scale = 1.0f;
		Vector4 m_color = g_vec4White;
		Vector2 m_pivot = Sprite::DEFAULT_PIVOT;

		wchar_t m_text[MAX_TEXT_SIZE];
		Font m_font;
	};
}




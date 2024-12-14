#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {

    void SPointLight::Updata()
    {
        //�g�p���̃��C�g�J�����̓J������Ԃł̍��W���v�Z����
        if (!isUse)
        {
            return;
        }
        positionInView = position;
        g_camera3D->GetViewMatrix().Apply(positionInView);
    }

    void SSpotLight::Update()
    {
        // �g�p���̃��C�g�̓J������Ԃł̍��W���v�Z����B
        if (!isUse) {
            return;
        }
        positionInView = position;
        g_camera3D->GetViewMatrix().Apply(positionInView);

        //�J������Ԃł̃��C�g�̕������v�Z����
        //directionInView = direction;
        Matrix cameraRotInv = g_camera3D->GetCameraRotation();
        cameraRotInv.Inverse();
        cameraRotInv.Apply(directionInView);
    }

    SceneLight::SceneLight()
    {

    }

    SceneLight::~SceneLight()
    {

    }

    void SceneLight::Init()
    {
        //���z��
        m_light.directionalLight.color.x = 1.0f;
        m_light.directionalLight.color.y = 1.0f;
        m_light.directionalLight.color.z = 1.0f;

        m_light.directionalLight.direction.x = 0.0f;
        m_light.directionalLight.direction.y = -1.0f;
        m_light.directionalLight.direction.z = 1.0f;
        m_light.directionalLight.direction.Normalize();
        m_light.directionalLight.castShadow = true;

        //���_�̈ʒu
        m_light.eyePos = g_camera3D->GetPosition();

        //����
        m_light.ambientLight.x = 0.2f;
        m_light.ambientLight.y = 0.2f;
        m_light.ambientLight.z = 0.2f;

        //�����̕���
        m_light.eyeDir = g_camera3D->GetForward();

        //�S�Ẵ|�C���g���C�g�𖢎g�p�ɂ���
        for (auto& pt : m_light.pointLights) {
            pt.UnUse();
            m_unusePointLightQueue.push_back(&pt);
        }
        //�S�ẴX�|�b�g���C�g�𖢎g�p�ɂ���
        for (auto& sp : m_light.spotLights) {
            sp.UnUse();
            m_unuseSpotLightQueue.push_back(&sp);
        }
    }

    void SceneLight::Update()
    {
        //���_�̈ʒu
        m_light.eyePos = g_camera3D->GetPosition();
        //�����̕���
        m_light.eyeDir = g_camera3D->GetForward();

        m_light.numPointLight = MAX_POINT_LIGHT - static_cast<int>(m_unusePointLightQueue.size());
        m_light.numSpotLight = MAX_SPOT_LIGHT - static_cast<int>(m_unuseSpotLightQueue.size());

        //m_light.eyeDir.Normalize();

    }
}

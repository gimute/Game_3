#include "k2EngineLowPreCompile.h"
#include "SceneLight.h"

namespace nsK2EngineLow {

    void SPointLight::Updata()
    {
        //使用中のライトカメラはカメラ空間での座標を計算する
        if (!isUse)
        {
            return;
        }
        positionInView = position;
        g_camera3D->GetViewMatrix().Apply(positionInView);
    }

    void SSpotLight::Update()
    {
        // 使用中のライトはカメラ空間での座標を計算する。
        if (!isUse) {
            return;
        }
        positionInView = position;
        g_camera3D->GetViewMatrix().Apply(positionInView);

        //カメラ空間でのライトの方向を計算する
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
        //太陽光
        m_light.directionalLight.color.x = 1.0f;
        m_light.directionalLight.color.y = 1.0f;
        m_light.directionalLight.color.z = 1.0f;

        m_light.directionalLight.direction.x = 0.0f;
        m_light.directionalLight.direction.y = -1.0f;
        m_light.directionalLight.direction.z = 1.0f;
        m_light.directionalLight.direction.Normalize();
        m_light.directionalLight.castShadow = true;

        //視点の位置
        m_light.eyePos = g_camera3D->GetPosition();

        //環境光
        m_light.ambientLight.x = 0.2f;
        m_light.ambientLight.y = 0.2f;
        m_light.ambientLight.z = 0.2f;

        //視線の方向
        m_light.eyeDir = g_camera3D->GetForward();

        //全てのポイントライトを未使用にする
        for (auto& pt : m_light.pointLights) {
            pt.UnUse();
            m_unusePointLightQueue.push_back(&pt);
        }
        //全てのスポットライトを未使用にする
        for (auto& sp : m_light.spotLights) {
            sp.UnUse();
            m_unuseSpotLightQueue.push_back(&sp);
        }
    }

    void SceneLight::Update()
    {
        //視点の位置
        m_light.eyePos = g_camera3D->GetPosition();
        //視線の方向
        m_light.eyeDir = g_camera3D->GetForward();

        m_light.numPointLight = MAX_POINT_LIGHT - static_cast<int>(m_unusePointLightQueue.size());
        m_light.numSpotLight = MAX_SPOT_LIGHT - static_cast<int>(m_unuseSpotLightQueue.size());

        //m_light.eyeDir.Normalize();

    }
}

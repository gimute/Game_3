///////////////////////////////////////
//ボリュームライト描画シェーダー
///////////////////////////////////////

//サンプラー
sampler Sampler : register(s0);

///////////////////////////////////////
// 構造体
///////////////////////////////////////

//ポイントライト
struct PointLight
{
    float3 position; //座標
    int isUse; //使用中フラグ
    float3 color; //ライトのカラー
    float range; //影響範囲
    float3 posintionInView; //カメラ空間での座標
    int pow; //影響率の累乗数
};

//スポットライト
struct SpotLight
{
    float3 position; //座標
    int isUse; //使用中フラグ
    float3 color; //ライトのカラー
    float range; //影響範囲
    float3 direction; //射出方向
    float angle; //射出範囲
    float3 positionInView; //カメラ空間での座標
    float rangePow; //距離による影響率の累乗数
    float3 directionInView; // カメラ空間での射出方向。
    float anglePow; //角度による影響率の累乗数
};

///////////////////////////////////////
// 定数バッファ。
///////////////////////////////////////

cbuffer cb : register(b0)
{
    float4x4 mvp; 
    float4 mulColor;
};

//ポイントライト用の定数バッファー
cbuffer finalPointLightCb : register(b1)
{
    PointLight pointLight; //スポットライト
    float4x4 ptLig_mViewProjInv; //ビュープロジェクション行列の逆行列
    float ptLig_randomSeed; //ランダムシード
}

//スポットライト用の定数バッファー
cbuffer finalSpotLightCb : register(b1)
{
    SpotLight spotLight;    //スポットライト
    float4x4 spLig_mViewProjInv;  //ビュープロジェクション行列の逆行列
    float spLig_randomSeed; //ランダムシード
}

struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

Texture2D<float4> albedoTexture : register(t0); // アルベドカラー
Texture2D<float4> g_volumeLightMapFront : register(t1);
Texture2D<float4> g_volumeLightMapBack : register(t2);

PSInput VSFinal(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    
    return psIn;
}

float GetRandomNumber(float2 texCoord, float Seed)
{
    return frac(sin(dot(texCoord.xy, float2(12.9898, 78.233)) + Seed) * 43758.5453);
}


float3 CalcWorldPosFromUVZ(float2 uv, float zInScreen, float4x4 mViewProjInv)
{
    float3 screenPos;
    screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2(-1.0f, 1.0f);
    screenPos.z = zInScreen;
    
    float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
    worldPos.xyz /= worldPos.w;
    return worldPos.xyz;
}

float4 PSFinal_SpotLight(PSInput In) : SV_Target0
{
    float3 lig = 0;
    float2 uv = In.uv;
    
    //ボリュームライトの深度値を受け取る
    float volumeFrontZ = g_volumeLightMapFront.Sample(Sampler, uv).r;
    float volumeBackZ = g_volumeLightMapBack.Sample(Sampler, uv).r;
    
    //ボリュームライトの深度値からワールド座標を復元する
    float3 volumePosBack = CalcWorldPosFromUVZ(uv, volumeBackZ, spLig_mViewProjInv);
    float3 volumePosFront = CalcWorldPosFromUVZ(uv, volumeFrontZ, spLig_mViewProjInv);
    
    float t0 = dot(spotLight.direction, volumePosFront - spotLight.position);
    float t1 = dot(spotLight.direction, volumePosBack - spotLight.position);
    float t = t0 / (t0 + t1);
    //ボリュームライトの中心?
    float3 volumeCenterPos = lerp(volumePosFront, volumePosBack, t);
    float volume = length(volumePosBack - volumePosFront);
    
    //ボリュームが無い箇所はピクセルキル
    clip(volume - 0.001f);
    
    //ピクセルのカラーを取得
    float4 albedoColor = albedoTexture.Sample(Sampler, uv);
    
    //距離による光の影響率を計算
    float3 ligDir = (volumeCenterPos - spotLight.position);
    float distance = length(ligDir);
    ligDir = normalize(ligDir);
    float3 affectBase = 1.0f - min(1.0f, distance / spotLight.range);
    float3 affect = pow(affectBase, spotLight.rangePow);

    //続いて角度による減衰を計算する
    //角度に比例して小さくなっていく影響率を計算する
    float angleLigToPixel = saturate(dot(ligDir, spotLight.direction));
    
    //dot()で求めた値をacos()に渡して角度を求める
    angleLigToPixel = abs(acos(angleLigToPixel));
    
    //角度による減衰を計算
    float3 angleAffectBase = max(0.0f, 1.0f - 1.0f / spotLight.angle * angleLigToPixel);
    angleAffectBase = min(1.0f, angleAffectBase * 1.8f);
    float3 angleAffect = pow(angleAffectBase, spotLight.anglePow);
    affect *= angleAffect;
    
    //三つの光を合成
    //光のベースを計算
    float3 ligBase = albedoColor * step(volumeFrontZ, albedoColor.w) * max(0.0f, log(volume)) * 0.1f;
    //光のベースに影響率を乗算する
    lig = ligBase * affect * spotLight.color;
    lig += ligBase * affect.y * spotLight.color;
    lig += ligBase * affect.z * spotLight.color;
    
    // 空気中のチリの表現としてノイズを加える。
    lig *= lerp(0.9f, 1.1f, GetRandomNumber(uv, spLig_randomSeed));

    return float4(lig, 1.0f);
}

float4 PSFinal_PointLight(PSInput In) : SV_Target0
{
    float3 lig = 0;
    float2 uv = In.uv;
	
    float volumeFrontZ = g_volumeLightMapFront.Sample(Sampler, uv).r;
    float volumeBackZ = g_volumeLightMapBack.Sample(Sampler, uv).r;
  
    float3 volumePosBack = CalcWorldPosFromUVZ(uv, volumeBackZ, ptLig_mViewProjInv);
    float3 volumePosFront = CalcWorldPosFromUVZ(uv, volumeFrontZ, ptLig_mViewProjInv);
    

    
    float3 volumeCenterPos = (volumePosFront + volumePosBack) * 0.5f;
    float volume = length(volumePosBack - volumePosFront);

    // ボリュームがない箇所はピクセルキル。
    clip(volume - 0.001f);

    float4 albedoColor = albedoTexture.Sample(Sampler, uv);
    
    // 距離による減衰。
    float3 ligDir = (volumeCenterPos - pointLight.position);
    float distance = length(ligDir);
    ligDir = normalize(ligDir);
    float affect = pow(1.0f - min(1.0f, distance / pointLight.range), pointLight.pow);

    lig = albedoColor * pointLight.color * affect * step(volumeFrontZ, albedoColor.w) * max(0.0f, log(volume)) * 0.05f;
    lig *= lerp(0.9f, 1.1f, GetRandomNumber(uv, ptLig_randomSeed));
    return float4(lig, 1.0f);
}
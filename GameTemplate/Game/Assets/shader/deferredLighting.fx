///////////////////////////////////////////////////////////
//定数
///////////////////////////////////////////////////////////
static const int MAX_POINT_LIGHT = 250; // ポイントライトの最大数
static const int MAX_SPOT_LIGHT = 250; // スポットライトの最大数

// 一度に実行されるスレッド数
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

///////////////////////////////////////////////////////////
//構造体
///////////////////////////////////////////////////////////
// ディレクションライト
struct DirectionalLight
{
    float3 direction; //ライトの方向
    int castShadow; //影をキャストするか？
    float3 color; //ライトのカラー
    
};

//ポイントライト
struct PointLight
{
    float3 position;    //座標
    int isUse;          //使用中フラグ
    float3 color;       //ライトのカラー
    float range;        //影響範囲
    float3 posintionInView; //カメラ空間での座標
    int pow;            //影響率の累乗数
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

///////////////////////////////////////////////////////////
//定数バッファー
///////////////////////////////////////////////////////////
cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
    float4 screenParam;
};

cbuffer LightCb : register(b1)
{
    //ライト情報
    DirectionalLight directionalLight;  //ディレクションライト
    PointLight pointLights[MAX_POINT_LIGHT]; //ポイントライトの配列
    SpotLight spotLights[MAX_SPOT_LIGHT];   //スポットライトの配列
    float3 eyePos;                      //視点
    int numPointLight;                  //ポイントライトの数
    float3 ambientLig;                     //環境光
    int numSpotLight;                   //スポットライトの数
    float3 eyeDir;      //視線の方向
    
    //その他
    float4x4 mViewProjInv;  //ゲームカメラのビュープロジェクション行列の逆行列
    
    float4x4 mlvp;  //シャドウ用ライトカメラのビュープロジェクション行列
    
    float3 ligCameraPos;    //シャドウマップ用のライトカメラのポジション

};

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

Texture2D<float4> albedoTexture : register(t0); // アルベド
Texture2D<float4> normalTexture : register(t1); // 法線
Texture2D<float> deothTexture : register(t2);   // 射影空間に正規化された深度値
Texture2D<float4> g_shadowMap : register(t3);  //シャドウマップ

// タイルごとのポイントライトのインデックスのリスト
StructuredBuffer<uint> pointLightListInTile : register(t20);
StructuredBuffer<uint> spotLightListInTile : register(t21);


sampler Sampler : register(s0);
///////////////////////////////////////////////////////////
//関数宣言
///////////////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor, float3 normal);
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower);
float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normal);
float3 CalcLighting(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower); //ライトの共通処理
float3 CalcLigFromDirectionLight(float3 normal, float3 worldPos, float specPower);
float3 CalcLigFromPointLight(float3 normal, float3 worldPos, float specPower, uint tileIndex);
float3 CalcLigFromSpotLight(float3 normal, float3 worldPos, float specPower, uint tileIndex);
//UV座標と深度値からワールド座標を計算する
float3 CalcWorldPosFromUVZ(float2 uv, float zInProjectionSpace, float4x4 mViewProjInv)
{
    float3 screenPos;
    screenPos.xy = (uv * float2(2.0f, -2.0f)) + float2(-1.0f, 1.0f);
    screenPos.z = zInProjectionSpace;

    float4 worldPos = mul(mViewProjInv, float4(screenPos, 1.0f));
    worldPos.xyz /= worldPos.w;
    return worldPos.xyz;
}

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    
    return psIn;
}

//ピクセルシェーダのエントリー関数
float4 PSMain(PSInput In) : SV_Target0
{
    //TBR用の処理
    //このピクセルが含まれているタイルの番号を計算する
    //スクリーンをタイルで分割した時のセルのX座標を求める
    uint numCellX = (screenParam.z + TILE_WIDTH - 1) / TILE_WIDTH;
    
    //タイルインデックスを計算する
    uint tileIndex = floor(In.pos.x / TILE_WIDTH)
                   + floor(In.pos.y / TILE_HEIGHT) * numCellX;
    
    
    ////////////////////////////////////////////////////////////
    
    
    // G-Bufferの内容をサンプリング
    float4 albedo = albedoTexture.Sample(Sampler, In.uv);
    float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
    float specPower = normalTexture.Sample(Sampler, In.uv).w;
    
    //法線を(0~1)から(-1~1)に復元してるっぽい
    normal = (normal * 2.0) - 1.0f;
    //長さが1を越えないように正規化
    normal = normalize(normal);
    
    float z = deothTexture.Sample(Sampler, In.uv);
    
    //射影空間の深度値からワールド座標を復元する
    float3 worldPos = CalcWorldPosFromUVZ(In.uv, z, mViewProjInv);
    
    
    //ディレクションライトによる光を求める
    float3 directionLight = CalcLigFromDirectionLight(normal, worldPos, specPower);
    //ポイントライトによる光を求める
    float3 pointLight = CalcLigFromPointLight(normal, worldPos, specPower, tileIndex);
    //スポットライトによる光を求める
    float3 spotLight = CalcLigFromSpotLight(normal, worldPos, specPower, tileIndex);
    
    //求めたライトの光と環境光を全て足して最終的な光を求める
    float3 finalLig = directionLight + pointLight + spotLight + ambientLig;
    
    //シャドウイング
    //ライトから見た座標を出す
    float4 posInLVP = mul(mlvp, float4(worldPos, 1.0f));
    
    //UV空間に座標変換
    //ライトから見た座標を正規化スクリーン座標系にし
    float2 shadowMapUV = posInLVP.xy / posInLVP.w;
    //左上が-1.0f,1.0fから
    //左上が0.0f,0.0fになるようにして、UV空間に変更
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;   

    //シャドウマップの範囲内かどうか判定
    if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
    {
        //シャドウマップから値をサンプリング
        float2 shadowValue = g_shadowMap.Sample(Sampler, shadowMapUV).xy;
        
        //ピクセルからライトの距離を計算する
        float zInLVP = length(worldPos.xyz - ligCameraPos) / 1000.0f;
        
        //このピクセルが遮蔽されているか調べる
        if(zInLVP > shadowValue.r && zInLVP <= 1.0f)
        {            
            //チェビシェフの不等式を利用して光が当たる確率を求める
            
            float depth_sq = shadowValue.x * shadowValue.x;
            
            //このグループの分散具合を求める
            //分散が大きいほど、varianceの数値は大きくなる
            float variance = min(shadowValue.y - depth_sq, 0.0001f);
            
            //このピクセルライトから見た深度値とシャドウマップの平均の深度値の差を求める
            float md = zInLVP - shadowValue.x;

            //光が届く確率を求める
            float lit_factor = variance / (variance + md * md);
            
            //元からディレクションライトの光を反射しない面は光が届く確立をいじって影を弱める
            float t = max(0.0f, dot(normal, directionalLight.direction) * -1.0f);
            lit_factor = min(1.0f, lit_factor + (1 - t));
            
            //シャドウカラーを求める
            float3 shadowColor = albedo.xyz * 0.5f;
            
            //光が当たる確率を使って通常カラーとシャドウカラーを線形補間
            albedo.xyz = lerp(shadowColor, albedo.xyz, lit_factor);
        }
        
    }
    
    //最終的な出力カラーを求める
    //ピクセルの色を受け取り
    float4 finalColor = albedo;
    //求めた最終的な光を乗算する
    finalColor.xyz *= finalLig;
    
    //求めた最終カラーを返す
    return finalColor;
}

///////////////////////////////////////////////////////////
//関数定義
///////////////////////////////////////////////////////////

//Lambert拡散反射光の計算
float3 CalcLambertDiffuse(float3 ligDir, float3 ligColor, float3 normal)
{   
    float t = max(0.0f, dot(normal, ligDir) * -1.0f);

    return ligColor * t;
}

//Phonng鏡面反射光の計算
float3 CalcPhongSpecular(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower)
{
    float3 toEye = normalize(eyePos - worldPos);
    
    float3 r = reflect(ligDir, normal);
    
    float t = max(0.0f, dot(toEye, r));
    
    t = pow(t, 5.0f);
    
    return ligColor * t * specPower;
}

//リムライト
float3 CalcLimLight(float3 ligDir, float3 ligColor, float3 normal)
{
    //リムライトの強さを求める
    float power1 = 1.0f - max(0.0f, min(dot(ligDir, normal), 1.0f));
    
    //カメラの向きを正規化してもベクトルの大きさが1を越えることがあり
    //描画がバグるのでmin関数で1を越えないようにする
    float power2 = 1.0f - max(0.0f, min(dot(eyeDir, normal) * -1.0f, 1.0f));
 
    float limPower = power1 * power2;
    //強さの変化を指数関数的にする
    limPower = pow(limPower, 1.3);
    
    //リムライトのカラーを計算して返す
    //なんかリムライトが強すぎるので0.5倍にする
    return ligColor * limPower * 0.5f;
}

//ライトの共通処理
float3 CalcLighting(float3 ligDir, float3 ligColor, float3 normal, float3 worldPos, float specPower)
{
    //拡散反射を求める
    float3 diffLig = CalcLambertDiffuse(ligDir, ligColor, normal);
    //鏡面反射を求める
    float3 phongLig = CalcPhongSpecular(ligDir, ligColor, normal, worldPos, specPower);
    //リムライトを求める
    float3 limLig = CalcLimLight(ligDir, ligColor, normal);
    
    //求めたライトの光を全て足して返す
    return diffLig + phongLig + limLig;
}

//ディレクションライトによる反射光計算
float3 CalcLigFromDirectionLight(float3 normal, float3 worldPos, float specPower)
{
    //ライティングの計算
    float3 lig = CalcLighting(directionalLight.direction, directionalLight.color, normal, worldPos, specPower);
    
    //return diffLig;
    //return phongLig;
    //return limLig;
    
    //最終的な光を返す
    return lig;
}

//ポイントライトによる反射光計算
float3 CalcLigFromPointLight(float3 normal, float3 worldPos, float specPower, uint tileIndex)
{
    //全てのポイントライトの結果を足した最終的なライト
    float3 finalLig = { 0.0f, 0.0f, 0.0f };
 
    //含まれるタイルの影響の開始位置と終了位置を計算する
    uint lightStart = tileIndex * numPointLight;
    uint lightEnd = lightStart + numPointLight;
    
    //タイルインデックスを計算する
    for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++)
    {
        uint ligNo = pointLightListInTile[lightListIndex];
        if (ligNo == 0xffffffff)
        {
            //このタイルに含まれるポイントライトはもうない
            break;
        }
        
        //拡散反射を計算
        //1.光源からサーフェイスに入射するベクトルを計算
        float3 ligDir = normalize(worldPos - pointLights[ligNo].position);
        //2.光源からサーフェイスまでの距離を計算
        float distance = length(worldPos - pointLights[ligNo].position);
            
        //ライティングの計算
        float3 lig = CalcLighting(ligDir, pointLights[ligNo].color, normal, worldPos, specPower);
            
        //距離に比例して小さくなっていく影響率を計算する
        float affect = 1.0f - min(1.0f, distance / pointLights[ligNo].range);
        //影響率を累乗しての変化を指数関数的にする
        affect = pow(affect, pointLights[ligNo].pow);
            
        //ライトに影響率を乗算した値を最終的なライトに加算する
        finalLig += lig * affect;
        
        
    }

    //全てのポイントライトの光を合算したライトを返す
    return finalLig;
}

float3 CalcLigFromSpotLight(float3 normal, float3 worldPos, float specPower, uint tileIndex)
{
    //全てのスポットライトの結果を足した最終的なライト
    float3 finalLig = { 0.0f, 0.0f, 0.0f };
    
    //含まれるタイルの影響の開始位置と終了位置を計算する
    uint lightStart = tileIndex * numSpotLight;
    uint lightEnd = lightStart + numSpotLight;
    
    for (uint lightListIndex = lightStart; lightListIndex < lightEnd; lightListIndex++)
    {
        uint ligNo = spotLightListInTile[lightListIndex];
        if (ligNo == 0xffffffff)
        {
            // このタイルに含まれるポイントライトはもうない
            break;
        }
        
        //サーフェイスに入射するスポットライトの光の向きを求める
        float3 ligDir = normalize(worldPos - spotLights[ligNo].position);
        //光源からサーフェイスまでの距離を計算
        float distance = length(worldPos - spotLights[ligNo].position);
        
        //ライティングの計算
        float3 lig = CalcLighting(ligDir, spotLights[ligNo].color, normal, worldPos, specPower);
     
        //影響率の計算
        //距離減衰による影響率を求める
        float distanceAffect = pow(1.0f - min(1.0f, distance / spotLights[ligNo].range), spotLights[ligNo].rangePow);
        
        //入射光と射出方向の角度による影響率を求める
        //入射光と射出方向の角度を求める
        float angleLigToPixel = dot(ligDir, spotLights[ligNo].direction);
        angleLigToPixel = abs(acos(angleLigToPixel));
        
        //角度に比例して小さくなっていく影響率を計算する
        float angleAffect = pow(max(0.0f, 1.0f - 1.0f / spotLights[ligNo].angle * angleLigToPixel), spotLights[ligNo].anglePow);
        
        //影響率を乗算したライトを最終的なライトに加算する
        finalLig += lig * distanceAffect * angleAffect;
    }

    //最終的なライトを返す
    return finalLig;
}


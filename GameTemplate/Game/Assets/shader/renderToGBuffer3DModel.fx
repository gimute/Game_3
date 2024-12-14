/*!
 * @brief G-Bufferへの描画
 */

// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    
    SSkinVSIn skinVert; //スキン用のデータ。
};

// ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
};

// ピクセルシェーダーからの出力
struct SPSOut
{
    float4 albedo : SV_Target0; // アルベド
    float4 normal : SV_Target1; // 法線
    float depth : SV_Target2;   //深度値
};

// モデルテクスチャ
Texture2D<float4> g_texture : register(t0);
Texture2D<float4> g_normalMap : register(t1);
Texture2D<float4> g_specularMap : register(t2);
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //ボーン行列。
// サンプラーステート
sampler g_sampler : register(s0);

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// モデル用の頂点シェーダーのエントリーポイント
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;

    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    
    psIn.pos = mul(m, vsIn.pos); // 1. モデルの頂点をワールド座標系に変換
    psIn.pos = mul(mView, psIn.pos); // 2. ワールド座標系からカメラ座標系に変換
    psIn.pos = mul(mProj, psIn.pos); // 3. カメラ座標系からスクリーン座標系に変換
    psIn.normal = normalize(mul(m, vsIn.normal));
    psIn.uv = vsIn.uv;
    
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));

    return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}

/// <summary>
/// モデル用のピクセルシェーダーのエントリーポイント
/// </summary>
SPSOut PSMain(SPSIn psIn)
{
    // step-6 G-Bufferに出力
    SPSOut psOut;
    
    //アルベドカラーを出力
    psOut.albedo = g_texture.Sample(g_sampler, psIn.uv);
    
    //法線マップからタンジェントスペースの法線をサンプリング
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;
    
    //タンジェントスペースの法線をを0～1の範囲から-1～1の範囲に復元する
    localNormal = (localNormal - 0.5f) * 2.0f;
    
    float3 normal = psIn.tangent * localNormal.x + psIn.biNormal * localNormal.y + psIn.normal * localNormal.z;
    
    //法線出力
    //出力は0～1に丸められてしまうのでマイナスの値が失われてしまう
    //なので-1～1を0～1に変換する
    //(-1~1) / 2.0 = (-0.5~0.5)
    //(-0.5~0.5) + 0.5 = (0.0~1.0)
    psOut.normal.xyz = (normal / 2.0f) + 0.5f;
    //スペキュラ強度をnormal.wに代入
    psOut.normal.w = g_specularMap.Sample(g_sampler, psIn.uv).r;
    //psOut.normal = (psIn.normal / 2.0f) + 0.5f;
    
    //深度値を出力
    psOut.depth = psIn.pos.z;
    
    return psOut;
}

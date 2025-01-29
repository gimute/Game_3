/*!
 * @brief シャドウマップ描画用のシェーダー
 */

// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

cbuffer ShadowParamCb : register(b1)
{
    float3 lightPos; //ライトの座標
}

//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};

// 頂点シェーダーへの入力
struct SVSIn
{
    float4 pos : POSITION;  // モデルの頂点座標
    float3 normal : NORMAL; // 法線
    float2 uv : TEXCOORD0;  // UV座標
    
    SSkinVSIn skinVert; //スキン用のデータ。
};
// ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos : SV_POSITION;   // スクリーン空間でのピクセルの座標
    float3 normal : NORMAL;     // 法線
    float2 uv : TEXCOORD0;      // uv座標
    float2 depth : TEXCOORD1; // ライト空間での座標
};

///////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //ボーン行列。


//スキン行列を計算する。
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
/// 頂点シェーダー
/// <summary>
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
    
    psIn.pos = mul(m, vsIn.pos);
    float3 worldPos = psIn.pos;
    //自分に自分の影が落ちる時めっちゃ気持ち悪くなるのでここで無理やり調整する
    //psIn.pos.z += 1.0f;
    
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    
    //ライトから見た頂点の深度値と、ライトから見た深度値の2乗を計算する
    psIn.depth.x = length(worldPos - lightPos) / 2000.0f;
    psIn.depth.y = psIn.depth.x * psIn.depth.x;
    
    psIn.normal = mul(m, vsIn.normal);
    return psIn;
}

// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}

// スキンありメッシュの頂点シェーダーのエントリー関数。
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}

/// <summary>
/// シャドウマップ描画用のピクセルシェーダー
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    
    
    // step-9 シャドウマップ描画用のピクセルシェーダーを実装
    return float4(psIn.depth.x, psIn.depth.y, 0.0f, 1.0f);
}

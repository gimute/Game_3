///////////////////////////////////////
//ボリュームライトモデル描画シェーダー
///////////////////////////////////////

//シーンの深度でテクスチャ
Texture2D <float4>g_sceneDepthTexture : register(t10);
//サンプラー
sampler Sampler : register(s0);

///////////////////////////////////////
//構造体
///////////////////////////////////////

//ピクセルシェーダーへの入力
struct SPSIn
{
    float4 pos : SV_Position;
    float4 posInProj : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
};

///////////////////////////////////////
// 定数バッファ。
///////////////////////////////////////
// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};


SPSIn VSMain(float4 pos : POSITION)
{
    SPSIn psIn;
    psIn.pos = mul(mWorld, pos);    //モデルの頂点をワールド座標系に変換
    //頂点シェーダーからワールド座標を出力
    psIn.worldPos = pos;
    psIn.pos = mul(mView, psIn.pos);    //モデルの頂点をワールド座標系に変換
    psIn.pos = mul(mProj, psIn.pos);    //カメラ座標系からスクリーン座標系に変換
    psIn.posInProj = psIn.pos;
    
    return psIn;
}

/// <summary>
/// 書き込む深度値を計算する。
/// </summary>
float CalcDrawDepth(SPSIn psIn)
{
    
    float2 uv = psIn.posInProj.xy / psIn.posInProj.w;
    uv = uv * float2(0.5f, -0.5f) + float2(0.5f, 0.5f);
    float sceneDepth = g_sceneDepthTexture.Sample(Sampler, uv).r;
    float z = min(sceneDepth, psIn.pos.z);
    
    return z;
}

/// <summary>
/// 前面/背面描画用のピクセルシェーダーエントリー関数。
/// </summary>
float4 PSMainFrontBackModel(SPSIn psIn) : SV_Target0
{
    //ボリュームライトマップに書き込む深度値を計算する
    float z = CalcDrawDepth(psIn);
    return float4(z, z, z, z);
}

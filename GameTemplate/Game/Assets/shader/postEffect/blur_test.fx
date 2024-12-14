//中央から外側に向うブラー

cbuffer cb : register(b0)
{
    float4x4 mvp;       //MVP行列
    float4 mulColor;    //乗算カラー
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

Texture2D<float4> sceneTexture : register(t0); // シーンテクスチャ
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

float4 PSMain(PSInput In) : SV_Target0
{
    //ピクセルのカラーを取得
    float4 color = sceneTexture.Sample(Sampler, In.uv);

    //中央から現在計算中のピクセルのuvに伸びるベクトル
    float2 centerToInUVVec;
    centerToInUVVec.x = (0.5f - In.uv.x);
    centerToInUVVec.y = (0.5f - In.uv.y);
    
    //画面の中央はブラーをせず端に行くほどブラーを強める感じにしたいので、
    //lerp用にベクトルの長さによって変動する値を用意する
    float t = ((centerToInUVVec.x * centerToInUVVec.x) + (centerToInUVVec.y * centerToInUVVec.y)) / 0.5f;
    
    //正規化
    //ここでちょっと変数の意味が変わってるから変数名変えたほうが良いかも?
    normalize(centerToInUVVec);
    //適当に小さくする
    centerToInUVVec /= 20.0f;
    
    //作ったベクトル方向のピクセルをサンプリング
    float4 blurColor;
    blurColor = sceneTexture.Sample(Sampler, In.uv + centerToInUVVec);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 2);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 3);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 4);
    blurColor += sceneTexture.Sample(Sampler, In.uv + centerToInUVVec * 5);
    
    
    
    //基準テクセルとサンプリングした5テクセルの平均なので6で除算する
    //color = blurColor + color;
    //color /= 6.0f;
    
    
    blurColor /= 5.0f;
    color = lerp(color, blurColor, t);
    
    
    return color;
}
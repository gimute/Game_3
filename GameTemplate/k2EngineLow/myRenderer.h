#pragma once

//描画回りで使う定数をまとめたヘッダーファイル、なはず

namespace nsK2EngineLow {

	//ポイントライトの最大数
	const int MAX_POINT_LIGHT = 250;
	const int MAX_SPOT_LIGHT = 250;

	// TBR用のパラメータ。
	const int TILE_WIDTH = 16;  // タイルの幅
	const int TILE_HEIGHT = 16; // タイルの高さ
	const int NUM_TILE = (FRAME_BUFFER_W / TILE_WIDTH) * (FRAME_BUFFER_H / TILE_HEIGHT); // タイルの数

	//レンダリングターゲットのフォーマットをまとめる構造体
	struct RenderTargetFormat {
		DXGI_FORMAT colorBufferFormat;	//カラーバッファーのフォーマット
		DXGI_FORMAT depthBufferFormat;	//深度バッファのフォーマット
	};

	//シャドウマップのフォーマット
	const RenderTargetFormat g_ShadowMapFormat = {
		DXGI_FORMAT_R32G32_FLOAT,	//カラーバッファ
		DXGI_FORMAT_D32_FLOAT		//深度バッファ
	};
	
	//メインレンダリングターゲットのフォーマット
	const RenderTargetFormat g_mainRenderTargetFormat{
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	};

	//ボリュームライトマップのフォーマット
	const RenderTargetFormat g_drawVolumeLightMapFormat = {
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_D32_FLOAT
	};

	//G-Bufferのカラーバッファーフォーマット
	const DXGI_FORMAT g_albedColorBuffer = DXGI_FORMAT_R8G8B8A8_UNORM;	//アルベドカラーのG-Buffer
	const DXGI_FORMAT g_normalSpecBuffer = DXGI_FORMAT_R8G8B8A8_UNORM;	//法線とスペキュラパワーのG-Buffer
	const DXGI_FORMAT g_depthBuffer = DXGI_FORMAT_R32_FLOAT;				//深度値のG-Buffer

}
#include "k2EngineLowPreCompile.h"
#include "LightCulling.h"
//ライトカリング
namespace nsK2EngineLow {
	void LightCulling::Init(
		Texture& depthTexture,
		ConstantBuffer& lightCB,
		RWStructuredBuffer& pointLightNoListInTileUAV,
		RWStructuredBuffer& spotLightNoListInTileUAV
	) {
		m_pointLightNoListInTileUAV = &pointLightNoListInTileUAV;
		m_spotLightNoListInTileUAV = &spotLightNoListInTileUAV;

		m_shader.LoadCS("Assets/shader/preProcess/lightCulling.fx", "CSMain");

		//ライトカリングのカメラ情報用の定数バッファーを作成
		m_cameraDataCB.Init(sizeof(CameraData), nullptr);

		//ディスクリプタヒープを初期化
		//要するにおぼんに乗せるものを設定する
		//シェーダーリソース
		m_descriptorHeap.RegistShaderResource(0, depthTexture);
		//アンオーダーアクセスリソース、全然わからん
		m_descriptorHeap.RegistUnorderAccessResource(0, pointLightNoListInTileUAV);
		m_descriptorHeap.RegistUnorderAccessResource(1, spotLightNoListInTileUAV);
		//定数バッファー
		m_descriptorHeap.RegistConstantBuffer(0, m_cameraDataCB);
		m_descriptorHeap.RegistConstantBuffer(1, lightCB);
		//登録を確定させる
		//おぼんに乗せる皿が決まったイメージ、中身は後から入れる
		m_descriptorHeap.Commit();


		//ルートシグネチャを作成
		//シェーダーに流すデータの種類と数をあらかじめ定義する物
		m_rootSignature.Init(
			D3D12_FILTER_MIN_MAG_MIP_LINEAR,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP,
			D3D12_TEXTURE_ADDRESS_MODE_WRAP
		);

		//パイプラインステートを初期化
		//入力ストリーム、シェーダ、ステート等をすべてひとつのオブジェクトのまとめたもの、らしい
		D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = { 0 };
		//ルートシグネチャ
		psoDesc.pRootSignature = m_rootSignature.Get();
		//コンピュートシェーダー
		psoDesc.CS = CD3DX12_SHADER_BYTECODE(m_shader.GetCompiledBlob());
		//ここは何もわからん
		psoDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
		psoDesc.NodeMask = 0;
		m_pipelineState.Init(psoDesc);
	}


	void LightCulling::Execute(RenderContext& rc)
	{
		//カリングに使うカメラの情報を取得する
		CameraData cameraData;
		//プロジェクション行列
		cameraData.mProj = g_camera3D->GetProjectionMatrix();
		//プロジェクション行列の逆行列
		//関数で直に逆行列取れた気もするけどとりあえずはそのままで
		cameraData.mProjInv.Inverse(g_camera3D->GetProjectionMatrix());
		//カメラの回転行列
		cameraData.mCameraRot = g_camera3D->GetCameraRotation();
		//カメラの描画範囲とフレームバッファーの縦横
		cameraData.screenParam.x = g_camera3D->GetNear();
		cameraData.screenParam.y = g_camera3D->GetFar();
		cameraData.screenParam.z = FRAME_BUFFER_W;
		cameraData.screenParam.w = FRAME_BUFFER_H;
		//カメラデータ定数バッファに登録(コピー)
		m_cameraDataCB.CopyToVRAM(cameraData);

		//ライトカリングのコンピュートシェーダーをディスパッチ
		//まず用意したルートシグネチャ、ディスクリプタヒープ、パイプラインステートを設定する
		rc.SetComputeRootSignature(m_rootSignature);
		rc.SetComputeDescriptorHeap(m_descriptorHeap);
		rc.SetPipelineState(m_pipelineState);

		//フレームバッファーの幅と高さをTILE_WIDTH、TILE_HEIGHTの倍数に切り上げる
		//式に使われている変数が全て整数型なので、切り捨てを利用して上手いことやってる
		UINT FRAME_BUFFER_W_ROUNDUP = ((FRAME_BUFFER_W + TILE_WIDTH - 1) / TILE_WIDTH) * TILE_WIDTH;
		UINT FRAME_BUFFER_H_ROUNDUP = ((FRAME_BUFFER_H + TILE_HEIGHT - 1) / TILE_HEIGHT) * TILE_HEIGHT;

		//グループの数を設定してディスパッチ
		//グループの数はタイルの数
		rc.Dispatch(
			FRAME_BUFFER_W_ROUNDUP / TILE_WIDTH,
			FRAME_BUFFER_H_ROUNDUP / TILE_HEIGHT,
			1);

		//リソースバリア
		//なんかリソースステートを遷移するとか言ってるけどよくわがんね
		rc.TransitionResourceState(
			m_pointLightNoListInTileUAV->GetD3DResoruce(),
			D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
			D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
		);
	}
}
#pragma once

#include"DirectXCommon.h"
#include<wrl.h>
#include<d3d12.h>

#include<DirectXMath.h>
#include"SpriteCommon.h"
class Sprite
{
private:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	struct Transform {
		DirectX::XMFLOAT3 scale;
		DirectX::XMFLOAT3 rotate;
		DirectX::XMFLOAT3 translate;
	};

	struct VertexData
	{
		DirectX::XMFLOAT4 position;
		DirectX::XMFLOAT2 texcoord;
	};
	struct MaterialData {
		DirectX::XMFLOAT4 color;
		DirectX::XMMATRIX uvTransform;
	};
public:
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common);
	void Update();
	void Draw();
private:

	void CreateVertex();
	//インデックス情報作成
	void CreateIndex();
	void CreateMaterial();
	//行列
	void CreateWVP();

private:
	DirectXCommon* dxCommon_ = nullptr;
	SpriteCommon* common_ = nullptr;


	ComPtr<ID3D12Resource> vertexResource;
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};
	//インデックス
	ComPtr<ID3D12Resource> indexResource;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};
	//マテリアル
	ComPtr<ID3D12Resource>materialResource;
	MaterialData* materialData = nullptr;
	//行列
	ComPtr<ID3D12Resource> wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU;

	//パラメーター
	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	Transform uvTransform = { {1,1,1}, {0,0,0},{0,0,0} };
	//scal   ROtate  translate
	Transform transform = { {1,1,1},{0,0,0},{0,0,0} };

	//	kamera
	Transform cameraTransform = { {1,1,1},{0,0,0},{0,0,-5} };
};


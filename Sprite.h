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
	void Initialize(DirectXCommon* dxCommon, SpriteCommon* common,std::wstring textureFilePath);
	void Update();
	void Draw();
	//Getter
	DirectX::XMFLOAT2 GetPosition() { return position; }
	float GetRotation()             { return rotation; }
	DirectX::XMFLOAT4 GetColor()    { return color_; }
	DirectX::XMFLOAT2 Getsize() { return size; }
	void SetPosition(DirectX::XMFLOAT2 pos) { position = pos; }
	void SetRotation(float rot)             { rotation = rot; }
	void SetColor(DirectX::XMFLOAT4 color) { color_ = color; }
	void SetSize(DirectX::XMFLOAT2 size) { this->size = size; }

	void SetTexture(std::wstring textureFilePath);
	
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
	VertexData* vertexData = nullptr;
	//インデックス
	ComPtr<ID3D12Resource> indexResource;
	D3D12_INDEX_BUFFER_VIEW indexBufferView{};
	//マテリアル
	ComPtr<ID3D12Resource>materialResource;
	MaterialData* materialData = nullptr;
	//行列
	ComPtr<ID3D12Resource> wvpResource;
	DirectX::XMMATRIX* wvpData = nullptr;

	

	//パラメーター
	DirectX::XMFLOAT4 color_ = { 1.0f,1.0f,1.0f,1.0f };
	Transform uvTransform = { {1,1,1}, {0,0,0},{0,0,0} };
	//scal   ROtate  translate
	Transform transform = { {1,1,1},{0,0,0},{0,0,0} };
	DirectX::XMFLOAT2 position = { 0,0 };
	float rotation = 0;

	DirectX::XMFLOAT2 size = { 512,512 };
	//画像保存されている場所
	uint32_t textureIndex_ = 0;
	//	kamera
	Transform cameraTransform = { {1,1,1},{0,0,0},{0,0,-5} };
};


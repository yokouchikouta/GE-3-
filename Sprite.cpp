#include "Sprite.h"

#include<DirectXMath.h>
#include"BufferResource.h"

#include"External/imgui/imgui.h"
#include "TextureManager.h"
using namespace Microsoft::WRL;
using namespace DirectX;
void Sprite::Initialize(DirectXCommon* dxCommon, SpriteCommon* common,std::wstring textureFilePath)
{
	dxCommon_ = dxCommon;
	common_ = common;
	
	textureIndex_ = TextureManager::GetInstance()->GetTextureIndexFilePath(textureFilePath);
	
		CreateVertex();
	CreateIndex();
	CreateMaterial();
	CreateWVP();
}

void Sprite::Update()
{
	transform.translate = { position.x,position.y,0 };
	transform.rotate = { 0,0,rotation };
	materialData->color = color_;
	transform.scale = { size.x,size.y,1.0f };


	vertexData[0].position = { 0.0f,1.0f,0.0f,1.0f };
	vertexData[0].texcoord = { 0.0f,1.0f };

	vertexData[1].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexData[1].texcoord = { 0.0f,0.0f };

	vertexData[2].position = { 1.0f,1.0f,0.0f,1.0f };
	vertexData[2].texcoord = { 1.0f,1.0f };

	vertexData[3].position = { 1.0f,0.0f,0.0f,1.0f };
	vertexData[3].texcoord = { 1.0f,0.0f };

	ImGui::Begin("Texture");
	ImGui::DragFloat3("Pos", &transform.translate.x, 0.1f);

	ImGui::DragFloat3("UV-Pos", &uvTransform.translate.x, 0.01f, -10.0f, 10.0f);
	ImGui::SliderAngle("UVRot", &uvTransform.rotate.z);
	ImGui::DragFloat3("UV-Scale", &uvTransform.scale.x, 0.01f, -10.f, 10.0f);
	ImGui::End();
}

void Sprite::Draw()
{
	//��]
	transform.rotate.y += 0.03f;
	//���[���h
	XMMATRIX scaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&transform.scale));
	XMMATRIX rotateMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&transform.rotate));
	XMMATRIX translationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&transform.translate));
	
	XMMATRIX rotationAndScaleMatrix = XMMatrixMultiply(rotateMatrix, scaleMatrix);
	XMMATRIX worldMatrix = XMMatrixMultiply(rotationAndScaleMatrix, translationMatrix);
	
	//���߂�
	XMMATRIX cameraScaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&cameraTransform.scale));
	XMMATRIX cameraRotateMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&cameraTransform.rotate));
	XMMATRIX cameraTranslationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&cameraTransform.translate));
	//	kaitenn
	XMMATRIX cameraRotateAndScameMatrix = XMMatrixMultiply(cameraRotateMatrix, cameraScaleMatrix);
	XMMATRIX cameraMatrix = XMMatrixMultiply(cameraRotateAndScameMatrix, cameraTranslationMatrix);
	
	XMMATRIX view = XMMatrixInverse(nullptr, cameraMatrix);
	
	XMMATRIX proj = XMMatrixOrthographicOffCenterLH(0, WinApp::window_width, WinApp::window_height, 0, 0.1f, 100.0f);

	XMMATRIX worldViewProjectionMatrix = worldMatrix * (view * proj);
	*wvpData = worldViewProjectionMatrix;
	
	//UV���W
	XMMATRIX uvScaleMatrix = XMMatrixScalingFromVector(XMLoadFloat3(&uvTransform.scale));
	XMMATRIX uvRotateMatrix = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&uvTransform.rotate));
	XMMATRIX uvTranslationMatrix = XMMatrixTranslationFromVector(XMLoadFloat3(&uvTransform.translate));

	XMMATRIX uvRotationAndScaleMatrix = XMMatrixMultiply(uvRotateMatrix, uvScaleMatrix);
	XMMATRIX uvWorldMatrix = XMMatrixMultiply(uvRotationAndScaleMatrix, uvTranslationMatrix);
	materialData->uvTransform = uvWorldMatrix;

	dxCommon_->GetCommandList()->SetGraphicsRootSignature(common_->GetRootSignature());
	dxCommon_->GetCommandList()->SetPipelineState(common_->GetPipelineState());

	dxCommon_->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);
	//�C���f�b�N�X���
	dxCommon_->GetCommandList()->IASetIndexBuffer(&indexBufferView);

	dxCommon_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());
	//�s��
	dxCommon_->GetCommandList()->SetGraphicsRootConstantBufferView(1, wvpResource->GetGPUVirtualAddress());
	//�摜
	dxCommon_->GetCommandList()->SetGraphicsRootDescriptorTable(2, TextureManager::GetInstance()->GetSrvHandleGPU(textureIndex_));
	//dxCommon_->GetCommandList()->DrawInstanced(6, 1, 0, 0);
	dxCommon_->GetCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);

}

void Sprite::SetTexture(std::wstring textureFilePath)
{
	{
		textureIndex_ = TextureManager::GetInstance()->GetTextureIndexFilePath(textureFilePath);
	}
}

void Sprite::CreateVertex()
{
	vertexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(VertexData) * 4);

	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(VertexData) * 4;
	vertexBufferView.StrideInBytes = sizeof(VertexData);

	//���_���
	
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	vertexData[0].position = { 0.0f,1.0f,0.0f,1.0f };
	vertexData[0].texcoord = { 0.0f,1.0f };

	vertexData[1].position = { 0.0f,0.0f,0.0f,1.0f };
	vertexData[1].texcoord = { 0.0f,0.0f };
	
	vertexData[2].position = { 1.0f,1.0f,0.0f,1.0f };
	vertexData[2].texcoord = { 1.0f,1.0f };

	vertexData[3].position = { 1.0f,1.0f,0.0f,1.0f };
	vertexData[3].texcoord = { 1.0f,0.0f };
}

void Sprite::CreateIndex()
{
	indexResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(uint32_t) * 6);

	indexBufferView.BufferLocation = indexResource->GetGPUVirtualAddress();
	indexBufferView.SizeInBytes = sizeof(uint32_t) * 6;
	indexBufferView.Format = DXGI_FORMAT_R32_UINT;
	uint32_t* indexData = nullptr;
	indexResource->Map(0, nullptr, reinterpret_cast<void**>(&indexData));

	//VertexData[0.1.2]�O�p�`
	indexData[0] = 0;  indexData[1] = 1;   indexData[2] = 2;
	indexData[3] = 1;  indexData[4] = 3;   indexData[5] = 2;

}

void Sprite::CreateMaterial()
{
	materialResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(MaterialData));
	
	
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	materialData->color = color_;
	materialData->uvTransform = XMMatrixIdentity();
	
}

void Sprite::CreateWVP()
{
	wvpResource = CreateBufferResource(dxCommon_->GetDevice(), sizeof(XMMATRIX));
	
	wvpResource->Map(0, nullptr, reinterpret_cast<void**>(&wvpData));

	*wvpData = XMMatrixIdentity();
}

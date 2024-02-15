#pragma once
#include"DirectXCommon.h"
#include<string>
#include<DirectXTex.h>
class TextureManager
{

private:
    struct TextureData {
        std::wstring filePath;
        DirectX::TexMetadata metaData;
        Microsoft::WRL::ComPtr<ID3D12Resource> resource;
        D3D12_CPU_DESCRIPTOR_HANDLE sevHandleCPU;
        D3D12_GPU_DESCRIPTOR_HANDLE srvHandleGPU;
    };
public:
    static TextureManager* GetInstance();
    void Finalize();

    void Initialize(DirectXCommon* dxCommon);

    //‰æ‘œ“Ç‚İ‚İ
     void  LoadTexture(const std::wstring& filePath);
     //“Ç‚İ‚ñ‚¾‰æ‘œ‚ğGPU
     void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);
private:
private:
    static TextureManager* instance;

    TextureManager() = default;
    ~TextureManager() = default;
    TextureManager(TextureManager&) = delete;
    TextureManager& operator=(TextureManager&) = delete;
private:
    DirectXCommon* dxCommon_ = nullptr;
    std::vector<TextureData>textureDatas;
};



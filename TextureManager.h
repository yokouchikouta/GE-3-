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
     //w’è‚µ‚½‰æ‘œ‚ª‰½”Ô–Ú‚É‚ ‚é‚Ì‚©
     uint32_t GetTextureIndexFilePath(const std::wstring& filePath);

     //ƒnƒ“ƒhƒ‹‚ğó‚¯æ‚é
     D3D12_GPU_DESCRIPTOR_HANDLE GetSrvHandleGPU(uint32_t textureIndex);

private:
     //“Ç‚İ‚ñ‚¾‰æ‘œ‚ğGPU
     void UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

private:
    static TextureManager* instance;
    static uint32_t kSRVIndexTop;


    TextureManager() = default;
    ~TextureManager() = default;
    TextureManager(TextureManager&) = delete;
    TextureManager& operator=(TextureManager&) = delete;
private:
    DirectXCommon* dxCommon_ = nullptr;
    std::vector<TextureData>textureDatas;
};



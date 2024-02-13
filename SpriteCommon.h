#pragma once

#include<string>
#include <wrl.h>
#include<dxcapi.h>
#include <d3d12.h>
#include"DirectXCommon.h"
class SpriteCommon
{
public:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	void Initialize(DirectXCommon* dxCommon);

	//Getter
	ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }
private:
	static IDxcBlob* CompilerShader(
		const std::wstring& fillePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtis,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHander
		);
private:
	DirectXCommon* dxCommon_ = nullptr;
	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
};



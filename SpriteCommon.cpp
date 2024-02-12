#include "SpriteCommon.h"


#include<cassert>


#pragma comment(lib,"dxcompiler.lib")

using namespace Microsoft::WRL;
void SpriteCommon::Initialize()
{
	HRESULT result{};

	ComPtr<IDxcUtils> dxcUtils;
	ComPtr<IDxcCompiler3> dxcCompiler;
	result = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
	assert(SUCCEEDED(result));
	result = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
	assert(SUCCEEDED(result));

	ComPtr<IDxcIncludeHandler> includeHandler;
	result = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
	assert(SUCCEEDED(result));
}

IDxcBlob* SpriteCommon::CompilerShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHander)
{
	//hlsl
	IDxcBlobEncoding* shaderSource = nullptr;
	HRESULT result = dxcUtils->LoadFile(filePath.c_str(),nullptr,&shaderSource);
	assert(SUCCEEDED(result));

	DxcBuffer shaderSourceBuffer;
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;

	LPCWSTR arguments[] = {
	filePath.c_str(),
	L"-E", L"main",
	L"-T",profile,
	L"-Zi",L"-Qembed_debag",
	L"-Zpr",
	};
	IDxcResult* shaderResult = nullptr;
	result = dxcCompiler->Compile(
		&shaderSourceBuffer,
		arguments,
		_countof(arguments),
		includeHander,
		IID_PPV_ARGS(&shaderResult)
	);
	assert(SUCCEEDED(result));

	IDxcBlobUtf8* shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError),nullptr);
	if (shaderError != nullptr && shaderError->GetStringPointer() != 0) {
		assert(false);

		IDxcBlob* shaderBlob = nullptr;
		result=	shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
		assert(SUCCEEDED(result));

		shaderSource->Release();
		shaderResult->Release();

		return shaderBlob;
	}
	return nullptr;
}

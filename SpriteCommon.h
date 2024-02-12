#pragma once

#include<string>
#include <wrl.h>
#include<dxcapi.h>
class SpriteCommon
{
public:
	void Initialize();
private:
	static IDxcBlob* CompilerShader(
		const std::wstring& fillePath,
		const wchar_t* profile,
		IDxcUtils* dxcUtis,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHander
		);
};



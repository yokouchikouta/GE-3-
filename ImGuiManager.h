#pragma once
#include "DirectXCommon.h"
class ImGuiManager
{
public:
	//������
	static void Initialize(HWND hwnd ,DirectXCommon* dxCommon);
	//�X�V�J�n
	static void NewFrame();
	//�X�V�I��
	static void CreateCommand();
	//�R�}���h����
	static void CommandsExcute(ID3D12GraphicsCommandList* commandList);
	//new����
	static ImGuiManager* Create();
public:
	//�f�X�g���N�^
	~ImGuiManager();
public:
	void ShowDemo();
};


#include "ImGuiManager.h"

#include"External/imgui/imgui.h"
#include"External/imgui/imgui_impl_dx12.h"
#include"External/imgui/imgui_impl_win32.h"
void ImGuiManager::Initialize(HWND hwnd, DirectXCommon* dxCommon)
{
//IMGUI初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX12_Init(
		dxCommon->GetDevice(),
		dxCommon->GetSwapChainDesc().BufferCount,
		dxCommon->GetRtvDesc().Format,
		dxCommon->GetSrvDescriptorHeap(),
		dxCommon->GetSrvDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
	dxCommon->GetSrvDescriptorHeap()->GetGPUDescriptorHandleForHeapStart()
	);
}

void ImGuiManager::NewFrame()
{
	//更新処理開始
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::CreateCommand()
{
	//更新処理終了時
	ImGui::Render();
}

void ImGuiManager::CommandsExcute(ID3D12GraphicsCommandList* commandList)
{
	//ImGui描画
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);
}

ImGuiManager* ImGuiManager::Create()
{
	ImGuiManager* instance = new ImGuiManager();
	return instance;
}

ImGuiManager::~ImGuiManager()
{
	//デストラクタ(delete)
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::ShowDemo()
{
	//ImGui確認用
	ImGui::ShowDemoWindow();
}

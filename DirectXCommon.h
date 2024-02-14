#pragma once
#include<wrl.h>
#include<d3d12.h>

#include<dxgi1_6.h>

#include<vector>
#include<chrono>
#include"WinApp.h"

class DirectXCommon
{
private:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initialize(WinApp*winApp);
	void PreDraw();
	void PostDraw();

	ID3D12Device* GetDevice()const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList()const { return commandList.Get(); }

	//スワップチェ－ン
	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc() { return swapChainDesc; };
	//RTV
	// レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC GetRtvDesc() { return rtvDesc; }
	//SRV
	ID3D12DescriptorHeap* GetSrvDescriptorHeap() { return srvDescriptorHeap.Get(); }
private:
	void DeviceInitialize();
	void CommandInitialize();
	void SwapChainInitialize();
	void RenderTargetInitialize();
	void DepthBufferInitialize();
	void FenceInitialize();

	void  InitializeFixFPS();
	void UpdateFixFPS();


	//ディスクリプタヒープ作成
	ID3D12DescriptorHeap* CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescripots,bool shaderVisible);
private:
	WinApp* winApp = nullptr;
	ComPtr<IDXGIFactory7> dxgiFactory;
	ComPtr<ID3D12Device> device;

	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandQueue> commandQueue;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	ComPtr<IDXGISwapChain4> swapChain;

	D3D12_RESOURCE_DESC depthResourceDesc{};
	ComPtr<ID3D12DescriptorHeap> rtvHeap;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;

	ComPtr<ID3D12Resource> depthBuff;
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	ComPtr<ID3D12DescriptorHeap> dsvHeap;

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{};
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	D3D12_RESOURCE_BARRIER barrierDesc{};
	//記録用時間計測
	std::chrono::steady_clock::time_point reference_;

	// レンダーターゲットビューの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//ディスクリプタヒープ
	//RTV(ゲーム画面を保存しておく)
	ComPtr<ID3D12DescriptorHeap>rtvDescriptorHeap;
	//SRV(画像などを保存しておく)
	ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap;
};


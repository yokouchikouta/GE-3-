#pragma once
#include<wrl.h>
#include<d3d12.h>

#include<dxgi1_6.h>

#include<vector>

#include"WinApp.h"
class DirectXCommon
{
private:
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
public:
	void Initialize(WinApp*winApp);
	void PreDraw();
	void PostDraw();
private:
	void DeviceInitialize();
	void CommandInitialize();
	void SwapChainInitialize();
	void RenderTargetInitialize();
	void DepthBufferInitialize();
	void FenceInitialize();
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

	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	D3D12_RESOURCE_BARRIER barrierDesc{};
};


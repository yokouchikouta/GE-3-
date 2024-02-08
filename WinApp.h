#pragma once
#include <Windows.h>

class WinApp
{
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	void Initialize();

	bool Update();
	//後処理
	void Finalize();


	HWND GetHwnd() const { return hwnd; }
	HINSTANCE GetHInstance() const { return w.hInstance; }
public:
	//ウィンドウサイズ
	static const int window_width = 1280;
	static const int window_height = 720;

private:
	HWND hwnd;
	WNDCLASSEX w{};
	MSG msg{};  // メッセージ
};


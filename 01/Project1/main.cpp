#include <Windows.h>

#include "Defs.h"

HRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wpara, LPARAM lparam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };

	wc.hInstance = hInstance;
	wc.lpfnWndProc = wndproc;
	wc.lpszClassName = defs::CLASSNAME.c_str();
	wc.style = CS_HREDRAW | CS_VREDRAW;

	//ウインドウクラスの登録
	if (FAILED(RegisterClass(&wc))) {
		MessageBox(nullptr, TEXT("Failed Register Window"), TEXT(""), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	//ウインドウスタイルを設定
	//基本的に窓の大きさは変えないので、WS_OVERLAPEDWINDOWから
	//ウインドウサイズの変更に関するフラグを消します。
	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE;

	//ウインドウを生成。実は生成しただけでまだ表示してない。
	auto hwnd = CreateWindow(wc.lpszClassName,
		TEXT("DirectX11 Test"),
		style,
		0, 0, 1280, 720, //X座標、Y座標、Width、Height
		NULL, 0, hInstance, 0);

	if (hwnd == NULL) return 1;

	//ここでやっと表示
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = { 0 };

	//メッセージループ
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return 0;
}

//ウインドウプロシージャ
HRESULT CALLBACK wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:

		return 0;
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}
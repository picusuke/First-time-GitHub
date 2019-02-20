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

	//�E�C���h�E�N���X�̓o�^
	if (FAILED(RegisterClass(&wc))) {
		MessageBox(nullptr, TEXT("Failed Register Window"), TEXT(""), MB_OK | MB_ICONERROR);
		return E_FAIL;
	}
	//�E�C���h�E�X�^�C����ݒ�
	//��{�I�ɑ��̑傫���͕ς��Ȃ��̂ŁAWS_OVERLAPEDWINDOW����
	//�E�C���h�E�T�C�Y�̕ύX�Ɋւ���t���O�������܂��B
	DWORD style = WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME | WS_VISIBLE;

	//�E�C���h�E�𐶐��B���͐������������ł܂��\�����ĂȂ��B
	auto hwnd = CreateWindow(wc.lpszClassName,
		TEXT("DirectX11 Test"),
		style,
		0, 0, 1280, 720, //X���W�AY���W�AWidth�AHeight
		NULL, 0, hInstance, 0);

	if (hwnd == NULL) return 1;

	//�����ł���ƕ\��
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = { 0 };

	//���b�Z�[�W���[�v
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

//�E�C���h�E�v���V�[�W��
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
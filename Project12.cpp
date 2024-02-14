#include "Windows.h"
#include "windowsx.h"
#include "tchar.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID CALLBACK MoveWindow(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	MoveWindow(hwnd, rect.left + 50, rect.top + 50, 300, 300, TRUE);
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	WCHAR className[] = L"FirstWindow";

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = NULL;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = className;

	wndClass.lpfnWndProc = WindowProc;

	if (!RegisterClassEx(&wndClass)) {
		return 0;
	}

	HWND hWnd = CreateWindowEx(
		0,
		className,
		L"My first window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, //x,y
		CW_USEDEFAULT, CW_USEDEFAULT, //width, height
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nShowCmd);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0); //WM_QUIT
		break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_RETURN:
		{
			MoveWindow(hwnd, 300, 300, 300, 300, TRUE);
			break;
		}
		case VK_LEFT:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (x > 0)
			{
				--x;
			}
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		case VK_RIGHT:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (x < 1366)
			{
				++x;
			}
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		case VK_DOWN:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (y < 768)
			{
				++y;
			}
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		case VK_UP:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (y > 0)
			{
				--y;
			}
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		}
		break;
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}
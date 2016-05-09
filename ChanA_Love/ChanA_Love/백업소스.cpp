//#include <windows.h>
//#include <gdiplus.h>
//using namespace Gdiplus;
//#pragma comment(lib, "Gdiplus.lib")
//
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HINSTANCE g_hInst;
//HWND hWndMain;
//LPCTSTR lpszClass = TEXT("Class");
//
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
//	, LPSTR lpszCmdParam, int nCmdShow)
//{
//	HWND hWnd;
//	MSG Message;
//	WNDCLASS WndClass;
//	g_hInst = hInstance;
//
//	WndClass.cbClsExtra = 0;
//	WndClass.cbWndExtra = 0;
//	WndClass.hbrBackground = (HBRUSH)(NULL_BRUSH);
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	WndClass.hInstance = hInstance;
//	WndClass.lpfnWndProc = WndProc;
//	WndClass.lpszClassName = lpszClass;
//	WndClass.lpszMenuName = NULL;
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;
//	RegisterClass(&WndClass);
//
//	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//		NULL, (HMENU)NULL, hInstance, NULL);
//	ShowWindow(hWnd, nCmdShow);
//
//	while (GetMessage(&Message, NULL, 0, 0)) {
//		TranslateMessage(&Message);
//		DispatchMessage(&Message);
//	}
//	return (int)Message.wParam;
//}
//GdiplusStartupInput gdiplusStartupInput;
//ULONG_PTR gdiplusToken;
//Image* image;
//
//void CALLBACK TimerProc(HWND hWnd, UINT iMessage, UINT idEvent, DWORD dwTime)
//{
//	HDC hdc = GetDC(hWnd);
//	Graphics graphics(hdc);
//	graphics.DrawImage(image, image->GetWidth(), 0, -1 * image->GetWidth(), image->GetHeight());
//	ReleaseDC(hWnd, hdc);
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMessage) {
//	case WM_CREATE:
//		hWndMain = hWnd;
//		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
//		image = new Image(L"cksdk_01.png");
//
//		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED); // 윈도우 스타일에 레이어드 속성추가
//		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
//		SetTimer(hWnd, 0, 100, TimerProc);
//		return 0;
//	case WM_DESTROY:
//		KillTimer(hWnd, 0);
//		delete image;
//		GdiplusShutdown(gdiplusToken);
//		PostQuitMessage(0);
//		return 0;
//	case WM_KEYDOWN:
//		if (wParam == VK_ESCAPE) {
//			DestroyWindow(hWnd);
//		}
//		return 0;
//	case WM_NCHITTEST:
//		UINT nHit;
//		nHit = DefWindowProc(hWnd, iMessage, wParam, lParam);
//		if (nHit == HTCLIENT)
//			nHit = HTCAPTION;
//		return nHit;
//
//	}
//	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
//}

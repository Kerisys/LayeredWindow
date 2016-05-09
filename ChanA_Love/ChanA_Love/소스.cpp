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
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	WndClass.hInstance = hInstance;
//	WndClass.lpfnWndProc = WndProc;
//	WndClass.lpszClassName = lpszClass;
//	WndClass.lpszMenuName = NULL;
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;
//	RegisterClass(&WndClass);
//
//	hWnd = CreateWindow(lpszClass, lpszClass, WS_POPUP,
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
//
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	GdiplusStartupInput gdiplusStartupInput;
//	static ULONG_PTR gdiplusToken;
//	static Image* image;
//	HDC hdc;
//	PAINTSTRUCT ps;
//	Graphics* graphics;
//	RECT rt;
//	switch (iMessage) {
//	case WM_CREATE:
//		hWndMain = hWnd;
//		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
//		image = new Image(L"cksdk_01.png");
//		
//		MoveWindow(hWnd, 0, GetSystemMetrics(SM_CYSCREEN)- image->GetHeight(), image->GetWidth(), image->GetHeight(), TRUE);
//		SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOPMOST); // 윈도우 스타일에 레이어드 속성추가
//		SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
//		return 0;
//	case WM_DESTROY:
//		delete image;
//		GdiplusShutdown(gdiplusToken);
//		PostQuitMessage(0);
//		return 0;
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		graphics = new Graphics(hdc);
//		GetWindowRect(hWnd, &rt);
//		FillRect(hdc, &rt,(HBRUSH) GetStockObject(NULL_BRUSH));
//
//		graphics->DrawImage(image, 0, 0, image->GetWidth(), image->GetHeight());
//		delete graphics;
//		EndPaint(hWnd, &ps);
//		return 0;
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case VK_ESCAPE:
//			DestroyWindow(hWnd);
//			break;
//		case VK_RIGHT:
//			GetWindowRect(hWnd, &rt);
//			SetWindowPos(hWnd, HWND_TOPMOST, rt.left + 10, rt.top, 0, 0, SWP_NOSIZE);
//			break;
//		default:
//			break;
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

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED, lpszClass, lpszClass, WS_POPUP,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

void UpdateLayered_AlphaPNG(HWND hWnd, Gdiplus::Image *pImage)
{
	if (pImage == NULL)
		return;

	if (!IsWindow(hWnd))
		return;

	HDC hdc = GetDC(hWnd);
	SIZE sz = { (LONG)pImage->GetWidth() , (LONG)pImage->GetHeight() };

	RECT rt;
	POINT pt = { 0 };
	GetWindowRect(hWnd, &rt);


	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, pImage->GetWidth(), pImage->GetHeight()); // HBITMAP 은 배경이 0으로 초기화되어있음
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

	Gdiplus::Graphics g(hMemDC);
	//g.Clear(Gdiplus::Color(0,0,0,0));
	//g.SetInterpolationMode(Gdiplus::InterpolationModeHighQuality);
	//g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);

	g.DrawImage(pImage, 0, 0, pImage->GetWidth(), pImage->GetHeight());

	// UpdateLayeredWindow 로 윈도우 전체를 그린다, 그러면 png 그림만 남는다
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }; // AlphaBlend() 
	BOOL bRet = UpdateLayeredWindow(hWnd, hdc, ((LPPOINT)&rt), &sz, hMemDC, &pt, 0x00000000, &bf, ULW_ALPHA); // 컬러키 : png 파일 읽으면 gdi+ 는 배경색이 기본적으로 0이다.

	// Release
	SelectObject(hMemDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);

}

class ChanA {
public:
	LONG x, y, width, height;
	LONG dx, dy;
	ULONG_PTR gdiplusToken;
	Image* image[2];
	UINT index;
	LONG screenX, screenY;
	bool AxisX = true;
	ChanA() {
		GdiplusStartupInput gdiplusStartupInput;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		image[0] = new Image(L"cksdk_01.png");
		image[1] = new Image(L"cksdk_02.png");
		index = 0;

		width = image[0]->GetWidth();
		height = image[0]->GetHeight();
		dx = dy = 0;
		screenX = GetSystemMetrics(SM_CXSCREEN);
		screenY = GetSystemMetrics(SM_CYSCREEN);
		x = 0;
		y = screenY-height;
	}

	~ChanA() {
		delete image[0];
		delete image[1];
		GdiplusShutdown(gdiplusToken);
	}
	bool IsJumping = false;
	void Update() {
		byte key[256];
		GetKeyboardState(key);
		dx = 0;
		if (key[37] >> 0x7) { // left arrow
			dx = -15;
			AxisX = false;
		}
		if (key[39] >> 0x7) { // right arrow
			dx = 15;
			AxisX = true;
		}
		if ( !IsJumping && key[32] >> 0x7) { // space bar
			IsJumping = true;
			dy -= 100; // 위로 힘을 준다.
		}

		dy += 15; // 중력 받음.

		x += dx; y += dy;

		if (x < 0) x = 0;
		if (x > screenX - width) x = screenX - width;
		if (y < 0) y = 0;
		if (y > screenY - height) {
			y = screenY - height;
			dy = 0;
			IsJumping = false;
		}

		if (abs(dx) + abs(dy) > 0) {
			index++;
			if (index > 1) index = 0;
		}
	}
	void Render(HWND hWnd) {
		if (!IsWindow(hWnd))
			return;
		if (image[index] == NULL)
			return;

		HDC hdc = GetDC(hWnd);

		HDC hMemDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height); // HBITMAP 은 배경이 0으로 초기화되어있음
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

		Gdiplus::Graphics g(hMemDC);

		g.DrawImage(image[index], (AxisX ? 0:width), 0, (AxisX ? width : -width), height);

		// UpdateLayeredWindow 로 윈도우 전체를 그린다, 그러면 png 그림만 남는다
		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }; // AlphaBlend() 
		POINT pos = { x, y };
		SIZE sz = { width, height };
		POINT ZeroPos = { 0 };
		
		BOOL bRet = UpdateLayeredWindow(hWnd, hdc, &pos, &sz, hMemDC, &ZeroPos, NULL, &bf, ULW_ALPHA); // 컬러키 : png 파일 읽으면 gdi+ 는 배경색이 기본적으로 0이다.
																												  // Release
		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(hMemDC);
		ReleaseDC(hWnd, hdc);
	}
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static ChanA* cksdk;
	//RECT rt;
	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		cksdk = new ChanA();
		SetTimer(hWnd, 0, 1000/30, NULL);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		delete cksdk;
		PostQuitMessage(0);
		return 0;
	case WM_TIMER:
		cksdk->Update();
		cksdk->Render(hWnd);
		return 0;
	case WM_KEYDOWN:
		if(wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		return 0;
	case WM_NCHITTEST:
		UINT nHit;
		nHit = DefWindowProc(hWnd, iMessage, wParam, lParam);
		if (nHit == HTCLIENT)
			nHit = HTCAPTION;
		return nHit;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

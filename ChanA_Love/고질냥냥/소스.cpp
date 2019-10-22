#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")
#include <vector>
using namespace std;
#include <time.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("고질냥냥");

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
    WndClass.hIcon = LoadIcon(NULL, IDI_SHIELD);
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

Image* LoadPNG(HMODULE hModule, LPCWSTR ResourceName)
{
    Image* image        = NULL;
    IStream* pStream    = NULL;

    HRSRC hResource     = FindResource(hModule, ResourceName, L"PNG");

    if (CreateStreamOnHGlobal(NULL, TRUE, &pStream) == S_OK) {
        PVOID pResourceData = LockResource(LoadResource(hModule, hResource));
        DWORD imageSize     = SizeofResource(hModule, hResource);
        DWORD dwReadWrite   = 0;
        pStream->Write(pResourceData, imageSize, &dwReadWrite);
        image = Image::FromStream(pStream);
        pStream->Release();
    }
    return image;
}

class GozilNyang {
public:
    LONG x, y, width, height;
    LONG dx, dy;
    ULONG_PTR gdiplusToken;

    UINT index;
    Image* image;
    Image* idle;
    // Image* breath[6];
    vector<Image*> breath;
    clock_t lastUpdate;

    LONG screenX, screenY;
    bool AxisX;     // 왼쪽/오른쪽
    bool IsJumping; // 점프중인가
    bool IsBreath;  // 브레스 스킬 시전중인가

    GozilNyang() {
        GdiplusStartupInput gdiplusStartupInput;
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

        AxisX = true;
        IsJumping = false;
        IsBreath = false;
        //idle = LoadPNG(g_hInst, MAKEINTRESOURCE(IDP_IDLE));

        for (int i = 0; i < 6; i++) {
            breath.push_back( LoadPNG( g_hInst, MAKEINTRESOURCE(IDP_BREATH1 + i) ) );
        }
        idle = breath[0];
        image = idle;

        width = image->GetWidth();
        height = image->GetHeight();
        dx = dy = 0;
        screenX = GetSystemMetrics(SM_CXSCREEN);
        screenY = GetSystemMetrics(SM_CYSCREEN);
        // x = 0;
        x = width/2-200;
        y = screenY - height;

        lastUpdate = clock();
    }

    ~GozilNyang() {
        image = NULL;
        idle = NULL;
        //delete idle;

        for(vector<Image*>::iterator iter=breath.begin(); iter != breath.end(); ++iter)
        {
            delete *iter;
        }
        breath.clear();

        GdiplusShutdown(gdiplusToken);
    }

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
        if (!IsJumping && key[38] >> 0x7) { // up arrow
            IsJumping = true;
            dy -= 100; // 위로 힘을 준다.
        }

        if (!IsJumping && !IsBreath && key[32] >> 0x7) { // space bar
            IsBreath = true;
        }


        if (IsBreath) {
            if (index < breath.size()) {
                clock_t deltaTime = (clock() - lastUpdate);
                if (10 <= deltaTime) {
                    image = breath.at(index++);
                    lastUpdate = clock();
                }
                dx = 0; dy = 0;

            }
            else {
                index = 0;
                IsBreath = false;
                image = idle;
            }
        }

        dy += 15; // 중력 받음.

        x += dx; y += dy;

        width = image->GetWidth();
        height = image->GetHeight();

        ///if (x < 0) x = 0;
        if (x < -400) x = -400;
        if (x > screenX - width+400) x = screenX - width+400;
        if (y < 0) y = 0;
        if (y > screenY - height) {
            y = screenY - height;
            dy = 0;
            IsJumping = false;
        }

    }
    void Render(HWND hWnd) {
        if (!IsWindow(hWnd))
            return;
        if (image == NULL)
            return;

        HDC hdc = GetDC(hWnd);

        HDC hMemDC = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, width, height); // HBITMAP 은 배경이 0으로 초기화되어있음
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

        Graphics g(hMemDC);

        g.DrawImage(image, (AxisX ? 0 : width), 0, (AxisX ? width : -width), height);

        BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }; // AlphaBlend()
        POINT pos = { x, y };
        SIZE sz = { width, height };
        POINT ZeroPos = { 0 };

        BOOL bRet = UpdateLayeredWindow(hWnd, hdc, &pos, &sz, hMemDC, &ZeroPos, 0, &bf, ULW_ALPHA); // 컬러키 : png 파일 읽으면 gdi+ 는 배경색이 기본적으로 0이다.

        g.ReleaseHDC(hMemDC);


        // Release
        SelectObject(hMemDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemDC);
        ReleaseDC(hWnd, hdc);
    }
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    static GozilNyang* nyang;
    switch (iMessage) {
    case WM_CREATE:
        hWndMain = hWnd;
        nyang = new GozilNyang();
        SetTimer(hWnd, 0, 1000 / 30, NULL);
        return 0;
    case WM_DESTROY:
        KillTimer(hWnd, 0);
        delete nyang;
        PostQuitMessage(0);
        return 0;
    case WM_TIMER:
        if (nyang) {
            nyang->Update();
            nyang->Render(hWnd);
        }
        return 0;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            DestroyWindow(hWnd);
        return 0;
    case WM_NCHITTEST:
        LRESULT nHit;
        nHit = DefWindowProc(hWnd, iMessage, wParam, lParam);
        if (nHit == HTCLIENT)
            nHit = HTCAPTION;
        return nHit;
    }
    return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

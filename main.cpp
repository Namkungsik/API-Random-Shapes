#include <windows.h>
#include <time.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void _Line(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, int pSty, COLORREF crPen);
void _Ellips(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, int num, int pSty, COLORREF crPen, COLORREF crBrush);
void _Rectangle(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, int num, int pSty, COLORREF crPen, COLORREF crBrush);
void _Text(HWND hwnd, HDC hdc, int x, int y, int tWidth, int tHeight, int rotate, int BkMode, COLORREF crPen);
void RandRect(HWND hwnd, HDC hdc);

void _BoundaryLine(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, COLORREF crBrush);

//// WinMain 함수 : 윈도즈 프로그램의 최초 진입점 ( Entry Point )
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR	  lpCmdLine,
	int		  nCmdShow)
{
	char	  szAppName[] = "예제";
	HWND	  hWnd;
	MSG      msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	//// 윈도 클래스 등록
	RegisterClass(&wndclass);

	//// 윈도 생성
	hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 100, 1000, 500,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	//// 생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//// 메시지 루프
	while (TRUE)
	{
		HDC			hdc;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)break;
			DispatchMessage(&msg);
		}
		else
		{
			hdc = GetDC(hWnd);
			_BoundaryLine(hWnd, hdc, 0, 0, 0, 0, RGB(0, 0, 0));
			RandRect(hWnd, hdc);
			Sleep(1000);
			ReleaseDC(hWnd, hdc);
		}
	}
	return (int)msg.wParam;
}

int g_nWidth, g_nHeight;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_SIZE:
		g_nWidth = LOWORD(lParam);
		g_nHeight = HIWORD(lParam);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void _Line(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, int pSty, COLORREF crPen)
{
	HPEN newPen, oldPen;

	int cWidth = 1;
	if (pSty == 0)
		cWidth = 2;

	if (g_nWidth && g_nHeight)
	{
		hdc = GetDC(hwnd);
		newPen = CreatePen(pSty, cWidth, crPen);
		oldPen = (HPEN)SelectObject(hdc, newPen);
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
		SelectObject(hdc, oldPen);
		ReleaseDC(hwnd, hdc);
		ValidateRect(hwnd, NULL);
	}
}

void _Ellips(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, int num, int pSty, COLORREF crPen, COLORREF crBrush)
{
	HPEN newPen, oldPen;
	HBRUSH newBrush, oldBrush;

	int cWidth = 1;
	if (pSty == 0)
		cWidth = 2;

	switch (num)
	{
	case 0:
		if (g_nWidth && g_nHeight)
		{
			hdc = GetDC(hwnd);
			newPen = CreatePen(pSty, cWidth, crPen);
			oldPen = (HPEN)SelectObject(hdc, newPen);
			Ellipse(hdc, x1, y1, x2, y2);
			SelectObject(hdc, oldPen);
			DeleteObject(newPen);
			ReleaseDC(hwnd, hdc);
			ValidateRect(hwnd, NULL);
		}
		break;
	case 1:
		if (g_nWidth && g_nHeight)
		{
			hdc = GetDC(hwnd);
			newBrush = CreateSolidBrush(crBrush);
			oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
			Ellipse(hdc, x1, y1, x2, y2);
			SelectObject(hdc, oldBrush);
			DeleteObject(newBrush);
			ReleaseDC(hwnd, hdc);
			ValidateRect(hwnd, NULL);
		}
		break;
	}
}

void _Rectangle(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, int num, int pSty, COLORREF crPen, COLORREF crBrush)
{
	HPEN newPen, oldPen;
	HBRUSH newBrush, oldBrush;

	int cWidth = 1;
	if (pSty == 0)
		cWidth = 2;

	switch (num)
	{
	case 0:
		if (g_nWidth && g_nHeight)
		{
			hdc = GetDC(hwnd);
			newPen = CreatePen(pSty, cWidth, crPen);
			oldPen = (HPEN)SelectObject(hdc, newPen);
			Rectangle(hdc, x1, y1, x2, y2);
			SelectObject(hdc, oldPen);
			DeleteObject(newPen);
			ReleaseDC(hwnd, hdc);
			ValidateRect(hwnd, NULL);
		}
		break;
	case 1:
		if (g_nWidth && g_nHeight)
		{
			hdc = GetDC(hwnd);
			newBrush = CreateSolidBrush(crBrush);
			oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
			Rectangle(hdc, x1, y1, x2, y2);
			SelectObject(hdc, oldBrush);
			DeleteObject(newBrush);
			ReleaseDC(hwnd, hdc);
			ValidateRect(hwnd, NULL);
		}
		break;
	}
}
void _Text(HWND hwnd, HDC hdc, int x, int y, int tWidth, int tHeight, int rotate, int BkMode, COLORREF crPen)
{
	char str[] = "NKS";
	HFONT MyFont, OldFont;

	if (g_nWidth && g_nHeight)
	{
		hdc = GetDC(hwnd);
		MyFont = CreateFont(10, 0, rotate, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS,
			"Times New Roman");
		OldFont = (HFONT)SelectObject(hdc, MyFont);
		SetBkMode(hdc, BkMode);
		SetBkColor(hdc, RGB(0, 0, 255));
		SetTextColor(hdc, crPen);
		TextOut(hdc, x, y, str, strlen(str));
		SelectObject(hdc, OldFont);
		DeleteObject(MyFont);

		ReleaseDC(hwnd, hdc);
		ValidateRect(hwnd, NULL);
	}
}
void _BoundaryLine(HWND hwnd, HDC hdc, int x1, int y1, int x2, int y2, COLORREF crPen)
{
	HPEN newPen, oldPen;

	x1 = 0;
	x2 = g_nWidth;
	y1 = g_nHeight / 2;
	y2 = g_nHeight / 2;

	if (g_nWidth && g_nHeight)
	{
		hdc = GetDC(hwnd);
		newPen = CreatePen(PS_SOLID, 1, crPen);
		oldPen = (HPEN)SelectObject(hdc, newPen);
		MoveToEx(hdc, x1, y1, NULL);
		LineTo(hdc, x2, y2);
		MoveToEx(hdc, g_nWidth, 0, NULL);
		LineTo(hdc, g_nWidth, g_nHeight);
		SelectObject(hdc, oldPen);
		newPen = CreatePen(PS_SOLID, 1, crPen);
		oldPen = (HPEN)SelectObject(hdc, newPen);
		MoveToEx(hdc, g_nWidth / 2, 0, NULL);
		LineTo(hdc, g_nWidth / 2, g_nHeight);
		ReleaseDC(hwnd, hdc);
		ValidateRect(hwnd, NULL);
	}
}

void RandRect(HWND hwnd, HDC hdc)
{
	srand(time(NULL));

	int num = rand() % 3;
	int crSel = rand() % 2;
	int pSty = rand() % 4;
	int bkMode = rand() % 3;

	int x1 = rand() % (g_nWidth);
	int x2 = rand() % (g_nWidth);
	int y1 = rand() % (g_nHeight);
	int y2 = rand() % (g_nHeight);
	int rColor = rand() % 256;
	int gColor = rand() % 256;
	int bColor = rand() % 256;

	int cLineX1 = (g_nWidth / 2) - (x1 / 2);
	int cLineX2 = (g_nWidth / 2) - (x2 / 2);
	int dLineY1 = (g_nHeight - (y1 / 2));
	int dLineY2 = (g_nHeight - (y2 / 2));

	int cX1 = (g_nWidth / 2 - x2 / 2);
	int cX2 = (g_nWidth / 2 - x1 / 2);
	int dY1 = ((g_nHeight)-y2 / 2);
	int dY2 = ((g_nHeight)-y1 / 2);

	if (g_nWidth && g_nHeight)
	{
		switch (num)
		{
		case 0:
			_Line(hwnd, hdc, x1 / 2, y1 / 2, x2 / 2, y2 / 2, pSty, 
				RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Line(hwnd, hdc, (g_nWidth / 2) + x1 / 2, y1 / 2, (g_nWidth / 2) + x2 / 2, y2 / 2, pSty,
				GetPixel(hdc, x1 / 2, y1 / 2));
			Sleep(1000);
			_Line(hwnd, hdc, cLineX1, (g_nHeight / 2) + y1 / 2, cLineX2, (g_nHeight / 2) + y2 / 2, pSty, 
				RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Line(hwnd, hdc, (g_nWidth / 2) + x1 / 2,dLineY1, (g_nWidth / 2) + x2 / 2,dLineY2, pSty,
				RGB(rColor, gColor, bColor));
			break;
		case 1:
			_Rectangle(hwnd, hdc, x1 / 2, y1 / 2, x2 / 2, y2 / 2, crSel, pSty, 
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Rectangle(hwnd, hdc, (g_nWidth / 2) + x1 / 2, y1 / 2, (g_nWidth / 2) + x2 / 2, y2 / 2, crSel, pSty, 
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Rectangle(hwnd, hdc, cX1, (g_nHeight / 2) + y1 / 2, cX2, (g_nHeight / 2) + y2 / 2, crSel, pSty, 
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Rectangle(hwnd, hdc, (g_nWidth / 2) + x1 / 2, dY1, (g_nWidth / 2) + x2 / 2, dY2, crSel, pSty, 
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			break;
		case 2:
			_Ellips(hwnd, hdc, x1 / 2, y1 / 2, x2 / 2, y2 / 2, crSel, pSty, 
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Ellips(hwnd, hdc, (g_nWidth / 2) + x1 / 2, y1 / 2, (g_nWidth / 2) + x2 / 2, y2 / 2, crSel, pSty,
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Ellips(hwnd, hdc, cX1, (g_nHeight / 2) + y1 / 2, cX2, (g_nHeight / 2) + y2 / 2, crSel, pSty, 
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Ellips(hwnd, hdc, (g_nWidth / 2) + x1 / 2, dY1, (g_nWidth / 2) + x2 / 2, dY2, crSel, pSty,
				RGB(rColor, gColor, bColor), RGB(rColor, gColor, bColor));
			break;
		/*case 3:
			_Text(hwnd, hdc, x1 / 2, y1 / 2, 10, 0, 0, bkMode, RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Text(hwnd, hdc, (g_nWidth / 2) + x1 / 2, y1 / 2, 10, 0, 0, bkMode, RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Text(hwnd, hdc, cLineX1, (g_nHeight / 2) + y1 / 2, 10, 0, 0, bkMode, RGB(rColor, gColor, bColor));
			Sleep(1000);
			_Text(hwnd, hdc, ((g_nWidth / 2) + x1 / 2) + 10, dLineY1, 10, 0, 1800, bkMode, RGB(rColor, gColor, bColor));
			Sleep(1000);*/
		default:
			break;
		}
	}
}
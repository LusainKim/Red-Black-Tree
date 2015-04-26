#include <Windows.h>
#include <time.h>
#include "Page.h"
#include "Button.h"

//윈도우 프로시저의 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//윈도우즈 프로시저 선언

HINSTANCE g_hInst;//인스턴스 핸들을 저장하기 위한 전역변수


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow)
{
	TCHAR szClassName[] = L"winMain";//윈도우 클래스 이름
	TCHAR szTitle[] = L"now loading";//타이틀 바에 출력될 이름

	MSG msg;			//메세지 구조체
	HWND hWnd;		//윈도우 핸들
	WNDCLASSEX wc;	//윈도우 클래스 구조체
	g_hInst = hInstance;	//인스스 핸들 저장
	//------------------------------------------------------ :: 윈도우 구조체에 값을 지정한다. ::-----------------------------------
	wc.cbSize = sizeof(WNDCLASSEX);										//윈도우 클래스 구조체의 크기
	wc.style = CS_HREDRAW | CS_VREDRAW;								//클래스 스타일

	//윈도우 프로시저를 윈도우클래스 구조체에 등록

	wc.lpfnWndProc = WndProc;											//윈도우 프로시저 지정
	wc.cbClsExtra = 0;															//윈도우 클래스 데이터 영역
	wc.cbWndExtra = 0;														//윈도우의 데이터 영역
	wc.hInstance = hInstance;												//인스턴스 핸들
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);						//아이콘 핸들
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);						//사용할 커서 핸들
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//바탕색 브러시
	wc.lpszMenuName = NULL;												//메뉴 이름
	wc.lpszClassName = szClassName;										//윈도우 클래스 이름
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);					//작은 아이콘 핸들
	//------------------------------------------------------ :: 윈도우 클래스를 등록한다.
	RegisterClassEx(&wc);							//   :: 윈도우 클래스 등록
	//------------------------------------------------------ :: 프레임 윈도우를 생성
	hWnd = CreateWindow(
		szClassName,								//윈도우 클래스 이름
		szTitle,											//타이틀 바에 출력될 문자열, 앞에서 지정함
		WS_OVERLAPPEDWINDOW,				//윈도우 스타일, 앞에서 지정
		CW_USEDEFAULT,							//윈도우 좌측 상단의 X 좌표
		CW_USEDEFAULT,							//윈도우 좌측 상단의 Y 좌표
		CLIENT_WIDTH,							//윈도우의 폭
		CLIENT_HEIGHT,							//윈도우의 높이
		NULL,											//부모 핸들의 높이
		NULL,											//메뉴, 혹은 자식 윈도우의 식별자
		hInstance,									//윈도우를 생성한 인스턴스 핸들,  WinMain의 첫번째 인자
		NULL											//CREATESTRUCT 구조체를 통해 전달되는 값
		);

	if (!hWnd)						//윈도우 생성에 실패 시
		return(FALSE);			//프로그램 종료
	//------------------------------------------------------ :: 프레임 윈도우를 화면에 출력
	ShowWindow(hWnd, nCmdShow);				//윈도우를 화면에 나타낸다.
	UpdateWindow(hWnd);								//윈도우의 클라이언트 영역을 칠한다.
	//------------------------------------------------------ :: 메시지 루프 : 루프를 돌며 메세지 큐로부터 메세지를 얻어와 처리한다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		//	if(!TranslateAccelerator(hWnd,hAccel,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static line l[3];
	HDC hdc;
	PAINTSTRUCT ps;
	HDC LayDC;
	HBITMAP Lay;
	static pButtonA button[3];
	static bool Gameover;
	switch (uMsg)
	{
	case WM_CREATE:
		srand((unsigned int)time(NULL));
		Gameover = false;
		for (auto& p : l)
		{
			p.SetFrequenct(rand() % 10);
			p.SetSpeed(rand() % 15 + 5);
		}

		for (int i = 0; i < 3; ++i)
		{
			button[i].Initialize(NULL, hWnd, { 0, 0 }, true, { 0, 0, 0, 0 },
				true, { 100 + i * 250, 300, 300 + i * 250, 350 });
			TCHAR str[5];
			wsprintf(str, L"%c", TCHAR(i + 'A'));
			button[i].SetName(str);
			button[i].SetLine(&l[i]);
		}

		SetTimer(hWnd, 0, 16, NULL);
		break;

	case WM_LBUTTONDOWN:
		if (Gameover)
		{
			Gameover = false;
			for (auto& p : l)
			{
				p.SetFrequenct(rand() % 10);
				p.SetSpeed(rand() % 15 + 5);
			}
			SetTimer(hWnd, 0, 16, NULL);
		}

		for (int i = 0; i < 3; ++i)
			button[i].OnProcessingMouseMessage(hWnd, uMsg, wParam, lParam);

		break;

	case WM_MOUSEMOVE:
		for (int i = 0; i < 3; ++i)
			button[i].OnProcessingMouseMessage(hWnd, uMsg, wParam, lParam);
		break;

	case WM_LBUTTONUP:
		for (int i = 0; i < 3; ++i)
			button[i].OnProcessingMouseMessage(hWnd, uMsg, wParam, lParam);
		break;

	case WM_KEYDOWN:
		if (wParam == 'Q' || wParam == VK_ESCAPE)
			DestroyWindow(hWnd);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case 0:

			for (auto& p : l)
			{
				p.addLine();

				if (p.getLine() > CLIENT_WIDTH * 0.8)
				{
					Gameover = true;
					KillTimer(hWnd, 0);
				}
			}
			InvalidateRect(hWnd, NULL, false);
			break;
		}
		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		LayDC = CreateCompatibleDC(hdc);
		Lay	 = CreateCompatibleBitmap(hdc, 1000, 800);
		SelectObject(LayDC, Lay);
		Rectangle(LayDC, -1, -1, CLIENT_WIDTH, CLIENT_HEIGHT);
		//-------------------------------------------------

		for (int i = 0; i < 3; ++i)
		{
			TCHAR str[5];
			wsprintf(str, L"%c", TCHAR(i + 'A'));
			RECT rc = { 35, i * 70 + 50, 85, i * 70 + 100 };
			DrawText(LayDC, str, -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			rc = { 85, i * 70 + 50, 85 + l[i].length, i * 70 + 100 };
			SetDCBrushColor(LayDC, l[i].getColor());
			FillRect(LayDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

		}

		for (int i = 0; i < 3; ++i)
			button[i].OnDraw(LayDC);

		if (Gameover)
		{
			RECT rc = { 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT };
			DrawText(LayDC, L"Game Over", -1, &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		}

		//-------------------------------------------------

		BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, LayDC, 0, 0, SRCCOPY);

		DeleteObject(Lay);
		DeleteDC(LayDC);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 0);
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}
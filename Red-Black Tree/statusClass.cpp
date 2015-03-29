#include"define.h"


statusClass::statusClass(LPCWSTR ClassName, LPCWSTR Title)
{
	IsWCInit = false;
	IsCreate = false;
	hWnd = pWnd = nullptr;
	g_hInst = nullptr;
	winSize = { 0, 0 };
	lstrcpy(szClassName, ClassName);	//윈도우 클래스 이름
	lstrcpy(szTitle, Title);			//타이틀 바에 출력될 문자열
}

statusClass::statusClass(LPCWSTR ClassName, LPCWSTR Title,
	int x, int y, WNDPROC WndProc)
{
	IsWCInit = false;
	IsCreate = false;
	hWnd = pWnd = nullptr;
	g_hInst = nullptr;
	lstrcpy(szClassName, ClassName);	//윈도우 클래스 이름
	lstrcpy(szTitle, Title);			//타이틀 바에 출력될 문자열
	winSize = { x, y };

}

void statusClass::SetWindowClass(
	WNDPROC WndProc,
	HINSTANCE hInst,
	UINT style,
	LPCWSTR Icon){
	
	if (IsWCInit)
		return;
	g_hInst = hInst;
	IsWCInit = ON;

	wc.cbSize = sizeof(WNDCLASSEX);

	wc.lpfnWndProc = WndProc;
	Proc = WndProc;
	wc.style = style;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInst;
	wc.hIcon = LoadIcon(g_hInst, Icon);
	wc.hCursor = LoadCursor(g_hInst, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(g_hInst, Icon);

	//------------------------------------------------------ :: 윈도우 클래스를 등록한다.
	RegisterClassEx(&wc);							//   :: 윈도우 클래스 등록

}
void statusClass::CreateWnd(DWORD SetType, POINT wndPos, POINT wndSize,
	bool IsCaption, HWND pwnd)
{
	POINT
		ws,
		wp;
	RECT
		getWinSize;
	

	if (IsPOINT(winSize, { 0, 0 }) && IsPOINT(wndSize, winSize))
		ws = winSize = wndSize = wndPos;
	else if (IsPOINT(winSize, { 0, 0 }) && !IsPOINT(wndSize, winSize))
		ws = winSize = wndSize;

	if (!IsPOINT(wndPos, P_default))
		wp = wndPos;
	else if (!pwnd)
	{
		GetWindowRect(GetDesktopWindow(), &getWinSize);
		wp = { (getWinSize.right - wndSize.x) / 2, (getWinSize.bottom - wndSize.y) / 2 };
	}
	else
		wp = { 0, 0 };

	if (IsCaption)
		ws = { GetSystemMetrics(SM_CXFRAME),
		GetSystemMetrics(SM_CYFRAME)
		+ GetSystemMetrics(SM_CYCAPTION) };
	else
		ws = { 0, 0 };

	if (IsCaption)
		ws = P_plus(ws, wndSize);
	else if (IsPOINT(wndSize, P_default))
		if (IsCaption)
			ws = P_plus(ws, winSize);
		else
			ws = winSize;
	else
		ws = wndSize;

	if (SetType == I_default)
		SetType = WS_CAPTION | WS_SYSMENU |
		WS_MINIMIZEBOX;// | WS_THICKFRAME;

	pWnd = pwnd;
	hWnd = CreateWindow(
		szClassName,									//윈도우 클래스 이름
		szTitle,												//타이틀 바에 출력될 문자열, 앞에서 지정함
		SetType,											//윈도우 스타일, 앞에서 지정
		wp.x,													//윈도우 좌측 상단의 X 좌표
		wp.y,													//윈도우 좌측 상단의 Y 좌표
		ws.x,													//윈도우의 폭
		ws.y,													//윈도우의 높이
		pWnd,												//부모 핸들의 높이
		NULL,												//메뉴, 혹은 자식 윈도우의 식별자
		g_hInst,												//윈도우를 생성한 인스턴스 핸들,  WinMain의 첫번째 인자
		NULL												//CREATESTRUCT 구조체를 통해 전달되는 값
		);
}
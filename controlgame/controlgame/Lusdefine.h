#pragma once

#include <Windows.h>

#pragma comment(lib,"msimg32")

#define FLAG bool
#define	ON	true
#define	OFF false

#define EXT extern 

#define	ResourceImage(hInstance,ImageName) \
			LoadBitmap(hInstance, MAKEINTRESOURCE(ImageName))
#define StorageImage(ImageName) MAKEINTRESOURCE(ImageName)

#define _60_fps 16
#define _30_fps 32

#define zeroVec {0,0}

#define WM_GETVALUE 0x401
#define wGETMSG		(WPARAM)0x001
#define wGETINITFLAG	(WPARAM)0x002

#define sideCheck(_min, _val, _max)	( ( ( (_min) <= (_val) ) && ( (_val) < (_max) ) ) ? true : false)

#define W_RGB RGB(255,255,255)
#define B_RGB RGB(0,0,0)
#define GRAY_RGB RGB(95,95,95)

#define ALPHA_SELECT	140

// DrawLine
#define DL_FILL ON
#define DL_FRAME OFF

// FontSize Part
#define DEFAULT_FontSize 15
#define TITLE_FontSize 80
#define LARGE_FontSize 25

#define DEFAULT_MSGWIDTH 170
#define DEFAULT_MSGHEIGHT 180

typedef struct tag_LusMsg
{
	HWND		hWnd;
	RECT		MsgSize;
	TCHAR		*Title;
	TCHAR		*Msg;
	TCHAR		*InBoxMsg_1;
	TCHAR		*InBoxMsg_2;
	int			InBoxMsgNum;
	POINT		MsgStartPos;
	COLORREF	TextColor;
	COLORREF	MsgColor;
	int			FontSize;
	void	*thisClass;
	void(*Msg_1_Func)(void *GClass);
	void(*Msg_2_Func)(void *GClass);
	tag_LusMsg()	{ hWnd = NULL; MsgSize = { 0, 0, 0, 0 }; InBoxMsgNum = 1; MsgStartPos = { 0, 0 }; FontSize = -1; thisClass = NULL; }
}LusMsg;

typedef struct tag_LusInputBox
{
	HWND		hWnd;
	RECT		MsgSize;
	TCHAR		*Title;
	TCHAR		*Msg;
	TCHAR		*YesBox;
	TCHAR		*NoBox;
	TCHAR		BoxValue[256];
	POINT		MsgStartPos;
	COLORREF	TextColor;
	COLORREF	MsgColor;
	int			FontSize;
	int			InputSize;
	int			InputMax;
	bool		IsOnlyUseNum;
	void		*thisClass;
	void(*resultFunc)(void *GClass, TCHAR *output);
	void(*undoFunc)(void *GClass);
	tag_LusInputBox(){
		hWnd = NULL; 
		MsgSize = { 0, 0, 0, 0 }; 
		MsgStartPos = { 0, 0 };
		FontSize = -1; 
		thisClass = NULL;
		IsOnlyUseNum = false;
		YesBox = L"확인";
		NoBox = L"취소";
		BoxValue[0] = '\0';
		InputMax = 256;
	}
}LusInputBox;

EXT FLAG Flag_LusMsgBox;

POINT operator+(const POINT& a, const POINT& b);
POINT operator-(const POINT& a, const POINT& b);
POINT operator*(float b, const POINT& a);
bool operator==(const POINT& a, const POINT& b);
RECT operator+(const POINT& pt, const RECT& rc);
RECT operator+(const RECT& rc, const POINT& pt);

 void close_LusMsgProc();

 void LusMsgBox(HWND hWnd, LusMsg Msg, HINSTANCE g_hInst, int _ALPHA_MSG);
 void LusInputBoxBox(HWND hWnd, LusInputBox Msg, HINSTANCE g_hInst, int alpha_message);
 
 bool flip(bool Is);
 void  numFix(LPWSTR DestMsg, int fixnum);
 int square(int val);
 double square(double val);
 int sideStore(int min, int value, int max);
 float sideStore(float min, float value, float max);


 int Length2(POINT StartPoint, POINT EndPoint);
 RECT SizeDown(RECT rc, int len);
 void LusMsgBox(HWND hWnd, LusMsg Msg, HINSTANCE g_hInst, int _ALPHA_MSG);
 bool flip(bool Is);
 void  numFix(LPSTR DestMsg, int fixnum);
 int square(int val);
 double square(double val);
 int sideStore(int min, int value, int max);
 bool PtInEllipse(LPCRECT lprc, POINT p);
 bool IsPOINT(POINT p1, POINT p2);
 void DrawLineBox(HDC mainDC, RECT rc, COLORREF main_RGB, COLORREF Line_RGB, int LineLen, bool Type);
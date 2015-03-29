#include<Windows.h>

#define FLAG bool
#define	ON	true
#define	OFF false

#define EXT extern 

#define	ResourceImage(hInstance,ImageName) \
			LoadBitmap(hInstance, MAKEINTRESOURCE(ImageName))
#define StorageImage(ImageName) MAKEINTRESOURCE(ImageName)

#define _60fps 16
#define _30fps 32

#define zeroVec {0,0}

#define WM_GETVALUE 0x401
#define wGETMSG		(WPARAM)0x001
#define wGETINITFLAG	(WPARAM)0x002

#define sideCheck(_min, _val, _max)	( ( ( (_min) <= (_val) ) && ( (_val) < (_max) ) ) ? true : false)

#define P_minus	LenOperMinus
#define P_plus	POINT_oper_plus
#define R_P_plus RECT_oper_plus_pt

#define W_RGB RGB(255,255,255)
#define B_RGB RGB(0,0,0)
#define GRAY_RGB RGB(95,95,95)

// DrawLine
#define DL_FILL ON
#define DL_FRAME OFF

EXT POINT LenOperMinus(POINT a, POINT b);
EXT POINT POINT_oper_plus(POINT a, POINT b);
EXT RECT RECT_oper_plus_pt(RECT rc, POINT pt);
EXT RECT SizeDown(RECT rc, int len);
EXT bool flip(bool Is);
EXT void  numFix(LPSTR DestMsg, int fixnum);
EXT int square(int val);
EXT double square(double val);
EXT int sideStore(int min, int value, int max);
EXT bool PtInEllipse(LPCRECT lprc, POINT p);
EXT bool IsPOINT(POINT p1, POINT p2);
EXT void DrawLineBox(HDC mainDC, RECT rc, COLORREF main_RGB, COLORREF Line_RGB, int LineLen, bool Type);
EXT void ErrorMsgBox(LPCWSTR Msg);
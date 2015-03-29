#include"Lusdefine.h"

#define MsgBlank 5
#define MsgWidth 160
#define ButtonHeight 35

RECT RECT_oper_plus_pt(RECT rc, POINT pt)
{
	RECT rc_result =
	{
		pt.x + rc.left,
		pt.y + rc.top,
		pt.x + rc.right,
		pt.y + rc.bottom
	};
	return rc_result;
}
POINT POINT_oper_plus(POINT a, POINT b)
{
	return{ a.x + b.x, a.y + b.y }; 
}

POINT LenOperMinus(POINT a, POINT b)
{
	POINT c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

void  numFix(LPWSTR DestMsg, int fixnum)
{
	TCHAR Fix[20] = L"0\0", returnMsg[20];
	int count = 0;

	while (fixnum >0)
	{
		int endnum = fixnum % 10;
		fixnum /= 10;
		Fix[count] = '0' + endnum;
		count++;
		if (count % 4 == 3 && fixnum > 0)
		{
			Fix[count] = ',';
			count++;
		}
	}
	if (count == 0)
		count++;
	for (int fa = 0; fa<count; fa++)
		returnMsg[fa] = Fix[count - fa - 1];
	returnMsg[count] = '\0';

	//	printf("%s\n", returnMsg);

	lstrcpy(DestMsg, returnMsg);

}

RECT SizeDown(RECT rc, int len)
{
	len = min(rc.right / 2, len);
	rc = { rc.left + len, rc.top + len, rc.right - len, rc.bottom - len };
	return rc;
}

int sideStore(int min, int value, int max)
{
	int return_val = value;
	if (min > value)
		return_val = min;
	if (value > max)
		return_val = max;

	return return_val;
}

bool flip(bool Is){ return !Is; }; 

int square(int val){ return (val * val); }

double square(double val){ return (val * val); }

bool PtInEllipse(LPCRECT lprc, POINT p)
{
	POINT cent;
	int length_1, length_2;

	cent = { (lprc->right + lprc->left) / 2, (lprc->bottom + lprc->top) / 2 };
	length_1 = (square(lprc->right - lprc->left) / 2);
	length_2 = square(cent.x - p.x) + square(cent.y - p.y);

	//	if ((lprc->right - lprc->left) / 2 == (lprc->bottom - lprc->top) / 2)
	{
		if (length_1 > length_2)
			return true;
		else return false;
	}
	return false;
}
bool IsPOINT(POINT p1, POINT p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	else
		return false;
}
int Length2(POINT StartPoint, POINT EndPoint)
{
	return
		square(StartPoint.x - EndPoint.x) + 
		square(StartPoint.y - EndPoint.y);
}

void DrawLineBox(HDC mainDC, RECT rc,
	COLORREF main_RGB, COLORREF Line_RGB, int LineLen, bool Type)
{
	SetDCBrushColor(mainDC, main_RGB);
	FillRect(mainDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

	rc = SizeDown(rc, LineLen);
	SetDCBrushColor(mainDC, Line_RGB);

	FrameRect(mainDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));

	if (Type == true)
	{
		rc = SizeDown(rc, 2);
		FillRect(mainDC, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
	}
}

void ErrorMsgBox(LPCWSTR Msg)
{
	MessageBox(NULL, Msg, L"Error!", MB_OK);
}
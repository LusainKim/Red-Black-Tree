#pragma once

#include "Page.h"

class pButton : public Page{
protected:
	bool		m_bPush;
	bool		m_bStay;
	
public:
	pButton();
	~pButton();
	virtual void Initialize(CGameFramework *parent, HWND hWnd, POINT startPos, bool View, RECT rc, bool bUseButton = false, RECT rcButton = { 0, 0, 0, 0 });
	virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void Update(float fTimeElapsed);
	virtual void OnDraw(HDC hDC);
};

class line{
public:
	int length;
	int speed;
	int frequency;
	int tick;
	COLORREF color;

	line(){ length = 0; color = RGB(rand() % 125 + 125, rand() % 125 + 125, rand() % 125 + 125); }
	void addLine(){ if (tick > frequency) { length += speed; tick = 0; } else tick++; }
	void AdjustLength(int len, bool init = false){ (init) ? length = len : length += len; }
	void SetSpeed(int spd){ speed = spd; }
	void SetFrequenct(int fre){ frequency = fre; tick = 0; }
	int getLine(){ return length; }
	COLORREF getColor(){ return color; }
};

class pButtonA : public pButton{
private:
	TCHAR	name[200];
	line*	nowline;
public:
	pButtonA();
	~pButtonA();
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void SetName(LPWSTR str){ lstrcpy(name, str); }
	void SetLine(line *l){ nowline = l; }
	virtual void OnDraw(HDC hDC);
};

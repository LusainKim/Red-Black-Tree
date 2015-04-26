
#include "Lusdefine.h"
#include "Button.h"
#include "Page.h"

#include <Windows.h>
#include <iostream>
#include <chrono>

using namespace std;

//式式式式式式式式式式式式式式式式式式式式式式式式
//				Font Define
//式式式式式式式式式式式式式式式式式式式式式式式式

#define FontSet_Arial 0,0,0,700,FALSE,FALSE,0,\
			DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,\
			DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, L"Arial "

#define FontSet_Arial_B 0,0,0,1000,FALSE,FALSE,0,\
			DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,\
			DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, L"Arial "

#define FontSet_Arial_L 0,0,0,1000,FALSE,FALSE,0,\
			DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,\
			DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, L"Arial "

//=============================

//////////////////////////////////////////////////////////
//							pButton

pButton::pButton()
{
	m_colorButton = RGB(155, 155, 155);
	m_bInitialize = false;
	m_bPush = false;
}

pButton::~pButton()
{
}

void pButton::Initialize(CGameFramework *parent, HWND hWnd, POINT startPos, bool View, RECT rc, bool bUseButton, RECT rcButton)
{
	Page::Initialize(parent, hWnd, startPos, View, rc, bUseButton, rcButton);
}

bool pButton::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	case WM_KEYUP:
		break;
	case WM_CHAR:
		break;
	default:
		return false;

	}
	return(true);
}

bool pButton::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	POINT mp = MousePoint(lParam);
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:

		if (PtInRect(&m_rcButton, mp))
			m_bPush = m_bStay = true;
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		if (m_bPush && PtInRect(&m_rcButton, mp))
			m_bStay = true;
		else m_bStay = false;
		break;

	case WM_LBUTTONUP:
		if (m_bStay && m_bPush)
			;	//	func
		m_bStay = false;
		m_bPush = false;
		break;

	default:
		return false;

	}
	return(true);
}

void pButton::Update(float fTimeElapse)
{

}

void pButton::OnDraw(HDC hDC)
{
	HFONT mainFont = CreateFont(25, FontSet_Arial_B);
	SelectObject(hDC, mainFont);

	DrawLineBox(hDC, m_rcButton, (!m_bStay) ? m_colorButton : RGB(55, 55, 55), RGB(255, 255, 255), 2, DL_FRAME);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, TEXT("Button"), -1, &m_rcButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	DeleteObject(mainFont);
}

//////////////////////////////////////////////////////////
//							pBCreate

pButtonA::pButtonA()
{
}

pButtonA::~pButtonA()
{
}

bool pButtonA::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	POINT mp = MousePoint(lParam);
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:

		if (PtInRect(&m_rcButton, mp))
			m_bPush = m_bStay = true;
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		if (m_bPush && PtInRect(&m_rcButton, mp))
			m_bStay = true;
		else m_bStay = false;
		break;

	case WM_LBUTTONUP:
		if (m_bPush && PtInRect(&m_rcButton, mp))
		{
			int adl = max(nowline->getLine() - rand() % 200 - 50, 0);
			nowline->AdjustLength( - adl);
			nowline->SetFrequenct(rand() % 10);
			nowline->SetSpeed(rand() % 15 + 5);
		}
		m_bStay = false;
		m_bPush = false;
		break;

	default:
		return false;

	}
	return(true);
}

void pButtonA::OnDraw(HDC hDC)
{
	HFONT mainFont = CreateFont(25, FontSet_Arial_B);
	SelectObject(hDC, mainFont);
	SetBkMode(hDC, TRANSPARENT);
	DrawLineBox(hDC, m_rcButton, (!m_bStay) ? m_colorButton : RGB(55, 55, 55), RGB(255, 255, 255), 2, DL_FRAME);
	SetTextColor(hDC, RGB(255, 255, 255));
	DrawText(hDC, name, -1, &m_rcButton, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	DeleteObject(mainFont);
}

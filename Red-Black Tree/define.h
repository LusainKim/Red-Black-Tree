#include<Windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#include"Lusdefine.h"
#include"rbTree.h"
#include"resource.h"

#pragma region global const

#define input_val_max	4 +1	// end null pointer

extern POINT default_winMain;

extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern LRESULT CALLBACK TreeProc(HWND, UINT, WPARAM, LPARAM);

#pragma endregion


#pragma region winproc

#define SWC_default_style	CS_HREDRAW | CS_VREDRAW
#define SWC_default_Icon		IDI_APPLICATION
#define P_default	{-1,-1}
#define I_default -1

class statusClass{
private:
	HINSTANCE
		g_hInst;
	HWND
		//	hWnd : 자신의 핸들 pWnd : 부모의 핸들
		hWnd, pWnd;
	POINT
		winSize;
	WNDCLASSEX
		wc;
	TCHAR
		szClassName[256],
		szTitle[256];
	WNDPROC
		Proc;
	FLAG 
		IsWCInit,
		IsCreate;
	

public:
	statusClass(LPCWSTR ClassName, LPCWSTR Title);
	statusClass(LPCWSTR ClassName, LPCWSTR Title,
		int x, int y, WNDPROC WndProc);

	void SetWindowClass(
		WNDPROC WndProc,
		HINSTANCE hInst,
		UINT style = CS_HREDRAW | CS_VREDRAW,
		LPCWSTR Icon = IDI_APPLICATION);

	POINT size(){ return winSize; }
	HINSTANCE Instance(){ return g_hInst; }
	HWND hwnd(){ return hWnd; }
	//SetType : I_default || wndPos, wndSize : P_default
	void CreateWnd(DWORD SetType, POINT wndPos, POINT wndSize,
		bool IsCaption, HWND pwnd = NULL);
};

extern statusClass wm, pc;
#pragma endregion

#pragma region rbTree

#define baseInt 60
#define heightInt 40
#define boxLen	15

void DrawTree(HDC hdc, POINT rootPos, POINT rembPos, int cntHeight,
	Node* pHeight, int size, POINT prevPos = { 0, 0 });

void InsertNode(HWND hWnd, LPWSTR msg_for_node, rbTree *tree, POINT *rembPos);
void deleteNode(HWND hWnd, LPWSTR msg_for_node, rbTree *tree, POINT *rembPos);

int insertSample(int cnt_Insert, rbTree *tree, POINT *rembPos);
#pragma endregion
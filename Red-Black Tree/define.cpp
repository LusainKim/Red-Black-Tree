#include"define.h"

POINT default_winMain = { 1200, 800 };

statusClass
	wm(L"winMain", L"Red-Black Tree"),
	pc(L"TreeView", NULL);


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK TreeProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




int pow(int under, int upper)
{
	int p = 1;
	while (upper > 1)
	{
		p = p * under;
		upper--;
	}
	return p;
}
void DrawTree(HDC hdc, POINT rootPos, POINT rembPos, int cntHeight,
	Node* pHeight, int size, POINT prevPos)
{
	TCHAR
		msg[20];

	POINT
		nodePos,
		nowPos;
	RECT
		nodeBox = { -boxLen, -boxLen, boxLen, boxLen },
		tmp;
	bool
		Isroot = false;
	int
		n_x = 0,
		linelen = baseInt * size / 2;
	if (pHeight->prev != nullptr)
	{
		nodePos = prevPos;
		nodePos = P_plus(nodePos, rembPos);
		MoveToEx(hdc, nodePos.x, nodePos.y, NULL);
	}

	if (pHeight->prev == nullptr)
		nodePos = { 0, rootPos.y + heightInt * cntHeight };
	else if (pHeight->prev->key > pHeight->key)
		nodePos = { prevPos.x - linelen / pow(2, cntHeight + 1),
		rootPos.y + heightInt * cntHeight };
	else
		nodePos = { prevPos.x + linelen / pow(2, cntHeight + 1),
		rootPos.y + heightInt * cntHeight };
		
	nowPos = nodePos;
	nodePos = P_plus(nodePos, rembPos);
	tmp = R_P_plus(nodeBox, nodePos);

	if (pHeight->prev != nullptr)
	{
		LineTo(hdc, nodePos.x, nodePos.y);
	}

	if (pHeight->prev == nullptr)
		FillRect(hdc, &tmp, (HBRUSH)GetStockObject(GRAY_BRUSH));
	else if (pHeight->color == black)
		FillRect(hdc, &tmp, (HBRUSH)GetStockObject(BLACK_BRUSH));
	else
	{
		SetDCBrushColor(hdc, RGB(255, 0, 0));
		FillRect(hdc, &tmp, (HBRUSH)GetStockObject(DC_BRUSH));
	}
	wsprintf(msg, L"%d", pHeight->key);
	DrawText(hdc, msg, -1, &tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//	선 때문에 가려지는 노드 새로 그려주기.
	if (pHeight->prev != nullptr)
	{
		nodePos = prevPos;
		nodePos = P_plus(nodePos, rembPos);
		tmp = R_P_plus(nodeBox, nodePos);

		if (pHeight->prev->prev == nullptr)
			FillRect(hdc, &tmp, (HBRUSH)GetStockObject(GRAY_BRUSH));
		else if (pHeight->prev->color == black)
			FillRect(hdc, &tmp, (HBRUSH)GetStockObject(BLACK_BRUSH));
		else
		{
			SetDCBrushColor(hdc, RGB(255, 0, 0));
			FillRect(hdc, &tmp, (HBRUSH)GetStockObject(DC_BRUSH));
		}
		wsprintf(msg, L"%d", pHeight->prev->key);
		DrawText(hdc, msg, -1, &tmp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
	if (pHeight->left != nullptr)
		DrawTree(hdc, rootPos, rembPos, cntHeight + 1, pHeight->left, size, nowPos);
	if (pHeight->right != nullptr)
		DrawTree(hdc, rootPos, rembPos, cntHeight + 1, pHeight->right, size, nowPos);


}

void InsertNode(HWND hWnd, LPWSTR msg_for_node, rbTree *tree, POINT *rembPos)
{
	int istnode;

	if (lstrlen(msg_for_node) < 1)
		return;
	
	istnode = _wtoi(msg_for_node);
	Node nNode;
	nNode.key = istnode;
	lstrcpy(msg_for_node, L"");
	if (!tree->search(istnode))
		tree->insert(nNode);
	if (tree->size() == 1)
		*rembPos = { default_winMain.x / 2, rembPos->y };
	//	ErrorMsgBox(msg_for_node);
	InvalidateRect(hWnd, NULL, false);
}

void deleteNode(HWND hWnd, LPWSTR msg_for_node, rbTree *tree, POINT *rembPos)
{
	int delnode;

	if (lstrlen(msg_for_node) < 1)
		return;

	delnode = _wtoi(msg_for_node);
	lstrcpy(msg_for_node, L"");
	tree->deleting(delnode);
	if (tree->size() == 1)
		*rembPos = { default_winMain.x / 2, rembPos->y };
	//	ErrorMsgBox(msg_for_node);
	InvalidateRect(hWnd, NULL, false);
}

int insertSample(int cnt_Insert, rbTree *tree, POINT *rembPos)
{
	Node nNode;
	bool IsInsert = false;
	switch (cnt_Insert)
	{
	case 0:
		nNode.key = 30;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 1:
		nNode.key = 20;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 2:
		nNode.key = 25;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 3:
		nNode.key = 40;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 4:
		nNode.key = 10;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 5:
		nNode.key = 35;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 6:
		nNode.key = 7;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 7:
		nNode.key = 5;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 8:
		nNode.key = 9;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 9:
		nNode.key = 33;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 10:
		nNode.key = 36;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 11:
		nNode.key = 52;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 12:
		nNode.key = 18;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 13:
		nNode.key = 76;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 14:
		nNode.key = 15;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 15:
		nNode.key = 16;
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	case 16:
		nNode.key = 17;
		if (!tree->search(nNode.key))
			IsInsert = true;
	default:
		nNode.key = (cnt_Insert * 617 % 1001);
		if (!tree->search(nNode.key))
			IsInsert = true;
		break;
	}


	if (IsInsert)
	{
		tree->insert(nNode);
		if (tree->size() == 1)
			*rembPos = { default_winMain.x / 2, 50 };
	}
	return cnt_Insert+1;
}
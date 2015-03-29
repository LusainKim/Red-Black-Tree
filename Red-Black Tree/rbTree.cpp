#include"define.h"
/*
	- root is black
	- all leafnode who include nullptr color is black
	- all red node's children are bleck
	- search where rootnode to leafnode, count black number, it is all same
*/
rbTree::rbTree()
{
	_root = nullptr;
	_size = 0;
}

bool rbTree::insert(Node node)
{
	auto Newnode = new Node;
	Node
		*pp = nullptr,	//	2 level upnode
		*p = nullptr,	// 1 level upnode
		*s = nullptr;	//	pp's another node
	nextnode
		preway,	//	p ↔ pp
		way;		//	p ↔ Newnode

	memcpy(Newnode, &node, sizeof(Node));

	Newnode->right = nullptr;
	Newnode->left = nullptr;
	Newnode->prev = nullptr;
	Newnode->color = red;
	_size++;

	if (_root == nullptr)
	{
		_root = Newnode;
		_root->color = black;
		return true;
	}

	p = _root;
	
	while (p != nullptr)
	{
		if (p->key < Newnode->key)
		{
			if (p->right != nullptr)
				p = p->right;
			else
			{
				way = right;
				break; 
			}
		}
		else if(p->key > Newnode->key)
		{
			if (p->left != nullptr)
				p = p->left;
			else
			{
				way = left;
				break;
			}
		}
		else if (p->key == Newnode->key)
		{
			delete Newnode;
			return false;
		}
	}
	//	Red-Black fix	//

	//	p를 정한다.
	Newnode->prev = p;


	//	newNode를 p와 연결한다.
	if (way == right)
		p->right = Newnode;
	else
		p->left = Newnode;

	
	if (p->color == black)	//	p가 black이면 생략
		return true;

	else	while(1)	// p가 red이면 난관이 시작된다.
	{
		if (p->color == black)	//	p가 black이면 생략
			return true;
		
		//	pp를 정한다.
		pp = p->prev;


		//	pp와 p와의 관계 확인
 		if (pp->right == p)
			preway = right;
		else
			preway = left;

		// s 정의
		if (preway == left)
			s = pp->right;
		else
			s = pp->left;

		//	s가 red라면 이야기는 빠르다.
		if (s != nullptr && s->color == red)
		{
			p->color = black;
			s->color = black;
			pp->color = red;

			if (pp->prev != nullptr)
			{
				if (pp->prev->color == red)
				{
					p = pp->prev; 
					if (p->right == pp)
						way = right;
					else
						way = left;
					continue;
				}
				else
					return true;
			}
			else
			{
				pp->color = black;
				_root = pp;
				return true;
			}
		}
		//	preway가 왼쪽 : 일반적으로 배운 방법
		if (preway == left)
		{
			
			if (s == nullptr || s->color == black)
			{

				if (way == right)
				{
					rotate(p, left);
					if (p->prev != pp)
						p = p->prev;
				}
				rotate(pp, right);
				rbColor	ctmp = p->color;
				p->color = pp->color;
				pp->color = ctmp;
				return true;

			}

		}
		else	//	preway가 오른쪽
		{

			if (s == nullptr || s->color == black)
			{

				if (way == left)
				{
					rotate(p, right);
					if (p->prev != pp)
						p = p->prev;
				}
				rotate(pp, left);
				rbColor	ctmp = p->color;
				p->color = pp->color;
				pp->color = ctmp;
				return true;

			}
		}
		
	}

	return true;
}

void rbTree::rotate(Node *x, nextnode direction)
{
	Node *y;

	if (direction == left)
	{
		y = x->right;
		x->right = y->left;
		if (y->left != nullptr)
			y->left->prev = x;
	}
	else
	{
		y = x->left;
		x->left = y->right;
		if (y->right != nullptr)
			y->right->prev = x;
	}

	y->prev = x->prev;

	if (x->prev == nullptr)
		_root = y;
	else if (x == x->prev->right)
	{
		x->prev->right = y;
	}
	else
	{
		x->prev->left = y;
	}

	if (direction == left)
		y->left = x;
	else
		y->right = x;

	x->prev = y;

	if (y->prev == nullptr)
		_root = y;
}

bool rbTree::search(int key)
{
	Node *
		p = _root;

	while (p != nullptr)
	{
		if (p->key < key)
		{
			if (p != nullptr)
				p = p->right;
		}
		else if (p->key > key)
		{
			if (p != nullptr)
				p = p->left;
		}
		else if (p->key == key)
			return true;
	}

	return false;
}

Node* rbTree::_search(int key)
{
	Node 
		*p = _root;

	while (p != nullptr)
	{
		if (p->key < key)
		{
			if (p != nullptr)
				p = p->right;
		}
		else if (p->key > key)
		{
			if (p != nullptr)
				p = p->left;
		}
		else if (p->key == key)
			return p;
	}

	return nullptr;
}

bool rbTree::delete_fix_color(Node *x, Node *p)
{
	Node
		*s, *l, *r;
	rbColor
		tmp_for_color;
	nextnode
		p_s;
//	return false;
	if (p == nullptr)
		return true;
	if (x == nullptr && p == nullptr)
		return false;
	if (x != nullptr &&x->color == red)
	{
		x->color = black;
		return true;
	}
	//	init.

	if (p->right == x)
	{
		s = p->left;
		p_s = right;
	}
	else
	{
		s = p->right;
		p_s = left;
	}

	if (s != nullptr)
	{
		l = s->left;
		r = s->right;
	}
	else
	{
		l = nullptr;
		r = nullptr;
	}

	if (CheckRed(p) && CheckBlack(s) && CheckBlack(r) && CheckBlack(l))
	{
		tmp_for_color = p->color;
		p->color = s->color;
		s->color = tmp_for_color;
		return true;
	}

	if (p_s == left &&CheckRed(r) && s->color == black)
	{

		rotate(p, left);

		tmp_for_color = p->color;
		p->color = s->color;
		s->color = tmp_for_color;

		r->color = black;
 		return true;
	}

	if (p_s == right &&CheckRed(l) && s->color == black)
	{
		rotate(p, right);

		tmp_for_color = p->color;
		p->color = s->color;
		s->color = tmp_for_color;

		l->color = black;
		return true;
	}

	if (p_s == left &&CheckBlack(r) && CheckRed(l) && s->color == black)
	{
		rotate(s, right);
		tmp_for_color = l->color;
		l->color = s->color;
		s->color = tmp_for_color;


		return delete_fix_color(x, p);
	}

	if (p_s == right &&CheckBlack(l) && CheckRed(r) && s->color == black)
	{
		rotate(s, left);
		tmp_for_color = r->color;
		r->color = s->color;
		s->color = tmp_for_color;

		return delete_fix_color(x, p);
	}


	if (s != nullptr && CheckBlack(l) && CheckBlack(r) && CheckBlack(s) && CheckBlack(p))
	{
		s->color = red;
		return delete_fix_color(p,p->prev);
	}
	
	if (CheckBlack(l) && CheckBlack(r) && CheckRed(s) && CheckBlack(p))
	{
		if (p_s == left)
			rotate(p, left);
		else
			rotate(p, right);
		tmp_for_color = p->color;
		p->color = s->color;
		s->color = tmp_for_color;

		return delete_fix_color(x,p);
	}

	return false;
}

bool rbTree::deleting(int key)
{
	Node 
		*p = _search(key),
		*pp,
		*x,
		*n;
	nextnode
		p_pp;
	rbColor
		color_to_p;
	if (p == nullptr)
		return false;

	if (p == _root && p->right == nullptr && p->left == nullptr)
	{
		delete p;
		_root = nullptr;
		_size--;
		return true;
	}

	if (p != _root && p->prev->left == p)
		p_pp = left;
	else
		p_pp = right;

	//	p is leaf
	if (p->right == nullptr && p->left == nullptr)
	{
		color_to_p = p->color;
		pp = p->prev;
		if (p_pp == right)
			p->prev->right = nullptr;
		else
			p->prev->left = nullptr;
		delete p;
		_size--;
		if (color_to_p == black)
			delete_fix_color(nullptr, pp);
		return true;
	}
	else if (p->left == nullptr)
	{
		if (p == _root)
		{
			p->right->prev = nullptr;
			_root = p->right;
			_root->color = black;
			delete p;
			_size--;
			return true;

		}
		else
		{
			pp = p->prev;
			n = p->right;
			color_to_p = p->color;
			n->prev = pp;
			n->right = p->right;
			n->left = p->left;
			memcpy(p, n, sizeof(Node));
			delete n;
			p->right = nullptr;
			_size--;
			p->color = color_to_p;
			if (color_to_p == black)
				delete_fix_color(nullptr, p);
			return true;
		}
	}
	else if (p->right == nullptr)
	{

		if (p == _root)
		{
			p->left->prev = nullptr;
			_root = p->left;
			_root->color = black;
			delete p;
			_size--;
			return true;

		}
		else
		{
			pp = p->prev;
			n = p->left;
			color_to_p = p->color;
			n->prev = pp;
			n->right = p->right;
			n->left = p->left;
			memcpy(p, n, sizeof(Node));
			delete n;
			p->left = nullptr;
			_size--;
			p->color = color_to_p;
			if (color_to_p == black)
				delete_fix_color(nullptr, p);
			return true;
		}
	}
	else	// p is get children
	{
		x = p->right;
		if (x != nullptr)
		{
			pp = nullptr;
			while (x->left != nullptr)
				x = x->left;

			if (x != p->right)
			{
				if (x->right == nullptr)
					x->prev->left = nullptr;
				else
				{
					x->prev->left = x->right;
					x->right->prev = x->prev;

				}

			}
			else
			{
				if (x->right == nullptr)
					x->prev->right = nullptr;
				else
				{
					x->prev->right = x->right;
					x->right->prev = x->prev;
				}
			}

		}
		pp = x->right;
		n = x->prev;
		rbColor tmp_for_color = p->color;
		color_to_p = x->color;
		x->right = p->right;
		x->left = p->left;
		x->prev = p->prev;
		memcpy(p, x, sizeof(Node));
		p->color = tmp_for_color;

		delete x;
		_size--;

		if (color_to_p == black)
			delete_fix_color(pp,n);

		return true;
	}

}

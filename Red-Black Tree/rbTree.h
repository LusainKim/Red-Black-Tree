
// RedBlack Tree

#define CheckBlack(p) (p == nullptr || p->color == black)
#define CheckRed(p) (p != nullptr && p->color == red)

enum rbColor{
	red,
	black
};
enum nextnode{
	right,
	left
};

typedef struct RBNode{
	int 
		key;

	rbColor 
		color;

	RBNode
		*left,
		*right,
		*prev;

}Node;

class rbTree{
private:
	Node
		*_root,
		*_search(int key);
	int
		_size;
	bool
		delete_fix_color(Node *x, Node* p);
public:
	rbTree();
	Node* root(){ return _root; }
	int size(){ return _size; }
	bool insert(Node node);
	void rotate(Node *rot, nextnode direction);
	bool search(int key);
	bool deleting(int key);
};
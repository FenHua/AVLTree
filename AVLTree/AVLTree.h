#include"iostream"
template<class T, class V>struct AVLTreeNode
{
	T _key;
	V _value;
	AVLTreeNode<T, V>*_left;
	AVLTreeNode<T, V>*_right;
	AVLTreeNode<T, V>*_parent;
	int _bf;//平衡因子
	AVLTreeNode(const T&key, const V&value) :_key(key), _value(value), _left(NULL), _right(NULL), _parent(NULL), _bf(0)
	{}
};

template<class T, class V>class AVLTree
{
	typedef AVLTreeNode<T, V> Node;
protected:
	Node*_root;
public:
	AVLTree() :_root(NULL)
	{}
	~AVLTree()
	{
		_Destroy(_root);
	}
	bool Insert(const T&key, const V&value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node*cur = _root;
		Node*parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				//存在相同节点
				return false;
		}
		cur = new Node(key, value);
		cur->_parent = parent;
		if (parent->_key < key)
			parent->_right = cur;
		else
			parent->_left = cur;
		while (parent)
		{
			if (parent->_left == cur)
				--parent->_bf;
			else if (parent->_right==cur)
				++parent->_bf;
			if (parent->_bf == 0)
				return true;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//继续向上调整
				cur = parent;
				parent = parent->_parent;
			}
			else
			{
				// 2 -2 旋转
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
						//左单旋
						_RotateL(parent);
					else if (cur->_bf == -1)
						//右左双旋
						_RotateRL(parent);
				}
				else
				{
					//-2
					if (cur->_bf == 1)
						//左右双旋
						_RotateLR(parent);
					else if (cur->_bf == -1)
						//右单旋
						_RotateR(parent );
				}
			}
		}
		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	bool IsBalanceOP()
	{
		int height = 0;
		return _IsBalanceOP(_root, height);
	}
protected:
	bool _IsBalanceOP(Node*root, int &height)
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}
		int left = 0;
		_IsBalanceOP(root->_left, height);
		int right = 0;
		_IsBalanceOP(root->_right, height);
		int bf = right - left;
		if (abs(bf)<2)
		{
			//平衡因子
			height = 1 + left>right ? left : right;
			return true;
		}
		return false;
	}
	void _InOrder(Node*root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	bool _IsBalance(Node*root)
	{
		if (root == NULL)
			return true;
		int left = _HeightTree(root->_left);
		int right = _HeightTree(root->_right);
		int bf = right - left;
		if (root->_bf != bf)
		{
			cout << "Is Unbalance:" << root->_key << endl;
			return false;
		}
		return abs(bf) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}
	int _HeightTree(Node*root)
	{
		if (root == NULL)
			return 0;
		int leftsize = 1 + _HeightTree(root->_left);
		int rightsize = 1 + _HeightTree(root->_right);
		return leftsize>rightsize ? leftsize : rightsize;
	}
	void _RotateL(Node*parent)
	{
		Node*subR = parent->_right;
		Node*subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		subR->_left = parent;
		Node*tmp = parent->_parent;
		parent->_parent = subR;
		if (tmp == NULL)
		{
			//parent是根节点
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			//parent不是根节点
			if (tmp->_left == parent)
				tmp->_left = subR;
			else
				tmp->_right = subR;
			subR->_parent = tmp;
		}
		subR->_bf = parent->_bf = 0;//平衡因子更新
	}
	void _RotateR(Node*parent)
	{
		Node*subL = parent->_left;
		Node*subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node*tmp = parent->_parent;
		parent->_parent = subL;
		if (tmp == NULL)
		{
			//parent 是根节点
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			//parent不是根节点
			if (tmp->_left == parent)
				tmp->_left = subL;
			else
				tmp->_right = subL;
			subL->_parent = tmp;
		}
		subL->_bf = parent->_bf = 0;//更新平衡因子
	}
	void _RotateLR(Node*parent)
	{
		Node*subL = parent->_left;
		Node*subLR = subL->_right;
		int bf = subLR->_bf;
		_RotateL(parent->_left);
		_RotateR(parent);
		if (bf == 0)
			subLR->_bf = subL->_bf = parent->_bf = 0;
		else if (bf == 1)
		{
			subL->_bf = -1;
			subLR->_bf = 1;
			parent->_bf = 0;
		}
		else
		{
			//-1
			subL->_bf = 0;
			subLR->_bf = -1;
			parent->_bf = 1;
		}
	}
	void _RotateRL(Node*parent)
	{
		Node*subR = parent->_right;
		Node*subRL = subR->_left;
		int bf = subRL->_bf;
		_RotateR(parent->_right);
		_RotateL(parent);
		if (bf == 0)
			parent->_bf = subR->_bf = subRL->_bf = 0;
		else if (bf == 1)
		{
			subR->_bf = 0;
			subRL->_bf = 1;
			parent->_bf = -1;
		}
		else
		{
			subR->_bf = 1;
			subRL->_bf = -1;
			parent->_bf = 0;
		}
	}
	void _Destroy(Node*&root)
	{
		if (root == NULL)
			return;
		Node*cur = root;
		if (cur)
		{
			_Destroy(root->_left);
			_Destroy(root->_right);
			delete cur;
			cur = NULL;
		}
	}
};
#pragma once

namespace RB {

enum color { black = 0, red };

template <
	class T
>
class rb_tree {
public:

	rb_tree() {}

	void insert(T x) {
		if (root_ == nullptr) {
			root_ = new Node{ black, x, nullptr, nullptr, nullptr };
			return;
		}
		root_ = insert(root_, x);
	}

private:
	struct Node {
		color col;
		T value;
		Node *l, *r, *p;
	};

	int size_ = 0;
	Node* root_ = nullptr;

	Node* rotateL(Node* node) {
		Node* x = node->r;
		Node* y = x->l;
		x->l = node;
		node->r = y;
		node->p = x;
		if (y != nullptr) {
			y->p = node;
		}
		return x;
	}
	Node* rotateR(Node* node) {
		Node* x = node->l;
		Node* y = x->r;
		x->r = node;
		node->l = y;
		node->p = x;
		if (y != nullptr) {
			y->p = node;
		}
		return x;
	}

	Node* insert(Node* node, T x) {
		if (node == nullptr)
	}
};

}

#pragma once

namespace RB {

enum color_t { black = 0, red };
enum rotation_t { left = 0, right, left_right, right_left };

template <
	class T
>
class rb_tree {
public:

	rb_tree() {}

	void insert(T x) {
		if (root_ == nullptr) return void(root_ = new Node{ black, x });
		insert_(x);
	}

private:
	struct Node {
		bool col;
		T value;
		Node *l = nullptr, *r = nullptr, *p = nullptr;

		void flip() {
			col ^= 1;
		}
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

	Node* insert_(Node* node, T x) {
		if (node == nullptr) {
			return new Node{ red, x };
		}
		else if (x < node->value) {
			return insert_(node->l, x);
		}
		else {
			return insert_(node->r, x);
		}
	}
	void insert_(T x) {
		Node* K = insert_(root_, x);
		Node* P = K->p;
		Node* S = (K == S->l ? S->r : S->l);

		if (P->col == black) return;
		
		Node* G = P->p;
		Node* U = (P == G->l ? G->r : G->l);

		if (U && P->col == red && U->col == red) {
			P->flip();
			if (G != root_) G->flip();
			U->flip();
			return;
		}

		if (P == G->r && K == P->r) {
			P->flip();
			G->flip();
			G = rotateL(G);
		}
		else if (P == G->l && K == P->l) {
			P->flip();
			G->flip();
			G = rotateR(G);
		}
		else if (P == G->r && K == P->l) {
			P = rotateR(P);
			K = P->r;
			S = P->l;

			P->flip();
			G->flip();
			G = rotateL(G);
		}
		else {
			P = rotateL(P);
			K = P->l;
			S = P->r;

			P->flip();
			G->flip();
			G = rotateR(G);
		}
	}
};

}

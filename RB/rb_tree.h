#pragma once
#include <ostream>
#include <cassert>
#include <cmath>

namespace RB {

enum color_t { black = 0, red };
enum rotation_t { left = 0, right, left_right, right_left };

template <
	class T
>
class rb_tree {
public:

	rb_tree() {}

	template <class U>
	friend std::ostream & operator << (std::ostream &, const rb_tree<U> &);

	void insert(T x) {
		if (root_ == nullptr) return void(root_ = new Node{ black, x });
		insert_(x);
		++size_;
	}
	void check_validity() {
		int cnst = 2 * log2(size_ + 1) + 5;
		assert(get_height(root_) <= cnst);
		int z = -1; check_black_nodes(root_, z, 1);
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

private:
	void rotateL(Node* x) {
		Node* y = x->r;
		x->r = y->l;
		if (y->l != nullptr) x->r->p = x;
		y->p = x;
		if (x->p == nullptr) root_ = y;
		else if (x == x->p->l) x->p->l = y;
		else x->p->r = y;
		y->l = x;
		x->p = y;
	}
	void rotateR(Node* x) {
		Node* y = x->l;
		x->l = y->r;
		if (y->r != nullptr) x->r->p = x;
		y->p = x;
		if (x->p == nullptr) root_ = y;
		else if (x == x->p->l) x->p->l = y;
		else x->p->r = y;
		y->r = x;
		x->p = y;
	}

	Node* insert_(Node*& node, T x) {
		if (node == nullptr) {
			return (node = new Node{ red, x });
		}
		else if (x < node->value) {
			Node* result = insert_(node->l, x);
			node->l->p = node;
			return result;
		}
		else {
			Node* result = insert_(node->r, x);
			node->r->p = node;
			return result;
		}
	}
	void insert_(T x) {
		Node* K = insert_(root_, x);
		assert(K->p != nullptr); // REMOVE ASSERTS
		Node* P = K->p;

		if (P->col == black) return;

		assert(P->p != nullptr); // REMOVE ASSERTS
		
		Node* G = P->p;
		Node* U = (P == G->l ? G->r : G->l);

		if (U != nullptr && P->col == red && U->col == red) {
			P->flip();
			U->flip();
			if (G != root_) G->flip();
			return;
		}

		if (P == G->r && K == P->r) {
			P->flip();
			G->flip();
			rotateL(G);
		}
		else if (P == G->l && K == P->l) {
			P->flip();
			G->flip();
			rotateR(G);
		}
		else if (P == G->r && K == P->l) {
			rotateR(P);
			K->flip();
			G->flip();
			rotateL(G);
		}
		else {
			rotateL(P);
			K->flip();
			G->flip();
			rotateR(G);
		}
	}

private:
	void dump(Node* node, std::ostream& out) const {
		if (node == nullptr) return;
		dump(node->l, out);
		out << node->value << " ";
		dump(node->r, out);
	}

private:
	int get_height(Node* x) {
		if (x == nullptr) return 0;
		return 1 + std::max(get_height(x->l), get_height(x->r));
	}
	void check_black_nodes(Node *x, int &rf, int cnt) {
		if (!x) return;
		if (x->l == nullptr && x->r == nullptr) {
			if (rf == -1) rf = cnt;
			else assert(cnt == rf);
		}
		if (x->l) {
			check_black_nodes(x->l, rf, cnt + (x->l->col == black));
		}
		if (x->r) {
			check_black_nodes(x->r, rf, cnt + (x->r->col == black));
		}
	}
};

template <class T>
std::ostream & operator << (std::ostream& out, const rb_tree<T>& t) {
	t.dump(t.root_, out);
	return out;
}

}

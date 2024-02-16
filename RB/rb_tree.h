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
		++size_;
		if (root_ == nullptr) return void(root_ = new Node{ black, x });
		insert_(x);
	}
	void erase(T x);
	bool search(T x);
	T lower_bound(T x);
	T min();
	T max();

	void check_validity() {
		int cnst = 2 * log2(size_ + 1) + 5;
		assert(get_height(root_) <= cnst);
		int z = -1; check_black_nodes(root_, z, 1);
	}

private:
	struct Node {
		bool col;
		T value;
		Node* l = nullptr;
		Node* r = nullptr;
		Node* p = nullptr;
		void flip() { col ^= 1; }
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

private:
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
	Node* find_node_(T x) {
		Node* node = root_;
		while (node != nullptr) {
			if (node->value == x) return node;
			else if (node->value > x) node = node->l;
			else node = node->r;
		}
		return nullptr;
	}

	void change_(Node* v, Node* u) {
		if (u->p == nullptr) root_ = v;
		else if (u == u->p->l) u->p->l = v;
		else u->p->r = v;
		v->p = u->p;
	}

	void fix_erase_(Node* x) {
		Node* s;
		while (x != root_ && x->col == black) {
			if (x == x->p->l) {
				s = x->p->r;
				if (x->col == red) {
					s->col = black;
					x->p->col = red;
					rotateL(x->p);
					s = x->p->r;
				}

				if (s->l->col == black && s->r->col == black) {
					s->col = red;
					x = x->p;
				}
				else {
					if (s->r->col == black) {
						s->l->col = black;
						s->col = red;
						rotateR(s);
						s = x->p->r;
					}

					s->col = x->p->col;
					x->p->col = black;
					s->r->col = black;
					rotateL(x->p);
					x = root_;
				}
			}
			else {
				s = x->p->l;
				if (x->col == red) {
					s->col = black;
					x->p->col = red;
					rotateR(x->p);
					s = x->p->l;
				}

				if (s->l->col == black && s->r->col == black) {
					s->col = red;
					x = x->p;
				}
				else {
					if (s->l->col == black) {
						s->r->col = black;
						s->col = red;
						rotateL(s);
						s = x->p->l;
					}

					s->col = x->p->col;
					x->p->col = black;
					s->l->col = black;
					rotateR(x->p);
					x = root_;
				}
			}
		}
		x->col = black;
	}

	void erase_(T value) {
		Node *z = find_node(value), *x, *y;
		if (z == nullptr) return;

		y = z;
		bool col_y = y->col;

		if (z->l == nullptr) {
			x = z->r;
			change_(z, z->r);
		}
		else if (z->r == nullptr) {
			x = z->l;
			change_(z, z->l);
		}
		else {
			y = min_node(z->r);
			col_y = y->col;
			x = y->r;
			if (y->p == z) x->p = y;
			else {
				change_(y, y->r);
				y->r= z->r;
				y->r->p = y;
			}
			change_(z, y);
			y->l = z->l;
			y->l->p = y;
			y->col = z->col;
		}
		delete z;
		if (col_y == black) fix_erase_(x);
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

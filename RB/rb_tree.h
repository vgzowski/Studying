#pragma once
#include <ostream>
#include <cassert>
#include <cmath>

namespace RB {

enum color_t { black = 0, red };

template <
	class T
>
class rb_tree {
public:

	rb_tree() : root_(null_v) {}

	template <class U>
	friend std::ostream & operator << (std::ostream &, const rb_tree<U> &);

	void insert(T x) {
		++size_;
		if (root_ == null_v) {
			root_ = new Node{ black, x, null_v, null_v, nullptr };
		}
		else {
			insert_(x);
		}
	}
	void erase(T x) {
		if (erase_(x)) {
			--size_;
		}
	}
	bool search(T x) {
		return find_node_(root_, x) != null_v;
	}

	T min() { return min_node_(root_)->value; }
	T max() { return max_node_(root_)->value; }

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
	Node* null_v = new Node{black, 0, nullptr, nullptr, nullptr};
	Node* root_;

private:
	void rotateL(Node* x) {
		Node* y = x->r;
		x->r = y->l;
		if (y->l != null_v) x->r->p = x;
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
		if (y->r != null_v) x->r->p = x;
		y->p = x;
		if (x->p == nullptr) root_ = y;
		else if (x == x->p->l) x->p->l = y;
		else x->p->r = y;
		y->r = x;
		x->p = y;
	}

private:
	Node* insert_(Node*& node, T x) {
		if (node == null_v) {
			return (node = new Node{ red, x, null_v, null_v, nullptr });
		}
		else if (x < node->value) {
			Node* result = insert_(node->l, x);
			node->l->p = node;
			return result;
		}
		else if (node->value < x) {
			Node* result = insert_(node->r, x);
			node->r->p = node;
			return result;
		}
		else {
			assert(false);
		}
	}
	void insert_(T x) {
		Node* K = insert_(root_, x);
		Node* P = K->p;

		if (P->col == black) return;

		Node* G = P->p;
		Node* U = (P == G->l ? G->r : G->l);

		if (U != null_v && P->col == red && U->col == red) {
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
	Node* find_node_(Node* node, T x) {
		assert(node != nullptr);
		while (node != null_v) {
			if (node->value == x) return node;
			else if (node->value > x) node = node->l;
			else node = node->r;
		}
		return null_v;
	}
	Node* min_node_(Node* x) {
		if (x == null_v) return null_v;
		while (x->l != null_v) x = x->l;
		return x;
	}
	Node* max_node_(Node *x) {
		if (x == null_v) return null_v;
		while (x->r != null_v) x = x->r;
		return x;
	}

	void change_(Node* u, Node* v) {
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
				if (s->col == red) {
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
				if (s->col == red) {
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

	bool erase_(T value) {
		Node *z = find_node_(root_, value), *x, *y;
		if (z == null_v) return false;

		y = z;
		bool col_y = y->col;

		if (z->l == null_v) {
			x = z->r;
			change_(z, z->r);
		}
		else if (z->r == null_v) {
			x = z->l;
			change_(z, z->l);
		}
		else {
			y = min_node_(z->r);
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
		return true;
	}

private:
	void dump(Node* node, std::ostream& out) const {
		if (node == null_v) return;
		dump(node->l, out);
		out << node->value << " ";
		dump(node->r, out);
	}

private:
	int get_height(Node* x) {
		if (x == null_v || x == nullptr) return 0;
		return 1 + std::max(get_height(x->l), get_height(x->r));
	}
	void check_black_nodes(Node *x, int &rf, int cnt) {
		if (x == null_v || x == nullptr) return;
		if (x->l == null_v) {
			if (rf == -1) rf = cnt + 1;
			else assert(cnt + 1 == rf);
		}
		if (x->r == null_v) {
			if (rf == -1) rf = cnt + 1;
			else assert(cnt + 1 == rf);
		}
		if (x->l != null_v) {
			check_black_nodes(x->l, rf, cnt + (x->l->col == black));
		}
		if (x->r != null_v) {
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

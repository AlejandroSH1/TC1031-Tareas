/*
 * 7 Árbol Desplegado Splay Tree
 * Alfredo Alejandro Soto Herrera
 * A01711368
 * 04/11/2024
 */

#ifndef SPLAY_H
#define SPLAY_H

#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
    if (val < value) {
        if (left != nullptr) {
            return left->add(val);
        } else {
            left = new Node<T>(val, nullptr, nullptr, this);
            return left;
        }
    } else {
        if (right != nullptr) {
            return right->add(val);
        } else {
            right = new Node<T>(val, nullptr, nullptr, this);
            return right;
        }
    }
}

template <class T>
Node<T>* Node<T>::find(T val) {
    if (val == value) {
        return this;
    } else if (val < value) {
        return left ? left->find(val) : this;
    } else {
        return right ? right->find(val) : this;
    }
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *succ, *old;
	if (val < value) {
		if (left != 0) {
			if (left -> value == val) {
				old = left;
				succ = left -> succesor();
				if (succ != 0) {
					succ -> left = old -> left;
					succ -> right = old -> right;
					succ -> parent = old -> parent;

					if (succ -> left)
						succ -> left -> parent = succ;
					if (succ -> right)
						succ -> right -> parent = succ;
				}
				left = succ;
				delete old;
				return this;
			} 
			else {
				return left -> remove(val);
			}
		}
		else {
			return this;
		}
	} 
	else {
		if (right != 0) {
			if (right -> value == val) {
				old = right;
				succ = right -> succesor();
				if (succ != 0) {
					succ -> left = old -> left;
					succ -> right = old -> right;
					succ -> parent = old -> parent;

					if (succ -> left)
						succ -> left -> parent = succ;
					if (succ -> right)
						succ -> right -> parent = succ;
				}
				right = succ;

				delete old;
				return this;
			} 
			else {
				return right -> remove(val);
			}
		}
		else {
			return this;
		}
	}
}

template <class T> 
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;
	le = left;
	ri = right;

	if (right == 0 && left == 0){
		return 0;
	}

	if (right == 0) {
		if (left != 0) {
			if (left -> right){
				right = left -> right;
			}
			left = left -> left;
		}
		return le;
	}

	if (right -> left == 0) {
		right = right -> right;
		ri -> right = 0;
		return ri;
	}

	Node<T> *par, *child;
	par = right;
	child = right->left;
	while (child->left != 0) {
		par = child;
		child = child->left;
	}
	par -> left = child -> right;
	child -> right = 0;
	return child;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;

	y->parent = x->parent;
	x->parent = y;

	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x) {
    while (x->parent != nullptr) {
        if (x->parent->value == root->value) {
            if (x->parent->left == x) {
                rot_right(x->parent);
            } else {
                rot_left(x->parent);
            }
        } else {
            Node<T>* p = x->parent;
            Node<T>* g = p->parent;
            if (p->left == x && g->left == p) {
                rot_right(g);
                rot_right(p);
            } else if (p->right == x && g->right == p) {
                rot_left(g);
                rot_left(p);
            } else if (p->left == x && g->right == p) {
                rot_right(p);
                rot_left(g);
            } else {
                rot_left(p);
                rot_right(g);
            }
        }
    }
    return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	std::string inorder() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {

	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T> 
void SplayTree<T>::remove(T val){
	if (root != 0) {
		if (val == root -> value) {
			Node<T> *succ = root -> succesor();
			if (succ != 0) {
					succ -> left = root -> left;
					succ -> right = root -> right;
					succ -> parent = 0;

					if (succ -> left)
						succ -> left -> parent = succ;
					if (succ -> right)
						succ -> right -> parent = succ;
			}
			delete root;
			root = succ;
		} 
		else {
			Node<T>* parent = root -> remove(val);
			root = root -> splay(root, parent);
		}
	}
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif
/*
 * 5 Árbol búsqueda binaria
 * Alfredo Alejandro Soto Herrera
 * A01711368
 * 07/10/2024
 */

#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

using namespace std;

template <class T>
class TreeNode {
private:
    T value;
    TreeNode *left, *right;
public:
    TreeNode(T);
    TreeNode<T>* add(T);

    void inorder(string&) const; 
    void preorder(string&) const; 
    void postorder(string&) const; 
    void levelorder(string&) const;
    void level(string&, int) const; 
    int height() const;
    int whatlevelamI(T) const;
    bool ancestors(T, string&) const;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}

template <class T>
TreeNode<T>* TreeNode<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            return left->add(val);
        } 
        else {
            left = new TreeNode<T>(val);
            return left;
        }
    } 
    else {
        if (right != 0) {
            return right->add(val);
        } 
        else {
            right = new TreeNode<T>(val);
            return right;
        }
    }
}

template <class T>
bool TreeNode<T>::ancestors(T val, string& result) const {
    if (value == val) return true;
    if (val < value) {
        if (left != 0) {
            if (left->ancestors(val, result)) {
                if (result.empty()) {
                    result = to_string(value);
                } 
                else {
                    result = to_string(value) + " " + result;
                }
                return true;
            }
        }
    } 
    else {
        if (right != 0) {
            if (right->ancestors(val, result)) {
                if (result.empty()) {
                    result = to_string(value);
                } 
                else {
                    result = to_string(value) + " " + result;
                }
                return true;
            }
        }
    }
    return false;
}

template <class T>
int TreeNode<T>::height() const {
    int le = 0;
    int ri = 0;
    if (left != 0) {
        le = left->height() + 1;
    }
    if (right != 0) {
        ri = right->height() + 1;
    }
    if (le == 0 && ri == 0) {
        return 1;
    }
    return (le > ri ? le : ri);
}

template <class T>
void TreeNode<T>::inorder(string &s) const {
    if (left != 0) {
        left->inorder(s);
    }
    if (s.size() != 0) {
        s += " ";
    }
    s += to_string(value);
    if (right != 0) {
        right->inorder(s);
    }
}

template <class T>
void TreeNode<T>::preorder(string &s) const {
    if (s.size() != 0) {
        s += " ";
    }
    s += to_string(value);
    if (left != 0) {
        left->preorder(s);
    }
    if (right != 0) {
        right->preorder(s);
    }
}

template <class T>
void TreeNode<T>::postorder(string &s) const {
    if (left != 0) {
        left->postorder(s);
    }
    if (right != 0) {
        right->postorder(s);
    }
    if (s.size() != 0) {
        s += " ";
    }
    s += to_string(value);
}

template <class T>
void TreeNode<T>::levelorder(string& s) const {
    int h = height();
    for (int i = 1; i <= h; i++) {
        level(s, i);
    }
}

template <class T>
void TreeNode<T>::level(string &s, int level) const {
    if (level == 1) {
        if (s.size() != 0) {
            s += " ";
        }
        s += to_string(value);
    } 
    else {
        if (left != 0) {
            left->level(s, level - 1);
        }
        if (right != 0) {
            right->level(s, level - 1);
        }
    }
}

template <class T>
int TreeNode<T>::whatlevelamI(T val) const {
    if (val == value) {
        return 1;
    }
    if (val < value) {
        if (left != 0) {
            return left->whatlevelamI(val) + 1;
        } 
        else {
            return 0;
        }
    } 
    else {
        if (right != 0) {
            return right->whatlevelamI(val) + 1;
        } 
        else {
            return 0;
        }
    }
}

template <class T>
class BST{
private:
    TreeNode<T> *root;
public:
    BST();
    void add(T);
    string visit();
    int height();
    string ancestors(T);
    int whatlevelamI(T);
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
void BST<T>::add(T val) {
    if (root == 0) {
        root = new TreeNode<T>(val);
    } 
    else {
        root->add(val);
    }
}

template <class T>
string BST<T>::visit() {
    string pre_str = "", in_str = "", post_str = "", lev_str = "";
    if (root != 0) {
        root->preorder(pre_str);
        root->inorder(in_str);
        root->postorder(post_str);
        root->levelorder(lev_str);
    }
    string result = "[" + pre_str + "]\n";
    result += "[" + in_str + "]\n";
    result += "[" + post_str + "]\n";
    result += "[" + lev_str + "]";
    return result;
}

template <class T>
int BST<T>::height() {
    if (root != 0) {
        return root->height();
    } 
    else {
        return 0;
    }
}

template <class T>
string BST<T>::ancestors(T val) {
    string result = "";
    if (root != 0) {
        root->ancestors(val, result);
    }
    return "[" + result + "]";
}

template <class T>
int BST<T>::whatlevelamI(T val) {
    if (root != 0) {
        return root->whatlevelamI(val);
    } 
    else {
        return -1;
    }
}
#endif
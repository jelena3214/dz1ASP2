#include <iostream>
#include <string>

using namespace std;

struct TreeNode {
	string key;
	string translation;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
};

struct TreeNode* create_tree_node(string key, string translation) {
	struct TreeNode* newkey = new TreeNode;
	newkey->key = key;
	newkey->translation = translation;
	newkey->left = nullptr;
	newkey->right = nullptr;
	newkey->parent = nullptr;

	return newkey;
}

struct TreeNode* bst_insert(struct TreeNode* root, struct TreeNode* newnode) {
	struct TreeNode* tmp = root;
	struct TreeNode* par = nullptr;

	while (tmp != nullptr) {
		par = tmp;
		if (newnode->key == tmp->key) {
			//TODO
		}
		else if (newnode->key < tmp->key) {//idemo u levo podstablo
			tmp = tmp->left;
		}
		else {
			tmp = tmp->right;
		}
	}
	if (par == nullptr) {
		root = newnode;
	}
	else if (newnode->key < par->key) {
		par->left = newnode;
	}
	else {
		par->right = newnode;
	}
	newnode->parent = par;

	return root;
}

struct TreeNode* bst_search(struct TreeNode* root, string key) {
	struct TreeNode* tmp = root;

	while (tmp != nullptr && tmp->key != key) {
		if (key < tmp->key) {
			tmp = tmp->left;
		}
		else {
			tmp = tmp->right;
		}
	}
	return tmp;
}

struct TreeNode* bst_delete_node(struct TreeNode* root, string key) {
	struct TreeNode* p = root;
	struct TreeNode* q = nullptr;
	struct TreeNode* rp = nullptr;

	while (p != nullptr && key != p->key) {
		q = p;
		if (key < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	if (p == nullptr) {
		//TO DO KADA NEMA KLJUCA
	}
	if (p->left == nullptr) {
		rp = p->right;
	}
	else if (p->right == nullptr) {
		rp = p->left;
	}
	else {
		struct TreeNode* f = p;
		rp = p->right;
		struct TreeNode* lp = p->left;

		while (lp != nullptr) {
			f = rp;
			rp = lp;
			lp = lp->left;
		}
		if (f != p) {
			f->left = p->right;
			rp->right = p->right;
		}
		rp->left = p->left;
	}

	if (q == nullptr) {
		root = rp;
	}
	else if (p == q->left) {
		q->left = rp;
	}
	delete p;

	return root;

}

int main() {
	struct TreeNode* root = nullptr;
	struct TreeNode* newnode = create_tree_node("b", "klk");

	root = bst_insert(root, newnode);
	struct TreeNode* newnode2 = create_tree_node("a", "klk");
	root = bst_insert(root, newnode2);

	cout << "tree:" << root->left->key << endl;
	root = bst_delete_node(root, "b");
	cout << "tree:" << root->key;
}
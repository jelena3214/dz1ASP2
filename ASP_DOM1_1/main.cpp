#include <iostream>
#include <string>
#include <vector>
#include <stack>


using namespace std;

//ISPIS //odredjivanje reci sa najvecim brojem raz prevoda, ubacivanje 3 ista kljuca? datoteka
struct TreeNode {
	string key;
	vector<string> translation;;
	int n;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
};

struct TreeNode* create_tree_node(string key, vector<string> translation) {
	struct TreeNode* newkey = new TreeNode;
	newkey->key = key;
	newkey->translation = translation;
	newkey->left = nullptr;
	newkey->right = nullptr;
	newkey->parent = nullptr;

	return newkey;
}

struct TreeNode* bst_succ(struct TreeNode* node) {
	struct TreeNode* p = node;
	struct TreeNode* q = nullptr;
	if (p->right != nullptr) {
		p = p->right;
		while (p->left != nullptr) {
			p = p->left;
		}
		return p;
	}
	else {
		q = p->parent;
		while (q != nullptr && p == q->right) {
			p = q;
			q = q->parent;
		}
	}
	return q;
}

struct TreeNode* bst_insert(struct TreeNode* root, struct TreeNode* newnode) {
	struct TreeNode* tmp = root;
	struct TreeNode* par = nullptr;

	while (tmp != nullptr) {
		par = tmp;
		if (newnode->key == tmp->key) {
			struct TreeNode* succ = bst_succ(tmp);
			struct TreeNode* parsucc = succ->parent;
			if (succ == parsucc->right) {
				parsucc->right = newnode;
			}
			else if (succ == parsucc->left) {
				parsucc->left = newnode;
			}
			newnode->parent = parsucc;
			succ->parent = newnode;
			newnode->right = succ;
			
			return root;
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
		return root;
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
	else {
		q->right = rp;
	}
	delete p;

	return root;

}

struct TreeNode* create_tree(struct TreeNode* root) {
	cout << "Za prekid unosa unesite 0\n";
	while (1) {
		cout << "Unesite kljuc ";
		string k;
		cin >> k;
		cout << endl;
		if (k == "0")break;
		cout << "Unosite prevod(e): ";
		
		vector<string> t;
		string input;

		cout << "Za prekid unosa unesite 0\n";
		cin >> input;

		while (input != "0")
		{
			t.push_back(input);
			cin >> input;
		}

		struct TreeNode* newnode = create_tree_node(k, t);
		root = bst_insert(root, newnode);
	}
	return root;
}

void delete_bst(struct TreeNode* root) {
	if (root == nullptr) return;

	delete_bst(root->left);
	delete_bst(root->right);

	delete root;
}

struct TreeNode* delete_all_same_keys(struct TreeNode* root, string key) {
	while (bst_search(root, key) != nullptr) {
		root = bst_delete_node(root, key);
	}
	return root;
}

void find_all_keys(struct TreeNode* root, string key) {
	struct TreeNode* p = root, *find;
	while ((find = bst_search(p, key)) != nullptr) {
		for (int i = 0; i < find->translation.size(); i++) {
			cout << find->translation[i] << " ";
		}
		p = bst_succ(find);
	}
}

void stack_test(struct TreeNode *root) {
	stack<struct TreeNode*> stack;
	struct TreeNode* p = root,*old;
	while (p->left != nullptr) {
		if (p->right != nullptr) {
			stack.push(p->right);
		}
		old = p;
		p = p->left;
		delete old;
	}//roditelji?

	while (!stack.empty()) {
		struct TreeNode* q = stack.top();
		stack.pop();
		while (q->left != nullptr) {
			if (q->right != nullptr) {
				stack.push(q->right);
			}
			old = q;
			q = q->left;
			delete old;
		}
		if (q->left == nullptr) {
			if (q->right != nullptr) {
				stack.push(q->right);
			}
			old = q;
			q = q->left;
			delete old;
		}
		else if (q->left == nullptr && q->right == nullptr) {
			delete q;
		}
	}
}

int main() {
	string meni = "Unesite neku od opcija:\n"
		"1. Formiranje stabla\n"
		"2. Pretraga stabla na zadatu rec i dohvatanje prevoda\n"
		"3. Umetanje novog cvora\n"
		"4. Brisanje zadatog kljuca\n"
		"5. Brisanje stabla\n"
		"6. Ispis stabla\n"
		"7. Prekid programa\n";

	struct TreeNode* root = nullptr;
	int choice;
	while (true) {
		cout << meni;
		cin >> choice;
		string word, k , input;
		vector<string> t;
		
		if (choice == 1) {
			root = create_tree(root);
		}
		if (choice == 2) {
			cout << "Unesite kljuc: ";
			cin >> word;
			find_all_keys(root, word);
		}
		if (choice == 3) {
			cout << "Unesite kljuc ";
			cin >> k;
			cout << endl;
			if (k == "0")break;
			cout << "Unosite prevod(e): ";

			cout << "Za prekid unosa unesite 0\n";
			cin >> input;

			while (input != "0")
			{
				t.push_back(input);
				cin >> input;
			}

			struct TreeNode* newnode = create_tree_node(k, t);
			root = bst_insert(root, newnode);
		}
		if (choice == 4) {
			cout << "Unesite kljuc koji zelite da obrisete: ";
			cin >> word;
			root = delete_all_same_keys(root, word);
		}
		if (choice == 5) {
			delete_bst(root);
		}
		if (choice == 6) {
			cout << "Ispis";
		}
		if (choice == 7) {
			cout << "Kraj";
			exit(0);
		}
	}

}
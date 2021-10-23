#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>


using namespace std;
//proveri brisanje sa stekom
//odredjivanje reci sa najvecim brojem raz prevoda, ubacivanje 3 ista kljuca?
struct TreeNode {
	string key;
	vector<string> translation;
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
			if (!parsucc && tmp->right == nullptr) {
				tmp->right = newnode;
				newnode->parent = tmp;
				return root;
			}
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
		struct TreeNode* lp = rp->left;

		while (lp != nullptr) {
			f = rp;
			rp = lp;
			lp = lp->left;
		}
		if (f != p) {
			f->left = rp->right;
			if(rp->right)rp->right->parent = f;
			rp->right = p->right;
			if(p->right)p->right->parent = rp;
		}
		rp->left = p->left;
		if(p->left)p->left->parent = rp;
	}

	if (q == nullptr) {
		root = rp;
	}
	else if (p == q->left) {
		q->left = rp;
		if(rp)rp->parent = q;
	}
	else {
		q->right = rp;
		if(rp) rp->parent = q;
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
		if (p->key != key)return;
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

int subtreeHeight(struct TreeNode *node) {
	if (!node)      return -1;
	return 1 + max(subtreeHeight(node->left), subtreeHeight(node->right));
}

int treeHeight(struct TreeNode *root) {
	if (!root) return -1;
	return subtreeHeight(root);
}

void printTree(struct TreeNode* root) {
	if (root == nullptr)  return;
	else {
		queue<struct TreeNode*> q;
		int i, line_len = 62;
		int first_skip = line_len, in_between_skip;

		q.push(root);
		for (i = 0; i <= treeHeight(root); i++) {
			int j = 1 << i, k, l;
			in_between_skip = first_skip;
			first_skip = (first_skip - 2) / 2;
			for (k = 0; k < first_skip; k++) cout << "  ";
			for (k = 0; k < j; k++) {
				struct TreeNode* btn = q.front();
				q.pop();
				if (btn) {
					q.push(btn->left);
					q.push(btn->right);
				}
				else {
					q.push(0);
					q.push(0);
				}
				if (btn)  cout << btn->key;
				else      cout << "  ";
				for (l = 0; l < in_between_skip; l++) cout<<"  ";
			}
			cout << "\n";
			cout << "\n";
		}
	}
}

void inorder(struct TreeNode* root, vector<string> *all_keys) {
	if (root == nullptr)return;
	inorder(root->left, all_keys);
	all_keys->push_back(root->key);
	inorder(root->right, all_keys);
}

string max_trans(struct TreeNode* root, vector<string> keys) {
	struct TreeNode* p = root, * find;
	string max, key;
	int len = 0, maxlen = 0;
	vector<string> tmp;
	while (!keys.empty()) {
		key = keys.front();
		keys.erase(keys.begin());

		while ((find = bst_search(p, key)) != nullptr) {
			for (int i = 0; i < find->translation.size(); i++) {
				tmp.push_back(find->translation[i]);
			}
			p = bst_succ(find);
			//if (p == nullptr)break;
			if ((p == nullptr) || (p->key != key))break;
		}
		sort(tmp.begin(), tmp.end());
		auto last = unique(tmp.begin(), tmp.end());
		tmp.erase(last, tmp.end());
		len = tmp.size();
		
		if (len > maxlen) {
			maxlen = len;
			max = key;
		}
		tmp.clear();
	}
	return max;
}

int main() {
	string meni = "Unesite neku od opcija:\n"
		"1. Formiranje stabla\n"
		"2. Pretraga stabla na zadatu rec i dohvatanje prevoda\n"
		"3. Umetanje novog cvora\n"
		"4. Brisanje zadatog kljuca\n"
		"5. Brisanje stabla\n"
		"6. Ispis stabla\n"
		"7. Kljuc sa najvise razlicitih prevoda\n"
		"8. Kraj programa\n";

	vector<string> *all_keys = new vector<string>;

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
			stack_test(root);
			root = nullptr;
		}
		if (choice == 6) {
			printTree(root);
		}
		if (choice == 7) {
			inorder(root, all_keys);
			sort(all_keys->begin(), all_keys->end());
			auto last = unique(all_keys->begin(), all_keys->end());
			all_keys->erase(last, all_keys->end());

			//for (int i = 0; i < all_keys->size(); i++) {
				//cout << (*all_keys)[i] << " ";
			//}

			cout << max_trans(root, *all_keys);

			all_keys->clear();
		}
		if (choice == 8) {
			cout << "Kraj programa";
			exit(0);
		}
	}

}
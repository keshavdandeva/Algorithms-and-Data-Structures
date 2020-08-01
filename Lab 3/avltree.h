#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <typeinfo>

using namespace std;

template<typename Key, typename Info>
class AvlTree{

	struct Node{

		Key key;
		Info info;
		int balance;
		Node *left;
		Node *right;

		Node(Key key1, Info info1, Node *left1, Node *right1){

			key = key1;
			info = info1;
			balance = 0;
			left = left1;
			right = right1;

		}

	};

	Node *root;

    // Functions to be called in public functions

	void Print(Node* node, int &a);         
	void deleteAll(Node* node);                 
	int Treesize(Node* node, int a);
	int TotalOccurrences(Node* node, int a);
	int height(Node *node);                     
	bool keyExistsCheck(Node* node, Key k1);   
	void printKeyCheck(Node* node,Key k1);


	Node* LeftRotation(Node *parent){

		Node *temp = parent->right;
		parent->right = temp->left;
		temp->left = parent;
		parent->balance = height(parent->right) - height(parent->left);
		temp->balance = height(temp->right) - height(temp->left);

		return temp;

	}
	Node* RightRotation(Node *parent){

		Node *temp = parent->left;
		parent->left = temp->right;
		temp->right = parent;
		parent->balance = height(parent->right) - height(parent->left);
		temp->balance = height(temp->right) - height(temp->left);

		return temp;

	}


	Node* LR_Rotation(Node *parent){

		Node *temp;
		temp = parent->left;
		parent->left = LeftRotation(temp);
		Node *node2 = RightRotation(parent);
		return node2;

	}
	Node* RL_Rotation(Node *parent){

		Node *temp;
		temp = parent->right;
		parent->right = RightRotation(temp);
		Node *node2 = LeftRotation(parent);
		return node2;

	}


	Node* treeBalance(Node *node){


		if(node->balance < -1){

			if(node->left->balance < 0){
				node = RightRotation(node);
			}

			else{
				node = LR_Rotation(node);
			}

		}else if(node->balance > 1){

			if(node->right->balance > 0){
				node = LeftRotation(node);
			}

			else{
				node = RL_Rotation(node);
			}
		}

		return node;

	}


	Node* insert(Node* node, Key k1, Info i1){

		if(node == NULL){

			Node *newNode = new Node(k1, i1, NULL, NULL);
			return newNode;

		}else if(k1 == node->key){

			node->info = i1;
			return node;

		}else if (k1 < node->key){

			node->left = insert(node->left, k1, i1);

		}else if(k1 > node->key){

			node->right = insert(node->right, k1, i1);

		}

		node->balance = height(node->right) - height(node->left);
		node = treeBalance(node);
		return node;

	}
	Node* insert(Node* node, Key k1){

		if(node == NULL){

			Node *newNode = new Node(k1, 1, NULL, NULL);
			return newNode;

		}else if(k1 == node->key){

			(node->info)++;
			return node;

		}else if (k1 < node->key){

			node->left = insert(node->left, k1);

		}else if(k1 > node->key){

			node->right = insert(node->right, k1);

		}

		node->balance = height(node->right) - height(node->left);
		node = treeBalance(node);
		return node;

	}


	Node* findMin(Node *node){

		if(node->left == NULL){
			return node;
		}

		return findMin(node->left);

	}
	Node* detachMin(Node *node){

		if(node == NULL) return NULL;
		if(node->left == NULL) return node->right;

		node->left = detachMin(node->left);
		return treeBalance(node);

	}
	Node* remove(Node *node, const Key &k1){

		if (k1 > node->key){
			node->right = remove(node->right, k1);
		}else if(k1 < node->key){
			node->left = remove(node->left, k1);
		}else{

			Node *lnode = node->left;
			Node *rnode = node->right;

			delete node;

			if(lnode == NULL && rnode == NULL){
				return NULL;
			}else if(lnode && !rnode){
				return lnode;
			}else if (rnode && !lnode){
				return rnode;
			}

			Node *minNode = findMin(rnode);
			minNode->right = detachMin(rnode);
			minNode->left = lnode;
			minNode->balance = height(minNode->right) - height(minNode->left);

			return treeBalance(minNode);

		}

		node->balance = height(node->right) - height(node->left);
		return treeBalance(node);

	}

public:

	AvlTree();
	~AvlTree();
	void printTree();
	void showRoot();
	void addNode(Key k, Info i);
	void addNode(Key k);
	bool keyExists(Key k); 
	void printKey(Key k1);          
	void removeNode(Key k);
	void deleteAll();
	int size();
	int occurenceSum();

};

template<typename Key, typename Info>
void AvlTree<Key, Info>::Print(Node* node, int &a){

	if(a == 50){    
		char c;
		cout << "To show more : enter 1, To exit : enter any other value ";
		fflush(stdin);
		if(c = getchar() == '1'){
			a = 0;    
		}
		else{
			a++;
		}
	}

	if(a > 50) return;
	if(node == NULL) return;

	Print(node->left, a);
	if(a > 50) return;

	cout << "Key: " << setw(15) << node->key << " | Info: " << setw(4) << node->info << " | Balance: " << node->balance;
	a++;

	if(node->left){
		cout << " | Left -> Key: " << setw(15) << node->left->key;
	}
	if(node->right){
		cout << " | Right -> Key: " << setw(15) << node->right->key;
	}

	cout << endl;
	if(a > 50) return;
	Print(node->right, a);

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::deleteAll(Node* node){

	if(node == NULL) return;

	deleteAll(node->left);
	deleteAll(node->right);

	free(node);

}

template<typename Key, typename Info>
int AvlTree<Key, Info>::Treesize(Node* node, int a){

	if(node == NULL) return a;

	a = Treesize(node->left, a);
	a++;
	a = Treesize(node->right, a);

	return a;

}

template<typename Key, typename Info>
int AvlTree<Key, Info>::TotalOccurrences(Node* node, int a){

	if(node == NULL) return a;

	a = TotalOccurrences(node->left, a);
	a += node->info;
	a = TotalOccurrences(node->right, a);

	return a;

}

template<typename Key, typename Info>
int AvlTree<Key, Info>::height(Node* node){

	if(node == NULL) return 0;

	int leftHeight = height(node->left);
	int rightHeight = height(node->right);

	if(leftHeight > rightHeight){
		return 1 + leftHeight;
	}else{
		return 1 + rightHeight;
	}

}

template<typename Key, typename Info>
bool AvlTree<Key, Info>::keyExistsCheck(Node* node, Key k1){

	if (node == NULL) return false;
	if (node->key == k1) return true;
	if (node->key < k1) return keyExistsCheck(node->right, k1);
	return keyExistsCheck(node->left, k1);

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::printKeyCheck(Node* node,Key k1){

	if (node == NULL) return;
	if (node->key == k1){
		cout << "Searched key: " << node->key << " | info: " << node->info << endl;
	}
	if (node->key < k1) printKeyCheck(node->right, k1);
	printKeyCheck(node->left, k1);

}


template<typename Key, typename Info>
AvlTree<Key, Info>::AvlTree(){

	root = NULL;

}

template<typename Key, typename Info>
AvlTree<Key, Info>::~AvlTree(){

	deleteAll(root);
	root = NULL;

}



template<typename Key, typename Info>
void AvlTree<Key, Info>::printTree(){

	if(root == NULL){
		cout << "Null Tree" << endl;
		return;
	} 

	cout << " --- Printing Tree --- " << endl;
	int i = 0;
	Print(root, i);
	cout << " ---------------------------- " << endl;

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::showRoot(){

	if(root == NULL){
		cout << "No root found, tree is empty" << endl;
		return;
	} 

	cout << "Root: " << root->key<< endl;

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::addNode(Key k, Info i){

	if(root == NULL){

		root = new Node(k, i, NULL, NULL);
		return;

	}

	root = insert(root, k, i);

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::addNode(Key k){

	int i;
	if(typeid(root->info).name() != typeid(i).name()){

		cout << "Invalid data type, cannot count occurences" << endl;
		return;

	}

	if(root == NULL){

		root = new Node(k, 1, NULL, NULL);
		return;

	}

	root = insert(root, k);

}

template<typename Key, typename Info>
bool AvlTree<Key, Info>::keyExists(Key k){

	if(!keyExistsCheck(root, k)){
		cout << "ERROR 404 : Key '" << k <<"' doesn't exist" << endl;
	}

	return keyExistsCheck(root, k);

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::printKey(Key k1){

	if(!keyExistsCheck(root, k1)){
		cout << "ERROR 404 : Key '" << k1 <<"' doesn't exist" << endl;
	}
	printKeyCheck(root, k1);

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::removeNode(Key k){

	if(keyExistsCheck(root, k)){
		cout << "Removing key: " << k << endl;
		root = remove(root , k);
	} 
	else cout << "ERROR 404 : Key '" << k <<"' doesn't exist" << endl;

}

template<typename Key, typename Info>
void AvlTree<Key, Info>::deleteAll(){

	deleteAll(root);
	root = NULL;

}

template<typename Key, typename Info>
int AvlTree<Key, Info>::size(){

	return Treesize(root, 0);

}

template<typename Key, typename Info>
int AvlTree<Key, Info>::occurenceSum(){

	int i;
	if(typeid(root->info).name() != typeid(i).name()){

		cout << "Invalid data type, cannot count occurences" << endl;
		return 0;

	}else{

		return TotalOccurrences(root, 0);

	}

}

int count_words(AvlTree<string, int>& tree, istream& source){

	string str;
	string word;
	fflush(stdin);
	while(getline(source, str)){

		if(str.empty())continue;

		for(int i = 0; i < str.size(); i++){

			if(str[i]>=65 && str[i]<=92){
				str[i]=str[i]+32;
			}

			if(ispunct(str[i])){
				if(str[i] != '\''){
					str[i] = ' ';
				}
			}

		}

		istringstream iss(str);
		while (iss >> word){
			tree.addNode(word);
		} 

		if(&source == &cin) break;

	}

	return 0;

}
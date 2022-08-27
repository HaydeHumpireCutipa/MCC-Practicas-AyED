#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;

template <typename K, typename V>
class Tree {
	struct Node {
		K key;
		V value;
		bool highlight;
		int height;
		Node* left;
		Node* right;
		Node(const K& k, const V& val, Node* lft, Node* rgt, int h = 0)
			:key(k), value(val), left(lft), right(rgt), height(h), highlight(false) {}
	};

public:
	Tree();
	void insert(const K& key, const V& value);
	void remove(const K& key);
	bool contains(const K& key) const;
	void preorder() {
		preorder(root); 
	}
	Node*& getRoot() {
		return root;
	}
	void print() {
		string filename = "graph.gv";
		
		ofstream myfile;
		myfile.open(filename);
		myfile << "digraph AVL {\n";
		myfile <<  "fontcolor=\"navy\";\n";
		myfile <<  "fontsize=20;\n";
		myfile <<  "labelloc=\"t\";\n";
		myfile <<  "label=\"UNSA\nAVL Tree\"\n";

		char* str = (char*)malloc(sizeof(char)*4096);
		printPri(root,1,str,myfile);
		free(str);
		myfile << "}";
	}

	bool search(Node*& root, const K& key)
	{
		// If root is NULL
		if (root == NULL)
			return false;
	
		// If found, return true
		else if (root->key == key) {
			root->highlight = true;
			return true;
		}
		// Recur to the left subtree if
		// the current node's value is
		// greater than key
		else if (root->key > key) {
			bool val = search(root->left, key);
			return val;
		}
	
		// Otherwise, recur to the
		// right subtree
		else {
			bool val = search(root->right, key);
			return val;
		}
	}

	K findMaximum(Node*& spot) {
		if (spot->right == nullptr){
            spot->highlight = true;
			return spot->key;
		}
		
		return findMaximum(spot->right);
	}

	K findMinimum(Node*& spot) {
		if (spot->left == nullptr){
            spot->highlight = true;
			return spot->key;
		}
		
		return findMinimum(spot->left);
	}
private:
	//Metodos privados
	void insert(const K& key, const V& value, Node*& spot);
	void remove(const K& key, Node*& spot);
	bool contains(const K& key, Node* root) const;
	Node* findMin(Node*& root) const;
	void rotateWithLeftChild(Node*& spot);
	void rotateWithRightChild(Node*& spot);
	void doubleWithLeftChild(Node*& spot);
	void doubleWithRightChild(Node*& spot);
	void balance(Node*& spot);
	int height(Node* spot) const;
	void preorder(Node* root);
	void printPri(Node* node, int position, char* stringBuilder, ofstream& salida);
	
	static const int ALOWED_IMBALANCE = 1;
	//variables privadas
	Node* root;
	int n;
};

template <typename K, typename V>
Tree<K, V>::Tree()
	:root(nullptr), n(0) {}

template <typename K, typename V>
void Tree<K, V>::insert(const K& key, const V& value) {
	insert(key, value, root);
}

template <typename K, typename V>
void Tree<K, V>::remove(const K& key) {
	remove(key, root);
}

template <typename K, typename V>
bool Tree<K, V>::contains(const K& key) const {
	return contains(key, root);
}

template <typename K, typename V>
void Tree<K, V>::insert(const K& key, const V& value, Node*& spot) {
	if (spot == nullptr) {
		++n;
		spot = new Node(key, value, nullptr, nullptr);
	}
	else {
		if (key > spot->key){
			insert(key, value, spot->right);
		}
		else {
			if (key < spot->key){
				insert(key, value, spot->left);
			}
		}
	}
	balance(spot);
}

template <typename K, typename V>
bool Tree<K, V>::contains(const K& key, Node* root) const {
	if (root != nullptr) {
		if (key > root->key)
			return contains(key, root->right);
		else if (key < root->key)
			return contains(key, root->left);
		else
			return true;
	}
	return false;
}

template <typename K, typename V>
void Tree<K, V>::remove(const K& key, Node*& spot) {
	if (spot == nullptr){
		return;
	}

	if (key < spot->key ){
		remove(key, spot->left);
	} else { 
		if (spot->key < key){
			remove(key, spot->right);
		}
		else {
			if (spot->left != nullptr && spot->right != nullptr) {
				spot->key = findMin(spot->right)->key;
				remove(spot->key, spot->right);
			} else {
				Node* oldNode = spot;
				spot = (spot->left != nullptr) ? spot->left : spot->right;
				delete oldNode;
			}
		}
	}
	
	balance(spot);
}

template <typename K, typename V>
typename Tree<K, V>::Node* Tree<K, V>::findMin(Node*& spot) const {
	if (spot->left == nullptr){
		return spot;
	}
	
	return findMin(spot->left);
}



template <typename K, typename V>
void Tree<K, V>::balance(Node*& spot) {
	if (spot != nullptr) {
		if (height(spot->left) - height(spot->right) > ALOWED_IMBALANCE) {
			//Realiza rotacion izquierda, compara si la falta esta en left left o left right intercalado
			if (height(spot->left->left) >= height(spot->left->right))
				rotateWithLeftChild(spot);
			else 
				doubleWithLeftChild(spot);
		}
		else {
			if (height(spot->right) - height(spot->left) > ALOWED_IMBALANCE) {
				//Realiza Rotacion derecha, compara si la falta esta en left left o left right intercalado
				if (height(spot->right->right) >= height(spot->right->left))
					rotateWithRightChild(spot);
				else 
					doubleWithRightChild(spot);
			}
		}
		spot->height = std::max(height(spot->left), height(spot->right)) + 1;
	}
}

template <typename K, typename V>
int Tree<K, V>::height(Node* spot) const {
	return (spot == nullptr) ? -1 : spot->height;
}

template <typename K, typename V>
void Tree<K, V>::rotateWithLeftChild(Node*& spot) {
	Node* temp = spot->left;
	spot->left = temp->right;
	temp->right = spot;
	spot->height = std::max(height(spot->left), height(spot->right)) + 1;
	temp->height = std::max(height(temp->left), height(spot)) + 1;
	spot = temp;
}

template <typename K, typename V>
void Tree<K, V>::rotateWithRightChild(Node*& spot) {
	Node* temp = spot->right;
	spot->right = temp->left;
	temp->left = spot;
	spot->height = std::max(height(spot->right), height(spot->left)) + 1;
	temp->height = std::max(height(temp->right), height(spot)) + 1;
	spot = temp;
}

template <typename K, typename V>
void Tree<K, V>::doubleWithLeftChild(Node*& spot) {
	rotateWithRightChild(spot->left);
	rotateWithLeftChild(spot);
}

template <typename K, typename V>
void Tree<K, V>::doubleWithRightChild(Node*& spot) {
	rotateWithLeftChild(spot->right);
	rotateWithRightChild(spot);
}

template <typename K, typename V>
void Tree<K, V>::preorder(Node* p) {
	if (p == nullptr)
		return;
	std::cout << p->key << " -- " << p->value << ";\n";
	preorder(p->left);
	preorder(p->right);
}

template <typename K, typename V>
void Tree<K, V>::printPri(Node* node, int position, char* stringBuilder, ofstream& salida) {
	sprintf(stringBuilder, "%d [label=\"%d\", shape=circle, color=%s];\n",position, node->key, node->highlight == true ? "red" : "black");
	salida << stringBuilder;
	int left = 2*position;
	if((node->left) != nullptr){
		sprintf(stringBuilder, "%d -> %d;\n",position,left);
		salida << stringBuilder;
		printPri(node->left,left,stringBuilder,salida);
	}
	int right = left + 1;
	if((node->right) != nullptr){
		sprintf(stringBuilder, "%d -> %d;\n",position,right);
		salida << stringBuilder;
		printPri(node->right,right,stringBuilder,salida);
	}
}


int main()
{
	int opcion=1;
	Tree<int, int> arbol;
	int valor=0;

    arbol.insert(12,100);
    arbol.insert(6,100);
    arbol.insert(2,100);
    arbol.insert(3,100);
    arbol.insert(8,100);
    arbol.insert(15,100);
    arbol.insert(29,100);
    arbol.insert(32,100);

	while(opcion!=6){
		cout<<"1) Insertar: "<<endl;
		cout<<"2) Eliminar: "<<endl;
		cout<<"3) Maximo: "<<endl;
		cout<<"4) Minimo: "<<endl;
		cout<<"5) Busqueda: "<<endl;
		cout<<"6) Salir: "<<endl;
		cout<<endl;
		cout<<"Ingresa tu opcion: ";
		cin>>opcion;
		switch(opcion){
			case 1:{
				cout<<"Ingrese el valor a agregar: "<<endl;
				cin>>valor;
				cout<<endl;
				arbol.insert(valor,100);
				arbol.print();
				system("dot -Tps graph.gv -o graph.ps");
				break;
			}
			case 2:{
				cout<<"Ingrese el valor a eliminar: "<<endl;
				cin>>valor;
				cout<<endl;
				arbol.remove(valor);
				arbol.print();
				system("dot -Tps graph.gv -o graph.ps");
				break;
			}
			case 3:{
				cout<<"El maximo: "<<arbol.findMaximum(arbol.getRoot())<<endl;
                arbol.print();
				system("dot -Tps graph.gv -o graph.ps");
				break;
			}
			case 4:{
				cout<<"El minimo: "<<arbol.findMinimum(arbol.getRoot())<<endl;
                arbol.print();
				system("dot -Tps graph.gv -o graph.ps");
				break;
			}
			case 5:{
				cout<<"Ingrese el valor a buscar: "<<endl;
				cin>>valor;
				cout<<endl;
				cout<<arbol.search(arbol.getRoot(), valor)<<endl;
				arbol.print();
				system("dot -Tps graph.gv -o graph.ps");
				break;
			}
			case 6:{
				break;
			}
			default:{
				cout<<"Opcion no valida"<<endl;
				break;
			}

		}
	}


	return 0;
}


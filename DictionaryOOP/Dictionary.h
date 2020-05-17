#pragma once
#include "Node.h"
#include "KeyComp.h"
#include<iostream>
//#include<climits>
using namespace std;
template <class K, class V> class Node;
template <class K, class V, class KeyComp> class Dictionary
{
	Node<K, V>* root;
	int noElements;

public:
	Dictionary();
	Dictionary(const Dictionary& d);
	Dictionary& operator=(const Dictionary& d);

	Node<K, V>* copyNode(Node<K, V>* n) const;
	void clearNode(Node<K, V>*& n);
	void clearDictionary();

	int getBalance(Node<K, V>* n);
	Node<K, V>* RotateLeft(Node<K, V>* x);
	Node<K, V>* RotateRight(Node<K, V>* y);

	Node<K, V>* addNode(K& key, V& value, Node<K, V>*& n);
	void insertNode(K k, V v);
	int getNoElements();

	Node<K, V> minValueNode(Node<K, V>* n);
	Node<K, V> deleteNode(Node<K, V>root, K k);
	void deleteNodeFromKey(K k);

	V find(K k, Node<K, V> n);
	V findKeyValue(K k);
	V operator[](const K k);

	void inOrder(Node<K, V> *n, ostream &out);
	friend ostream& operator<<(ostream& out, const Dictionary& d);

	~Dictionary();
};

inline int max(int a, int b) { if (a > b) return a; return b; }

template <class K, class V, class KeyComp>
Dictionary<K, V, KeyComp>::Dictionary()		//constructor fara parametrii
{
	root = NULL;
	noElements = 0;
}

template <class K, class V, class KeyComp>
Node<K, V>* Dictionary<K, V, KeyComp>::copyNode(Node<K, V>* n) const		//functie care copiaza un nod
{
	if (n != NULL)
	{
		Node< K, V>* root = new Node<K, V>;
		root->left = copyNode(n->getLeft());
		root->right = copyNode(n->getRight());
		root->parent = n->getParent();
		root->key = n->getKey();
		root->value = n->getValue();
		//root->height = n->getHeight();
		return root;
	}
	else
		return NULL;
}

template <class K, class V, class KeyComp>			
Dictionary<K, V, KeyComp>::Dictionary(const Dictionary& d)		//constructor de copiere
{
	root = NULL;
	this->root = copyNode(d.root);
	this->noElements = d.noElements;
}

template <class K, class V, class KeyComp>
Dictionary <K, V, KeyComp>& Dictionary<K, V, KeyComp>:: operator=(const Dictionary& d)		//supraincarcarea operatorului egal pentru dictionare
{
	clearDictionary();
	root = copyNode(d.root);
	this->noElements = d.noElements;
	return *this;
}

template <class K, class V, class KeyComp>
void Dictionary<K, V, KeyComp>::clearNode(Node <K, V>*& n)		//functie care sterge tot de la un anumit nod in jos, inclusiv nodul
{
	if (n != NULL)
	{
		clearNode(n->left);
		clearNode(n->right);
		delete n;
	}
	n = NULL;
}

template <class K, class V, class KeyComp>
void Dictionary<K, V, KeyComp>::clearDictionary()		//functie care sterge tot dictionarul, stergand fiecare nod pe rand
{
	clearNode(root);
}

template <class K, class V, class KeyComp>
Node<K, V>* Dictionary<K, V, KeyComp>::RotateLeft(Node<K, V>* x)
{
	Node<K, V>* y = x->right;
	Node<K, V>* z = y->left;

	y->left = x;
	x->right = z;

	x->height = max(x->left->getHeight(), x->right->getHeight()) + 1;
	y->height = max(y->left->getHeight(), y->right->getHeight()) + 1;

	return y;
}


template <class K, class V, class KeyComp>
Node <K, V>* Dictionary<K, V, KeyComp>::RotateRight(Node<K, V>* y)
{
	Node<K, V>* x = y->left;
	Node<K, V>* z = x->right;

	x->right = y;
	y->left = z;

	y->height = max(y->left->getHeight(), y->right->getHeight()) + 1;
	x->height = max(x->left->getHeight(), x->right->getHeight()) + 1;

	return x;

}

template <class K, class V, class KeyComp>
int Dictionary<K, V, KeyComp>::getBalance(Node<K, V>* n)
{
	if (n == NULL)
		return 0;
	return n->left->getHeight() - n->right->getHeight();
}
template <class K, class V, class KeyComp>
Node<K, V>* Dictionary<K, V, KeyComp>::addNode(K& key, V& value, Node<K, V>*& n)
{
	if (n == NULL)
	{
		n = new Node<K, V>;
		n->left = NULL;
		n->right = NULL;
		n->key = key;
		n->value = value;
		n->height = 1;
		return n;
	}

	if (key < n->getKey())
	{
		Node <K, V>* nou = addNode(key, value, n->left);
		n->left = nou;
		nou->parent = n;
	}
	else
	{
		if (key > n->getKey())
		{
			Node <K, V>* nou = addNode(key, value, n->right);
			n->right = nou;
			nou->parent = n;
		}
		else
		{
			n->value = value;
			return n;
		}
	}

	n->height = 1 + max(n->left->getHeight(), n->right->getHeight());
	
	int  balance = getBalance(n);

	if (balance > 1 && key < n->left->key)	// cazul left-left
		return RotateRight(n);

	if (balance<-1 && key>n->right->key)	//cazul right-right
		return RotateLeft(n);

	if (balance > 1 && key > n->left->key)	//cazul left-right
	{
		n->left = RotateLeft(n->left);
		return RotateLeft(n);
	}

	if (balance<-1 && key>n->right->key)	//cazul right-left
	{
		n->right = RotateRight(n->right);
		return RotateRight(n);
	}

	return n;
}

template <class K, class V, class KeyComp>
void Dictionary<K, V, KeyComp>::insertNode(K key, V value)
{
	root = addNode(key, value, root);
	noElements++;
}

template <class K, class V, class KeyComp>
int Dictionary<K, V, KeyComp>::getNoElements()
{
	return this->noElements;
}

template <class K, class V, class KeyComp>
Node<K, V> Dictionary<K, V, KeyComp>::minValueNode(Node<K, V>* n)
{
	Node<K, V>* current = n;
	while (current->left != NULL)
	{
		current = current->left;
	}
	return current;
}

template <class K, class V, class KeyComp>
Node<K, V> Dictionary<K, V, KeyComp>::deleteNode(Node<K, V> root, K key)
{
	if (root == NULL) return root;
	if (key < root->key)
	{
		root->left = deleteNode(key, root->left);
	}
	else
	{
		if (key > root->key)
		{
			root->right = deleteNode(key, root->right);
		}
		else
		{
			if (root->left == NULL || root->right = NULL)	//cazul in care nodul are un copil sau niciunul
			{
				Node<K, V>* nou = root->left ? root->left : root->right;

				if (nou == NULL) // niciun fiu
				{
					nou = root;
					root = NULL;
				}
				else
				{
					*root = *nou;
				}
				delete nou;
			}
			else
			{
				Node<K, V>* nou = minValueNode(root->right);
				root->key = nou->key;
				root->right = deleteNode(root->right, key);
			}
		}
	}
	if (root == NULL)
	{
		return root;
	}
	root->height = 1 + max(root->left->getHeight(), root->right->getHeight());
	int balance = getBalance(root);

	if (balance > 1 && getBalance(root->left) >= 0)		//cazul left-left
		return RotateRight(root);

	if (balance > 1 && getBalance(root->left) < 0)		//cazul left-right
	{
		root->left = leftRotate(root->left);
		return RotateRight(root);
	}
	if (balance < -1 && getBalance(root->right) <= 0)		//cazul right-right
		return RotateLeft(root);
	if (balance < -1 && getBalance(root->right) > 0)		//cazul right-left
	{
		root->right = rightRotate(root->right);
		return RotateLeft(root);
	}
	return root;
}

template <class K, class V, class KeyComp>
void Dictionary<K, V, KeyComp>::deleteNodeFromKey(K k)
{
	root = deleteNode(root, k);
	noElements--;
}
template <class K, class V, class KeyComp>
V Dictionary<K, V, KeyComp>:: find(K k, Node<K, V> n)
{
	if (root->key == k)
		return root->getValue();
	else
	{
		if (root->key > k)
		{
			return find(k, root->left);
		}
		else
		{
			return find(k, root->right);
		}
	}
}
template <class K, class V, class KeyComp>
V Dictionary<K, V, KeyComp>::findKeyValue(K k)
{
	return find(k, root);
}
template <class K, class V, class KeyComp>
V Dictionary<K, V, KeyComp>:: operator[](const K k)
{
	K key = k;
	return this->findKeyValue(key);
}

template <class K, class V, class KeyComp>
void Dictionary<K, V, KeyComp>::inOrder(Node<K, V>* n, ostream &out)
{
	if (n != NULL)
	{
		inOrder(n->left);
		out << n->getKey()<< " "<<n->getValue();
		inOrder(n->right);
	}
}

template <class K, class V, class KeyComp>
ostream& operator<<(ostream& out, const Dictionary<K, V, KeyComp>& d)
{
	out << "Chei" << " " << "Valori:";
	Node<K, V> * nou = d.root;
	inOrder(nou, out);
	return out;
}

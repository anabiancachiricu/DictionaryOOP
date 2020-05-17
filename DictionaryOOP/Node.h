#pragma once
#include"Dictionary.h"
#include"KeyComp.h"
#include<iostream>
using namespace std;
template<class K, class V, class KeyComp> class Dictionary;
template<class K, class V> class Node
{
	K key;
	V value;
	Node<K, V>* left, * right, *parent;
	int height;

public:

	Node()
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		key = NULL;
		height = 0;
		value = NULL;
	}

	Node(K k, V v)
	{
		left = NULL;
		right = NULL;
		parent = NULL;
		key = k;
		value = v;
		height = 0;
	}

	K getKey() const
	{
		return this->key;
	}

	V getValue() const
	{
		return this->value;
	}

	Node<K, V>* getLeft() const
	{
		return this->left;
	}

	Node<K, V>* getRight() const
	{
		return this->right;
	}

	Node<K, V>* getParent() const
	{
		return this->parent;
	}

	int getHeight()
	{
		if (this == NULL)
			return 0;
		return this->height;
	}
	friend class Dictionary<K, V, KeyComp<K>>;
};


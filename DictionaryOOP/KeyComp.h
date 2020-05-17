#pragma once
#include<string>
#include<iostream>
using namespace std;
template<class K> 
class KeyComp
{
public:
	int operator() ( const K& key1, const K& key2)
	{
		if (key1 > key2)
			return 1;
		else
			if (key1 < key2)
				return -1;
			else return 0;
	}
};
template<>
class KeyComp<std::string>
{
public:
	int operator() (const string &key1, const string& key2)
	{
		int n;
		if (key1.length < key2.length)
			 n = key1.length;
		else
			 n = key2.length;
		string k1 = key1.copy;
		string k2 = key2.copy;
		k1.resize(n);
		k2.resize(n);
		if (k1 == k2)  return 0;
		else if (k1 < k2) return -1;
		else return 1;
	}
};


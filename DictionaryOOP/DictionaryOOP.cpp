//Pentru ca algoritmul sa ruleze in timp O(log n) o sa folosesc un AVL
#include <iostream>
#include<cassert>
#include "Node.h"
#include "KeyComp.h"
#include "Dictionary.h"
using namespace std;
template<class K, class V, class KeyComp> class Dictionary;
template<class K, class V> class Node;
 
int main()
{
    Dictionary<int, int, KeyComp<int>>* d;
    d = new Dictionary<int, int, KeyComp<int>>;
    d->insertNode(1, 4);
    d->insertNode(2, 5);
    d->insertNode(3, 8);
    d->insertNode(6, 3);
    d->insertNode(5, 2);
    assert(d->getNoElements() == 5);
    assert(d->findKeyValue(3) == 8);
    Dictionary<int, int, KeyComp<int>>* d2;
    d2 = d;
    assert( d2->getNoElements()==5);
    cout << "Programul ruleaza";
}


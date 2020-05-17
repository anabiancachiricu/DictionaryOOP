//Pentru ca algoritmul sa ruleze in timp O(log n) o sa folosesc un AVL
#include <iostream>
#include "Node.h"
#include "KeyComp.h"
#include "Dictionary.h"
using namespace std;
template<class K, class V, class KeyComp> class Dictionary;
template<class K, class V> class Node;
 
int main()
{
   Dictionary<int, int, KeyComp<int>> *d;
   d->insertNode(1, 4);
  
}


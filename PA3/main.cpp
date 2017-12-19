//#include "DictionaryBST.hpp"
//#include "DictionaryHashtable.hpp"
#include "DictionaryTrie.hpp"
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
   DictionaryTrie tree;
   if (tree.insert("asd", 5)) cout << 1;
   if (tree.insert("rtsd", 3)) cout << 1;
   if (tree.insert("a", 7)) cout << 1;
   if (tree.find("a")) cout << 1;
   if (tree.find("rtsd")) cout << 1;
   if (tree.find("a")) cout << 1;
   if (!tree.find("b")) cout << 1;
   
   return 0;
}

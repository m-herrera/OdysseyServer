//
// Created by dario1227 on 14/06/18.
//

#ifndef ODYSSEYSERVER_HUFFMANCODEULTIMATE_H
#define ODYSSEYSERVER_HUFFMANCODEULTIMATE_H

#include "Node.h"
#include <iostream>
using namespace std;
class HuffmanCodeUltimate{
public:

   static  Node* getNode(char ch, int freq, Node* left, Node* right);
   static void encode(Node* root, string str, map<char, string> &huffmanCode);
  static  void decode(Node* root, string str);
    static void buildHuffmanTree(string text);


};
#endif //ODYSSEYSERVER_HUFFMANCODEULTIMATE_H
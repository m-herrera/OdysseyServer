//
// Created by dario1227 on 14/06/18.
//

#ifndef ODYSSEYSERVER_HUFFMANCODEULTIMATE_H
#define ODYSSEYSERVER_HUFFMANCODEULTIMATE_H

#include "Node.h"
#include <iostream>
#include <map>
using namespace std;
class HuffmanCodeUltimate{
public:

    static Node *getNode(char ch, int freq, Node *left, Node *right);

    static void encode(Node *root, string str, map<char, string> &huffmanCode);

    static string decode(Node *root, string str);

    static boost::property_tree::ptree buildHuffmanTree(string text);

    static std::string getTree(boost::property_tree::ptree xml);


};
#endif //ODYSSEYSERVER_HUFFMANCODEULTIMATE_H

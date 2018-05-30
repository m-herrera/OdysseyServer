//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_BTREE_H
#define ODYSSEYSERVER_BTREE_H

#include "BTreeNode.h"
#include "Metadata.h"
#include <iostream>

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;  // Minimum degree
public:
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {  root = nullptr;  t = _t; }

    // function to traverse the tree
    void traverse()
    {  if (root != nullptr) root->traverse(); }

    // function to search a key in this tree
    void search(std::vector<Metadata*>& vector,std::string k)
    {  return (root == nullptr)? void() : root->search(vector,k); }

    // The main function that inserts a new key in this B-Tree
    void insert(Metadata* k);

    std::vector<Metadata*> search(std::string k);

    void empty()
    {  if (root != nullptr) root->empty(); }
};


#endif //ODYSSEYSERVER_BTREE_H

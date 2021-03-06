//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_BTreeNode_H
#define ODYSSEYSERVER_BTreeNode_H

#include "Metadata.h"

class BTreeNode
{
    std::vector<Metadata*> *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf);   // Constructor

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(Metadata* k);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[].  The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A function to search a key in subtree rooted with this node.
    void search(std::vector<Metadata*> &vector,std::string k);   // returns NULL if k is not present.

    void empty();
// Make BTree friend of this so that we can access private members of this
// class in BTree functions
    friend class BTree;
};


#endif //ODYSSEYSERVER_BTreeNode_H

//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_BTREE_H
#define ODYSSEYSERVER_BTREE_H

#include "BTreeNode.h"
#include "Metadata.h"
#include <iostream>

class BTree{
public:
    BTreeNode *root = nullptr;
    void insert(Metadata* val);
    void _delete(Metadata* val,BTreeNode *myNode);
    Metadata* search(std::string);
private:
    BTreeNode* createNode(Metadata* val, BTreeNode *child);
    void addValToNode(Metadata*val, int pos, BTreeNode *node, BTreeNode *child);
    void splitNode(Metadata* val, Metadata** pval, int pos, BTreeNode *node,BTreeNode *child, BTreeNode **newNode);
    int setValueInNode(Metadata* val, Metadata** pval,BTreeNode *node, BTreeNode **child);
    void copySuccessor(BTreeNode *myNode, int pos);
    void removeVal(BTreeNode *myNode, int pos);
    void doRightShift(BTreeNode *myNode, int pos);
    void doLeftShift(BTreeNode *myNode, int pos);
    void mergeNodes(BTreeNode *myNode, int pos);
    void adjustNode(BTreeNode *myNode, int pos);
    int delValFromNode(Metadata* val,BTreeNode *myNode);
    Metadata* searchAux(std::string,BTreeNode *myNode);
};


#endif //ODYSSEYSERVER_BTREE_H

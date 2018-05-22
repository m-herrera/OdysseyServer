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
    BtreeNode *root = nullptr;
    void insert(Metadata* val);
    void _delete(Metadata* val,BtreeNode *myNode);
    void traversal(BtreeNode *myNode);
private:
    BtreeNode* createNode(Metadata* val, BtreeNode *child);
    void addValToNode(Metadata*val, int pos, BtreeNode *node, BtreeNode *child);
    void splitNode(Metadata* val, Metadata** pval, int pos, BtreeNode *node,BtreeNode *child, BtreeNode **newNode);
    int setValueInNode(Metadata* val, Metadata** pval,BtreeNode *node, BtreeNode **child);
    void copySuccessor(BtreeNode *myNode, int pos);
    void removeVal(BtreeNode *myNode, int pos);
    void doRightShift(BtreeNode *myNode, int pos);
    void doLeftShift(BtreeNode *myNode, int pos);
    void mergeNodes(BtreeNode *myNode, int pos);
    void adjustNode(BtreeNode *myNode, int pos);
    int delValFromNode(Metadata* val,BtreeNode *myNode);
};


#endif //ODYSSEYSERVER_BTREE_H

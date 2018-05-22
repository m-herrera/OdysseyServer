//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_AVLTREE_H
#define ODYSSEYSERVER_AVLTREE_H


#include "AVLTreeNode.h"

class AVLTree {
public:
    AVLTreeNode* root = nullptr;
    void makeEmpty(AVLTreeNode* t);
    void insert(Metadata* x);
    void remove(Metadata* x);
    void display();

private:
    AVLTreeNode* insert(Metadata* x, AVLTreeNode* t);
    AVLTreeNode* singleRightRotate(AVLTreeNode* &t);
    AVLTreeNode* singleLeftRotate(AVLTreeNode* &t);
    AVLTreeNode* doubleLeftRotate(AVLTreeNode* &t);
    AVLTreeNode* doubleRightRotate(AVLTreeNode* &t);
    AVLTreeNode* findMin(AVLTreeNode* t);
    AVLTreeNode* findMax(AVLTreeNode* t);
    AVLTreeNode* remove(Metadata* x, AVLTreeNode* t);
    int height(AVLTreeNode* t);
    int getBalance(AVLTreeNode* t);
    void inorder(AVLTreeNode* t);
};


#endif //ODYSSEYSERVER_AVLTREE_H

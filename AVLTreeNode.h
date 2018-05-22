//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_AVLTREENODE_H
#define ODYSSEYSERVER_AVLTREENODE_H

#include "Metadata.h"

struct AVLTreeNode
{
    Metadata* data;
    AVLTreeNode* left = nullptr;
    AVLTreeNode* right = nullptr;
    int height;
};


#endif //ODYSSEYSERVER_AVLTREENODE_H

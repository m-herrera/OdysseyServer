//
// Created by marco on 13/05/18.
//

#ifndef ODYSSEYSERVER_TREENODE_H
#define ODYSSEYSERVER_TREENODE_H


#include "User.h"

struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    User* data;
};



#endif //ODYSSEYSERVER_TREENODE_H

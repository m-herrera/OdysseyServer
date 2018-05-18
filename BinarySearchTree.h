//
// Created by marco on 13/05/18.
//

#ifndef ODYSSEYSERVER_BINARYSEARCHTREE_H
#define ODYSSEYSERVER_BINARYSEARCHTREE_H


#include "User.h"
#include "BinarySearchTreeNode.h"

class BinarySearchTree {
private:
    bool insertAux(User* user, TreeNode** parent);
    User* getAux(std::string username, TreeNode* parent);
public:
    TreeNode* root = nullptr;
    bool insert(User* user);
    User* get(std::string username);
    void delete_(std::string username);

};



#endif //ODYSSEYSERVER_BINARYSEARCHTREE_H

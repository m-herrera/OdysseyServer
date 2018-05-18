//
// Created by marco on 13/05/18.
//

#include "BinarySearchTree.h"


bool BinarySearchTree::insert(User* user){
    return insertAux(user,&root);

}

bool BinarySearchTree::insertAux(User* user, TreeNode** parent){
    if (*parent == nullptr){
        *parent = new TreeNode();
        (*parent)->data = user;
        return true;
    }
    else if (user->getUsername() > (*parent)->data->getUsername()){
        return insertAux(user,&(*parent)->right);

    }else if (user->getUsername() < (*parent)->data->getUsername()){
        return insertAux(user,&(*parent)->left);
    }else{
        return false;
    }
}

User* BinarySearchTree::get(std::string username){
    return getAux(username,root);
}

User* BinarySearchTree::getAux(std::string username, TreeNode* parent){
    if(parent == nullptr){
        return nullptr;
    }
    else if (username > parent->data->getUsername()){
        return getAux(username,parent->right);
    }else if (username < parent->data->getUsername()) {
        return getAux(username, parent->left);
    }else{
        return parent->data;
    }
}

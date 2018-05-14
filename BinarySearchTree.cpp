//
// Created by marco on 13/05/18.
//

#include "BinarySearchTree.h"


bool BinarySearchTree::insert(User* user){
    TreeNode* node = insertAux(user,root);
    if(node != nullptr){
        root = node;
        return true;
    }else{
        delete(node);
        return false;
    }

}

TreeNode* BinarySearchTree::insertAux(User* user, TreeNode* parent){
    if (parent == nullptr){
        parent = new TreeNode();
        parent->data = user;
    }
    else if (user->getUsername() > parent->data->getUsername()){
        TreeNode* node = insertAux(user,parent->right);
        if(node != nullptr){
            parent->right = node;
        }else{
            delete(node);
            return nullptr;
        }

    }else if (user->getUsername() < parent->data->getUsername()){
        TreeNode* node = insertAux(user,parent->left);
        if(node != nullptr){
            parent->left = node;
        }else{
            delete(node);
            return nullptr;
        }
    }else{
        return nullptr;
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

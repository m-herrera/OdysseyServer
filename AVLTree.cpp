//
// Created by marco on 21/05/18.
//

#include "AVLTree.h"


using namespace std;

void AVLTree::makeEmpty(AVLTreeNode* t)
{
    if(t == nullptr)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

AVLTreeNode* AVLTree::insert(Metadata* x, AVLTreeNode* t)
{
    if(t == nullptr)
    {
        t = new AVLTreeNode;
        t->data.push_back(x);
        t->height = 0;
        t->left = t->right = nullptr;
    }
    else if(x->artist < t->data.at(0)->artist)
    {
        t->left = insert(x, t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(x->artist < t->left->data.at(0)->artist)
                t = singleRightRotate(t);
            else
                t = doubleRightRotate(t);
        }
    }
    else if(x->artist > t->data.at(0)->artist)
    {
        t->right = insert(x, t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(x->artist > t->right->data.at(0)->artist)
                t = singleLeftRotate(t);
            else
                t = doubleLeftRotate(t);
        }
    }else{
        t->data.push_back(x);
    }

    t->height = max(height(t->left), height(t->right))+1;
    return t;
}

AVLTreeNode* AVLTree::singleRightRotate(AVLTreeNode* &t)
{
    AVLTreeNode* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

AVLTreeNode* AVLTree::singleLeftRotate(AVLTreeNode* &t)
{
    AVLTreeNode* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

AVLTreeNode* AVLTree::doubleLeftRotate(AVLTreeNode* &t)
{
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}

AVLTreeNode* AVLTree::doubleRightRotate(AVLTreeNode* &t)
{
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

AVLTreeNode* AVLTree::findMin(AVLTreeNode* t)
{
    if(t == nullptr)
        return nullptr;
    else if(t->left == nullptr)
        return t;
    else
        return findMin(t->left);
}

AVLTreeNode* AVLTree::findMax(AVLTreeNode* t)
{
    if(t == nullptr)
        return nullptr;
    else if(t->right == nullptr)
        return t;
    else
        return findMax(t->right);
}

AVLTreeNode* AVLTree::remove(Metadata* x, AVLTreeNode* t)
{
    AVLTreeNode* temp;

    // Element not found
    if(t == nullptr)
        return nullptr;

        // Searching for element
    else if(x->artist < t->data.at(0)->artist)
        t->left = remove(x, t->left);
    else if(x->artist > t->data.at(0)->artist)
        t->right = remove(x, t->right);

        // Element found
        // With 2 children
    else if(t->left && t->right)
    {
        temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->data.at(0), t->right);
    }
        // With one or zero child
    else
    {
        temp = t;
        if(t->left == nullptr)
            t = t->right;
        else if(t->right == nullptr)
            t = t->left;
        delete temp;
    }
    if(t == nullptr)
        return t;

    t->height = max(height(t->left), height(t->right))+1;

    // If AVLTreeNode is unbalanced
    // If left AVLTreeNode is deleted, right case
    if(height(t->left) - height(t->right) == 2)
    {
        // right right case
        if(height(t->left->left) - height(t->left->right) == 1)
            return singleLeftRotate(t);
            // right left case
        else
            return doubleLeftRotate(t);
    }
        // If right AVLTreeNode is deleted, left case
    else if(height(t->right) - height(t->left) == 2)
    {
        // left left case
        if(height(t->right->right) - height(t->right->left) == 1)
            return singleRightRotate(t);
            // left right case
        else
            return doubleRightRotate(t);
    }
    return t;
}

int AVLTree::height(AVLTreeNode* t)
{
    return (t == nullptr ? -1 : t->height);
}

int AVLTree::getBalance(AVLTreeNode* t)
{
    if(t == nullptr)
        return 0;
    else
        return height(t->left) - height(t->right);
}

void AVLTree::inorder(AVLTreeNode* t,std::vector<Metadata*> & list,std::string artist)
{
    if(t == nullptr)
        return;
    inorder(t->left,list,artist);
    for(Metadata* data : t->data) {
        std::string artist2 = data->artist;
        std::transform(artist2.begin(), artist2.end(), artist2.begin(), ::tolower);
        if (artist2 == artist) {
            list.push_back(data);
        }
    }
    inorder(t->right,list,artist);
}



void AVLTree::insert(Metadata* x)
{
    root = insert(x, root);
}

void AVLTree::remove(Metadata* x)
{
    root = remove(x, root);
}

std::vector<Metadata*> AVLTree::search(std::string artist)
{
    std::transform(artist.begin(), artist.end(), artist.begin(), ::tolower);
    std::vector<Metadata*> response;
    inorder(root,response,artist);
    return response;
}

void AVLTree::empty(){
    emptyAux(root);

}

void AVLTree::emptyAux(AVLTreeNode* t){
    if(t == nullptr)
        return;
    emptyAux(t->left);
    emptyAux(t->right);
    delete(t);
}
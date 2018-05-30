//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_AVLTREE_H
#define ODYSSEYSERVER_AVLTREE_H


#include "AVLTreeNode.h"

class AVLTree {
public:
    /**
     * elemento raíz del arbol
     */
    AVLTreeNode* root = nullptr;

    /**elimina los nodos por debajo del nodo al que se aplique
     *
     * @param t nodo al que se eliminan sus nodos hijos
     */
    void makeEmpty(AVLTreeNode* t);

    /**Agrega un elemento en el árbol
     *
     * @param x elemento por agregar
     */
    void insert(Metadata* x);

    /**elimina un elemento en el árbol
     *
     * @param x elemento por eliminar
     */
    void remove(Metadata* x);

    /**recorre los elementos en el árbol
    *
    *
    */
    std::vector<Metadata*> search(std::string);

    void empty();

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
    void inorder(AVLTreeNode* t,std::vector<Metadata*> & list,std::string album);
    void emptyAux(AVLTreeNode* t);
};


#endif //ODYSSEYSERVER_AVLTREE_H

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
    /**
     * elemento raíz
     */
    BTreeNode *root = nullptr;

    /**Agrega un elemento en el árbol
     *
     * @param val elemento por agregar
     */
    void insert(Metadata* val);

    /**Elimina un elemento de la lista a partir de un nodo específico
     *
     * @param val elemento por eliminar
     * @param myNode elemento a partir del cual eliminar
     */
    void _delete(Metadata* val,BTreeNode *myNode);

    /**Busca un elemento en el arbol
     *
     * @param elemento elemento buscado
     * @return nullptr en caso de no encontrarlo
     */
    std::vector<Metadata*> search(std::string elemento);
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
    std::vector<Metadata*> searchAux(std::string,BTreeNode *myNode);
};


#endif //ODYSSEYSERVER_BTREE_H

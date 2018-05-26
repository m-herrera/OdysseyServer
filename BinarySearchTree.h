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
    /*
     * Nodo raíz
     */
    TreeNode* root = nullptr;

    /**Agrega un elemento en el árbol
     *
     * @param userelemento por agregar
     * @return false si el elemento ya existe y true en
     * caso contrario
     */
    bool insert(User* user);

    /**
     * Busca un elemento en el árbol
     * @param username nombre del elemento buscado
     * @return nullptr en caso de no encontrarlo
     */
    User* get(std::string username);

    /**elimina un elemento en el árbol
     *
     * @param username nombre del elemento por eliminar
     */
    void delete_(std::string username);

};



#endif //ODYSSEYSERVER_BINARYSEARCHTREE_H

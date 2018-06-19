//
// Created by kenneth on 6/18/18.
//

#include "Create_xml.h"
void Create_xml::createtree(Node *node, Node *nodo_xml,char* name) {
    int repeticiones = node->freq;
    char valor = node->ch;
    //PONER VALOR AL NODO DEL XML con esos dos y el name
            if(node->right!= nullptr){
                //crear nuevo XML NODE Y PEGARLO A NODO_XML

                createtree(node->right,new Node,"right");
            }
            if(node->left!=nullptr){
                //CREAR NUEVO CMLNODE Y PEGARLO AL NODO XML
                createtree(node->left,new Node,"left");
            }
}
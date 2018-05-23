//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_BTreeNode_H
#define ODYSSEYSERVER_BTreeNode_H

#include "Metadata.h"

#define MAX 4
#define MIN 2

struct BTreeNode {
    Metadata* val[MAX + 1];
    int count;
    BTreeNode *link[MAX + 1];
};

#endif //ODYSSEYSERVER_BTreeNode_H

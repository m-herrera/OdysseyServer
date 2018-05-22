//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_BTREENODE_H
#define ODYSSEYSERVER_BTREENODE_H

#include "Metadata.h"

#define MAX 4
#define MIN 2

struct BtreeNode {
    Metadata* val[MAX + 1];
    int count;
    BtreeNode *link[MAX + 1];
};

#endif //ODYSSEYSERVER_BTREENODE_H

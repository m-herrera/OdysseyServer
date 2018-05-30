//
// Created by marco on 21/05/18.
//
#include "BTree.h"


std::vector<Metadata*> BTree::search(std::string k){
    std::transform(k.begin(),k.end(),k.begin(),::tolower);
    std::vector<Metadata*> result;
    search(result,k);
    return result;
}

// The main function that inserts a new key in this B-Tree
void BTree::insert(Metadata* k)
{
    // If tree is empty
    if (root == nullptr)
    {
        // Allocate memory for root
        root = new BTreeNode(t, true);
        root->keys[0].push_back(k);  // Insert key
        root->n = 1;  // Update number of keys in root
    }
    else // If tree is not empty
    {
        // If root is full, then tree grows in height
        if (root->n == 2*t-1)
        {
            // Allocate memory for new root
            BTreeNode *s = new BTreeNode(t, false);

            // Make old root as child of new root
            s->C[0] = root;

            // Split the old root and move 1 key to the new root
            s->splitChild(0, root);

            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (s->keys[0].at(0)->name < k->name)
                i++;
            s->C[i]->insertNonFull(k);

            // Change root
            root = s;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(k);
    }
}

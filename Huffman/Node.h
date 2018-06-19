//
// Created by dario1227 on 14/06/18.
//

#ifndef ODYSSEYSERVER_NODE_H
#define ODYSSEYSERVER_NODE_H

#include <boost/property_tree/ptree.hpp>

class Node
{
public:
    char ch;
    int freq;
    Node *left, *right;

    boost::property_tree::ptree toXML() {
        boost::property_tree::ptree tree;
        if (this == nullptr) {
            tree.put("freq", -1);
            return tree;
        }
        tree.put("ch", ch);
        tree.put("freq", freq);
        tree.push_back(std::make_pair("left", left->toXML()));
        tree.push_back(std::make_pair("right", right->toXML()));
        return tree;
    }
};
#endif //ODYSSEYSERVER_NODE_H

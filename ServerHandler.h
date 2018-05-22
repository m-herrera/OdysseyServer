//
// Created by marco on 13/05/18.
//

#ifndef ODYSSEYSERVER_SERVERHANDLER_H
#define ODYSSEYSERVER_SERVERHANDLER_H


#include <vector>
#include "User.h"
#include "BinarySearchTree.h"
#include "Metadata.h"
#include <fstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

class ServerHandler {
public:
    static BinarySearchTree* users;
    static const std::string trackPath;
    static const std::string metadataPath;
    static const std::string metadataTemplate;
    static Metadata songs[];
    static void updateUsers();
    static void loadUsers();

private:
    static void updateUsersAux(boost::property_tree::ptree* users, TreeNode* parent);
};


#endif //ODYSSEYSERVER_SERVERHANDLER_H

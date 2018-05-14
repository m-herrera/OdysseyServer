//
// Created by marco on 13/05/18.
//

#ifndef ODYSSEYSERVER_SERVERHANDLER_H
#define ODYSSEYSERVER_SERVERHANDLER_H


#include <vector>
#include "User.h"
#include "BinarySearchTree.h"

class ServerHandler {
public:
    static BinarySearchTree users;
    static const std::string trackPath;
    static const std::string usersPath;
    static void updateUsers();
    static void loadUsers();

private:
    static void updateUsersAux(boost::property_tree::ptree* users, TreeNode* parent);
};


#endif //ODYSSEYSERVER_SERVERHANDLER_H

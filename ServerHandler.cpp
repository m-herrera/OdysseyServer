//
// Created by marco on 13/05/18.
//

#include <fstream>
#include <boost/property_tree/json_parser.hpp>
#include "ServerHandler.h"

const std::string ServerHandler::trackPath  ="/home/marco/Desktop/Odyssey++/Tracks/";

const std::string ServerHandler::usersPath  ="/home/marco/Desktop/Odyssey++/users.json";

BinarySearchTree ServerHandler::users;

void ServerHandler::updateUsers(){
    boost::property_tree::ptree data;
    boost::property_tree::ptree* users2 = new boost::property_tree::ptree();
    updateUsersAux(users2,users.root);
    data.add_child("users",*users2);
    boost::property_tree::write_json(usersPath,data);
    delete(users2);
}

void ServerHandler::updateUsersAux(boost::property_tree::ptree* users, TreeNode* parent){
    if(parent == nullptr){
        return;
    }
    updateUsersAux(users,parent->left);
    users->push_back(std::make_pair("",parent->data->toJSON()));
    updateUsersAux(users,parent->right);
}

void ServerHandler::loadUsers() {

    boost::property_tree::ptree data;
    boost::property_tree::read_json(usersPath,data);
    for(boost::property_tree::ptree::value_type const& v : data.get_child("users")){
        User* usuario = new User();
        usuario->fromJSON(v.second);
        users.insert(usuario);
    }
}
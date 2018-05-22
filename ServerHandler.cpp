//
// Created by marco on 13/05/18.
//


#include "ServerHandler.h"

const std::string ServerHandler::trackPath  ="/home/marco/Desktop/Odyssey++/Tracks/";

const std::string ServerHandler::metadataPath  ="/home/marco/Desktop/Odyssey++/metadata.json";

const std::string ServerHandler::metadataTemplate  ="{\"users\" : [], \n  \"songs\" : []}";

Metadata ServerHandler::songs[] = {};

BinarySearchTree* ServerHandler::users = nullptr;

void ServerHandler::updateUsers(){
    boost::property_tree::ptree data;
    boost::property_tree::read_json(metadataPath,data);
    boost::property_tree::ptree* users2 = new boost::property_tree::ptree();
    updateUsersAux(users2,users->root);
    data.erase("users");
    data.add_child("users",*users2);
    boost::property_tree::write_json(metadataPath,data);
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
    if (users == nullptr){
        users = new BinarySearchTree();
    }
    std::ifstream f(metadataPath);
    if(!f.good()){
        std::ofstream metadata;
        metadata.open(ServerHandler::metadataPath, std::ios::out);
        metadata.write(metadataTemplate.data(),metadataTemplate.size());
    }
    boost::property_tree::ptree data;
    boost::property_tree::read_json(metadataPath,data);
    for(boost::property_tree::ptree::value_type const& v : data.get_child("users")){
        User* newUser = new User();
        newUser->fromJSON(v.second);
        users->insert(newUser);
    }
}
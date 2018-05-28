//
// Created by marco on 13/05/18.
//


#include "ServerHandler.h"

const std::string ServerHandler::trackPath  ="/home/marco/Desktop/Odyssey++/Tracks/";

const std::string ServerHandler::metadataPath  ="/home/marco/Desktop/Odyssey++/metadata.json";

const std::string ServerHandler::metadataTemplate  ="{\"users\" : [], \n  \"songs\" : []}";

int ServerHandler::NumberOfSongs = 0;

std::vector<Metadata*> ServerHandler::songs;

BTree* ServerHandler::songsNames = nullptr;

AVLTree* ServerHandler::songsArtists = nullptr;

BinarySearchTree* ServerHandler::users = nullptr;

const int ServerHandler::pageSize = 10;

const int ServerHandler::chunkSize = 40000;

std::string ServerHandler::sortBy = "name";

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

    boost::property_tree::ptree data;
    boost::property_tree::read_json(metadataPath,data);
    for(boost::property_tree::ptree::value_type const& v : data.get_child("users")){
        User* newUser = new User();
        newUser->fromJSON(v.second);
        users->insert(newUser);
    }
}

void ServerHandler::loadSongs() {

    if (songsNames == nullptr){
        songsNames = new BTree();
    }
    if (songsArtists == nullptr){
        songsArtists = new AVLTree();
    }

    boost::property_tree::ptree data;
    boost::property_tree::read_json(metadataPath,data);
    for(boost::property_tree::ptree::value_type const& v : data.get_child("songs")){
        Metadata* song = new Metadata();
        song->fromJSON(v.second);
        songsArtists->insert(song);
        songsNames->insert(song);
        songs.push_back(song);
        NumberOfSongs++;
    }
}

void ServerHandler::loadSetUp(){
    std::ifstream f(metadataPath);
    if(!f.good()){
        std::ofstream metadata;
        metadata.open(ServerHandler::metadataPath, std::ios::out);
        metadata.write(metadataTemplate.data(),metadataTemplate.size());
    }
    loadUsers();
    loadSongs();
}

void ServerHandler::updateSongs(){
    boost::property_tree::ptree data;
    boost::property_tree::read_json(metadataPath,data);
    boost::property_tree::ptree* songs = new boost::property_tree::ptree();
    updateSongsAux(songs,songsNames->root);
    data.erase("songs");
    data.add_child("songs",*songs);
    boost::property_tree::write_json(metadataPath,data);
    delete(songs);
}

void ServerHandler::updateSongsAux(boost::property_tree::ptree* songs, BTreeNode* parent){
    int i;
    if (parent) {
        for (i = 0; i < parent->count; i++) {
            updateSongsAux(songs,parent->link[i]);
            songs->push_back(std::make_pair("",parent->val[i + 1]->toJSON()));
        }
        updateSongsAux(songs,parent->link[i]);
    }
}

void ServerHandler::quickSort(){}

void ServerHandler::bubbleSort(){}

void ServerHandler::radixSort(){}
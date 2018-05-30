//
// Created by marco on 13/05/18.
//


#include "ServerHandler.h"
#include "Sorter.h"

const std::string ServerHandler::trackPath  ="/home/marco/Desktop/Odyssey++/Tracks/";

const std::string ServerHandler::metadataPath  ="/home/marco/Desktop/Odyssey++/metadata.json";

const std::string ServerHandler::metadataTemplate  ="{\"users\" : [], \n  \"songs\" : []}";

int ServerHandler::NumberOfSongs = 0;

std::vector<Metadata*> ServerHandler::songs;

std::vector<Metadata*> ServerHandler::sortedAlbums;

BTree* ServerHandler::songsNames = nullptr;

AVLTree* ServerHandler::songsArtists = nullptr;

BinarySearchTree* ServerHandler::users = nullptr;

const int ServerHandler::pageSize = 10;

const int ServerHandler::chunkSize = 327680;

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

    if (songsNames == nullptr)
        songsNames = new BTree(5);

    if (songsArtists == nullptr)
        songsArtists = new AVLTree();

    boost::property_tree::ptree data;
    boost::property_tree::read_json(metadataPath,data);
    for(boost::property_tree::ptree::value_type const& v : data.get_child("songs")){
        Metadata* song = new Metadata();
        song->fromJSON(v.second);
        songsArtists->insert(song);
        songsNames->insert(song);
        songs.push_back(song);
        insertAlbum(song);
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
    for(Metadata* data : ServerHandler::songs)
        songs->push_back(std::make_pair("",data->toJSON()));

    data.erase("songs");
    data.add_child("songs",*songs);
    boost::property_tree::write_json(metadataPath,data);
    delete(songs);
}


void ServerHandler::quickSort(){
    Sorter::quickSort(songs,0,NumberOfSongs-1);
}

void ServerHandler::bubbleSort(){
    Sorter::bubbleSort(songs,NumberOfSongs);
}

void ServerHandler::radixSort(){
    Sorter::radixSort(songs,NumberOfSongs);
}

void ServerHandler::insertAlbum(Metadata* insert){
    int i = 0;
    for(Metadata* song: sortedAlbums){
        if(song->album > insert->album){
            break;
        }
        i++;
    }
    sortedAlbums.insert(sortedAlbums.begin()+i,insert);
}

std::vector<Metadata*> ServerHandler::searchAlbums(std::string album) {
    std::transform(album.begin(),album.end(),album.begin(),::tolower);
    std::vector<Metadata*> response;
    for(Metadata* song : sortedAlbums){
        std::string album2 = song->album;
        std::transform(album2.begin(),album2.end(),album2.begin(),::tolower);
        if( album2 == album){
            response.push_back(song);
        }
    }
    return response;
}
//
// Created by marco on 13/05/18.
//


#include "ServerHandler.h"
#include "Sorter.h"
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

const std::string ServerHandler::trackPath  ="/home/marco/Desktop/Odyssey++/Tracks/";

int ServerHandler::NumberOfSongs = 0;

std::vector<Metadata*> ServerHandler::songs;

std::vector<Metadata*> ServerHandler::sortedAlbums;

BTree* ServerHandler::songsNames = nullptr;

AVLTree* ServerHandler::songsArtists = nullptr;

BinarySearchTree* ServerHandler::users = nullptr;

sql::Connection* ServerHandler::dbConnection = nullptr;

const int ServerHandler::pageSize = 10;

const int ServerHandler::chunkSize = 327680;

std::string ServerHandler::sortBy = "name";

void ServerHandler::loadSetUp(){
    loadUsers();
    loadMetadata();
}

void ServerHandler::loadUsers() {
    if (users == nullptr){
        users = new BinarySearchTree();
    }
    sql::Statement* stmt = dbConnection->createStatement();
    sql::ResultSet* result = stmt->executeQuery("SELECT * FROM Users");
    while(result->next()){
        User* newUser = new User();
        newUser->setUsername(result->getString("user_name"));
        newUser->setFirstName(result->getString("first_name"));
        newUser->setLastName(result->getString("last_name"));
        newUser->setPassword(result->getString("password"));
        newUser->setBirthday(result->getString("birthday"));
        users->insert(newUser);
    }
    stmt->close();
    result->close();
    delete(stmt);
    delete(result);
}

void ServerHandler::loadMetadata() {

    if (songsNames == nullptr)
        songsNames = new BTree(5);

    if (songsArtists == nullptr)
        songsArtists = new AVLTree();

    sql::Statement* stmt = dbConnection->createStatement();
    sql::ResultSet* result = stmt->executeQuery("SELECT * FROM Multimedia");
    while(result->next()){
        Metadata* metadata = new Metadata();
        metadata->name = result->getString("name");
        metadata->artist = result->getString("artist");
        metadata->album = result->getString("album");
        metadata->pathName = result->getString("path");
        metadata->lyrics = result->getString("lyrics");
        metadata->genre = result->getString("genre");
        metadata->year = result->getInt("year");
        metadata->type = result->getBoolean("type");

        songsArtists->insert(metadata);
        songsNames->insert(metadata);
        songs.push_back(metadata);
        insertAlbum(metadata);
        NumberOfSongs++;
    }
    stmt->close();
    result->close();
    delete(stmt);
    delete(result);
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
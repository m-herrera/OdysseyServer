//
// Created by marco on 13/05/18.
//

#ifndef ODYSSEYSERVER_SERVERHANDLER_H
#define ODYSSEYSERVER_SERVERHANDLER_H


#include <vector>
#include "User.h"
#include "BinarySearchTree.h"
#include "Metadata.h"
#include "BTree.h"
#include "AVLTree.h"
#include <fstream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

class ServerHandler {
public:
    static BinarySearchTree* users;
    static const std::string trackPath;
    static const std::string metadataPath;
    static const std::string metadataTemplate;
    static int NumberOfSongs;
    static std::vector<Metadata*> songs;
    static BTree* songsNames;
    static AVLTree* songsArtists;
    static const int pageSize;
    static const int chunkSize;
    static std::string sortBy;

    static void updateUsers();
    static void updateSongs();
    static void loadSetUp();
    static void quickSort();
    static void bubbleSort();
    static void radixSort();

private:
    static void loadUsers();
    static void loadSongs();
    static void updateUsersAux(boost::property_tree::ptree* users, TreeNode* parent);
    static void updateSongsAux(boost::property_tree::ptree* users, BTreeNode* parent);
};


#endif //ODYSSEYSERVER_SERVERHANDLER_H

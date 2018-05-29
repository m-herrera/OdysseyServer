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
    /**
     * estructura que almacena usuarios
     */
    static BinarySearchTree* users;

    /**
     * path de la carpeta donde se almacenan las canciones
     */
    static const std::string trackPath;

    /**
     * path del .json donde se almacenará la metadata
     */
    static const std::string metadataPath;

    /**
     * estructura default del .json con la metadata,
     * en caso de que el .json no exista
     */
    static const std::string metadataTemplate;

    /**
     * cantidad de canciones en el servidor
     */
    static int NumberOfSongs;

    /**
     * lista de canciones en el servidor según su álbum
     */
    static std::vector<Metadata*> songs;

    static std::vector<Metadata*> sortedAlbums;

    /**
     * estructura que almacena canciones según su nombre
     */
    static BTree* songsNames;

    /**
     * estructura que almacena canciones según su artista
     */
    static AVLTree* songsArtists;

    /**
     * tamaño de una pagina para lazyloading en el cliente
     */
    static const int pageSize;

    /**
     * tamaño de los chunks para el streaming
     */
    static const int chunkSize;

    /**
     * tipo de ordenamiento por default
     */
    static std::string sortBy;

    /**
     * actualiza los json con los usuarios en las
     * estructuras dinámicas
     */
    static void updateUsers();

    /**actualiza los json con las canciones en las
     * estructuras dinámicas
     */
    static void updateSongs();

    /**
     * carga los usuarios y las canciones de los archivos
     * json a las estructuras dinámicas
     */
    static void loadSetUp();

    static void insertAlbum(Metadata*);

    static std::vector<Metadata*> searchAlbums(std::string);

    /**
     * ordena la lista de canciones mediante quicksort
     */
    static void quickSort();

    /**
     * ordena la lista de canciones mediante bubblesort
     */
    static void bubbleSort();

    /**
     * ordena la lista de canciones mediante radixsort
     */
    static void radixSort();

private:
    static void loadUsers();
    static void loadSongs();
    static void updateUsersAux(boost::property_tree::ptree* users, TreeNode* parent);

};


#endif //ODYSSEYSERVER_SERVERHANDLER_H

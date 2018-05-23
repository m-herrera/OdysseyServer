//
// Created by marco on 12/05/18.
//

#ifndef ODYSSEYSERVER_REQUESTHANDLER_H
#define ODYSSEYSERVER_REQUESTHANDLER_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "User.h"
#include "ServerHandler.h"
#include <boost/property_tree/xml_parser.hpp>
#include "base64.h"


class RequestHandler {
public:
    static std::string handle(boost::property_tree::ptree xmlRequest);
    static std::string encryptPassword(std::string password);
//private:
    static std::string handleLogIn(boost::property_tree::ptree xmlRequest);
    static std::string handleRegistration(boost::property_tree::ptree xmlRequest);
    static std::string handleUpload(boost::property_tree::ptree xmlRequest);
    static boost::property_tree::ptree handleSongLibrary(boost::property_tree::ptree xmlRequest);
    static std::string handlePlay(boost::property_tree::ptree xmlRequest);
    static void generateSalt(char* buffer, int size);
    static boost::property_tree::ptree getSongs(int page);
    static boost::property_tree::ptree getChunk(std::string parh,int page);
};


#endif //ODYSSEYSERVER_REQUESTHANDLER_H

//
// Created by marco on 12/05/18.
//

#ifndef ODYSSEYSERVER_REQUESTHANDLER_H
#define ODYSSEYSERVER_REQUESTHANDLER_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "base64.h"


class RequestHandler {
public:
    static std::string handle(boost::property_tree::ptree xmlRequest);
    static std::string encryptPassword(std::string password);
private:
    static std::string handleLogIn(boost::property_tree::ptree xmlRequest);
    static std::string handleRegistration(boost::property_tree::ptree xmlRequest);
    static std::string handleUpload(boost::property_tree::ptree xmlRequest);
    static void generateSalt(char* buffer, int size);
};


#endif //ODYSSEYSERVER_REQUESTHANDLER_H

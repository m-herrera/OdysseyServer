//
// Created by marco on 12/05/18.
//

#include <boost/property_tree/xml_parser.hpp>
#include "RequestHandler.h"
#include "User.h"
#include "ServerHandler.h"



std::string RequestHandler::handle(boost::property_tree::ptree xmlRequest){
    std::string response = "";
    std::string opCode = "-1";
    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")){
        if (v.first != "<xmlattr>"){
            continue;
        }
        opCode =  v.second.get<std::string>("opcode");
        if(opCode == "1"){
            response = handleLogIn(xmlRequest);
        }
        else if(opCode == "2"){
            response = handleRegistration(xmlRequest);
        }
        else if(opCode == "3"){
            response = handleUpload(xmlRequest);
        }

    }
    boost::property_tree::ptree responseXML;
    responseXML.put("response",response);
    responseXML.put("response.<xmlattr>.opcode",opCode);
    std::ostringstream stream;
    boost::property_tree::write_xml(stream,responseXML);
    return stream.str();

}

std::string RequestHandler::handleLogIn(boost::property_tree::ptree xmlRequest){
    std::cout<< "Log In Request" <<std::endl;
    User* user = nullptr;
    std::string response = "invalid username or password";
    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")) {
        if (v.first == "username") {
            user = ServerHandler::users->get(v.second.data());
            if (user == nullptr) {
                break;
            }
        }else if(v.first == "password"){
            if(user == nullptr){
                response = "error";
            }
            else if (user->getPassword() == encryptPassword(v.second.data())) {
                response = "access granted";
            }
            break;
        }
    }
    return response;

}

std::string RequestHandler::handleRegistration(boost::property_tree::ptree xmlRequest){
    std::string response = "successful registration";
    User* newUser = new User(); 
    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")){
        if (v.first == "first_name"){
            newUser->setFirstName(v.second.data());
        }
        else if(v.first == "last_name"){
            newUser->setLastName(v.second.data());
        }
        else if(v.first == "username"){
            newUser->setUsername(v.second.data());
        }
        else if(v.first == "password"){
            std::string encryptedPassword = encryptPassword(v.second.data());
            newUser->setPassword(encryptedPassword);
        }
        else if(v.first == "age"){
            newUser->setAge(std::stoi(v.second.data()));
        }
        else if(v.first == "genres"){
            std::vector<std::string> genres;
            for (auto& item : xmlRequest.get_child("genres"))
                genres.push_back(item.second.data());
            newUser->setGenres(genres);
        }
        else if(v.first == "friends"){
            std::vector<std::string> friends;
            for (auto& item : xmlRequest.get_child("friends"))
                friends.push_back(item.second.data());
            newUser->setFriends(friends);
        }
    }
    if(!ServerHandler::users->insert(newUser)){
        response = "username already exists";
    }
    ServerHandler::updateUsers();
    return response;
}

std::string RequestHandler::handleUpload(boost::property_tree::ptree xmlRequest){
    std::cout<< "Upload Request" <<std::endl;
    std::ofstream trackFile;
    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")){
        if(v.first == "name"){
            trackFile.open(ServerHandler::trackPath + v.second.data().data(), std::ios::out);
        }
        else if( v.first == "content") {
            std::string rawData = base64_decode(v.second.data());
            trackFile.write(rawData.data(), rawData.size());
        }
    }
    trackFile.close();
    return "successful upload";
}

std::string RequestHandler::encryptPassword(std::string password){
    int size = password.size();
    int ascii[size];
    int index = 0;
    int sum = 0;
    for(char character : password){
        ascii[index] = int(character);
        index++;
        sum+= int(character);
    }
    int offset = size % sum;
    std::string response = "";
    for(index = 0; index < size; index++){
        char asciiCharacter= ascii[index] + offset;
        response += asciiCharacter;
    }
    char salt[size*3];
    generateSalt(salt,size*3);
    unsigned char data[response.size()];
    std::copy( response.begin(), response.end(), data);
    data[response.length()] = 0;
    response = base64_encode(data,response.size());
    //response.append(salt);
    return response;
}

void RequestHandler::generateSalt(char *buffer, const int size) {
    static const char alphanum[] =
            "0123456789"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < size; ++i) {
        buffer[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    buffer[size] = 0;
}
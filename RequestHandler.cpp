//
// Created by marco on 12/05/18.
//

#include "RequestHandler.h"


std::string RequestHandler::handle(boost::property_tree::ptree xmlRequest){
    boost::property_tree::ptree response;
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
        else if(opCode == "4"){
            response = handleSongLibrary(xmlRequest);
        }
        else if(opCode == "5"){
            response = handlePlay(xmlRequest);
        }

    }
    boost::property_tree::ptree responseXML;
    responseXML.put_child("response",response);
    responseXML.put("response.<xmlattr>.opcode",opCode);
    std::ostringstream stream;
    boost::property_tree::write_xml(stream,responseXML);
    return stream.str();

}

boost::property_tree::ptree RequestHandler::handleLogIn(boost::property_tree::ptree xmlRequest){
    std::cout<< "Log In Request" <<std::endl;
    User* user = nullptr;
    boost::property_tree::ptree response;

    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")) {
        if (v.first == "username") {
            user = ServerHandler::users->get(v.second.data());
            if (user == nullptr) {
                response.put("error",false);
                response.put("description","invalid username or password");
                response.put("status",false);
                break;
            }
        }else if(v.first == "password"){
            if(user == nullptr){
                response.put("error",true);
            }
            else if (user->getPassword() == encryptPassword(v.second.data())) {
                response.put("error",false);
                response.put("description","access granted");
                response.put("status",true);
            }else{
                response.put("error",false);
                response.put("description","invalid username or password");
                response.put("status",false);
            }
            break;
        }
    }
    return response;

}

boost::property_tree::ptree RequestHandler::handleRegistration(boost::property_tree::ptree xmlRequest){
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

    boost::property_tree::ptree response;
    response.put("error",false);

    if(!ServerHandler::users->insert(newUser)){
        response.put("description","username already exists");
        response.put("status",false);
    }else{
        response.put("description","successful registration");
        response.put("status",true);
    }
    ServerHandler::updateUsers();
    return response;
}

boost::property_tree::ptree RequestHandler::handleUpload(boost::property_tree::ptree xmlRequest){
    std::cout<< "Upload Request" <<std::endl;
    std::ofstream trackFile;
    ServerHandler::NumberOfSongs ++;
    trackFile.open(ServerHandler::trackPath +"Track"+ std::to_string(ServerHandler::NumberOfSongs), std::ios::out);
    Metadata* song = new Metadata();
    song->pathName = "Track"+std::to_string(ServerHandler::NumberOfSongs);
    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")){
        if(v.first == "name"){
            song->name = v.second.data();
        }
        else if(v.first == "artist"){
            song->artist = v.second.data();
        }
        else if(v.first == "album"){
            song->album = v.second.data();
        }
        else if( v.first == "content") {
            std::string rawData = base64_decode(v.second.data());
            trackFile.write(rawData.data(), rawData.size());
        }
    }
    ServerHandler::songsNames->insert(song);
    ServerHandler::songsArtists->insert(song);
    ServerHandler::updateSongs();
    trackFile.close();

    boost::property_tree::ptree response;
    response.put("error",false);
    response.put("description","successful upload");
    response.put("status",true);

    return response;
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

boost::property_tree::ptree RequestHandler::handleSongLibrary(boost::property_tree::ptree xmlRequest){
    boost::property_tree::ptree responseXML;
    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")){
        if(v.first == "sortBy"){
            ServerHandler::sortBy = v.second.data();
        }
        else if(v.first == "sortWith"){
            if(v.second.data() == "quickSort"){
                ServerHandler::quickSort();
            }
            else if(v.second.data() == "bubbleSort"){
                ServerHandler::bubbleSort();
            }
            else if(v.second.data() == "radixSort"){
                ServerHandler::radixSort();
            }
        }
        else if(v.first == "page"){
            responseXML = getSongs(std::atoi(v.second.data().data()));
        }
    }
    return responseXML;
}

boost::property_tree::ptree RequestHandler::getSongs(int page){
    int index = 0;
    int songs = 0;

    if(page != 0){
        index = page*ServerHandler::pageSize;
    }
    boost::property_tree::ptree tree;
    boost::property_tree::ptree parent;
    for(int i = 0; i < ServerHandler::pageSize;i++){
        if (index >= ServerHandler::songs.size()){
            break;
        }
        tree.push_back(std::make_pair("song",ServerHandler::songs.at(index)->toXML()));
        index++;
        songs++;
    }

    int pages = (int)std::ceil((double)ServerHandler::songs.size()/(double)ServerHandler::pageSize);
    parent.put("numberOfSongs",songs);
    parent.put("pages",pages);
    parent.put("pageSize",ServerHandler::pageSize);
    parent.add_child("songs",tree);
    return parent;

}


boost::property_tree::ptree RequestHandler::handlePlay(boost::property_tree::ptree xmlRequest){
    boost::property_tree::ptree responseXML;
    Metadata* song = nullptr;
    for(boost::property_tree::ptree::value_type const& v : xmlRequest.get_child("request")){
        if(v.first == "name"){
            song = ServerHandler::songsNames->search(v.second.data());
            if (song == nullptr){
                responseXML.put("error",true);
                responseXML.put("description","song doesn't exist");

            }
        }
        else if(v.first == "chunk"){
            responseXML = getChunk(song->pathName,std::atoi(v.second.data().data()));
            responseXML.put("error",false);
            responseXML.put("description","success");
        }
    }

    return responseXML;
}

boost::property_tree::ptree RequestHandler::getChunk(std::string path,int chunk){

    std::fstream trackFile;
    trackFile.open(ServerHandler::trackPath +path, std::ios::in|std::ios::binary);

    if(!trackFile){}

    int seek = 0;
    int bytes = 0;
    if(chunk != 0){
        seek = chunk*ServerHandler::chunkSize;
    }

    trackFile.seekg(0, std::ios::end);
    int size = trackFile.tellg();
    trackFile.seekg(0, std::ios::beg);

    if(seek != 0) {trackFile.seekg(seek);}

    char* data = new char[ServerHandler::chunkSize];

    if(seek + ServerHandler::chunkSize > size){
        bytes = size-seek;
        trackFile.read(data,bytes);

    }else{
        bytes = ServerHandler::chunkSize;
        trackFile.read(data,bytes);
    }
    trackFile.close();

    boost::property_tree::ptree parent;
    int chunks = (int)std::ceil((double)size/(double)ServerHandler::chunkSize);
    parent.put("NumberOfBytes",bytes);
    parent.put("chunks",chunks);
    parent.put("chunkSize",ServerHandler::chunkSize);

    std::string strData(data, bytes);

        unsigned char newData[strData.size()];
    std::copy( strData.begin(), strData.end(), newData);
    newData[strData.length()] = 0;

    strData = base64_encode(newData,strData.size());
    parent.put("content",strData);

    delete[] data;
    return parent;

}


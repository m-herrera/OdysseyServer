//
// Created by marco on 26/05/18.
//

#include "Metadata.h"
#include "ServerHandler.h"
#include <mysql_connection.h>
#include <cppconn/statement.h>

void Metadata::toDB() {

    sql::Statement* stmt = ServerHandler::dbConnection->createStatement();
    std::string command = "INSERT INTO Multimedia (name,artist,album,path,lyrics,genre,year,type) VALUES ('"+
                          this->name+"','"+this->artist+"','"+this->album+"','"+this->pathName+"','"+this->lyrics+"','"+this->genre+"',"+std::to_string(this->year)+","+std::to_string(this->type)+")";

    stmt->execute(command);

    stmt->close();
    delete(stmt);
}

boost::property_tree::ptree Metadata::toXML() {

    boost::property_tree::ptree xml;
    xml.put("name", this->name);
    xml.put("album", this->album);
    xml.put("artist", this->artist);
    xml.put("lyrics", this->lyrics);
    xml.put("genre", this->genre);
    xml.put("year",this->year);
    return xml;
}

std::string Metadata::get(std::string param){
    if(param == "name"){
        return boost::algorithm::to_lower_copy(this->name);
    }
    else if(param == "album"){
        return boost::algorithm::to_lower_copy(this->album);
    }
    else if(param == "artist"){
        return boost::algorithm::to_lower_copy(this->artist);
    }
    else if(param == "genre"){
        return boost::algorithm::to_lower_copy(this->genre);
    }
}

//
// Created by marco on 21/05/18.
//

#ifndef ODYSSEYSERVER_METADATA_H
#define ODYSSEYSERVER_METADATA_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class Metadata{
public:
    std::string name = "";
    std::string artist = "";
    std::string album  = "";
    std::string pathName = "";

    /**carga un json en el objeto
     *
     * @param json
     */
    void fromJSON(boost::property_tree::ptree json) {

        for(boost::property_tree::ptree::value_type const& v : json){
            if (v.first == "name"){
                this->name = v.second.data();
            }
            else if(v.first == "artist"){
                this->artist = v.second.data();
            }
            else if(v.first == "album"){
                this->album = v.second.data();
            }
            else if(v.first == "pathName"){
                this->pathName = v.second.data();
            }

        }
    }
    /**crea un json a partir del objeto
     *
     * @return arbol que representa el json
     */
    boost::property_tree::ptree toJSON() {

        boost::property_tree::ptree json;
        json.put("name", this->name);
        json.put("album", this->album);
        json.put("artist", this->artist);
        json.put("pathName", this->pathName);
        return json;
    }

    /**crea un xml a partir del objeto
     *
     * @return arbol que representa el xml
     */
    boost::property_tree::ptree toXML() {

        boost::property_tree::ptree xml;
        xml.put("name", this->name);
        xml.put("album", this->album);
        xml.put("artist", this->artist);
        return xml;
    }

};



#endif //ODYSSEYSERVER_METADATA_H

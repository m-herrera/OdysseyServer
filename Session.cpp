//
// Created by Jasson Rodríguez Méndez.
//

#include <iostream>
#include "Session.h"
#include <boost/property_tree/xml_parser.hpp>

Session::Session(boost::asio::io_service *ioservice) : tcp_socket(*ioservice){}

void Session::start() {
    std::cout<<"Conectado"<<std::endl;
    tcp_socket.async_read_some(boost::asio::buffer(bytes), boost::bind(&Session::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::read_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    std::string request = "";
    request.append(bytes);
    std::cout<<"Request: " << bytes<<std::endl;
    std::istringstream is(request);
    if(!ec){
        boost::property_tree::ptree pt;
        try{
            boost::property_tree::read_xml(is, pt);
            std::string strResponse = request;

            std::cout<<strResponse<<std::endl;

            boost::asio::async_write(tcp_socket, boost::asio::buffer(strResponse),
                                     boost::bind(&Session::write_handler, this, boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));
        }catch(const boost::property_tree::xml_parser::xml_parser_error& ex){
            std::cout <<"NOT XML"<<std::endl;
            if (boost::asio::placeholders::bytes_transferred){
                std::cout <<"Nothing more to read"<<std::endl;
            }
            tcp_socket.async_read_some(boost::asio::buffer(bytes), boost::bind(&Session::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

        }
    }else if(ec.value() == 2){
        std::cout<<"Cliente desconectado"<<std::endl;
    }else{
        std::cout<<"Codigo de error: "<<ec<<std::endl;
        tcp_socket.async_read_some(boost::asio::buffer(bytes), boost::bind(&Session::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}

void Session::write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    if(!ec){
        std::cout<<"Request finalizado\n"<<std::endl;
        for(int b = 0; b < sizeof(bytes); b++) {
            bytes[b] = '\0';
        }
        tcp_socket.async_read_some(boost::asio::buffer(bytes), boost::bind(&Session::read_handler, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }else{
        std::cout<<"Error de escritura: "<<ec<<std::endl;
    }
}
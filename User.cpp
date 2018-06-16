//
// Created by marco on 13/05/18.
//

#include <cppconn/statement.h>
#include "User.h"
#include "ServerHandler.h"
//#include <mysql_connection.h>

const std::string &User::getFirstName() const {
    return firstName;
}

void User::setFirstName(const std::string &firstName) {
    User::firstName = firstName;
}

const std::string &User::getLastName() const {
    return lastName;
}

void User::setLastName(const std::string &lastName) {
    User::lastName = lastName;
}

const std::string &User::getUsername() const {
    return username;
}

void User::setUsername(const std::string &username) {
    User::username = username;
}

const std::string &User::getPassword() const {
    return password;
}

void User::setPassword(const std::string &password) {
    User::password = password;
}

const std::vector<std::string> &User::getGenres() const {
    return genres;
}

void User::setGenres(const std::vector<std::string> &genres) {
    User::genres = genres;
}

const std::vector<std::string> &User::getFriends() const {
    return friends;
}

void User::setFriends(const std::vector<std::string> &friends) {
    User::friends = friends;
}

std::string User::getBirthday() const {
    return birthday;
}

void User::setBirthday(std::string birthday) {
    User::birthday = birthday;
}


void User::toDB() {

    sql::Statement* stmt = ServerHandler::dbConnection->createStatement();
    std::string command = "INSERT INTO Users (user_name,first_name,last_name,password,birthday) VALUES ('"+
        this->username+"','"+this->firstName+"','"+this->lastName+"','"+this->password+"','"+this->birthday+"')";

    stmt->execute(command);

    stmt->close();
    delete(stmt);
}

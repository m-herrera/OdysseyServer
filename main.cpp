#include <boost/asio.hpp>
#include <cppconn/driver.h>
#include "Server.h"
#include <cppconn/statement.h>
int main() {
    sql::Driver *driver;

    driver = get_driver_instance();
    ServerHandler::dbConnection = driver->connect("tcp://127.0.0.1:3306","root","root");
    ServerHandler::dbConnection->setSchema("OdysseyDB");

    /*
    sql::Statement* stmt = ServerHandler::dbConnection->createStatement();
    stmt->execute("TRUNCATE TABLE Multimedia");
    stmt->execute("TRUNCATE TABLE Users");
    */

    boost::asio::io_service ioservice;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 2000);

    Server server(endpoint, &ioservice);
    ServerHandler::loadSetUp();
    srand(time(nullptr));
    ioservice.run();

    return 0;

}
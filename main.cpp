#include <boost/asio.hpp>
#include "Server.h"
#include "User.h"
#include "ServerHandler.h"

int main() {

    boost::asio::io_service ioservice;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 2000);

    Server server(endpoint, &ioservice);
    ServerHandler::loadUsers();
    srand(time(nullptr));
    ioservice.run();
    return 0;
}
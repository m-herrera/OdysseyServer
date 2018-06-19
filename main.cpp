#include <boost/asio.hpp>
#include <cppconn/driver.h>
#include "Server.h"
#include "Raid5_controller/GOD_controller.h"
#include <cppconn/statement.h>

void writefile() {
//    FILE *iFile2 =  fopen("/home/kenneth/Desktop/videoplayback", "rb");
//    fseek(iFile2, 0, SEEK_END);
//    long lSize = ftell(iFile2);
//    rewind(iFile2);
//    char* buffer = (char *) malloc(sizeof(char) * lSize);
//    fread(buffer, 1, lSize, iFile2);

    FILE *iFile1;
    iFile1 = fopen("JAson", "wb");
    char *lol = GOD_controller::get_file("VIDEO");
    fwrite(lol, 1, 1970176 * 2, iFile1);
}
int main() {
//writefile();
    sql::Driver *driver;

    driver = get_driver_instance();
    ServerHandler::dbConnection = driver->connect("tcp://127.0.0.1:3306", "root", "kennet117s");
    ServerHandler::dbConnection->setSchema("OdysseyDB");


    sql::Statement* stmt = ServerHandler::dbConnection->createStatement();
    //stmt->execute("alter table Multimedia modify lyrics longtext");
    //stmt->execute("TRUNCATE TABLE Multimedia");
    //stmt->execute("TRUNCATE TABLE Users");
    //stmt->execute("TRUNCATE TABLE Auxiliar");

    boost::asio::io_service ioservice;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 2000);

    Server server(endpoint, &ioservice);
    ServerHandler::loadSetUp();
    srand(time(nullptr));
    ioservice.run();

    return 0;

}
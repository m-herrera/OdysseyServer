cmake_minimum_required(VERSION 3.9)
project(OdysseyServer)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)
find_package(Boost COMPONENTS system REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(OdysseyServer main.cpp Server.h Server.cpp Session.h Session.cpp base64.cpp base64.h RequestHandler.cpp RequestHandler.h Huffman/HuffmanCodeUltimate.cpp User.cpp User.h ServerHandler.cpp ServerHandler.h BinarySearchTree.cpp BinarySearchTree.h BinarySearchTreeNode.cpp BinarySearchTreeNode.h BTree.cpp BTreeNode.h BTree.h AVLTreeNode.h AVLTree.cpp AVLTree.h Metadata.h Sorter.cpp Sorter.h Metadata.cpp BTreeNode.cpp Huffman/HuffmanCodeUltimate.h Huffman/Node.h Raid5_controller/Existence_controller.cpp Raid5_controller/Existence_controller.h Raid5_controller/file_controller.cpp Raid5_controller/file_controller.h Raid5_controller/GOD_controller.cpp Raid5_controller/GOD_controller.h)
    target_link_libraries(OdysseyServer ${Boost_LIBRARIES})
endif()

target_link_libraries (OdysseyServer ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (OdysseyServer mysqlcppconn)
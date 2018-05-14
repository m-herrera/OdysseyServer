cmake_minimum_required(VERSION 3.9)
project(OdysseyServer)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)
find_package(Boost COMPONENTS system REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(OdysseyServer main.cpp Server.h Server.cpp Session.h Session.cpp base64.cpp base64.h RequestHandler.cpp RequestHandler.h User.cpp User.h ServerHandler.cpp ServerHandler.h BinarySearchTree.cpp BinarySearchTree.h BinarySearchTreeNode.cpp BinarySearchTreeNode.h)
    target_link_libraries(OdysseyServer ${Boost_LIBRARIES})
endif()

target_link_libraries (OdysseyServer ${CMAKE_THREAD_LIBS_INIT})

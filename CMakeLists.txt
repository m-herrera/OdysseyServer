cmake_minimum_required(VERSION 3.9)
project(OdysseyServer)

set(CMAKE_CXX_STANDARD 11)

find_package (Threads)
#set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(OdysseyServer main.cpp Server.h Server.cpp Session.h Session.cpp)
    target_link_libraries(OdysseyServer ${Boost_LIBRARIES})
endif()

target_link_libraries (OdysseyServer ${CMAKE_THREAD_LIBS_INIT})

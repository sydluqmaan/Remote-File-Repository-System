cmake_minimum_required(VERSION 3.30)
project(RFR_SERVER)

set(CMAKE_CXX_STANDARD 20)

find_package(Crow CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(nlohmann_json REQUIRED)

add_executable(RFR_SERVER main.cpp
        networking.cpp
        networking.h
        authentication.cpp
        authentication.h
        dbInterface.cpp
        dbInterface.h
        configInterface.cpp
        configInterface.h
        fileInterface.cpp
        fileInterface.h)

target_link_libraries(RFR_SERVER
        PRIVATE
        Crow::Crow
        Boost::system
        Boost::thread
        ws2_32
        OpenSSL::SSL
        OpenSSL::Crypto
        nlohmann_json::nlohmann_json)
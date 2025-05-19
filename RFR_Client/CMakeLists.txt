cmake_minimum_required(VERSION 3.16)
project(RFR_CLIENT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

include_directories("D:/vcpkg/packages/rapidjson_x64-windows/include")

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(RFR_CLIENT
    src/main.cpp
    src/cli.cpp
    src/commandHandler.cpp
    src/configInterface.cpp
    src/networking.cpp
    src/authentication.cpp
    src/JSONUtilities.cpp

    include/CLI11.hpp
    include/cli.h
    include/commandHandler.h
    include/configInterface.h
    include/networking.h
    include/authentication.h
    include/JSONUtilities.h
)

target_link_libraries(RFR_CLIENT
    CURL::libcurl
    nlohmann_json::nlohmann_json
    ws2_32
    wsock32
)

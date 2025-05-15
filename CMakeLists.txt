cmake_minimum_required(VERSION 3.20)
project(crmautoservice LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(crmautoservice
        main.cpp
        Menu.cpp
        ServiceManager.cpp
        Utils.cpp
        DataStructures.cpp # Додано новий файл
)
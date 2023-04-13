cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

project(project)

include_directories(headers)

# Установка списка исходных файлов
set(SOURCES
    src/main.cpp
    src/EchoOperation.cpp
    src/CatOperation.cpp
    src/UniqOperation.cpp
    src/Parser.cpp
    src/Conveyor.cpp
)

# Добавление исполняемого файла
add_executable(project ${SOURCES})
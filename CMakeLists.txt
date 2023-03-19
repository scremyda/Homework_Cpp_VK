cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)


project(my_project)

include_directories(headers)

# Установка списка исходных файлов
set(SOURCES
    src/main.cpp
    src/Parser.cpp
    src/ErrorProcessing.cpp
)

# Добавление исполняемого файла
add_executable(my_project ${SOURCES})
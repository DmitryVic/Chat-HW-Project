cmake_minimum_required(VERSION 3.10)
project(Chat)

# СПринудительно установить стандарт c++ 20
set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавить исходники
add_executable(Chat 
    src/main.cpp 
    src/User.cpp
    )

# Подключить заголовки из include/
target_include_directories(Chat PRIVATE include/)
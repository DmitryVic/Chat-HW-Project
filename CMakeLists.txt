cmake_minimum_required(VERSION 3.10)
project(Chat)

# Добавить исходники
add_executable(Chat main.cpp)

# Подключить заголовки из include/
target_include_directories(Chat PRIVATE include/)
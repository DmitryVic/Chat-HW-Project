cmake_minimum_required(VERSION 3.10)
project(Chat)

# СПринудительно установить стандарт c++ 20
# Исправление опечатки в STANDART -> STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Настройки только для MSVC
# Для MinGW в Windows
# Решает проблему с локализацией
if(MINGW)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# Добавить исходники
add_executable(Chat 
    src/main.cpp 
    src/user.cpp
    src/database.cpp
    src/chatPrivate.cpp
    src/chathared.cpp
    src/interactionChatPrvate.cpp
    src/interactionChatHared.cpp
    )

# Подключить заголовки из include/
target_include_directories(Chat PRIVATE include/)
cmake_minimum_required(VERSION 3.10)
project(Chat)

# Генерация compile_commands.json для cppcheck
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#путь для генерации
set(CMAKE_EXPORT_COMPILE_COMMANDS_FILE "${CMAKE_SOURCE_DIR}/compile_commands.json")

# СПринудительно установить стандарт c++ 17
# Исправление опечатки в STANDART -> STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для MinGW в Windows
# Решает проблему с локализацией
if(MINGW)
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# Если Линукс Решает проблему с локализацией
# передает компилятору флаг -DSET_GLOBAL_LOCALE_LINUX что SET_GLOBAL_LOCALE_LINUX существует в коде
# тоже самое если в коде написать #define SET_GLOBAL_LOCALE_LINUX
# -D(ИМЯ) сказать компилятору что макрос определен 
if(UNIX AND NOT APPLE)
    add_definitions(-DSET_GLOBAL_LOCALE_LINUX)
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
#target_include_directories(Chat PRIVATE include/)
# Явно укажите include-директории для cppcheck
target_include_directories(Chat PRIVATE 
    include/
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# Автоматический запуск CppCheck ТОЛЬКО в Debug
find_program(CPPCHECK cppcheck)
if(CPPCHECK AND CMAKE_BUILD_TYPE STREQUAL "Debug")  # AND CMAKE_BUILD_TYPE STREQUAL "Debug" только в дебагере
    add_custom_target(cppcheck ALL
        COMMAND ${CPPCHECK} 
            --project=${CMAKE_BINARY_DIR}/compile_commands.json
            --enable=warning,performance,portability,style
            --suppress=missingIncludeSystem
            --suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck-suppressions
            --inline-suppr
            --check-level=exhaustive
        COMMENT "Запуск CppCheck (только в Debug-сборке)..."
    )
endif()

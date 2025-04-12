#pragma once
#include <memory>
#include <string>
#include <vector>

namespace autorization {
    class User;

    // Создает обьект User и добавляет его в Database
    // Проверяет логин на уникальность и данные на пустоту
    // возвращает указатель на пользователя если он создан или nullptr  !!
    std::shared_ptr<User> regUser(std::string login, std::string pasword, std::string name);

    // Авторизует пользователя по логину и паролю
    // возвращает указатель на пользователя если он найден
    // если не найден, то nullptr !!
    std::shared_ptr<User> autorizationUser(std::string login, std::string pasword);

}
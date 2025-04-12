#pragma once
#include <string>
#include <vector>
#include <memory>

// для хранения указателей на класс User
class User;

// Хранит список всех участников и прочую информацию, если потребуется
class Database
{
private:
    //Список пользователей
    std::vector<std::shared_ptr<User>> usersInChat;
public:
    Database();
    ~Database();

    // Добавить пользовател
    // вернет true - при успехе, false - при ошибке
    // !! Обязательно добавить проверку на уникальность логина!! Логин уникален!!
    bool setUser(std::shared_ptr<User> user);

    // Получить список всех пользователей
    // !! Проверять на пустоту nullptr !!
    std::vector<std::shared_ptr<User>> getAllUsersInChat() const;

    // Получить указатель на пользователя по логину (уникален для каждого)
    // !! Проверять на пустоту nullptr !!
    std::shared_ptr<User> getOneUserByLogin(std::string login) const;


};



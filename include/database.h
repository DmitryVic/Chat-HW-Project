#pragma once
#include <string>
#include <vector>
#include <memory>

// для хранения указателей на класс User
class User;

// Хранит список всех участников, регистрирует и логирует пользователей
class Database
{
private:
    //Список пользователей
    std::vector<std::shared_ptr<User>> usersInChat;
public:
    Database();
    ~Database();

    // Добавить пользовател принимает и временные, и существующие объекты
    void setUser(std::shared_ptr<User> user);

    // Получить список всех пользователей
    std::vector<std::shared_ptr<User>> getAllUsersInChat() const;

    // Получить указатель на пользователя по логину (уникален для каждого)
    std::shared_ptr<User> getOneUserByLogin(const std::string &login) const;

    
    // Создает объект User и добавляет его в usersInChat
    // Возвращает shared_ptr<User> при успехе или nullptr при ошибке
    std::shared_ptr<User> regUser(
        const std::string& login,
        const std::string& password,
        const std::string& name
    );

    // Возвращает shared_ptr<User> при успехе или nullptr при ошибке
    std::shared_ptr<User> autorizUser(
        const std::string& login,
        const std::string& password
    );
};



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

    // Добавить пользовател принимает и временные, и существующие объекты
    // !! Проверка на уникальность логина осуществляется в классе User, можно использовать без проверок
    void setUser(std::shared_ptr<User> user);

    // Получить список всех пользователей
    std::vector<std::shared_ptr<User>> getAllUsersInChat() const;

    // Получить указатель на пользователя по логину (уникален для каждого)
    // !! Проверять на пустоту nullptr !!
    std::shared_ptr<User> getOneUserByLogin(std::string login) const;


};



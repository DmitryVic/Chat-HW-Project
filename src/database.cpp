#include "database.h"
#include "colorConsole.h"
#include "user.h" 
#include <iostream>



Database::Database()
{
    std::cout << _BLUE <<  "База данных запущена!" <<  _CLEAR << std::endl;
}

Database::~Database()
{
    
}

// Добавить пользовател
// вернет true - при успехе, false - при ошибке
// !! Проверка на уникальность логина осуществляется в классе User, можно использовать без проверок
void Database::setUser(std::shared_ptr<User>&& user){
    this->usersInChat.push_back(user);
}

// Получить список всех пользователей
std::vector<std::shared_ptr<User>> Database::getAllUsersInChat() const{
    return this->usersInChat;
}

// Получить указатель на пользователя по логину (уникален для каждого)
// !! Проверять на пустоту nullptr !!
std::shared_ptr<User> Database::getOneUserByLogin(std::string login) const{
    //если список пользовватель пуст - nullptr
    if (this->usersInChat.empty())
    {
        return nullptr;
    }

    // Проверка, есть ли пользователь с таким логином, если да, то возвращаем указатель на него
    for (const auto& user : usersInChat) {
        if (user->getLogin() == login) {
            return user;
        }
    }

    // не нашли пользователя возвращаем nullptr
    return nullptr;
    
}
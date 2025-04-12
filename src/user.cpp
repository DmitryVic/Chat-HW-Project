#include "user.h"
#include "chat.h"
#include "database.h"
#include "exept.h"
#include <exception>


User::User(std::string login, std::string pasword, std::string name, std::weak_ptr<Database> dataB)
{
    // если хотябы одно поле пустое
    if (login.empty() || pasword.empty() || name.empty())
    {
        throw ErrorCreateUserData(); // исключение, пользователь не создан
    }
    else
    {
        // Получить shared_ptr
        if (dataB.expired()) {
            throw ErrorCreateNotDataB();
        }
        
        auto db = dataB.lock();  // Точно не nullptr проверка выше выдает исключение

        if (db->getOneUserByLogin(login)) {  // если пользователя нет, вернет nullptr
            // Пользователь с таким логином уже существует
            throw ErrorCreateUserExists();
        }
        else
        {
            // создаем пользователя, все нормально
            this->_login = login;
            this->_pasword = pasword;
            this->_name = name;
            this->_dataB = dataB;
        }
    }
}

User::~User()
{
    
}

// Получить логин
std::string User::getLogin() const{
    return this->_login;
}

// Получить имя
std::string User::getName() const{
    return this->_name;
}

// Получить список чатов пользователя
std::vector<std::shared_ptr<Chat>> User::getConnectionChatId() const{
    return this->_connectionChatId;
}
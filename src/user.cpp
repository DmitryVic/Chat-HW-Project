#include "user.h"
#include "chat.h"
#include "database.h"
#include "exept.h"
#include <exception>


User::User(std::string login, std::string pasword, std::string name): _login(login), _pasword(pasword), _name(name) {}

User::~User() {}

// Получить логин
std::string User::getLogin() const{
    return this->_login;
}

// Получить имя
std::string User::getName() const{
    return this->_name;
}

// Получить проль не безопасный
std::string User::getPass() const{
    return this->_pasword;
}


// Получить список чатов пользователя
std::vector<std::shared_ptr<Chat>> User::getConnectionChatId() const{
    return this->_connectionChatId;
}

// Добавить пользователя в чат общий или при личных сообщениях
// вернет true - при успехе, false - при ошибке
bool User::setChat(std::shared_ptr<Chat> chat){
    this->_connectionChatId.push_back(chat);
    return true; // Возвращаем true при успехе
}
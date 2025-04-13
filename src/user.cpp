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


// Получение и добавление в чаты для приваток
std::vector<std::shared_ptr<ChatPrivate>> User::getConnectionChatPrivate() const {
    return _connectChatPrivate;
}

bool User::setChat(std::shared_ptr<ChatPrivate> chat) {
    _connectChatPrivate.push_back(chat);
    return true;
}

// Получение и добавление в чаты для общих чатов
std::vector<std::shared_ptr<ChatHared>> User::getConnectionChatHared() const {
    return _connectChatHared;
}

bool User::setChat(std::shared_ptr<ChatHared> chat) {
    _connectChatHared.push_back(chat);
    return true;
}
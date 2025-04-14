#include "user.h"
#include "chat.h"
#include "database.h"
#include "exept.h"
#include <exception>
#include "chatPrivate.h"
#include "chathared.h"


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


// Получение чатов
std::vector<std::shared_ptr<ChatPrivate>> User::getConnectionChatPrivate() const {
    return _connectChatPrivate;
}


std::vector<std::shared_ptr<ChatHared>> User::getConnectionChatHared() const {
    return _connectChatHared;
}


//Добавление в чаты
bool User::setChat(std::shared_ptr<ChatPrivate> chat) {
    _connectChatPrivate.push_back(chat);
    return true;
}

bool User::setChat(std::shared_ptr<ChatHared> chat) {
    _connectChatHared.push_back(chat);
    return true;
}

// проверяет есть чаты с данным узером
bool User::userInChatsP(std::weak_ptr<User> user) const{
    size_t sizeConnectChatPrivate = this->_connectChatPrivate.size();
    if (sizeConnectChatPrivate != 0)                                    // если не пустой вектор
    {
        for (size_t i = 0; i < sizeConnectChatPrivate; i++)
        {
            if (this->_connectChatPrivate[i]->userInChat(user))     // если переданный юзер есть в даном чате, обращаемся к чату проверить
            {
                return true;
            }
        }
    }
    return false;
}
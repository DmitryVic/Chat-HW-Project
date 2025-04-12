#pragma once
#include "chat.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>

class ChatPrivate : public Chat
{
public:
    // при создни нужно указать пользователей для usersInChat, при этом historyChat будет пустым без истории
    // getAllMessage выводит сообщений нет
    ChatPrivate(std::weak_ptr<User> thisUser, std::weak_ptr<User> otherUser);
    ~ChatPrivate();
    
    // Должен передать количество участников в ChatHared или имя пользователя
    // добавить дополнительные поля для классов - счетчик для ChatHared, ptr для ChatPrivate
    // !!! проверять на пустоту historyChat в функцииt, проверять на пустоту string при вызове
    std::string showUsers() const override;

    // Должен предать все сообщения из historyChat, форматируя текст относительно пользователя User, тоесть того, кто открыл чат
    // !!! проверять на пустоту historyChat в функцииt, проверять на пустоту string при вызове
    std::string getAllMessage(std::weak_ptr<User> user) const override;

    // Указатель взять из dataBace shared_ptr и из него сделать weak_ptr
    // Добавить пользователя в чат общий или при личных сообщениях
    // Добавить проверку на ChatPrivate, если в нем уже 2, то отклонить заявку
    // вернет true - при успехе, false - при ошибке
    bool setUsersInChat(std::weak_ptr<User> user) override;

    // Добавить сообщение
    // передаем указатель отправителя и само сообщение, записываем в historyChat
    // вернет true - при успехе, false - при ошибке
    bool addMessage(std::weak_ptr<User> sender, const std::string& msg) override;

};



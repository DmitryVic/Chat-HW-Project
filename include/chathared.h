#pragma once
#include "chat.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>

class ChatHared : public Chat
{
private:
std::string _nameChat;

public:
    // при создни нужно указать пользователей для usersInChat, при этом historyChat будет пустым без истории
    // ChatHared имеет название чата, можно создавать разные чаты с одними и темиже пользователями для разных целей
    // Любой может добавить пользователя, удалить никто не может
    ChatHared(std::weak_ptr<User> thisUser, std::weak_ptr<User> otherUser, std::string nameChat);
    ~ChatHared();
    
    // Должен передать количество участников в ChatHared или имя пользователя
    // добавить дополнительные поля для классов - счетчик для ChatHared, ptr для ChatPrivate
    // !!! проверять на пустоту historyChat в функцииt, проверять на пустоту string при вызове
    std::string showUsers() const override;

    // Получить число пользователей в чате
    std::string showUsersNamber() const;

    // Должен предать все сообщения из historyChat, форматируя текст относительно пользователя User, тоесть того, кто открыл чат
    // !!! проверять на пустоту historyChat в функцииt, проверять на пустоту string при вызове
    std::string getAllMessage(std::weak_ptr<User> user) const override;

    // Добавить сообщение
    // передаем указатель отправителя и само сообщение, записываем в historyChat
    // вернет true - при успехе, false - при ошибке
    bool addMessage(std::weak_ptr<User> sender, const std::string& msg) override;

    //Добавить еще пользователя в чат
    bool addUserInChat(std::weak_ptr<User> user);

    // Получить название чата
    std::string getNameChat() const;

};
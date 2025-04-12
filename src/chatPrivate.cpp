#include "chat.h"
#include "chatPrivate.h"
#include "exept.h"
#include "colorConsole.h"
#include "user.h" 
#include <iostream>

// Реализация конструктора и деструктора
ChatPrivate::ChatPrivate(std::weak_ptr<User> thisUser, std::weak_ptr<User> otherUser) 
: Chat() 
{
    if (usersInChat.size() < 2) {   // если уже содержит пользователей
        // Добавляем пользователей в чат
        usersInChat.push_back(thisUser);
        usersInChat.push_back(otherUser);
    } else {
        throw ErrorChat();
    }
}
ChatPrivate::~ChatPrivate() = default;

// можно будет доработать полд вывод собеседника, передать weak_ptr<User> того, кто зашел в чат через БД и логин юзера но нужно заменить chat или убрать
std::string ChatPrivate::showUsers() const{
    std::string out = "";
    auto u1 = usersInChat[0].lock();
    auto u2 = usersInChat[1].lock();
    if (u1 && u2 ) {
        out += _BLUE;
        out += "Приватный чат: ";
        out += u1->getName();
        out += " и ";
        out += u2->getName();
        out += _CLEAR;
        return out;
    }
    out += _MAGENTA;
    out += "Срок действия чата истек";
    out += _CLEAR;
    return out;
}


std::string ChatPrivate::getAllMessage(std::weak_ptr<User> user) const{

}


bool ChatPrivate::setUsersInChat(std::weak_ptr<User> user){

}


bool ChatPrivate::addMessage(std::weak_ptr<User> sender, const std::string& msg){

}
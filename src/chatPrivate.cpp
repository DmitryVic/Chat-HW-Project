#include "chat.h"
#include "chatPrivate.h"
#include "exept.h"
#include "colorConsole.h"
#include "user.h" 
#include <iostream>
#include <vector>
#include <utility>

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
    try
    {
        if (user.expired())                            // если sender указывает на не существующий объект
            throw ErrorChat();
        
        std::string output;
        if (this->historyChat.size() == 0)
        {
            output += _CYAN;
            output += "\nИстоия чата пуста. Напишите сообщение первым!\n\n";
            output += _CLEAR;
            return output;
        }
        else
        {
            size_t longHistoryChat = this->historyChat.size();
            for (size_t i = 0; i < longHistoryChat; i++)
            {
                // указатель на пользователя в historyChat и user привожу к shared_ptr и сравниваю
                // если это переданный пользователь, то меняю форматирование текста
                if (this->historyChat[i].first.lock() == user.lock())
                {
                    output += "\n";
                    output += _CYAN;
                    output += this->historyChat[i].first.lock()->getName(); // Добавляю имя пользователя в вывод
                    output += _CLEAR;
                    output += "\t";
                    output += this->historyChat[i].second;
                }
                else{
                    output += "\n";
                    output += _YELLOW;
                    output += this->historyChat[i].first.lock()->getName(); // Добавляю имя пользователя в вывод
                    output += _CLEAR;
                    output += "\t";
                    output += this->historyChat[i].second;
                }
            }
            return output;
        }
    }
    catch (const ErrorChat& e) {                        //обрабатываем исключения, дополня их
        std::cerr << _RED << "(Код ошибки 5) Пользователь удален: " << e.what() << _CLEAR << std::endl;
    } 
    



}


bool ChatPrivate::addMessage(std::weak_ptr<User> sender, const std::string& msg){
    try
    {
        if (sender.expired())                            // если sender указывает на не существующий объект
            throw ErrorChat();

        if (msg.size() == 0)                            // если сообщение пустое
            throw ErrorChatMess();
        
        this->historyChat.emplace_back(sender, msg);    //emplace_back - избегает лишнего копирования, сразу передает значения
        return true;
    }
    catch (const ErrorChatMess& e) {                    //обрабатываем исключения, дополня их
        std::cerr << _RED << "(Код ошибки 3) Не верные данные: " << e.what() << _CLEAR << std::endl;
    }
    catch (const ErrorChat& e) {                        //обрабатываем исключения, дополня их
        std::cerr << _RED << "(Код ошибки 4) Отправитель не найден: " << e.what() << _CLEAR << std::endl;
    } 
    return false;
}
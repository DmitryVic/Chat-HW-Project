#include "chathared.h"
#include "chat.h"
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include "exept.h"
#include "user.h" 
#include "colorConsole.h"
#include <iostream>


// Конструктор Деструктор
ChatHared::ChatHared(std::weak_ptr<User> thisUser, std::weak_ptr<User> otherUser, std::string nameChat){
    if (nameChat.size() == 0)
        throw ErrorChat();                              // Пустое название чата

    if (thisUser.expired() || otherUser.expired())      // если указывает на не существующий объект
        throw ErrorChat();

    usersInChat.push_back(thisUser);                    // Добавляем пользователей в чат
    usersInChat.push_back(otherUser);
    this->_nameChat = nameChat;                         // Название чата
}
ChatHared::~ChatHared() = default;


// Передать string пользователей
std::string ChatHared::showUsers() const{
    std::string output;
    if (this->usersInChat.size() == 0){                  //вряд ли такое будет, но на всякий случай
        output = "Пользователей нет";
        return output;}

    size_t sizeUsersInChat = usersInChat.size();
    for (size_t i = 0; i < sizeUsersInChat; i++)
    {
        output += usersInChat[i].lock()->getName();     // Добавляем имя
        if (i + 1 != sizeUsersInChat)                   // если не последний в списке ", "
            output += ", ";
    }
    return output;
}

// Получить число пользователей в чате
std::string ChatHared::showUsersNamber() const{
    return std::to_string(this->usersInChat.size()); // to_string - явное преобразование в строку, нельзя передать size_t
}

// Получить все сообщения
std::string ChatHared::getAllMessage(std::weak_ptr<User> user) const{
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
    catch (const ErrorChat& e) {
        std::cerr << _RED << "(Код ошибки 6) Пользователь удален: " << e.what() << _CLEAR << std::endl;
        return _RED + std::string("Ошибка") + _CLEAR; // Возвращаем сообщение об ошибке
    }
    return ""; // Запасной вариант (технически недостижим)
}

// Добавить сообщение
bool ChatHared::addMessage(std::weak_ptr<User> sender, const std::string& msg){
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
        std::cerr << _RED << "(Код ошибки 7) Не верные данные: " << e.what() << _CLEAR << std::endl;
        return false;
    }
    catch (const ErrorChat& e) {                        //обрабатываем исключения, дополня их
        std::cerr << _RED << "(Код ошибки 8) Отправитель не найден: " << e.what() << _CLEAR << std::endl;
        return false;
    } 
    return false;
}

//Добавить еще пользователя в чат
bool ChatHared::addUserInChat(std::weak_ptr<User> user){
    try
    {
        if (user.expired())                             // если указывает на не существующий объект
            throw ErrorChat();
        usersInChat.push_back(user);                    // Добавляем пользователей в чат
        return true;
    }
    catch (const ErrorChat& e) {                        //обрабатываем исключения, дополня их
        std::cerr << _RED << "(Код ошибки 8) Отправитель не найден: " << e.what() << _CLEAR << std::endl;
        return false;
    } 
    return false;                                       // не достижимо, подстаховка
}

// Получить название чата
std::string ChatHared::getNameChat() const{
    return this->_nameChat;
}
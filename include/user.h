#pragma once
#include <string>
#include <vector>
#include <memory>
#include "database.h"


class ChatPrivate;
class ChatHared;

/*
Класс User взаимодействует с классами:
        Database                - создает данный клас и осуществляет логирование
        Chat    -> ChatPrivate     - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся приватным чатам Хранит. историю сообщений.
                -> ChatHared    - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся общим чатам. Хранит историю сообщений.
*/
class User
{
private:
    std::string _login;
    std::string _pasword;
    std::string _name;
    std::vector<std::shared_ptr<ChatPrivate>> _connectChatPrivate;
    std::vector<std::shared_ptr<ChatHared>> _connectChatHared;
public:
    // Передать логин, пароль, имя
    // Проверка на создание в БД, БД владееет пользователями, создание Юзера через нее
    User(std::string login, std::string pasword, std::string name);
    
    ~User();
    
    // Получить логин
    std::string getLogin() const;

    // Получить имя
    std::string getName() const;

    // Получить проль не безопасный
    std::string getPass() const;

    /*
    Хоел изначально реализовать методы ниже шаблонами, но как оказалось лучше
    показалось боле безопасно и более читаемо
    Изначально хранил в одном векторе общего интерфейса Chat, но можно вызывать только те методы, которые объявлены в этом базовом классе
    а для ChatHared есть дополнительный функционал и в данной реализации можно легко подсчитать приватные и общие чаты
    */

    // Получить список чатов пользователя
    std::vector<std::shared_ptr<ChatPrivate>> getConnectionChatPrivate() const;
    std::vector<std::shared_ptr<ChatHared>> getConnectionChatHared() const;

    // Добавить пользователя в чат общий или при личных сообщениях
    // вернет true - при успехе, false - при ошибке
    bool setChat(std::shared_ptr<ChatPrivate> chat);
    bool setChat(std::shared_ptr<ChatHared> chat);

};



#pragma once
#include <string>
#include <vector>
#include <memory>
#include "database.h"

// Исправлена ошибка объявления chat.h
class Chat;

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
    std::vector<std::shared_ptr<Chat>> _connectionChatId;
    std::weak_ptr<Database> _dataB; //База данных одна на всех, но требуется для получения списка пользователей
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

    // Получить список чатов пользователя
    std::vector<std::shared_ptr<Chat>> getConnectionChatId() const;

    // Добавить пользователя в чат общий или при личных сообщениях
    // вернет true - при успехе, false - при ошибке
    bool setChat(std::shared_ptr<Chat> chat);

};



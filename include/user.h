#pragma once
#include <string>
#include <vector>
#include <memory>
#include "database.h"

// Исправлена ошибка объявления chat.h
class Chat;

/*
Класс User взаимодействует с классами:
        Database                - обмен данными авторизации, должен хранить указатели на всех пользователей shared_ptr нужен в том числе для преобразования 
                                        в weak_ptr в классах Chat
        Chat    -> ChatPrivate     - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся приватным чатам Хранит. историю сообщений.
                -> ChatHared    - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся общим чатам. Хранит историю сообщений.
        Autorization            - Autorization - набор функций  в пространстве именa utorization, создает объект класса User, или осуществляет логирование пользователя по уже имеющимся объектам User
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
    // Осуществляет проверку на уникальность логина и пустоту файлов
    // иначе выдает исключения ErrorCreateUserExists, ErrorCreateUserData
    // weak_ptr<Database> требуется передать для поиска по базе данных такихе пользователе при создании
    User(std::string login, std::string pasword, std::string name, std::weak_ptr<Database> dataB);
    
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



#pragma once
#include <string>
#include <vector>
#include <memory>
#include "chat.h"

/*
Класс User взаимодействует с классами:
        Database                - обмен данными авторизации, должен хранить указатели на всех пользователей shared_ptr нужен в том числе для преобразования 
                                        в weak_ptr в классах Chat
        Chat    -> ChatPrivate     - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся приватным чатам Хранит. историю сообщений.
                -> ChatHared    - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся общим чатам. Хранит историю сообщений.
        Autorization            - Autorization создает объект данного класса, или осуществляет логирование пользователя по уже имеющимся объектам User
*/
class User
{
private:
    std::string _login;
    std::string _pasword;
    std::string _name;
    std::vector<std::shared_ptr<Chat>> _connectionChatId;
public:
    // Передать логин, пароль, имя
    User(std::string login, std::string pasword, std::string name);
    
    // Получить логин
    std::string getLogin() const;

    // Получить имя
    std::string getName() const;

    // Получить список чатов пользователя
    std::vector<std::shared_ptr<Chat>> getConnectionChatId() const;

    // Добавить пользователя в чат общий или при личных сообщениях
    // Добавить проверку на ChatPrivate, если в нем уже 2, то отклонить заявку
    // вернет true - при успехе, false - при ошибке
    bool setChat(std::shared_ptr<Chat>);

    ~User();
};



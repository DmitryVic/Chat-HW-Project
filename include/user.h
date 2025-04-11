#pragma once
#include <string>
#include <vector>
#include <memory>
#include "chat.h"

/*
Класс User взаимодействует с классами:
        Database                - обмен данными авторизации, обмен данными
        Chat -> ChatPrivate     - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся приватным чатам
                -> ChatHared    - объект User хранит указатели на чаты, что обеспечивает доступ к уже имеющимся общим чатам
        Autorization            - Autorization создает объект данного класса, или осуществляет логирование пользователя по уже имеющимся объектам User
*/

class User
{
private:
    unsigned int id;
    std::string _login;
    std::string _pasword;
    std::string _name;
    std::vector<std::shared_ptr<Chat>> _connectionChatId;
public:
    User(std::string login, std::string pasword, std::string name);
    ~User();
};



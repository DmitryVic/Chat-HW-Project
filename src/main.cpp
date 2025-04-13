#include <iostream>
#include "database.h"
#include "colorConsole.h"
#include "user.h"
#include "chatPrivate.h"
#include "chat.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    /*
    В данном файле должен быть реализован главный функционал
    
    (функция) главное меню
        выход
        зарегистрироваться
            (функция) регистрация
        залогиниться или назад
            открыть список чатов
                (функция) выбрать чат 
                (функция) назад
            открыть список контактов
                (функция) написать в личное сообщение в первый раз
                (функция) назад

    Классы:
        User - класс пользователя, хранит указатели на чаты, что обеспечивает доступ к ChatPrivate ChatHared
        Database - обмен данными авторизации, должен хранить указатели на всех пользователей shared_ptr
            создает пользователей и осуществляет их логирование
        Chat - родительский класс ChatPrivate, ChatHared
        ChatPrivate - объект User хранит указатели на чаты, что обеспечивает доступ к уже существующим приватным чатам
        ChatHared - объект User хранит указатели на чаты, что обеспечивает доступ к уже существующим общим чатам
        
    */
   
    setlocale(LC_ALL, "ru-RU.UTF-8");   // Русский вывод в консоле

    try 
    {
        std::shared_ptr<Database> database(new Database());


        cout << _GREEN <<  "Готов к работе" <<  _CLEAR << std::endl;

        auto user1 = database->regUser("login", "password", "name");
        if (user1) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }
        
        cout << "Имитирую регистрацию нового юзера" << endl;
        auto user2 = database->regUser("login2", "password", "name");
        if (user2) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }

        cout << "Имитирую логирование юзера" << endl;
        user1 = database->autorizUser("login", "password");
        if (user1) {
            std::cout << _GREEN << "Пользователь успешно авторизирован!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка авторизации пользователя\n" <<  _CLEAR;
        }

        // cout << "Пытаюсь создать юзера с неправильными данными" << endl;
        // user1 = autorization::regUser("", "", "", database);
        // if (user1) {
        //     std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        // } else {
        //     std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        // }
        
        // Создаем shared_ptr чата, передавая weak_ptr пользователей
        std::shared_ptr<Chat> chat1 = std::make_shared<ChatPrivate>(
            std::weak_ptr<User>(user1), 
            std::weak_ptr<User>(user2)
        );
        user1->setChat(chat1);
        user2->setChat(chat1);
        cout << "STOP" << endl;
        
    }
    catch(exception& e)
    {
        cout << e.what();
    }
    cout << "STOP" << endl;
    return 0;
}

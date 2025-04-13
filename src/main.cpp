#include <iostream>
#include "database.h"
#include "colorConsole.h"
#include "user.h"
#include "chatPrivate.h"
#include "chathared.h"
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

        auto user1 = database->regUser("login", "password", "Максим");
        if (user1) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }
        
        cout << "Имитирую регистрацию нового юзера" << endl;
        auto user2 = database->regUser("login2", "password", "Олег");
        if (user2) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }



        
        // Создаем shared_ptr чата, передавая weak_ptr пользователей
        std::shared_ptr<ChatPrivate> chat1 = std::make_shared<ChatPrivate>(
            std::weak_ptr<User>(user1), 
            std::weak_ptr<User>(user2)
        );
        user1->setChat(chat1);
        user2->setChat(chat1);
        

        cout << "\nПользователь 1 зашел в чат\n" << chat1->showUsers() << chat1->getAllMessage(user1) << endl;
        chat1->addMessage(user1, "Привет, как дела?");
        chat1->addMessage(user1, "Чего не отвечаешь?");
        cout << "\nПользователь 1 зашел в чат\n" << chat1->showUsers() << chat1->getAllMessage(user1) << endl;
        
        cout << "\nПользователь 2 зашел в чат\n" << chat1->showUsers() << chat1->getAllMessage(user2) << endl;
        chat1->addMessage(user2, "Привет, я был занят");
        cout << "\nПользователь 2 зашел в чат\n" << chat1->showUsers() << chat1->getAllMessage(user2) << endl;

        cout << "Имитирую регистрацию нового юзера" << endl;
        user2 = database->regUser("login3", "password", "Алена");
        if (user2) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }

        // Создаем shared_ptr чата, передавая weak_ptr пользователей
        std::shared_ptr<ChatHared> chat2 = std::make_shared<ChatHared>(
            std::weak_ptr<User>(user1), 
            std::weak_ptr<User>(user2),
            "Чат беседа"
        );
        user1->setChat(chat2);
        user2->setChat(chat2);
        
        cout << "\nПользователь 1 зашел в чат\n" << chat2->showUsers() << chat2->getAllMessage(user1) << " -  " << chat2->showUsersNamber() << endl;
        chat2->addMessage(user1, "Привет, как дела?");
        chat2->addMessage(user1, "Чего не отвечаешь?");
        cout << "\nПользователь 1 зашел в чат\n" << chat2->showUsers() << chat2->getAllMessage(user1) << " -  " << chat2->showUsersNamber() << endl;
        
        user2 = database->getOneUserByLogin("login2");
        chat2->addUserInChat(user2);
        user2->setChat(chat2);
        cout << "\nПользователь 2 зашел в чат\n" << chat2->showUsers() << chat2->getAllMessage(user2) << " -  " << chat2->showUsersNamber() << endl;
        chat2->addMessage(user2, "Привет, я был занят");
        cout << "\nПользователь 2 зашел в чат\n" << chat2->showUsers() << chat2->getAllMessage(user2) << " -  " << chat2->showUsersNamber() << endl;

        
    }
    catch(exception& e)
    {
        cout << e.what();
    }
    cout << "STOP" << endl;
    return 0;
}

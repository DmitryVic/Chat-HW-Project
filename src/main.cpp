#include <iostream>
#include "database.h"
#include "colorConsole.h"
#include "user.h"
#include "autorization.h"
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
        Database - обмен данными авторизации, должен хранить указатели на всех пользователей shared_ptr нужен в том числе для преобразования 
            в weak_ptr в классах Chat
        Chat - родительский класс ChatPrivate, ChatHared
        ChatPrivate - объект User хранит указатели на чаты, что обеспечивает доступ к уже существующим приватным чатам
        ChatHared - объект User хранит указатели на чаты, что обеспечивает доступ к уже существующим общим чатам
        
        Autorization - набор функций  в пространстве именa utorization, создает объект класса User, или осуществляет логирование пользователя по уже имеющимся объектам User
    */
   
    setlocale(LC_ALL, "ru-RU.UTF-8");   // Русский вывод в консоле

    try 
    {
        std::shared_ptr<Database> database(new Database());


        cout << _GREEN <<  "Готов к работе" <<  _CLEAR << std::endl;

        auto user1 = autorization::regUser("login", "password", "name", database);
        if (user1) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }
        
        cout << "Имитирую регистрацию нового юзера" << endl;
        user1 = autorization::regUser("login2", "password", "name", database);
        if (user1) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }

        cout << "Имитирую логирование юзера" << endl;
        user1 = autorization::autorizUser("login", "password", database);
        if (user1) {
            std::cout << _GREEN << "Пользователь успешно авторизирован!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка авторизации пользователя\n" <<  _CLEAR;
        }

        cout << "Пытаюсь создать юзера с неправильными данными" << endl;
        user1 = autorization::regUser("", "", "", database);
        if (user1) {
            std::cout << _GREEN << "Пользователь успешно создан!\n" <<  _CLEAR;
        } else {
            std::cout << _RED << "Ошибка создания пользователя\n" <<  _CLEAR;
        }
        
        
        
    }
    catch(exception& e)
    {
        cout << e.what();
    }
    cout << "STOP" << endl;
    return 0;
}

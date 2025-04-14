#include <iostream>
#include <memory>
#include "database.h"
#include "colorConsole.h"
#include "user.h"
#include "chatPrivate.h"
#include "chathared.h"
#include "chat.h"
#include <string>
#include <vector>
#include <limits> //Для  cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include "template.h"
#include "interactionChatPrvate.h"

using namespace std;




void chatStart(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){
    char menu = '9';

    while (menu != '0')
    {
        cout << _GREY_BG << "\n\n\t\tЗдраствуйте - " << userAuthorization->getName() << "\n" << _CLEAR << endl << endl;
        cout << "Для выбора введите значение."<< endl 
            << _CYAN << " Меню:" << _CLEAR << endl
            << "0 - Выход в главное меню;" << endl
            << "1 - Открыть список приватных чатов - написать пользователю;" << endl
            << "2 - Открыть список общих чатов - создать общий чат или зайти в имеющийся" << endl
            << "Ведите значение" << endl;
        cin >> menu;
        switch (menu)
        {
        case '0':
            cout << _GREEN << "Возврат в главное меню!" << _CLEAR;
            return;
        case '1':
            menuChatPrivate(db, userAuthorization);
            break;
        case '2':
            //menuChatHared(db, userAuthorization);
            break;
        default:
            cout << _YELLOW << "Не верно введено значение, попробуй еще раз" << _CLEAR << endl;
            break;
        }
    }
    
}

void authorization(shared_ptr<Database>& db){
    cout << _GREY_BG << "\n\n\t\tАвторизация\n" << _CLEAR << endl << endl;
    string login;
    string pass;

    cin.clear(); // Сбрасывает флаги ошибок
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищает буфер до новой строки

    cout << "Введите логин" << endl;
    getline(cin, login);

    cout << "Введите пароль" << endl;
    getline(cin, pass);
    
    auto userAuthorization = db->autorizUser(login, pass);
    if (!userAuthorization)
    {
        cout << _MAGENTA << "Не удалось авторизоваться, возврат в главное меню" << _CLEAR << endl;
        return;
    }
    else
    {
        cout << _GREEN << "Авторизация выполнена!" << _CLEAR;
        chatStart(db, userAuthorization);
    }
    
}

void reg(shared_ptr<Database>& db){
    cout << _GREY_BG << "\n\n\t\tРегистрация\n" << _CLEAR << endl << endl;
    string login;
    string pass;
    string name;

    cin.clear(); // Сбрасывает флаги ошибок
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищает буфер до новой строки

    cout << "Введите логин" << endl;
    getline(cin, login);

    cout << "Введите пароль" << endl;
    getline(cin, pass);

    cout << "Введите свое имя" << endl;
    getline(cin, name);

    auto userAuthorization = db->regUser(login, pass, name);
    if (!userAuthorization)
    {
        cout << _MAGENTA << "Не удалось зарегистрироваться, возврат в главное меню" << _CLEAR << endl;
        return;
    }
    else
    {
        cout << name << _GREEN << " - Вы успешно зарегистрировались" << _CLEAR;
        chatStart(db, userAuthorization);
    }    
}

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

    char menu = '9';
    shared_ptr<Database> database(new Database());
    cout << _GREEN <<  "Готов к работе" <<  _CLEAR << std::endl;

    while (menu != '0')
    {
        cout << _GREY_BG << "\n\n\t\tДобо пожаловать в чат!\n" << _CLEAR << endl << endl;
        cout << "Для выбора введите значение."<< endl 
            << _CYAN << " Меню:" << _CLEAR << endl
            << "0 - Закрыть приложение;" << endl
            << "1 - Авторизация;" << endl
            << "2 - Регистрация" << endl
            << "Ведите значение" << endl;
        cin >> menu;
        switch (menu)
        {
        case '0':
            cout << _GREEN << "Досвидания!" << _CLEAR;
            return 0;
        case '1':
            authorization(database);
            break;
        case '2':
            reg(database);
            break;
        default:
            cout << _YELLOW << "Не верно введено значение, попробуй еще раз" << _CLEAR << endl;
            break;
        }

    }
    
    
    return 0;
}

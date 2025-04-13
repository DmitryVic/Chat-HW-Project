#include <iostream>
#include "database.h"
#include "colorConsole.h"
#include "user.h"
#include "chatPrivate.h"
#include "chathared.h"
#include "chat.h"
#include <string>
#include <vector>
#include <limits> //Для  cin.ignore(numeric_limits<streamsize>::max(), '\n');

using namespace std;


void menuChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){

}

void openChatPrivate(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization, shared_ptr<ChatPrivate>& chatP){
    cout << _CYAN << "Зашли в приватный чат" << _CLEAR  << endl;
    cout << chatP->getAllMessage(userAuthorization) << endl;
    chatP->addMessage(userAuthorization, "Новое сообщение, для тестирования!");
    cout << chatP->getAllMessage(userAuthorization) << endl;

}

void  UserChoiceChatPrivate(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){
    vector<size_t> chatIndexList;                                        // для сохранения индексов чатов
    size_t userNamberInput = 999;                                    // для получения номера пользователя и открытия чата
    
    while (userNamberInput != 0)
    {
        cout << _BLUE << "Список ваших приватных чатов" << _CLEAR  << endl;
        //Проверка на пустой список была ранее - не требуется
        size_t sizeChatPrivate = userAuthorization->getConnectionChatPrivate().size();
        for (size_t i = 0; i < sizeChatPrivate; i++)
        {
            cout << "[ " << i + 1 << " ] "  << userAuthorization->getConnectionChatPrivate()[i]->showUsers() << endl;
            chatIndexList.push_back(i + 1);
        }
        cout << endl;
        cout    << _CYAN << " Меню:" << _CLEAR << endl
                << "0 - Назад;" << endl
                << "N - номер чата из списка, кому написать?" << endl
                << "Ведите значение" << endl;
        
        cin >> userNamberInput;
        if (userNamberInput == 0) // Выходим при 0
            return;

        for (size_t i = 0; i < sizeChatPrivate; i++)
        {
            if (chatIndexList[i] == userNamberInput)            // если значение пользователя совпало с записанными индексами
            {
                openChatPrivate(db, userAuthorization, userAuthorization->getConnectionChatPrivate()[i]);  // ОШИБКА ПЕРЕДАЕТСЯ НЕ ВЕРНОЕ ЗНАЧЕНИЕ РАЗОБРАТЬСЯ
            } else if (i + 1 == sizeChatPrivate)                // в последней итерации если не нашли значение выводим сообщение
            {
                cout << _YELLOW << "Вы ввель не коректное значение, попробуйте еще раз" << _CLEAR  << endl;
            }   
        }
        
    }
}

void createChatPrivate(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){
    vector<size_t> userIndexList;                                        // для сохранения индексов пользователей
    vector<shared_ptr<User>> userList = db->getAllUsersInChat();    // берем копию списка пользователей для безопасности
    size_t userNamberInput = 999;                                    // для получения номера пользователя и открытия чата
    size_t sizeChatPrivate = userList.size();                       // размер полученного листа пользователей                
    cout << _GREY_BG << "\n\n\t\tСписок пользователей " << "\n" << _CLEAR << endl << endl;

    while (userNamberInput != 0)
    {
        if (userList.size() <= 1)
        {
            cout << _YELLOW << "Нету пользователей, которым вы моглы бы написать. Зайдите позже" << _CLEAR  << endl;
        }
        else
        {
            for (size_t i = 0; i < sizeChatPrivate; i++)
            {
                if (userList[i]->getLogin() == userAuthorization->getLogin())
                {
                    break;
                }
                else
                {
                    cout << "[ " << i + 1 << " ] " << userList[i]->getName() << endl;
                    userIndexList.push_back(i + 1);
                }
            }
            cout << endl;
        }
        cout    << _CYAN << " Меню:" << _CLEAR << endl
                << "0 - Назад;" << endl
                << "N - номер пользователя из списка, кому написать?" << endl
                << "Ведите значение" << endl;
        
        cin >> userNamberInput;
        if (userNamberInput == 0) // Выходим при 0
            return;
        
        for (size_t i = 0; i < sizeChatPrivate; i++)
        {
            if (userList[i]->getLogin() == userAuthorization->getLogin())
            {
                break;
            }

            if (userIndexList[i] == userNamberInput)            // если значение пользователя совпало с записанными индексами
            {
                std::shared_ptr<ChatPrivate> chatP = std::make_shared<ChatPrivate>( //создаем чат
                    std::weak_ptr<User>(userAuthorization), 
                    std::weak_ptr<User>(userList[userNamberInput - 1])
                );
                userAuthorization->setChat(chatP);              // Записали нашему пользователю созданый чат
                userList[userNamberInput - 1]->setChat(chatP);      // Записали выбраному пользомателю созданый чат
                openChatPrivate(db, userAuthorization, chatP);  // Запускаем чат
            } else if (i + 1 == sizeChatPrivate)                // в последней итерации если не нашли значение выводим сообщение
            {
                cout << _YELLOW << "Вы ввель не коректное значение, попробуйте еще раз" << _CLEAR  << endl;
            }   
        }
    }
}

void menuChatPrivate(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){
    char menu = '9';

    while (menu != '0')
    {
        cout << _GREY_BG << "\n\n\t\tПриватные чаты пользователя - " << userAuthorization->getName() << "\n" << _CLEAR << endl << endl;
        cout << _BLUE << "Список ваших приватных чатов" << _CLEAR  << endl;
        if (userAuthorization->getConnectionChatPrivate().size() == 0)
        {
            cout << _BLUE << "История чатов пуста, напишите кому-нибудь!" << _CLEAR  << endl;
        }
        else
        {
            size_t sizeChatPrivate = userAuthorization->getConnectionChatPrivate().size();
            for (size_t i = 0; i < sizeChatPrivate; i++)
            {
                cout << userAuthorization->getConnectionChatPrivate()[i]->showUsers() << endl;
            }
            cout << endl;
        }
        
        
        cout << "Для выбора введите значение."<< endl 
            << _CYAN << " Меню:" << _CLEAR << endl
            << "0 - Назад;" << endl
            << "1 - Написать пользователю;" << endl
            << "2 - Зайти в имеющийся чат" << endl
            << "Ведите значение" << endl;
        cin >> menu;
        switch (menu)
        {
        case '0':
            cout << _GREEN << "Назад!" << _CLEAR;
            return;
        case '1':
            createChatPrivate(db, userAuthorization);
            break;
        case '2':
            if (userAuthorization->getConnectionChatPrivate().size() == 0)
            {
                cout << _BLUE << "История чатов пуста, напишите кому-нибудь!" << _CLEAR  << endl;
            }
            else
            {
                UserChoiceChatPrivate(db, userAuthorization); // Для запроса у пользователя а какой чат открыть, далее в этой Ф уже будет открыт чат
            }
            break;
        default:
            cout << _YELLOW << "Не верно введено значение, попробуй еще раз" << _CLEAR << endl;
            break;
        }
    }
}



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
            menuChatHared(db, userAuthorization);
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

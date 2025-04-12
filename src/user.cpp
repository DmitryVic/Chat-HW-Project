#include "user.h"
#include "chat.h"
#include "database.h"
#include <exception>

//создаем класс от класса exception
// Ошибка передаваемых данных
class ErrorCreateUserData : public std::exception 
{
public:
	//переопределяем виртуальный метод обещая
	//не использовать исключения внутри
    virtual const char* what() const noexcept override   
    {
        return "Пользователь не создан, коректные данные";
    }
};

//создаем класс от класса exception
// Ошибка логин уже занят
class ErrorCreateUserExists : public std::exception
{
public:
	//переопределяем виртуальный метод обещая
	//не использовать исключения внутри
    virtual const char* what() const noexcept override   
    {
        return "Пользователь не создан, такой пользователь уже существует";
    }
};

//создаем класс от класса exception
// Ошибка базы данных
class ErrorCreateNotDataB : public std::exception
{
public:
	//переопределяем виртуальный метод обещая
	//не использовать исключения внутри
    virtual const char* what() const noexcept override   
    {
        return "Техническая неисправность";
    }
};

User::User(std::string login, std::string pasword, std::string name, std::weak_ptr<Database> dataB)
{
    // если хотябы одно поле пустое
    if (login.empty() || pasword.empty() || name.empty())
    {
        throw ErrorCreateUserData(); // исключение, пользователь не создан
    }
    else
    {
        // Получить shared_ptr
        if (dataB.expired()) {
            throw ErrorCreateNotDataB();
        }
        
        auto db = dataB.lock();  // Точно не nullptr проверка выше выдает исключение

        if (db->getOneUserByLogin(login)) {  // если пользователя нет, вернет nullptr
            // Пользователь с таким логином уже существует
            throw ErrorCreateUserExists();
        }
        else
        {
            // создаем пользователя, все нормально
            this->_login = login;
            this->_pasword = pasword;
            this->_name = name;
            this->_dataB = dataB;
        }
    }
}

User::~User()
{
    
}
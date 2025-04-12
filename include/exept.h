#pragma once
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
        return "Пользователь не создан, не коректные данные";
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

// Ошибка Чата
class ErrorChat : public std::exception 
{
public:
	//переопределяем виртуальный метод обещая
	//не использовать исключения внутри
    virtual const char* what() const noexcept override   
    {
        return "Чат - отказано в доступе";
    }
};
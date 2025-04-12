#include "database.h"
#include "colorConsole.h"
#include <iostream>



Database::Database()
{
    std::cout << _BLUE <<  "База данных запущена!" <<  _CLEAR << std::endl;
}

Database::~Database()
{
    
}

// Добавить пользовател
// вернет true - при успехе, false - при ошибке
// !! Обязательно добавить проверку на уникальность логина!! Логин уникален!!
bool Database::setUser(std::shared_ptr<User> user){

}

// Получить список всех пользователей
// !! Проверять на пустоту nullptr !!
std::vector<std::shared_ptr<User>> Database::getAllUsersInChat() const{

}

// Получить указатель на пользователя по логину (уникален для каждого)
// !! Проверять на пустоту nullptr !!
std::shared_ptr<User> Database::getOneUserByLogin(std::string login) const{
    
}
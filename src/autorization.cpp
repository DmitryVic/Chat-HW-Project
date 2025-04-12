#include "autorization.h"
#include "exept.h"
#include "colorConsole.h"
#include <iostream>

namespace autorization {
    std::shared_ptr<User> regUser(
        const std::string& login,
        const std::string& password,
        const std::string& name,
        std::weak_ptr<Database> dataB
    ) {
        try {
            // Пытаемся создать пользователя
            auto user = std::make_shared<User>(login, password, name, dataB);
            
            // Добавляем в базу данных
            if (auto db = dataB.lock()) {
                db->setUser(user);          // Передаём копию shared_ptr в БД тк нужно вернуть еще указатель для работы с текущем пользователем не оптимизировать
                return user;                // std::move(user) нарушает оптимизацию компилятора RVO (Return Value Optimization)
                                            // не даёт преимуществ, так как копирование shared_ptr - атомарная операция
            }
            return nullptr;
            
        } catch (const ErrorCreateUserExists& e) {  //обрабатываем исключения от класса User, дополня их
            std::cerr << _RED << "(Код ошибки 1) Ошибка регистрации: " << e.what() << _CLEAR << std::endl;
        } catch (const ErrorCreateUserData& e) {    // cerr стандартный поток для вывода ошибок и диагностических сообщений
            std::cerr << _RED << "(Код ошибки 2) Ошибка данных: " << e.what() << _CLEAR << std::endl;
        } catch (const ErrorCreateNotDataB& e) {
            std::cerr << _RED << "(Код ошибки 3) Ошибка БД: " << e.what() << _CLEAR<< std::endl;
        }
        return nullptr;
    }

    // Возвращает shared_ptr<User> при успехе или nullptr при ошибке
    std::shared_ptr<User> autorizUser(
        const std::string& login,
        const std::string& password,
        std::weak_ptr<Database> dataB
    ){
        try {
            if (dataB.lock()) {               //если база данных передана корректно, если нет, то дойдем до return nullptr в конце
                auto user = dataB.lock()->getOneUserByLogin(login);// нашли логин в базе данных
                if (user.get()) // если не nullptr
                {
                    if (user->getPass() == password )   //если пароль совпадает логин уже и так совпал, нашелся же пользователь
                    {
                        return user;                    // std::move(user) нарушает оптимизацию компилятора RVO (Return Value Optimization)
                                                        // не даёт преимуществ, так как копирование shared_ptr - атомарная операция
                    }
                    else
                    {
                        return nullptr;
                    }  
                }
                else
                {
                    return nullptr;
                }
            }
        } catch (const ErrorCreateNotDataB& e) {        //обрабатываем исключения от класса User, дополня их исключения рег не нужны
            // cerr стандартный поток для вывода ошибок и диагностических сообщений
            std::cerr << _RED << "(Код ошибки 4) Ошибка БД: " << e.what() << _CLEAR<< std::endl;
        }
        // cerr стандартный поток для вывода ошибок и диагностических сообщений
        std::cerr << _RED << "(Код ошибки 5) Ошибка БД: БД не существует" << _CLEAR<< std::endl;
        return nullptr;
    }

}
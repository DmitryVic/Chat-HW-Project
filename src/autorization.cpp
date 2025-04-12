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
                db->setUser(std::move(user));
                return user;
            }
            return nullptr;
            
        } catch (const ErrorCreateUserExists& e) {
            std::cerr << _RED << "Ошибка регистрации: " << e.what() << _CLEAR << std::endl;
        } catch (const ErrorCreateUserData& e) {
            std::cerr << _RED << "Ошибка данных: " << e.what() << _CLEAR << std::endl;
        } catch (const ErrorCreateNotDataB& e) {
            std::cerr << _RED << "Ошибка БД: " << e.what() << _CLEAR<< std::endl;
        }
        return nullptr;
    }
}
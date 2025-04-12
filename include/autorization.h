#pragma once
#include <memory>
#include <string>
#include "database.h"
#include "user.h"

namespace autorization {
    // Создает объект User и добавляет его в Database
    // Возвращает shared_ptr<User> при успехе или nullptr при ошибке
    std::shared_ptr<User> regUser(
        const std::string& login,
        const std::string& password,
        const std::string& name,
        std::weak_ptr<Database> dataB
    );

     
    // Возвращает shared_ptr<User> при успехе или nullptr при ошибке
     std::shared_ptr<User> autorizUser(
        const std::string& login,
        const std::string& password,
        std::weak_ptr<Database> dataB
    );
}
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <utility>

// Исправлена ошибка объявления user.h
class User;

/*
Chat - абстрактный класс, наследники ChatPrivate, ChatHared
*/
class Chat
{
private:  
    /*
        historyChat - состоит из списка пар 
            pair - должен содержать указатель на пользователя и само сообщение
            pair  в последующем можно заменить на tuple, если будет нужно больше полей, например, дата/время
        
        .first - weak_ptr<User>
        .second - string Message
    */
    std::vector<std::pair<std::weak_ptr<User>, std::string>> historyChat;
    //Список участников
    std::vector<std::weak_ptr<User>> usersInChat;

public:
    virtual ~Chat() = default;
    
    // Должен передать количество участников в ChatHared или имя пользователя
    // добавить дополнительные поля для классов - счетчик для ChatHared, ptr для ChatPrivate
    // !!! проверять на пустоту historyChat в функцииt, проверять на пустоту string при вызове
    virtual std::string showUsers();

    // Должен предать все сообщения из historyChat, форматируя текст относительно пользователя User, тоесть того, кто открыл чат
    // !!! проверять на пустоту historyChat в функцииt, проверять на пустоту string при вызове
    virtual std::string getOllMessage(std::weak_ptr<User>);

    // Указатель взять из dataBace shared_ptr и из него сделать weak_ptr
    // Добавить пользователя в чат общий или при личных сообщениях
    // Добавить проверку на ChatPrivate, если в нем уже 2, то отклонить заявку
    // вернет true - при успехе, false - при ошибке
    bool setUsersInChat(std::weak_ptr<User>);
};



// #pragma once
// #include "database.h"
// #include "user.h"
// #include "chathared.h"
// #include "chat.h"
// #include "template.h"
// #include <memory>
// using namespace std;

// //открывает чат, записывает принятые сообщения от пользователей и добавляет еще пользователей
// void openChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization, shared_ptr<ChatHared>& chatP);

// // предоставляет доступ выбора чата из имеющихся
// void  UserChoiceChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization);

// // дает возможность создать новый общий чат выбрав 1 пользователеля, в самом чате можно добавить еще пользователя openChatHared
// void createChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization);

// //предоставляет выбор меню создать чат или зайти в имеющийся чат
// void menuChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization);
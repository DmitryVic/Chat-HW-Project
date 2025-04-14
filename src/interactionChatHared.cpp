// #include "interactionChatHared.h"
// #include "database.h"
// #include "user.h"
// #include "chathared.h"
// #include "chat.h"
// #include "template.h"
// #include "colorConsole.h"
// #include <iostream>
// #include <string>
// #include <vector>
// #include <limits> //Для  cin.ignore(numeric_limits<streamsize>::max(), '\n');
// using namespace std;


// // открывает чат, записывает принятые сообщения от пользователей и добавляет еще пользователей
// void openChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization, shared_ptr<ChatHared>& chatP){}

// // предоставляет доступ выбора чата из имеющихся
// void  UserChoiceChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){}

// // дает возможность создать новый общий чат выбрав 1 пользователеля, в самом чате можно добавить еще пользователя openChatHared
// void createChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){

//     size_t userNamberInput = 999;                                           // для получения номера пользователя и открытия чата
//     while (userNamberInput != 0)
//     {
//         vector<size_t> userIndexList;                                        // для сохранения индексов пользователей
//         vector<shared_ptr<User>> userList = db->getAllUsersInChat();        // берем копию списка пользователей для безопасности
//         size_t sizeChatHared = userList.size();                             // размер полученного листа пользователей                

//         cout << _GREY_BG << "\n\n\t\tСписок пользователей " << "\n" << _CLEAR << endl << endl;
//         if (userList.size() <= 1)
//         {
//             cout << _YELLOW << "Нету пользователей. Зайдите позже" << _CLEAR  << endl;
//         }
//         else
//         {
//             for (size_t i = 0; i < sizeChatHared; i++)
//             {
//                 if (userList[i]->getLogin() == userAuthorization->getLogin())  // пропускаем себя
//                 {
//                     continue;
//                 }
//                 else
//                 {
//                     cout << "[ " << i + 1 << " ] " << userList[i]->getName() << endl;
//                     userIndexList.push_back(i + 1);
//                 }
//             }
//             cout << endl;
//         }
//         cout    << _CYAN << " Меню:" << _CLEAR << endl
//                 << "0 - Назад;" << endl
//                 << "N - номер пользователя из списка, кому написать?" << endl
//                 << "Ведите значение" << endl;
        
//         cin >> userNamberInput;
//         if (userNamberInput == 0) // Выходим при 0
//             return;

//         // НЕ КОРРЕКТНАЯ ПРОВЕРКА НУЖНО ПРОСТОУБЕДИТЬСЯ ЧТО ЕСТЬ ЭТАЦИФРА В ВЕКТОРЕ МОЖНО СДЕЛАТЬ КАК РАЗ ШАБЛОН
//         if (contains(userIndexList, userNamberInput))            // если значение пользователя совпало с записанными индексами заменено userIndexList[i-1]
//         {
//             // Если данный чат еще не создан - запрашиваем через метод класса юзер, который перебирает все чаты, запрашивая у метода чата наличие юзера
//             if (!userAuthorization->userInChatsP(weak_ptr<User>(userList[userNamberInput - 1])))
//             {
//                 shared_ptr<ChatHared> chatP = make_shared<ChatHared>( //создаем чат
//                 weak_ptr<User>(userAuthorization), 
//                 weak_ptr<User>(userList[userNamberInput - 1])
//                 );
//                 userAuthorization->setChat(chatP);                  // Записали нашему пользователю созданый чат
//                 userList[userNamberInput - 1]->setChat(chatP);      // Записали выбраному пользомателю созданый чат
//                 openChatHared(db, userAuthorization, chatP);      // Запускаем чат
//             }
//             else
//             {
//                 cout << _YELLOW << "У вас уже есть чат с данным пользователем" << _CLEAR  << endl;
//             }
            
//         } else                // в последней итерации если не нашли значение выводим сообщение
//         {
//             cout << _YELLOW << "Вы ввели не коректное значение, попробуйте еще раз" << _CLEAR  << endl;
//         } 
//     }
// }



// //предоставляет выбор меню создать чат или зайти в имеющийся чат
// void menuChatHared(shared_ptr<Database>& db, shared_ptr<User>& userAuthorization){
//     char menu = '9';

//     while (menu != '0')
//     {
//         cout << _GREY_BG << "\n\n\t\tОбщие чаты пользователя - " << userAuthorization->getName() << "\n" << _CLEAR << endl << endl;
//         cout << _BLUE << "Список ваших общих чатов" << _CLEAR  << endl;
//         if (userAuthorization->getConnectionChatHared().size() == 0)
//         {
//             cout << _BLUE << "История чатов пуста, напишите кому-нибудь!" << _CLEAR  << endl;
//         }
//         else
//         {
//             size_t sizeChatHared = userAuthorization->getConnectionChatHared().size();
//             for (size_t i = 0; i < sizeChatHared; i++)
//             {
//                 cout << userAuthorization->getConnectionChatHared()[i]->showUsers() << endl;
//             }
//             cout << endl;
//         }
        
        
//         cout << "Для выбора введите значение."<< endl 
//             << _CYAN << " Меню:" << _CLEAR << endl
//             << "0 - Назад;" << endl
//             << "1 - Создать новый общий чат;" << endl
//             << "2 - Зайти в имеющийся чат" << endl
//             << "Ведите значение" << endl;
//         cin >> menu;
//         switch (menu)
//         {
//         case '0':
//             cout << _GREEN << "Назад!" << _CLEAR;
//             return;
//         case '1':
//             createChatHared(db, userAuthorization);
//             break;
//         case '2':
//             if (userAuthorization->getConnectionChatHared().size() == 0)
//             {
//                 cout << _BLUE << "История чатов пуста, напишите кому-нибудь!" << _CLEAR  << endl;
//             }
//             else
//             {
//                 UserChoiceChatHared(db, userAuthorization); 
//             }
//             break;
//         default:
//             cout << _YELLOW << "Не верно введено значение, попробуй еще раз" << _CLEAR << endl;
//             break;
//         }
//     }
// }
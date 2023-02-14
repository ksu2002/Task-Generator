#ifndef ERROR_H
#define ERROR_H

#include <ostream>
#include <string>
using namespace std;

class Error // базовый класс для ошибок
{
public:
   virtual ~Error() {}; // деструктор
   virtual string errorMessage() = 0; // сообщение для печати
};

class WrongRange : public Error// недопустимый диапазон
{
public:
   string errorMessage();// сообщение для печати
};

#endif
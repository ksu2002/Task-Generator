#ifndef ERROR_H
#define ERROR_H

#include <ostream>
#include <string>
using namespace std;

class Error // ������� ����� ��� ������
{
public:
   virtual ~Error() {}; // ����������
   virtual string errorMessage() = 0; // ��������� ��� ������
};

class WrongRange : public Error// ������������ ��������
{
public:
   string errorMessage();// ��������� ��� ������
};

#endif
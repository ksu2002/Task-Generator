#include"TaskGenerator.hpp"
using namespace std;

int main() { //�������� �������
   srand(time(0));
   TasksGenerator *taskgenerator = new TasksGenerator();// ��������� �������������� ��������
   taskgenerator->draw();// ��������� ����
   taskgenerator->generate();//��������� ��������
   delete taskgenerator;//������� ������
}
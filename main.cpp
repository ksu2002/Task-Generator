#include"TaskGenerator.hpp"
using namespace std;

int main() { //основная функция
   srand(time(0));
   TasksGenerator *taskgenerator = new TasksGenerator();// генератор арифметических примеров
   taskgenerator->draw();// отрисовка окна
   taskgenerator->generate();//генерация примеров
   delete taskgenerator;//очистка памяти
}
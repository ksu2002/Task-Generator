#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <ostream>
#include "graphics.h"
#include <string>
using namespace std;

class ResultWindow {//окно сообщения
protected:
   IMAGE *background = NULL;//фоновое изображение окна
public:
   virtual ~ResultWindow();//деструктор
   virtual void draw() = 0;//отрисовка окна
};

class SuccessWindow : public ResultWindow {//окно сообщения об успешной генерации
public:
   void draw();//отрисовка окна
};

class ErrorWindow : public ResultWindow {//окно сообщения об ошибке
public:
   void draw();//отрисовка окна
};

#endif
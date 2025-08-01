#ifndef INTERFACE_H
#define INTERFACE_H

#include "graphics.h"
#include <string>
using namespace std;

extern int isMouseClicked;
extern int isMouseReleased;

class TextView {//���� �����
   int posX, posY, sizeX, sizeY;//���������� � ������� ���� �����
   bool isNumberDialed = false;//�������� �� ���� �����
   string number;//������ ��� �������� ��������� �����
   int length = 0;//����� ������
   int result = 0;//��������� �����
public:
   //����������� �������� ���������� ����� � ������� ����
   TextView(int posX, int posY, int sizeX, int sizeY) : posX(posX), posY(posY), sizeX(sizeX), sizeY(sizeY) {};
   int isClick(int x, int y);// ������� �� �������
};

class Button { //������
protected:
   int posX, posY, sizeX, sizeY;//���������� � ������� ������
public:
   //����������� �������� ���������� ����� � ������� ������
   Button(int posX, int posY, int sizeX, int sizeY) : posX(posX), posY(posY), sizeX(sizeX), sizeY(sizeY) {};
   virtual bool isClick(int x, int y);// ������� �� �������
};

class Checkbox : public Button//������
{
   IMAGE *checkbox = NULL;//�����������
   char op;//��������
   bool isShowImage = false;//�������� �� ��������� �����������
public:
   //����������� �������� ���������� �����, ������� � ���� ��������
   Checkbox(int posX, int posY, int sizeX, int sizeY, char op) : Button(posX, posY, sizeX, sizeY), op(op) {};
   ~Checkbox();// ����������
   bool isClick(int x, int y);// ������� �� �������
   char getOperation();//����������� ��������� ��������
   void loadImage();//�������� �����������
};

#endif
#include"TaskGenerator.hpp"
#include"interface.hpp"
#include"Error.hpp"
#include"ResultWindow.hpp"
int isMouseClicked = 0;
int isMouseReleased = 0;
int maxNumberOfGenerations = 1000;

void TasksGenerator::draw() {
   initwindow(600, 450);
   IMAGE *background = NULL;
   background = loadBMP("backgr.bmp");
   int p = 0; // сначала текуща€ видима€ страница 0
   int t = 0; // номер кадра (врем€)
   int mX, mY;
   TextView buttonTaskNumb(450, 62, 100, 25);
   TextView buttonOperationsNumb(450, 97, 100, 25);
   TextView buttonMin(450, 132, 100, 25);
   TextView buttonMax(450, 167, 100, 25);
   Checkbox buttonPlusOp(269, 261, 20, 20, '+');
   buttonPlusOp.loadImage();
   Checkbox buttonMinusOp(269, 296, 20, 20, '-');
   buttonMinusOp.loadImage();
   Checkbox buttonMultiplyOp(269, 331, 20, 20, '*');
   buttonMultiplyOp.loadImage();
   Checkbox buttonDivideOp(269, 366, 20, 20, '/');
   buttonDivideOp.loadImage();
   Checkbox buttonSignChange(269, 401, 20, 20, '.');
   buttonSignChange.loadImage();
   Button button(450, 371, 100, 50);
   while (1) {
      p = 1 - p;
      setactivepage(p); // активна€ страница ==. 1-видима€
      setbkcolor(COLOR(239, 228, 204)); // цвет фона
      clearviewport(); // закраска текущей страницы цветом фона
      ++t;
      putimage(0, 0, background, COPY_PUT);
      if (isMouseReleased != 0) isMouseReleased = 0;
      if (isMouseClicked != mousebuttons()) {
         isMouseReleased = isMouseClicked;
         isMouseClicked = mousebuttons();
      }
      mX = mousex();
      mY = mousey();
      tasksNumb = buttonTaskNumb.isClick(mX, mY);
      operationsNumb = buttonOperationsNumb.isClick(mX, mY);
      max = buttonMax.isClick(mX, mY);
      min = buttonMin.isClick(mX, mY);
      if (buttonPlusOp.isClick(mX, mY))
         operations.push_back(buttonPlusOp.getOperation());
      if (buttonMinusOp.isClick(mX, mY))
         operations.push_back(buttonMinusOp.getOperation());
      if (buttonMultiplyOp.isClick(mX, mY))
         operations.push_back(buttonMultiplyOp.getOperation());
      if (buttonDivideOp.isClick(mX, mY))
         operations.push_back(buttonDivideOp.getOperation());
      if (buttonSignChange.isClick(mX, mY))
         operations.push_back(buttonSignChange.getOperation());
      if (button.isClick(mX, mY) == 1)break;
      setvisualpage(p); // делаем активную страницу видимой
      delay(30); // задержка на 1/30 секунды
   }
   closegraph();
   freeimage(background);
}

bool TasksGenerator::checkIsNumberIsFits(char op, int numberLeft, int res, int &numberRight) {
   switch (op) {
   case '.':
      numberRight = abs(res);
      if (res >= 0) return false;
      break;
   case '+':
      numberRight = res - numberLeft;
      break;
   case '-':
      numberRight = numberLeft - res;
      break;
   case '*':
      if (numberLeft == 0) {
         numberRight = max + 1;
         return false;
         break;
      }
      numberRight = res / numberLeft;
      if (res % numberLeft != 0) return false;
      break;
   case '/':
      if (res == 0) {
         numberRight = max + 1;
         return false;
         break;
      }
      numberRight = numberLeft / res;
      if (numberLeft % res != 0) return false;
      if (numberLeft == numberRight && numberLeft == 0) return false;
      break;
   }
   if (op != '.' && (numberRight > max || numberRight < min)) return false;
   return true;
}
Task *TasksGenerator::decomposeLeftAndCreateRightOperands(char op, int numberRight, int operationsNumbLeftOperand, int res) {
   Task *operandLeft;
   Task *operandRight;
   operandLeft = generateTask(operationsNumbLeftOperand, res);
   operandRight = new Task(numberRight);
   return new Task(operandLeft, op, operandRight);
}
Task *TasksGenerator::decomposeRightAndCreateLeftOperands(char op, int numberLeft, int operationsNumbRightOperand, int res) {
   Task *operandLeft;
   Task *operandRight;
   if (op == '.') {
      op = '-';
      operandLeft = nullptr;
      operandRight = generateTask(operationsNumbRightOperand, res);
   }
   else {
      operandLeft = new Task(numberLeft);
      operandRight = generateTask(operationsNumbRightOperand, res);
   }
   return  new Task(operandLeft, op, operandRight);

}


Task *TasksGenerator::decomposeBothOperand(char op, int numberLeft, int operationsNumbLeftOperand, int numberRight, int operationsNumbRightOperand) {
   Task *generatedTask;
   return generatedTask = new Task(generateTask(operationsNumbLeftOperand, numberLeft), op, generateTask(operationsNumbRightOperand, numberRight));
}
Task *TasksGenerator::createLeftandRigth(char op, int numberLeft, int numberRight) {
   Task *operandLeft;
   Task *operandRight;
   if (op == '.') {
      op = '-';
      operandLeft = nullptr;
      operandRight = new Task(numberRight);
   }
   else {
      operandLeft = new Task(numberLeft);
      operandRight = new Task(numberRight);
   }
   return new Task(operandLeft, op, operandRight);
}

Task *TasksGenerator::generateTask(int operationsNumb, int res) {
   Task *generatedTask;
   int numberLeft;
   char op;
   int numberRight;
   int counter = 0;
   do {
      op = operations[rand() % operations.size()];
      numberLeft = min + rand() % (max - min + 1);
      counter++;
      if (counter == maxNumberOfGenerations) throw WrongRange();
   } while (!checkIsNumberIsFits(op, numberLeft, res, numberRight));

   int operationsLeftOperand;
   if (op == '.') operationsLeftOperand = 0;
   else  operationsLeftOperand = rand() % (operationsNumb);
   int operationsRightOperand = operationsNumb - operationsLeftOperand - 1;

   if (operationsLeftOperand > 0 && operationsRightOperand == 0)
      return decomposeLeftAndCreateRightOperands(op, numberRight, operationsLeftOperand, numberLeft);
   if (operationsLeftOperand == 0 && operationsRightOperand > 0)
      return  decomposeRightAndCreateLeftOperands(op, numberLeft, operationsRightOperand, numberRight);
   if (operationsLeftOperand == 0 && operationsRightOperand == 0)
      return createLeftandRigth(op, numberLeft, numberRight);
   return decomposeBothOperand(op, numberLeft, operationsLeftOperand, numberRight, operationsRightOperand);
}

void TasksGenerator::generate() {
   fstream file;
   file.open("kontr1.txt", std::ofstream::out | std::ofstream::trunc);
   for (int i = 0; i < tasksNumb; i++) {
      Task *task;
      int res = min + rand() % (max - min + 1);
      try {
         task = generateTask(operationsNumb, res);
      }
      catch (Error &e)
      {
         file << e.errorMessage() << endl;
         ErrorWindow *errorWindow = new ErrorWindow();
         errorWindow->draw();
         delete errorWindow;
         return;
      }
      tasks.push_back(task);
      task->print(file);
      delete task;
      file << ' ' << '=' << '\n' << '\n' << "ќтвет: " << res << '\n' << '\n';
   }
   file.close();
   SuccessWindow *successWindow = new SuccessWindow();
   successWindow->draw();
   delete successWindow;
}
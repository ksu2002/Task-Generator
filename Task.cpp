#include"Task.hpp"

Task::~Task()  {
   if (operandRight) delete operandRight;
   if (operandLeft) delete operandLeft;
}

int Task::prioritet() {
   if (operation == '+') return 1;
   if (operation == '-')
      if (operandLeft != nullptr) return 1;
      else return 0;
   if (operation == '*' || operation == '/') return 2;
   return 3;
}

char Task::getOperation() {
   return operation;
}

void Task::print(ostream &os) {
   if (operation == '#') {
      if (number < 0) {
         os << '(';
         os << number;
         os << ')';
      }
      else os << number;
      return;
   }
   if (operation == '-' && operandLeft == nullptr) {
      os << ' ' << operation << ' ';
      os << '(';
      operandRight->print(os);
      os << ')';
      return;
   }
   if (operandLeft->prioritet() < prioritet()) {
      os << '(';
      operandLeft->print(os);
      os << ')';
   }
   else operandLeft->print(os);

   os << ' ' << operation << ' ';

   if (operandRight->prioritet() <= prioritet() && getOperation() != '+') {
      os << '(';
      operandRight->print(os);
      os << ')';
   }
   else operandRight->print(os);
   return;
}

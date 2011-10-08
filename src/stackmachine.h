#pragma once

#include "list.h"
#include "oper.h"

class StackMachine
{
    public:
        StackMachine();
        void put(Oper elem);  // Основной приемный шлюз
        double getValue();    // Получение результата работы
        double getVar(char var);  // Доступ к сохраненным переменным
        bool isOK();          // Флаг ошибок
        void memoryOut();     // Печать содержимого памяти
    private:
        double memory[256];
        List<Oper> stack;
        bool noError;
        void engine(char operation, Oper op2, Oper op1);
        double calc(char operation, double realOp2, double realOp1);
        double checkOperand(Oper op);
};


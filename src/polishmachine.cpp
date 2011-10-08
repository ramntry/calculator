#include <cmath>
#include <iostream>
#include "list.h"
#include "oper.h"
#include "polishmachine.h"

using namespace std;

// masks
const char * operations[] = {
        "^0R", "*1L", "/1L", "+2L", "-2L", "=3R", ",4L" // карта операций:
, ""};                             // символ : приоритет : ассоциированность

const char * brackets[]   = {
        "(.", ")(", "<.", "><", "[.", "][", "{.", "}{"
, ""};

char getMask(char * buf, const Oper & elem, const char * masks[])
{
    int index = 0;
    char ch = masks[index][0];
    while (ch != elem.operation && ch != '\0')
    {
        index++;
        ch = masks[index][0];
    }
    for (int i=0; buf[i] = masks[index][i]; i++);
    return buf[0];
}

Oper getNext()
{
    char buf = ' ';
    while (isspace(buf))
    {
        cin >> buf;
        if (cin.eof())
            return Oper('\0');
    }
    if (isdigit(buf) || buf == '.')
    {
        cin.putback(buf);
        double num;
        cin >> num;
        return Oper(num);
    }
    Oper res(buf);
    char tmp[4];
    if (!getMask(tmp, res, operations) &&
        !getMask(tmp, res, brackets))
        return Oper(buf, true);
    return res;
}

bool isOverrable(Oper op1, Oper op2)
{
    char buf1[4];
    char buf2[4];
    getMask(buf1, op1, operations);
    getMask(buf2, op2, operations);
    
    return (buf1[1] > buf2[1]  // приоритет "верхней" операции строго меньше
            || (buf1[1] == buf2[1]  // или они равны, но только если
                && !(buf1[2] == 'R' && buf2[2] == 'R')));  // обе операции
                                                      // не являются правыми
}

int polishMachine(List<Oper> & queue)
{
    List<Oper> stack;
    Oper res = getNext();
    char buf[4];
    while (res.isOperand || res.operation)
    {
        if (res.isOperand)    // Операнд сразу сбрасываем в очередь
            queue.append(res);
        else
        {
            if (getMask(buf, res, brackets))  // Иначе если скобка
            {
                if (buf[1] == '.')    // открывающая
                    stack.push(res);  // - сразу в стек
                else                  // если закрывающая
                {
                    char openBracket = buf[1];
                    while (!stack.isEmpty() &&
                            getMask(buf, stack.look(), operations))
                    {   // Выбрать все операции из стека в очередь
                        queue.append(stack.pop());
                    }
                    if (stack.isEmpty() ||
                            openBracket != stack.look().operation)
                            // если стек пуст
                            // или скобка другого типа
                        return 1;
                    stack.pushOut(); // выкинуть открывающую скобку из стека
                }
            } else if (getMask(buf, res, operations)) // если операция
            {
                while (!stack.isEmpty() && // пока стек не пуст или не
                       !getMask(buf, stack.look(), brackets) &&  // скобка
                           isOverrable(res, stack.look()))  // и меньше
                    queue.append(stack.pop());              // приоритет

                stack.push(res);
            }
        }
        res = getNext();
    }
    while (!stack.isEmpty())
    {
        if (getMask(buf, stack.look(), brackets))
            return 1;
        queue.append(stack.pop());
    }
    return 0;
}


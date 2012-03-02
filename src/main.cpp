/**
 * @author Roman Tereshin,
 *         roman.tereshin@student.spbu.ru
 */


#include <iostream>
#include "polishmachine.h"
#include "stackmachine.h"
#include "list.h"

using namespace std;

int cli_main(int argc, char **argv)
{
    clog << "This program converts the infix notation to postfix\n"
         << "and calculates the expression\n"
         << "(send LF EOF (enter, ctrl+D) to stop the input)\n"
         << "Enter the expression: ";

    List<Oper> queue;
    int errorLevel = polishMachine(queue);
    if (errorLevel)
    {
        cerr << "Brackets error" << endl;
        return errorLevel;
    }

    for (int i = 0; i < queue.size(); i++)
    {
        queue[i].out();
        cout << ' ';
    }

    StackMachine stackMachine;
    while (!queue.isEmpty() && stackMachine.isOK())  // Мегамолотилка :)
        stackMachine.put(queue.pop());

    cout << "   =  " << stackMachine.getValue() << endl;
    stackMachine.memoryOut();

    return 0;
}

int stackMashineRefactorTest()
{
    StackMachine stackmachine;

    stackmachine.put(3.0);
    stackmachine.put(2.0);
    stackmachine.put('-');

    cout << "3 - 2 = " << stackmachine.getValue() << endl;

    return 0;
}

int main(int argc, char **argv)
{
    return stackMashineRefactorTest();
//    return cli_main(argc, argv);
}


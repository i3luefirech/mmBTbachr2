#include <iostream>

#include "../inc/multimouse.h"

multimouse * mm = nullptr;

int main() {
    std::cout << "Hello, I am Multi Mouse!" << std::endl;

    mm = new multimouse();

    std::cout << "Start!" << std::endl;

    mm->start();

    while(1);

    std::cout << "Bye!" << std::endl;
    free(mm);

    return 0;
}
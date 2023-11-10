#include <iostream>
#include "bares_manager.h"

int main () {
    

    std::string input;

    while (getline (std::cin, input)) {

    br::BARES expression(input);

    expression.parses();    //Retorna os tokens da expressao sintaticamente correta ou um erro

    expression.calculate(); // retorna o resultado da expressao ou um erro

    std::cout << expression.get_result();   // resultado ou mensagem de erro
    }

}
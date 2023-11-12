#include <iostream>
#include "bares_manager.h"

int main () {
    

    std::string input {" "};

    while (std::getline(std::cin, input)) {
    
   

    br::BARES expression(input);

    expression.parses();    //Retorna os tokens da expressao sintaticamente correta ou um erro

    expression.calculate(); // retorna o resultado da expressao ou um erro

    // auto a {expression.get_result()};

    //  while (a.find('\n') != std::string::npos) {
    //     a.erase(a.find('\n'));
    // }


    // std::cout << a + "\n";   // resultado ou mensagem de erro
    std::cout << expression.get_result() << "\n";
    }

}
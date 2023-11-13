#include <iostream>
#include "bares_manager.h"

int main () {
    

    std::string input {" "};

    while (std::getline(std::cin, input)) {
    
   

    br::BARES expression(input);

    expression.parses();    // Parsing

    expression.calculate(); // Cálculo

    std::cout << expression.get_result() << "\n"; // Impressão
    }

}
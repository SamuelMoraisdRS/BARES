#include <iostream>
#include "bares_manager.h"

int main () {
    std::string input {" "};
    while (std::getline(std::cin, input)) {
    br::BARES expression(input);

    expression.parses();    // Parsing

    expression.calculate(); // Calculates the value

    std::cout << expression.get_result() << "\n"; // Prints the result
    }

}
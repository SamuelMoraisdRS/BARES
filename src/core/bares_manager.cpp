#include "bares_manager.h"

using namespace br;
    void BARES::parses() {
        Parser validator(expression);
        auto outcome {validator.validate_infix()};
        auto error_pos {validator.get_error_col()};
        if (outcome == error_msg_e::NO_ERROR) {
            validator.formats_expression();
            tokens = validator.get_tokens();
            std::cout << "TAMANHO DO TOKENS " << tokens.size() << std::endl;
            std::cout << "Tokens : \n";
            for (std::string e : tokens) {
                std::cout << e << std::endl;
            }
        } else {
            result = get_msg(outcome, error_pos);
            error_found = true;
            std::cout << "na funcao do bares\n";
            std::cout << error_found << std::endl;
        }
    }


    void BARES::calculate() {
        if (not error_found) {
            std::cout << "Convertendo...\n";
            calc.convert_to_posfix(tokens);
            result = calc.evaluate_expr();
        // std::cout << "Expressão pós-fixa: " << test << std::endl;
        } else {

        }
    }






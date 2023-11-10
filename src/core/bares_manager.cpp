#include "bares_manager.h"

using namespace br;
    void BARES::parses() {

        // Checks if the expression is empty
        if (expression.find_first_not_of(' ') == std::string::npos) {
            empty_expression = true;
        }
        
        if (not empty_expression) {
            Parser validator(expression);
            auto outcome {validator.validate_infix()};
            // outcome = validator.get_outcome();
            
            auto error_pos {validator.get_error_col()};
            
            // std::cout << "outcome: " << outcome << std::endl;
            // std::cout << "Outcome (no manager) : " << outcome << "\n";
            if (outcome == error_msg_e::NO_ERROR) {
                validator.formats_expression();
                if (validator.get_outcome() == INTEGER_OUT_OF_RANGE) {
                    outcome = INTEGER_OUT_OF_RANGE;
                    error_found = true;
                    result = get_msg(outcome, error_pos) + "\n";
                }
                tokens = validator.get_tokens();
                // std::cout << "TAMANHO DO TOKENS " << tokens.size() << std::endl;
                // std::cout << "Tokens : \n";
                // for (std::string e : tokens) {
                 // std::cout << e << std::endl;
                // }
            } else {
                result = get_msg(outcome, error_pos) + "\n";
                error_found = true;
                // std::cout << "na funcao do bares\n";
                // std::cout << error_found << std::endl;
            }
        }
        
    }


    void BARES::calculate() {
        if (not error_found and not empty_expression) {
            // std::cout << "Convertendo...\n";
            calc.convert_to_posfix(tokens);
            result = calc.evaluate_expr() + "\n";
        // std::cout << "Expressão pós-fixa: " << test << std::endl;
        } else if (empty_expression) {
            result = expression;
        } else {

        }
    }






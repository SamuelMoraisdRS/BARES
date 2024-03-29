#include "bares_manager.h"

using namespace br;
    void BARES::parses() {

        // Checks if the expression is empty
        bool char_check {false};

        for (char c : expression) {
            if (c !=' ') {
                char_check = true;
            }
        }
        if (char_check == false) {
            empty_expression = true;
        }

        if (not empty_expression) {
            Parser validator(expression);
            auto outcome {validator.validate_infix()};            
            auto error_pos {validator.get_error_col()};

            if (outcome == EXTRA_SYMBOL_AFTER_EXPR or outcome == MISSING_TERM
                or outcome == MISSING_LP) {
                error_pos++;
            }
            
            if (outcome == error_msg_e::NO_ERROR) {
                validator.formats_expression();
                if (validator.get_outcome() == INTEGER_OUT_OF_RANGE) {
                    outcome = INTEGER_OUT_OF_RANGE;
                    error_pos = validator.get_error_col() + 1;
                    error_found = true;
                    result = get_msg(outcome, error_pos);
                }
                tokens = validator.get_tokens();
            } else {
                result = get_msg(outcome, error_pos);
                error_found = true;
            }
        } else {
            error_found = true;
            result = get_msg(UNEXPECTED_END_EXPR, expression.size() + 1);
        }
        
    }


    void BARES::calculate() {
        if (not error_found and not empty_expression) {
            calc.convert_to_posfix(tokens);
            result = calc.evaluate_expr();
        } else {
            // Does nothing
        }
    }






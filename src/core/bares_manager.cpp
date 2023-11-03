#include "bares_manager.h"

namespace br {
    void BARES::parses() {
        Parser validator(expression);
        auto outcome {validator.validate_infix()};
        auto error_pos {validator.get_error_col()};
        if (outcome == error_msg_e::NO_ERROR) {
            expression = validator.get_formatted_expr();
            std::cout << "não teve erro" << std::endl;
        } else {
            result = get_msg(outcome, error_pos);
            error_found = true;
            std::cout << error_found << std::endl;
        }
    }


    void BARES::calculate() {
        if (not error_found) {

        }
    }


}


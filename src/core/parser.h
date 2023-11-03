#ifndef __PARSER__
#define __PARSER__

// converte para posfixo e encontra erros de 
#include "../libs/messages.h"

#include "../libs/tokenizer.h"

#include "../libs/EBNF_validator.h"

class Parser {
private:
    std::string expr;
    size_t expr_runner = 0;     //!< Idx that'll run through the expression during validation
    StrTokenizer tokenizer;
    error_msg_e outcome = error_msg_e::NO_ERROR;              //!< Variable that'll indicate if the validation was succesful/what error occurred
public:
    Parser(std::string & e) : expr {e} {};
    error_msg_e validate_infix();
    void formats_expression();
    std::string get_formatted_expr() {
        return expr;
    }
    short get_error_col() {
        return expr_runner;
    }
private:
 std::string tokenize_expr();
 error_msg_e check_expression();
 error_msg_e check_term();
 error_msg_e check_int();
 error_msg_e check_natural_num();
//  error_msg_e check_digit_exc_zero();
 error_msg_e check_digit();
 error_msg_e check_wsp();
 error_msg_e check_operator();

 error_msg_e advance_runner() {
    // if (expr_runner == expr.size() - 1) {
    //     return error_msg_e::UNEXPECTED_END_EXPR;
    // }
    expr_runner++;
    return error_msg_e::NO_ERROR;
 }
};

#endif  // __PARSER__
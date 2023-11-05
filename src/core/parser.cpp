#include "parser.h"


void right_trim(std::string& in) {
    // apaga do ultimo caractere nao branco ate o fim da string
    in.erase(in.find_last_not_of(" \t") + 1);
  }
error_msg_e Parser::validate_infix() {
    // "exp" é a expressão recebida em bares_manager
    // check_
    // expr = exp;
    auto res {check_expression()};
    // formats_expression();
    // if (expr_runner == expr.size() - 1) {
    //     res = error_msg_e::NO_ERROR;
    // }
    return res;   
}
 

 void Parser::formats_expression() {
    StrTokenizer tokenizer(expr, " \t", true);
    tokens = tokenizer.get_token_list();
 }
 error_msg_e Parser::check_expression() {
    std::cout << "primeiro check\n";
    outcome = check_term();
    
    // If expression contains only one term
    
    check_wsp();

        while (expr_runner < expr.size() - 1) {
            
        
        if (outcome != error_msg_e::NO_ERROR and outcome != error_msg_e::END) {
            std::cout << "outcome : " << outcome << std::endl;
            break;
        }
        outcome = check_operator();
        std::cout << "passou na checagem do operador\n";
        if (outcome != error_msg_e::NO_ERROR) {
            break;
        }
        outcome = check_wsp();
        if (outcome != error_msg_e::NO_ERROR) {
            break;
        }
        
        std::cout << "ultimo check\n";
        outcome = check_term();
        if (outcome != error_msg_e::NO_ERROR) {
            break;
        }

        outcome = check_wsp();
    }
    return outcome;
        
    } 
 
 error_msg_e Parser::check_term() {
    check_wsp();
    if (expr[expr_runner] == '(') {
        check_wsp();
        check_expression();
        check_wsp();
        if (expr[expr_runner] != ')') {
            return error_msg_e::MISSING_LP;
        }
    } else {
        return check_int();
    }
    // if (check_int() == error_msg_e::NO_ERROR) {
    //     std::cout << "checou se é so um inteiro" << std::endl;
    //     return error_msg_e::NO_ERROR;
    // } else if (expr_runner == expr.size() - 1) {
    //     std::cout << "entrou aqui\n";
    //     return error_msg_e::NO_ERROR;
    // } else {
    //     if (expr[expr_runner] != '(') {
    //         std::cout << "check term (parenteses)" << std::endl;
    //          return error_msg_e::MISSING_TERM;
    //     }
    //     check_expression();
    //     if (expr[expr_runner] != ')') {
    //         return error_msg_e::MISSING_LP;
    //     }
    // }
 }
 error_msg_e Parser::check_int() {
    std::string curr_char;
    if (expr[expr_runner] == '-') {
        expr[expr_runner] = ',';
        expr_runner++;
    }
    return check_natural_num();
 }
 error_msg_e Parser::check_natural_num() {
    error_msg_e b;
    do {
        b = check_digit();
    } while (check_digit() == error_msg_e::NO_ERROR);
    if (b == error_msg_e::END) {
        b = error_msg_e::NO_ERROR;
    }
    return b;
    // return NO_ERROR;
 }
//  short Parser::check_digit_exc_zero();
 error_msg_e Parser::check_digit() {
    
    auto curr_char = expr[expr_runner];
    if (curr_char == '0' or curr_char == '1' or curr_char == '2' or curr_char == '3' or
        curr_char == '4' or curr_char == '5' or curr_char == '6' or curr_char == '7' or
        curr_char == '8' or curr_char == '9') {
            std::cout << "checando digito" << std::endl;
            std::cout << "Runner (digit): " << expr_runner << std::endl;
            return advance_runner();
            
        } else if ( expr_runner == expr.size() or expr[expr_runner] == ' ' or expr[expr_runner] == '+' or expr[expr_runner] == '-' or expr[expr_runner] == '/'
        or expr[expr_runner] == '^' or expr[expr_runner] == '%') {
                    return error_msg_e::END;
                   } 
        
        
        else {
            std::cout << "size : " <<expr.size() << std::endl;
            return error_msg_e::EXTRA_SYMBOL_AFTER_EXPR;   // Placeholder return
        }
 }
 error_msg_e Parser::check_wsp() {
    auto situation {error_msg_e::NO_ERROR};
    while (expr[expr_runner] == ' ') {
        situation = advance_runner();
        std::cout << "Runner (wsp): " << expr_runner << std::endl;
    }
    return situation;
 }
 error_msg_e Parser::check_operator() {
    if (expr[expr_runner] == '+' or expr[expr_runner] == '-' or expr[expr_runner] == '/'
        or expr[expr_runner] == '^' or expr[expr_runner] == '%') {
            std::cout << "checando operador" << std::endl;
            std::cout << expr.size() << std::endl;
            return advance_runner();
            std::cout << "Runner (op): " << expr_runner << std::endl;
        }
    else if (expr_runner == expr.size() - 1){
        std::cout << "ta aqui\n";
        std::cout << expr.size() << std::endl;
        return error_msg_e::UNEXPECTED_END_EXPR;
    }
     else {
        return NO_ERROR;
    }
 }
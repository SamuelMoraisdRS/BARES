#include "parser.h"


error_msg_e Parser::validate_infix() {

    auto res {check_expression()};
   
    return res;   
}
 
 void Parser::formats_expression() {
    
    // Separa os operadores (para a tokenização)
    
    auto sz {expr.size()};

    expr += " ";

    for (size_t i {0}; i < sz; i++) {
        std::string e {""};
        e += expr[i];
        if (is_operator(e) or e == "(" or e == ")") {
            expr.insert(i, " ");
            expr.insert(i + 2, " ");
            // Ajusta os indices para colocar os espacos na posicao anterior e posterior ao operador
            i +=2;
            sz += 2;
        }
    }


    std::cout << "EXPRESSAO COM ESPACAMENTOS: " << expr << "\n";

    StrTokenizer tokenizer(expr, " \t", true);
    tokens = tokenizer.get_token_list();
 }


 error_msg_e Parser::advance_runner() {
    expr_runner++;
    return error_msg_e::NO_ERROR;
 }


 error_msg_e Parser::check_expression() {

    std::cout << "primeiro check\n";

    //Se expressao tem apenas um termo
    outcome = check_term();
    
    check_wsp();
        
        while (expr_runner < expr.size() - 1) {
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
        if (outcome != error_msg_e::NO_ERROR and outcome != error_msg_e::END) {
            std::cout << "outcome : " << outcome << std::endl;
            break;
        }
    }
    return outcome;
        
    } 
 
 error_msg_e Parser::check_term() {
    check_wsp();
    if (expr[expr_runner] == '(') {
        advance_runner();
        check_wsp();
        check_expression();
        check_wsp();
        std::cout << "chegou no parentese de fechamento\n";
        if (expr[expr_runner] != ')') {
            return error_msg_e::MISSING_LP;
        } else {
            advance_runner();
            return NO_ERROR;
        }
    } else {
        return check_int();
    }
    
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
 
 }

 error_msg_e Parser::check_digit() {
    
    auto curr_char = expr[expr_runner];
    std::cout << "Qual o digito agr: "<< curr_char << std::endl;
    std::string converted_element {curr_char}; 
    if (curr_char == '0' or curr_char == '1' or curr_char == '2' or curr_char == '3' or
        curr_char == '4' or curr_char == '5' or curr_char == '6' or curr_char == '7' or
        curr_char == '8' or curr_char == '9') {
            std::cout << "checando digito" << std::endl;
            std::cout << "Runner (digit): " << expr_runner << std::endl;
            return advance_runner();
            
        } else if ( expr_runner == expr.size() or is_operator(converted_element) or is_wsp(curr_char)) {
                    return error_msg_e::END;
                   } 
    
        else {
            std::cout << "size : " <<expr.size() << std::endl;
            return error_msg_e::EXTRA_SYMBOL_AFTER_EXPR;   // Placeholder return
        }
 }
 error_msg_e Parser::check_wsp() {
    auto situation {error_msg_e::NO_ERROR};
    while (is_wsp(expr[expr_runner])) {
        std::cout << "Runner (wsp): " << expr_runner << std::endl;
        situation = advance_runner();
    }
    return situation;
 }
 error_msg_e Parser::check_operator() {
    if (expr[expr_runner] == '+' or expr[expr_runner] == '-' or expr[expr_runner] == '/'
        or expr[expr_runner] == '^' or expr[expr_runner] == '%' or expr[expr_runner] == '*') {
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
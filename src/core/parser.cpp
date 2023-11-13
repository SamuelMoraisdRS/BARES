#include "parser.h"


error_msg_e Parser::validate_infix() {
    
    auto res {check_expression()};
   
//    std::cout << "res: "<< res << std::endl;

    outcome = res;
    return res;  
    

     
}
 
 void Parser::formats_expression() {
    

    // Necessary to correctly index the out of range integer error
    auto expr_backup {expr};
    auto sz {expr.size()};
    expr += " ";

    // Adds white spaces between operands and operators, to facilitate the tokenization
    for (size_t i {0}; i < sz; i++) {
        std::string e {""};
        e += expr[i];
        if (is_operator(e) or e == "(" or e == ")") {
            expr.insert(i, " ");
            expr.insert(i + 2, " ");

            i +=2;
            sz += 2;
        }
    }
    
    // Tokenizes the expression
    StrTokenizer tokenizer(expr, " \t", true);
    tokens = tokenizer.get_token_list();

    // Converts the unary minus into a proper integer and spots the 'invalid integer' error
    for (std::string & e : tokens) {
        if (e.find(",") != std::string::npos) {
            e.replace(e.find(","),1,"-");
        }
        if (not is_operator(e) and e != "(" and e != ")") {
            auto numeric_value {std::stoll(e)};
            if ((numeric_value > UPPER_VALUE_RANGE) or (numeric_value < LOWER_VALUE_RANGE)) {
                outcome = error_msg_e::INTEGER_OUT_OF_RANGE;
                expr_runner = expr_backup.find(e);
            } 
       } 
    }
 }


 error_msg_e Parser::advance_runner() {
    expr_runner++;
    return error_msg_e::NO_ERROR;
 }


 error_msg_e Parser::check_expression() {

    //If expr has only one term
    outcome = check_term();

    if (outcome != NO_ERROR) {
        return outcome;
    }
    
    check_wsp();

        // If the expression isn't over yet
        while (expr_runner < expr.size()) {
        outcome = check_operator();
        if (outcome != error_msg_e::NO_ERROR) {
            break;
        }

        
        
        outcome = check_wsp();
        if (outcome != error_msg_e::NO_ERROR) {
            break;
        }
      
        outcome = check_term();
        if (outcome != error_msg_e::NO_ERROR) {
            break;
        }
        
        outcome = check_wsp();
        if (outcome != error_msg_e::NO_ERROR) {
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
        // If the expression within the parenthesis is incomplete
        if (expr_runner == expr.size()) {
            return MISSING_TERM;
        }
        outcome = check_expression();
        check_wsp();
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
    if (expr[expr_runner] == '-' or expr_runner <! expr.size()) {        
        return MISSING_TERM;
    } 
    b = check_digit();
    while (check_digit() == error_msg_e::NO_ERROR and expr_runner < expr.size()) {
        b = check_digit();
    }
    if (b == error_msg_e::END) {
        b = error_msg_e::NO_ERROR;
    }
    return b;
 
 }

 error_msg_e Parser::check_digit() {
    
    auto curr_char = expr[expr_runner];    
    if (is_digit(curr_char)) {
            return advance_runner();
        } else if ( (is_wsp(curr_char) and is_digit(expr[expr_runner-1])) or
                   (is_operator(curr_char) and is_digit(expr[expr_runner-1]))) {
                    // The analysed number has ended without errors
                    return error_msg_e::END;
        } else {
                return error_msg_e::MISSING_TERM;
        }
        return error_msg_e::NO_ERROR;   // to remove warning
 }
 error_msg_e Parser::check_wsp() {
    auto situation {error_msg_e::NO_ERROR};
    while (is_wsp(expr[expr_runner])) {
        situation = advance_runner();    
    }
    return situation;
 }
 error_msg_e Parser::check_operator() {
    if (expr[expr_runner] == '+' or expr[expr_runner] == '-' or expr[expr_runner] == '/'
        or expr[expr_runner] == '^' or expr[expr_runner] == '%' or expr[expr_runner] == '*') {
            return advance_runner();
        }
    else if (expr_runner == expr.size()){
        expr_runner++;
        return error_msg_e::EXTRA_SYMBOL_AFTER_EXPR;
    }
     else {
        return EXTRA_SYMBOL_AFTER_EXPR;
    }
 }
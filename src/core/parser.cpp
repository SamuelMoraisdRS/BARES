#include "parser.h"


error_msg_e Parser::validate_infix() {
    
    auto res {check_expression()};
   
//    std::cout << "res: "<< res << std::endl;

    outcome = res;
    return res;  
    

     
}
 
 void Parser::formats_expression() {
    
    // Separa os operadores (para a tokenização)

    // Necessário para identificar corretamente o erro de inteiro fora do range aceito
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
    // debug
    // std::cout << "EXPRESSAO COM ESPACAMENTOS: " << expr << "\n";

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
            // std::cout << "checando se : " << numeric_value << " está no range\n";
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

    // std::cout << "primeiro check\n";

    //Se expressao tem apenas um termo
    outcome = check_term();

    if (outcome != NO_ERROR) {
        // std::cout << "erro no primeiro check\n";
        // std::cout << "erro no primeiro check\n";
        return outcome;
    }
    // std::cout << "checou a primeira vez\n";
    
    check_wsp();
        
        // Se a expressão não acabou
        while (expr_runner < expr.size()) {
        outcome = check_operator();
        // std::cout << "passou na checagem do operador\n";
        if (outcome != error_msg_e::NO_ERROR) {
            // std::cout << "erro no operador\n";
            break;
        }

        
        
        outcome = check_wsp();
        if (outcome != error_msg_e::NO_ERROR) {
            break;
        }
        
        
        // std::cout << "ultimo check\n";
        
        outcome = check_term();
        if (outcome != error_msg_e::NO_ERROR) {
            // std::cout << "erro no segundo termo\n";
            break;
        }
        
        outcome = check_wsp();
        if (outcome != error_msg_e::NO_ERROR) {
            // std::cout << "outcome : " << outcome << std::endl;
            break;
        }
    }
    return outcome;
        
    } 
 
 error_msg_e Parser::check_term() {
    check_wsp();
    // std::cout << "indice(wsp): " << expr_runner << std::endl;
    if (expr[expr_runner] == '(') {
        advance_runner();
        check_wsp();
        check_expression();
        check_wsp();
        // std::cout << "chegou no parentese de fechamento\n";
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
        // std::cout << "char atual: " << expr[expr_runner] <<std::endl;
        expr_runner ++;
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

    // std::cout << "Qual o digito agr: "<< curr_char << std::endl;
    
    if (is_digit(curr_char)) {
            // std::cout << "checando digito" << std::endl;
            // std::cout << "Runner (digit): " << expr_runner << std::endl;
            has_operator = false;
            return advance_runner();

            
        } else if ((curr_char == '-' and expr[expr_runner + 1] == '-') or 
                    curr_char == ' ' and not is_digit(expr[expr_runner - 1])) {
            // std::cout << "char atual : " << curr_char <<  std::endl;
            return error_msg_e::MISSING_TERM;
        } else if (expr_runner == expr.size() and has_operator) {
            expr_runner++;
            return  MISSING_TERM;
        }
         else if ( (is_wsp(curr_char) and is_digit(expr[expr_runner-1])) or is_operator(curr_char)) {
                    // std::cout << "parou de checar digito\n";
                    // std::cout << "termo final: " << expr[expr_runner] << std::endl;
                    // std::cout << "termo anterior: " << expr[expr_runner-1] << std::endl;
                    return error_msg_e::END;
                   } 
        else {
            // std::cout << "size : " <<expr.size() << std::endl;
           
                return error_msg_e::MISSING_TERM;
           
               // Placeholder return
        }
 }
 error_msg_e Parser::check_wsp() {
    auto situation {error_msg_e::NO_ERROR};
    while (is_wsp(expr[expr_runner])) {
        // std::cout << "Runner (wsp): " << expr_runner << std::endl;
        situation = advance_runner();    
    }
    return situation;
 }
 error_msg_e Parser::check_operator() {
    if (expr[expr_runner] == '+' or expr[expr_runner] == '-' or expr[expr_runner] == '/'
        or expr[expr_runner] == '^' or expr[expr_runner] == '%' or expr[expr_runner] == '*') {
            // std::cout << "checando operador" << std::endl;
            // std::cout << expr.size() << std::endl;

            // if (expr_runner == expr.size() - 1) {
            //     return MISSING_TERM;
            // }
            // std::cout << "operador atual: " << expr[expr_runner] << std::endl;
            has_operator = true;
            return advance_runner();
            // std::cout << "Runner (op): " << expr_runner << std::endl;
        }
    else if (expr_runner == expr.size()){
        // std::cout << "ta aqui\n";
        // std::cout << expr.size() << std::endl;
        
        expr_runner++;
        return error_msg_e::EXTRA_SYMBOL_AFTER_EXPR;
    }
     else {
        return NO_ERROR;
    }
 }
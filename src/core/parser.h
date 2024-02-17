#ifndef __PARSER__
#define __PARSER__

// converte para posfixo e encontra erros de 
#include "../libs/bares_common.h"

#include "../libs/tokenizer.h"



class Parser {
private:
    std::string expr;                                   //!< Input expression
    size_t expr_runner = 0;                             //!< Idx that'll run through the expression during validation
    StrTokenizer tokenizer;                             //!< Splits the expression into tokens
    std::vector<std::string> tokens;                    //!< List of tokens containing the expression's elements
    error_msg_e outcome = error_msg_e::NO_ERROR;        //!< Variable that'll indicate if the validation was succesful/what error occurred
public:
    /// Ctro 
    Parser(std::string & e) : expr {e} {

    };
    /// Checks if the infix expression is correct, return the corresponding error msg if not.
    error_msg_e validate_infix();
    /// Formats the validated expression and tokenizes them.
    void formats_expression();
    /// Returns the token list
    std::vector<std::string> get_tokens() const {
        return tokens;
    }
    /// Returns the collumn in which an error was detected
    int get_error_col() const {
        return expr_runner;
    }
    /// Returns the outcome 
    error_msg_e get_outcome() const {
        return outcome;
    }
private:
 
 /// Splits the expression into tokens 
 std::string tokenize_expr();

//== These methods will be used to check the EBNF grammar
 error_msg_e check_expression();
 error_msg_e check_term();
 error_msg_e check_int();
 error_msg_e check_natural_num();
 error_msg_e check_digit();
 error_msg_e check_wsp();
 error_msg_e check_operator();

 /// Increments the runner variable
 error_msg_e advance_runner();
};

#endif  // __PARSER__
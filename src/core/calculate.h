#ifndef __CALCULATE__
#define __CALCULATE__



// converte e faz o calculo

#include <cmath>
#include <iostream>
#include <string>
#include "../libs/data_structs.h"
#include "../libs/bares_common.h"

using namespace ds;


class Calculator {
private:
    ds::Queue<std::string> infix_queue;                     //!< Queue containg the infix expression
    ds::Stack<int> operand_stck;                            //!< Stack that holds the expressions operands
    ds::Stack<std::string> operator_stck;                   //!< Stack that holds the expressions operators
    ds::Queue<std::string> posfix_expr;                     //!< Queue containing the posfix expression
    error_msg_e expression_error = error_msg_e::NO_ERROR;   //!< Variabel that holds the current error msg

    private:


    // == These methods are used to evaluate the expression

    /// Checks the precedence between the operators in the operator stack
    /// @param a First operator
    /// @param b Second operator
    /// @return 'True' if the operator at the top of the stack should be popped, 'False' if otherwise
    bool higher_precedence (std::string a, std::string b);

    // == Operations
    
    int div (const int & a, const int & b);
    int mult (const int & a, const int & b);
    int sum (const int & a, const int & b);
    int minus (const int & a, const int & b);
    int mod (const int & a, const int & b);
    int pow (const int & a, const int & b);

    /// @brief Identifies an error during one of the operations
    void identify_error(int error_id);

    /// @brief Applies the operation on the expression
    /// @param op Operation 
    /// @param a First operand
    /// @param b Second operand
    /// @return The expression value
    int apply_operation(std::string op, int a, int b);

    /// @brief This method is used to correctly convert expressions inside of parenthesis, if there are
    /// nested parenthesis, it will be called recursively
    /// @param previous_operators The stack containing the operators extracted from the expression outside of
    /// the current nesting
    void convert_nested_expr(Stack<std::string> & previous_operators);
public:
    /// Converts the infiz expression expression into its posfix counterpart
    /// @param a The vector representing the infix expression
    void convert_to_posfix(std::vector<std::string> a);
    
    /// Evaluates the posfix expression
    /// @return The expression's result, as a std::string object
    std::string evaluate_expr();

};

#endif  // __CALCULATE__
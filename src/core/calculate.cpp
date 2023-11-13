#include "calculate.h"

using namespace ds;

bool Calculator::higher_precedence (std::string a, std::string b) {
        operator_e operatorA, operatorB;
        if (a == "+") {operatorA = operator_e::SUM;}
        if (a == "-") {operatorA = operator_e::MINUS;}
        if (a == "/") {operatorA = operator_e::DIV;}
        if (a == "%") {operatorA = operator_e::MOD;}
        if (a == "^") {operatorA = operator_e::POW;}
        if (a == "*") {operatorA = operator_e::MULT;}
    
        if (b == "+") {operatorB = operator_e::SUM;}
        if (b == "-") {operatorB = operator_e::MINUS;}
        if (b == "/") {operatorB = operator_e::DIV;}
        if (b == "%") {operatorB = operator_e::MOD;}
        if (b == "^") {operatorB = operator_e::POW;}
        if (b == "*") {operatorB = operator_e::MULT;}
        
        // Checks which term has higher precedence
        if (operatorA > operatorB) {
            return false;
        } else if (operatorA < operatorB) {
            return true;
        } else {                            // If they have equal precedence
            if ((int)operatorA <= 1) {
                return true;
            } else  {
                return false;
            }
        }
        return false;   // To remove the warning
    };

    // == Operations
    
    int Calculator::div (const int & a, const int & b) {
        return b/a;
    }
    int Calculator::mult (const int & a, const int & b) {
        return a*b;
    }
    int Calculator::sum (const int & a, const int & b) {
        return a+b;
    }
    int Calculator::minus (const int & a, const int & b) {
        return b-a;
    }
    int Calculator::mod (const int & a, const int & b) {
        return b%a;
    }
    int Calculator::pow (const int & a, const int & b) {
        return std::pow(a,b);
    }

    void Calculator::identify_error(int error_id) {
        if (error_id == 1) {
            expression_error = UNDEFINED_VALUE;
        } else if (error_id == 2) {
            expression_error = DIVISION_BY_ZERO;
        } else if (error_id == 3) {
            expression_error = NUMERIC_OVERFLOW;
        }
    }

    
    int Calculator::apply_operation(std::string op, int a, int b) {
        if (op == "+") {
            return sum(a,b);
        } else if (op == "-") {
            return minus(a,b);
        } else if (op == "/") {
            if (a == 0) {
                identify_error(2);
                return 0;   //stub
            }
            return div(a,b);
        } else if (op == "%") {
            return mod(a,b);
        } else if (op == "*") {
            return mult(a,b);
        } else if (op == "^") {
            if (a == 0 and b == 0) {
                identify_error(1);
                return 0;
            }
            return pow(b,a);
        }
        return 0;
    }


    void Calculator::convert_nested_expr(Stack<std::string> & previous_operators) {
        // The operators found within the current parenthesis
        Stack<std::string> parenthesis_oprs;
        std::string term {""};
                while (term != ")") {
                term = infix_queue.dequeue();
                if (term == ")") {
                    break;
                } else if (term == "(") {
                    // Recursive call
                    convert_nested_expr(parenthesis_oprs);
                } else if (not is_operator(term) and term != ")") {
                    posfix_expr.enqueue(term);
                } else if (parenthesis_oprs.empty()){
                    parenthesis_oprs.push(term);
                } else {
                    if (term != ")") {
                    while ((not parenthesis_oprs.empty()) and higher_precedence(term, parenthesis_oprs.get_upper())) {
                        posfix_expr.enqueue(parenthesis_oprs.pop());
                        }
                    parenthesis_oprs.push(term);
                    } else {
                        // Does nothing
                    }
                    
                }
            } while (not parenthesis_oprs.empty()) {    // Dumps the remaining operators into the expression
                posfix_expr.enqueue(parenthesis_oprs.pop());
            } 
    }

    void Calculator::convert_to_posfix(std::vector<std::string> a) {
        // Fills the infix expression queue
        for (std::string e : a) {
            infix_queue.enqueue(e);
        }

        // Conversion
        while (not infix_queue.empty()) {
            ds::Stack<std::string> nested_opr;
            auto term {infix_queue.dequeue()};

            if (term == "(") {
                convert_nested_expr(operator_stck);
            } else if (not is_operator(term)) {    
                posfix_expr.enqueue(term);
            } else if (operator_stck.empty()) {
                operator_stck.push(term);
            }  else {
                while (((not operator_stck.empty())) and (higher_precedence(term, operator_stck.get_upper()))) {
                    posfix_expr.enqueue(operator_stck.pop());
                }
                operator_stck.push(term);
            }
        }
    
        while (not operator_stck.empty()) {
            posfix_expr.enqueue(operator_stck.pop());
        }

     }
    
    std::string Calculator::evaluate_expr() {
        while (not posfix_expr.empty()) {
            auto e {posfix_expr.dequeue()};
            if (not is_operator(e)) {
                operand_stck.push(std::stol(e));
            } else {
                std::pair<int,int> operands {operand_stck.pop_operands()};
                auto operand1 {operands.first};
                auto operand2 {(operands.second)};
                auto result {apply_operation(e, operand1, operand2)};
                operand_stck.push(result);
            }
        }
        auto value {operand_stck.pop()};
        auto result {std::to_string(value)};

        if (value > UPPER_VALUE_RANGE or value < LOWER_VALUE_RANGE) {
            expression_error = error_msg_e::NUMERIC_OVERFLOW;
        }
        if (expression_error != NO_ERROR) {
            result = get_msg(expression_error, -1); 
        }
        return result;
    }


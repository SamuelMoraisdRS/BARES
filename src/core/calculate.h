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
    ds::Queue<std::string> infix_queue;
    ds::Stack<int> operand_stck;
    ds::Stack<std::string> operator_stck;
    ds::Queue<std::string> posfix_expr;
    
    error_msg_e expression_error = error_msg_e::NO_ERROR;

    private:


    // == Checks operands or operators

   

    bool higher_precedence (std::string a, std::string b) {
        operator_e operatorA, operatorB;
        if (a == "+") {operatorA = operator_e::SUM;}
        else if (a == "-") {operatorA = operator_e::MINUS;}
        else if (a == "/") {operatorA = operator_e::DIV;}
        else if (a == "%") {operatorA = operator_e::MOD;}

        if (b == "+") {operatorA = operator_e::SUM;}
        else if (b == "-") {operatorB = operator_e::MINUS;}
        else if (b == "/") {operatorB = operator_e::DIV;}
        else if (b == "%") {operatorB = operator_e::MOD;}

        if (operatorA > operatorB) {
            return true;
        } else if (operatorA < operatorB) {
            return false;
        } else {
            if ((int)operatorA <= 1) {
                return true;
            } else if ((int)operatorB == 2) {
                return false;
            }
        }
        return false;   // Para remover o warning
    };

    // == Operations
    
    int div (const int & a, const int & b) {
        return b/a;
    }
    int mult (const int & a, const int & b) {
        return a*b;
    }
    int sum (const int & a, const int & b) {
        return a+b;
    }
    int minus (const int & a, const int & b) {
        return b-a;
    }
    int mod (const int & a, const int & b) {
        return b%a;
    }
    int pow (const int & a, const int & b) {
        return std::pow(a,b);
    }

    void identify_error(int error_id) {
        if (error_id == 1) {
            expression_error = UNDEFINED_VALUE;
        } else if (error_id == 2) {
            expression_error = DIVISION_BY_ZERO;
        } else if (error_id == 3) {
            expression_error = NUMERIC_OVERFLOW;
        }
    }

    
    int apply_operation(std::string op, int a, int b) {
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
    }

   
    
public:

    void convert_nested_expr(Stack<std::string> & previous_operators) {
        Stack<std::string> parenthesis_oprs;
        std::string term {""};
                while (term != ")") {
                term = infix_queue.dequeue();
                
                if (term == ")") {
                    break;
                } else if (term == "(") {
                    std::cout << "entrou na recursao\n"; 
                    convert_nested_expr(parenthesis_oprs);
                } else if (not is_operator(term) and term != ")") {
                    std::cout << "term inserido (parenteses): " << term << "\n";
                    posfix_expr.enqueue(term);
                } else if (parenthesis_oprs.empty()){
                    parenthesis_oprs.push(term);
                    std::cout << "OPERADOR "<< term << std::endl;
                } else {
                    if (term != ")") {
                        while ((not parenthesis_oprs.empty()) and higher_precedence(term, parenthesis_oprs.get_upper())) {
                    posfix_expr.enqueue(parenthesis_oprs.pop());
                    std::cout << "OPERADOR "<< posfix_expr.back() << std::endl;
                    // std::cout << "5*\n";
                    }
                 parenthesis_oprs.push(term);
                    } else {

                    }
                    
                }
            }
            while (not parenthesis_oprs.empty()) {
                posfix_expr.enqueue(parenthesis_oprs.pop());
            } 
            while (not previous_operators.empty()) {
                std::cout << "upper element (previous_operator): " << previous_operators.get_upper() << "\n";
                posfix_expr.enqueue(previous_operators.pop());
            }
    }

    error_msg_e convert_to_posfix(std::vector<std::string> a) {
        
        // Preenche a fila infixa
        for (std::string e : a) {
            std::cout << "preenchendo a fila da infixa: " << e << "\n";
            infix_queue.enqueue(e);
        }

             
        while (not infix_queue.empty()) {

            ds::Stack<std::string> nested_opr;
            auto term {infix_queue.dequeue()};

            if (term == "(") {
                convert_nested_expr(operator_stck);
                for (std::string e : posfix_expr.data) {
                    std::cout << "expressao posfixa dps dos parenteses: " << e << " ";
                }
                std::cout << std::endl;
            } else if (not is_operator(term)) {    
                std::cout << "termo atual (fora dos parenteses): " << term << "\n";
                posfix_expr.enqueue(term);
            } else if (operator_stck.empty()) {
                operator_stck.push(term);
                // std::cout << "4*\n";
            }  else {
                while ((not operator_stck.empty()) and higher_precedence(term, operator_stck.get_upper())) {
                    posfix_expr.enqueue(operator_stck.pop());
                    // std::cout << "5*\n";
                }
                operator_stck.push(term);
                // std::cout << "6*\n";
            }
            // std::cout << "7*\n";
        }
    
        while (not operator_stck.empty()) {
            posfix_expr.enqueue(operator_stck.pop());
        }
        // std::cout << posfix_expr.back() << std::endl;

        

        std::cout << "Mostrando a expressao pos fixa\n";
        std::cout << posfix_expr.size();
        std::string teste;
        for (std::string e : posfix_expr.data) {
            teste += e + " ";
            std::cout << e << std::endl;
        }
        teste += "\n";
        std::cout << teste;
     }
    
    std::string evaluate_expr() {
        while (not posfix_expr.empty()) {
            auto e {posfix_expr.dequeue()};
            if (not is_operator(e)) {
                std::cout << "Valor a ser calculado: " << e << std::endl;
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
            expression_error = NUMERIC_OVERFLOW;
        }
        if (expression_error != NO_ERROR) {
            result = get_msg(expression_error, -1);   // 1000 is a stub
        }
        return result;
    }
    ds::Queue<std::string> get_expr_queue() {
        return infix_queue;
    }

};

#endif  // __CALCULATE__
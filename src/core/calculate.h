#ifndef __CALCULATE__
#define __CALCULATE__



// converte e faz o calculo

#include <cmath>
#include <iostream>
#include "../libs/data_structs.h"

using namespace ds;

enum class operator_e {
    SUM = 0,
    MINUS = 0,
    MULT = 1,
    DIV = 1,
    MOD = 1,
    POW
};

class Calculator {
private:
    ds::Queue<std::string> infix_queue;
    ds::Stack<std::string> operand_stck;
    ds::Stack<std::string> operator_stck;
    ds::Queue<std::string> posfix_expr;

    private:


    // == Checks operands or operators

    bool is_operator(const std::string & term) {
        return (term == "+" or term == "-" or term == "/" or term == "*" or
                term == "%" or term == "^");
    }

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
            if ((short)operatorA <= 1) {
                return true;
            } else if ((short)operatorB == 2) {
                return false;
            }
        }
    }

    // == Operations
    short div (const short & a, const short & b) {
        return a/b;
    }
    short mult (const short & a, const short & b) {
        return a*b;
    }
    short sum (const short & a, const short & b) {
        return a+b;
    }
    short minus (const short & a, const short & b) {
        return a-b;
    }
    short pow (const short & a, const short & b) {
        return std::pow(a,b);
    }

public:
    void convert_to_posfix(std::vector<std::string> a) {
        
        for (std::string e : a) {
            infix_queue.enqueue(e);
        }
        std::cout << "Fila do infixo\n";
        for (std::string e : infix_queue.data) {
            std::cout << e << std::endl;
        }

        
        
        std::cout << "1*\n";
        for (size_t i {0}; i++; i < infix_queue.size()-1) {
            auto term {infix_queue.dequeue()};
            std::cout << "2*\n";
            std::cout << "termo: " << term << std::endl;
            if (not is_operator(term)) {    
                posfix_expr.enqueue(term);
                std::cout << "3*\n";
            } else if (operator_stck.empty()) {
                operator_stck.push(term);
                std::cout << "4*\n";
            } else {
                while ((not operator_stck.empty()) and higher_precedence(operator_stck.get_upper(), term)) {
                    posfix_expr.enqueue(operator_stck.pop());
                    std::cout << "5*\n";
                }
                operator_stck.push(term);
                std::cout << "6*\n";
            }
            std::cout << "7*\n";
        }
        while (not operator_stck.empty()) {
            posfix_expr.enqueue(operand_stck.pop());
        }

        std::cout << "MOstrando a expressao pos fixa\n";
        std::cout << posfix_expr.size();

        for (std::string e : posfix_expr) {
            std::cout << e << std::endl;
        }
     }

    ds::Queue<std::string> get_expr_queue() {
        return infix_queue;
    }

    std::vector<std::string> get_posfix() {
        return posfix_expr.data;
    }
};

#endif  // __CALCULATE__
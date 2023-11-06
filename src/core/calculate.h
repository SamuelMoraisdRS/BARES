#ifndef __CALCULATE__
#define __CALCULATE__



// converte e faz o calculo

#include <cmath>
#include <iostream>
#include "../libs/data_structs.h"
#include "../libs/bares_common.h"

using namespace ds;


class Calculator {
private:
    ds::Queue<std::string> infix_queue;
    ds::Stack<std::string> operand_stck;
    ds::Stack<std::string> operator_stck;
    ds::Queue<std::string> posfix_expr;

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
            if ((short)operatorA <= 1) {
                return true;
            } else if ((short)operatorB == 2) {
                return false;
            }
        }
    };

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
        
        // Preenche a fila infixa
        for (std::string e : a) {
            infix_queue.enqueue(e);
        }
      
        size_t sz {infix_queue.size()};
        
        std::cout << "1*\n";
        for (size_t i {0}; i < sz; i++) {

            std::cout << "entrou\n";
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
                while ((not operator_stck.empty()) and higher_precedence(term, operator_stck.get_upper())) {
                    posfix_expr.enqueue(operator_stck.pop());
                    std::cout << "5*\n";
                }
                operator_stck.push(term);
                std::cout << "6*\n";
            }
            std::cout << "7*\n";
        }

    	std::cout << "saiu\n" << operator_stck.size() << "\n";

        while (not operator_stck.size() == 0) {
            std::cout << "entrou na parte final\n";
            posfix_expr.enqueue(operator_stck.pop());
        }
        std::cout << "parte final\n";

        std::cout << posfix_expr.data.back() << std::endl;

        std::cout << "MOstrando a expressao pos fixa\n";
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
        for (std::string e : posfix_expr) {
            if (not is_operator(e)) {
                operand_stck.push(e);
            } else {
                auto operand1 {operand_stck.pop_operands().first};
                auto operand2 {operand_stck.pop_operands().second};
                
            }
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
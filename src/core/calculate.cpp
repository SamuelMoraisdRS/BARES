// #include <string>
// #include "calculate.h"

// using namespace ds;

// void Calculator::convert_to_posfix() {
//     auto first {infix_queue.begin()};
//     while (first != infix_queue.end()) {
//         auto term {infix_queue.dequeue()};
//         if (is_operand(term)) {
//             posfix_expr.enqueue(term);
//         } else if (operator_stck.empty()){
//             operator_stck.push(term);
//         } else {
//             while ((not operator_stck.empty()) and higher_precedence(operator_stck.get_upper(), term)) {
//                 posfix_expr.enqueue(operator_stck.pop());
//             } operand_stck.push(term);
//             operator_stck.push(term);
//         }
//     }

//     ds::Queue<std::string> Calculator::get_expr_queue() ;{
//     return infix_queue;
//     }

//     std::vector<std::string> Calculator::get_posfix() {
//         return posfix_expr.data;
//     }

//     bool is_operand(const std::string & term) {
//         return (term == "+" or term == "-" or term == "/" or term == "*" or
//                 term == "%" or term == "^");
//     }

//     bool higher_precedence (std::string a, std::string b) {
//         operator_e operatorA, operatorB;
//         if (a == "+") {operatorA = operator_e::SUM;}
//         else if (a == "-") {operatorA = operator_e::MINUS;}
//         else if (a == "/") {operatorA = operator_e::DIV;}
//         else if (a == "%") {operatorA = operator_e::MOD;}

//         if (b == "+") {operatorA = operator_e::SUM;}
//         else if (b == "-") {operatorB = operator_e::MINUS;}
//         else if (b == "/") {operatorB = operator_e::DIV;}
//         else if (b == "%") {operatorB = operator_e::MOD;}

//         if (operatorA > operatorB) {
//             return true;
//         } else if (operatorA < operatorB) {
//             return false;
//         } else {
//             if ((short)operatorA <= 1) {
//                 return true;
//             } else if ((short)operatorB == 2) {
//                 return false;
//             }
//         }
//     }

    
//     short Calculator::div (const short & a, const short & b) {
//         return a/b;
//     }
//     short Calculator::mult (const short & a, const short & b) {
//         return a*b;
//     }
//     short Calculator::sum (const short & a, const short & b) {
//         return a+b;
//     }
//     short Calculator::minus (const short & a, const short & b) {
//         return a-b;
//     }
//     short Calculator::pow (const short & a, const short & b) {
//         return std::pow(a,b);
//     }

// }
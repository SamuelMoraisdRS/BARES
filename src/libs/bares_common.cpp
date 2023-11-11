#include "bares_common.h"
#include <iostream>

std::string get_msg(const short & msg_idx, const short & col = -1) {
    std::string sufix;
    if (msg_idx <= 4) {
         sufix += std::to_string(col) + ")!";
    } else if (msg_idx == 10) {
        return "";
    }
    return (msgs[msg_idx] + sufix);
};

bool is_operator(std::string term) {
    return (term == "+" or term == "-" or term == "/" or term == "*" or
            term == "%" or term == "^");
}

bool is_operator(char term) {
    return (term == '+' or term == '-' or term == '/' or term == '*' or
            term == '%' or term == '^');
}

bool is_wsp(const char & term) {
    return (term == ' ' or term == '\t');
}

bool is_digit(char term) {
    return (term == '0' or term == '1' or term == '2' or term == '3' or
        term == '4' or term == '5' or term == '6' or term == '7' or
        term == '8' or term == '9'); 
}


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


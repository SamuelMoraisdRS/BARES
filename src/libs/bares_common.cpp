#include "bares_common.h"
#include <iostream>

std::string get_msg(const short & msg_idx, const short & col) {
    std::string sufix;
    if (msg_idx < 4) {
         sufix += std::to_string(col) + ")!";
    } else if (msg_idx == 10) {
        return "";
    }
    return (msgs[msg_idx] + sufix + "\n");
};

bool is_operator(std::string term) {
        
        std::cout << "Checando operador\n";
        return (term == "+" or term == "-" or term == "/" or term == "*" or
                term == "%" or term == "^");
    }


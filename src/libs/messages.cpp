#include "messages.h"

std::string get_msg(const short & msg_idx, const short & col) {
    std::string sufix;
    if (msg_idx < 4) {
         sufix += std::to_string(col) + ")!";
    } else if (msg_idx == 10) {
        return "";
    }
    return (msgs[msg_idx] + sufix + "\n");
};
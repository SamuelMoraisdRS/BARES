
#include <string>

class Msgs {
private:
    std::string curr_msg;

    const std::string msgs [8] {
        "Missing <term> at column (",
        "Unexpected end of expression at column (",
        "Extra symbol after valid expression found at column (",
        "Missing closing ”)” at column (",
        "Integer constant out of range beginning at column (",
        "Undefined value!",
        "Division by zero!",
        "Numeric overflow error!"
    };


public:

std::string get_msg(const short & msg_idx, const short & col) {
    return (msgs[msg_idx] + (msg_idx > 4 ? (std::to_string(col) + ")!") : "") + "\n");
};


};
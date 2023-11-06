#ifndef __MSGS__
#define __MSGS__
#include <string>

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


    
    /// Tracks the error type
    enum  error_msg_e : short {
        MISSING_TERM = 0,
        UNEXPECTED_END_EXPR,
        EXTRA_SYMBOL_AFTER_EXPR,
        MISSING_LP,
        INTEGER_OUT_OF_RANGE,
        UNDEFINED_VALUE,
        DIVISION_BY_ZERO,
        NUMERIC_OVERFLOW,
        NO_ERROR = 10,
        END
    };

std::string get_msg(const short & msg_idx, const short & col);

#endif

#ifndef __OPERATORS__
#define __OPERATORS__
bool is_operator(std::string term);

bool is_wsp(const char & term);



enum class operator_e {
SUM = 0,
MINUS = 0,
MULT = 1,
DIV = 1,
MOD = 1,
POW
};



#endif


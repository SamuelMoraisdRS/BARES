
#ifndef __COMMON__
#define __COMMON__
#include <string>

    //!< Array containing the possible error msgs
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

    //!< Tracks the error type
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

    
    const int UPPER_VALUE_RANGE {32767};    //!< The maximum integer accepted in an expression
    const int LOWER_VALUE_RANGE {-32768};   //!< The minimum integer accepted in an expression

/// Returns the appropriate message, in std::string format
/// @param msg_idx The index indicating what message should be displayed
/// @param col  The collumn in which the error has been found
std::string get_msg(const short & msg_idx, const short & col);

/// These functions return 'true' if the element is an operator
/// @param term The term that will be checked
bool is_operator(std::string term);
bool is_operator(char term);

/// Returns 'true' if 'term' a whitespace character (' ' or '\t')
bool is_wsp(const char & term);
/// Returns 'true' if 'term' is a digit 
bool is_digit(char term);

/// Values attributed to each operation. Will be used to determine the precedence between two operators
enum class operator_e {
SUM = 0,
MINUS = 0,
MULT = 1,
DIV = 1,
MOD = 1,
POW
};

#endif // __COMMON__


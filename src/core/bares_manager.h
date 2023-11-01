// une todas as classes
#include <string>
#include "calculate.h"
#include "parser.h"

namespace br
{
    // constexpr std::string error_msgs []
    
    
    
    
    /// Tracks the error type
    enum  error_msg_e : short {
        MISSING_TERM = 0,
        UNEXPECTED_END_EXPR,
        EXTRA_SYMBOL_AFTER_EXPR,
        MISSING_LP,
        INTEGER_OUT_OF_RANGE,
        UNDEFINED_VALUE,
        DIVISION_BY_ZERO,
        NUMERIC_OVERFLOW
    };


    class BARES {
private:
    std::string input_expr;  //!< Input expression string
    Parser validator;         //!< finds sintatical errors and returns a properly formatted infix expression
    Calculator calc          //!< Calculates the formatted expression
    std::string result;      //!< Final expression returned to user
    bool error_found = false; //!< Indicates if an error was found in the parsing process
public:
    ///Ctro
    BARES(std::string input) : input_expr {input} {
    }
    ~BARES() = default;


    /// Parses the input string (formats it and finds errors)

    // Se houver erro, error_found =  true  e result = mensagem de erro
    void parses();  

    // [1] Se houver erro no parse, faz nada ( error_found ==  true)
    // [2] Senão, convere para posfixo
    // [3] Calcula
    // [4] Result = resultado da expressao ou result = erro
    void calculates();

    
};
    
} // namespace name



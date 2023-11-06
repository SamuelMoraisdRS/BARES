#ifndef __BARES__
#define __BARES__


// une todas as classes
#include <string>
#include "calculate.h"
#include "parser.h"
// #include "../libs/messages.h"


namespace br
{
    // constexpr std::string error_msgs []
    
    
    

    class BARES {
private:
    std::string expression;             //!< Input expression string
    Calculator calc;                    //!< Calculates the formatted expression
    std::string result;                 //!< Final expression returned to user
    bool error_found = false;           //!< Indicates if an error was found in the parsing process
    std::vector<std::string> tokens;    
public:
    ///Ctro
    BARES(std::string input) : expression {input} {
    }
    ~BARES() = default;

    /// Parses the input string (formats it and finds errors)

    // Se houver erro, error_found =  true  e result = mensagem de erro
    // Se n houver erro, result = expressão tokenizada
    void parses();  

    // [1] Se houver erro no parse, faz nada ( error_found ==  true)
    // [2] Senão, convere para posfixo
    // [3] Calcula
    // [4] Result = resultado da expressao ou result = erro
    void calculate();

    std::string get_result() const {
        return result;
    }
private:
    // std::string get_msg(const short & msg_idx, const short & col);
    
};
    
} // namespace name
#endif  // __BARES_


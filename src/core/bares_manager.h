#ifndef __BARES__
#define __BARES__


#include <string>
#include "calculate.h"
#include "parser.h"

namespace br
{
    class BARES {
private:
    std::string expression;             //!< Input expression string
    Calculator calc;                    //!< Calculates the formatted expression
    std::string result;                 //!< Final expression returned to user
    bool error_found = false;           //!< Indicates if an error was found in the parsing process
    std::vector<std::string> tokens;    //!< Expression split into tokens
    bool empty_expression = false;      //!< Flag that indicates if the expression is empty 
public:
    ///Ctro
    BARES(std::string input) : expression {input} {
    }
    ~BARES() = default;

    /// Parses the input string (formats it and finds errors)
    void parses();  

    /// Converts the input expression into its postfix form and evaluates it.
    void calculate();

    /// Returns the result, that might be an error msg or a numeric value 
    std::string get_result() const {
        return result;
    }    
};
} // namespace br
#endif  // __BARES_


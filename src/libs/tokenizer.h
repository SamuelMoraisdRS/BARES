#ifndef __TOKENIZER__
#define __TOKENIZER__

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/// @brief Class to tokenize a strign
class StrTokenizer {
  std::string input;                //!< Input String
  std::string divider;              //!< List of the characters used to split the string
  bool trimming;                    //!< Flag that indicates if whitespaces should be trimmed
  std::vector<std::string> tokens;  //!< Token list
  size_t current_token;             //!< Current token index

public:
  StrTokenizer() = default;
  /// Ctro
  /// @param i Input
  /// @param d Divider
  /// @param t Flag to indicate if the wrapping should be done
  StrTokenizer(const std::string i, const std::string d = ", ", const bool t = true);
  /// Returns a token
  std::string get_token();
  /// Returns the token list 
  std::vector<std::string> get_token_list() { return tokens; }

  /// @brief Deletes whitespaces in the left side
  /// @param in Token
  void left_trim(std::string& in);

  /// @brief Deletes whitespaces in the right side
  /// @param in Token
  void right_trim(std::string& in);
};

#endif  // __TOKENIZER__
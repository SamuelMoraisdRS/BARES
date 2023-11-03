#ifndef __TOKENIZER__
#define __TOKENIZER__

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

/// @brief Classe para dividir uma string em tokens
class StrTokenizer {
  std::string input;                //!< string original a ser tokenizada
  std::string divider;              //!< lista com delimitadores
  bool trimming;                    //!< flag para realizar ou não "trim"
  std::vector<std::string> tokens;  //!< lista de tokens
  size_t current_token;             //!< Índice do token

public:
  StrTokenizer() = default;
  /// Construtor
  /// @param i String a ser dividida
  /// @param d Divisores usados para fracionar a string
  /// @param t Variável que informa se o wrapping deve ser feito
  StrTokenizer(const std::string i, const std::string d = ", ", const bool t = true);
  /// Retorna um 
  std::string get_token();
  std::vector<std::string> get_token_list() { return tokens; }

  /// @brief Apaga espaços em branco à esquerda do token
  /// @param in Token
  void left_trim(std::string& in);

  /// @brief Apaga espaços em branco à direita do token
  /// @param in Token
  void right_trim(std::string& in);
};

#endif  // __TOKENIZER__
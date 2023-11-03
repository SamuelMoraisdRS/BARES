#include "tokenizer.h"

/// @brief Construtor
/// @param i input a ser tokenizado
/// @param d lista de caracteres divisores
/// @param t flag que define se vai ter trimming ou não
StrTokenizer::StrTokenizer(const std::string i, const std::string d, const bool t)
    : input{ std::move(i) }, divider{ std::move(d) }, trimming{ std::move(t) } {
  size_t begin{ 0 };
  size_t end{ 0 };
  current_token = 0;

  while (end < input.size()) {
    auto position = divider.find(input[end]);
    // Verifica se é divisor
    if (position != std::string::npos) {  // se for divisor

      // copia a substring pro vector
      auto token = input.substr(begin, (end - begin));
      if (token != "") {

        tokens.push_back(token);
      }

      /// atualizar o begin
      begin = end + 1;

      end++;
    } else {

      end++;
    }
  }
  if (begin != end) {
    auto token = input.substr(begin, (end - begin));
    tokens.push_back(token);
  }
  // limpa espacos vazios em cada token
  for (auto& e : tokens) {
    if (trimming) {
      left_trim(e);
      right_trim(e);
    }
  }
}

void StrTokenizer::left_trim(std::string& in) {
    // apaga caracteres em branco
    in.erase(0, in.find_first_not_of(" \t"));
  }


  void StrTokenizer::right_trim(std::string& in) {
    // apaga do ultimo caractere nao branco ate o fim da string
    in.erase(in.find_last_not_of(" \t") + 1);
  }
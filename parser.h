#include "lexer.h"

class Parser {
  protected:
    double expression();
    double factor();
    double number();

  public:
    Lexer *lexer;

    double parse(std::string input);
};

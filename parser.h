#include "lexer.h"

class Parser {
  protected:
    double expression();
    double component();
    double factor();

  public:
    Lexer *lexer;

    double parse(std::string input);
};

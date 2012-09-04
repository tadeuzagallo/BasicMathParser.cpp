#include <iostream>
#include "token.h"

class Lexer {
  public:
    std::string input;
    Token *previousToken;
    bool returnPreviousToken;
    int pos;

    Lexer(std::string _input);
    void revert();
    Token *getNextToken();
};

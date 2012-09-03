#include "parser.h"

double Parser::parse(std::string input) {
  this->lexer = new Lexer(input);

  double expressionValue = this->expression();

  Token *token = this->lexer->getNextToken();

  if(token->kind == Token::END) {
    return expressionValue;
  } else {
    std::cout << "End expected" << std::endl;
    exit(0);
  }
}

double Parser::expression() {
  double component1 = this->factor();

  Token *token = this->lexer->getNextToken();
  while (token->kind == Token::PLUS || token->kind == Token::MINUS) {
    double component2 = this->factor();

    if(token->kind == Token::PLUS) {
      component1 += component2;
    } else {
      component1 -= component2;
    }

    token = this->lexer->getNextToken();
  }

  this->lexer->revert();

  return component1;
}

double Parser::factor() {
  double factor1 = this->number();

  Token *token = this->lexer->getNextToken();
  while (token->kind == Token::MULTIPLY || token->kind == Token::DIVIDE) {
    double factor2 = this->number();

    if (token->kind == Token::MULTIPLY) {
      factor1 *= factor2;
    } else {
      factor1 /= factor2;
    }

    token = this->lexer->getNextToken();
  }

  this->lexer->revert();

  return factor1;
}

double Parser::number() {
  Token *token = this->lexer->getNextToken();
  double value;

  if (token->kind == Token::L_PAREN) {
    value = this->expression();
    Token *expectedRParen = this->lexer->getNextToken();

    if(expectedRParen->kind != Token::R_PAREN) {
      std::cout << "Unterminated expression" << std::endl;
      exit(0);
    }
  } else if (token->kind == Token::NUMBER) {
    value = token->value;
  } else {
    std::cout << "Not a number" << std::endl;
    exit(0);
  }

  return value;
}

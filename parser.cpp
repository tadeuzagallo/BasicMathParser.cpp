#include "parser.h"
#include <math.h>

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
  double component1 = this->component();

  Token *token = this->lexer->getNextToken();
  while (token->kind == Token::PLUS || token->kind == Token::MINUS) {
    double component2 = this->component();

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

double Parser::component() {
  double factor1 = this->factor();

  Token *token = this->lexer->getNextToken();
  while (token->kind == Token::MULTIPLY || token->kind == Token::DIVIDE) {
    double factor2 = this->factor();

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

double Parser::factor() {
  Token *token = this->lexer->getNextToken();
  double value;
  int multiplier = 1;

  if(token->kind == Token::PLUS || token->kind == Token::MINUS) {
    if (token->kind == Token::MINUS) {
      multiplier = -1;
    }

    token = this->lexer->getNextToken();
  }

  if (token->kind == Token::L_PAREN) {
    value = this->expression();
    Token *expectedRParen = this->lexer->getNextToken();

    if(expectedRParen->kind != Token::R_PAREN) {
      std::cout << "Unterminated expression" << std::endl;
      exit(0);
    }
  } else if (token->kind == Token::NUMBER) {
    value = token->value;
  } else if (token->kind == Token::LITERAL) {
    value = this->expression();
    
    if (token->name == "sin") {
      value = sin(value);
    } else if(token->name == "cos") {
      value = cos(value);
    } else if(token->name == "abs") {
      value = abs(value);
    } else if(token->name == "round") {
      value = round(value);
    } else if(token->name == "ceil") {
      value = ceil(value);
    } else if(token->name == "floor") {
      value = floor(value);
    } else {
      std::cerr << "Function '" << token->name << "' not found... maybe not implemented yet..." << std::endl;
      exit(0);
    }
  } else {
    std::cout << "Not a number" << std::endl;
    exit(0);
  }

  return value * multiplier;
}

#include "lexer.h"

#define NUMBER_MAX_LENGTH 100
#define FUNCTION_MAX_LENGTH 10

#define DEBUG 0

Lexer::Lexer(std::string _input): input(_input), returnPreviousToken(false), pos(0) {
}

Token *Lexer::getNextToken() {
  if (this->returnPreviousToken) {
    this->returnPreviousToken = false;
    return this->previousToken;
  }

  Token *token = new Token();

  if (DEBUG) { 
    std::cout << "INPUT: " << this->input << ", CUR_POS: " << this->pos << ", CUR_CHAR: " << this->input[this->pos] << ", NEXT_CHAR: " << this->input[this->pos+1] << std::endl;
  }

  while (this->input[this->pos++] == ' ');
  this->pos--;

  if (DEBUG) { 
    std::cout << "INPUT: " << this->input << ", CUR_POS: " << this->pos << ", CUR_CHAR: " << this->input[this->pos] << ", NEXT_CHAR: " << this->input[this->pos+1] << std::endl;
  }

  switch(this->input[this->pos]) {
    case '+':
      if (DEBUG) {
        std::cout << "PLUS SIGN FOUND!" << std::endl;
      }

      token->kind = Token::PLUS;
      break;
    case '-':
      if (DEBUG) {
        std::cout << "MINUS SIGN FOUND!" << std::endl;
      }

      token->kind = Token::MINUS;
      break;
    case '*':
      if (DEBUG) {
        std::cout << "MULTIPLY SIGN FOUND!" << std::endl;
      }

      token->kind = Token::MULTIPLY;
      break;
    case '/':
      if (DEBUG) {
        std::cout << "DIVIDE SIGN FOUND!" << std::endl;
      }

      token->kind = Token::DIVIDE;
      break;
    case '(':
      if (DEBUG) {
        std::cout << "LEFT PARENT FOUND!" << std::endl;
      }

      token->kind = Token::L_PAREN;
      break;
    case ')':
      if (DEBUG) {
        std::cout << "RIGHT PARENT FOUND!" << std::endl;
      }

      token->kind = Token::R_PAREN;
      break;
    case '\0':
      if (DEBUG) {
        std::cout << "REACHED END OF INPUT!" << std::endl;
      }

      token->kind = Token::END;
      break;
    default:
      if (isdigit(this->input[this->pos])) {
        char number[NUMBER_MAX_LENGTH],
             next;
        int _pos = 0;

        number[_pos++] = this->input[this->pos];
        
        while(_pos < NUMBER_MAX_LENGTH && (next = this->input[++this->pos]) == '.' || (next - '0' >= 0 && next - '0' <= 9)) {
          number[_pos++] = next;
        }

        number[_pos] = '\0';

        token->kind = Token::NUMBER;
        token->value = atof(number);

        if (DEBUG) {
          std::cout << "NUMBER " << token->value << " FOUND!" << std::endl;
        }

        this->pos--;
      } else if (isalpha(this->input[this->pos])) {
        char fn[FUNCTION_MAX_LENGTH],
             next;
        int _pos = 0;

        fn[_pos++] = this->input[this->pos];
        while (_pos < FUNCTION_MAX_LENGTH && (next = this->input[++this->pos]) >= 'a' && next <= 'z') {
          fn[_pos++] = next;
        }

        fn[_pos] = '\0';

        token->kind = Token::LITERAL;
        token->name = std::string(fn);

        this->pos--;
      } else {
        std::cout << "Invalid input" << std::endl;
        exit(0);
      }
  }

  this->pos++;

  this->previousToken = token;

  if (!token->kind) {
    return 0;
  }

  return token;
}

void Lexer::revert() {
  this->returnPreviousToken = true;
}

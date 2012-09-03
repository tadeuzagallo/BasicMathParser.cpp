#include "parser.h"

int main(int argc, char *argv[])  {
  int i;

  if (argc <= 1) {
    return 0;
  }

  Parser *parser = new Parser();
  for(i = 1; i < argc; i++) {
    double result = parser->parse(argv[i]);
    printf("%s -> %f\n", argv[i], result);
  }

  return 0;
}

#include <string>

class Token {
  public:
    enum {
      PLUS = 1,
      MINUS,
      MULTIPLY,
      DIVIDE,

      NUMBER,
      LITERAL,

      L_PAREN,
      R_PAREN,

      END
    };

    int  kind;
    double value;
    std::string name;
};

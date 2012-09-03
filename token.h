class Token {
  public:
    enum {
      PLUS = 1,
      MINUS,
      MULTIPLY,
      DIVIDE,

      NUMBER,

      L_PAREN,
      R_PAREN,

      END
    };

    int  kind;
    double value;
};

all:
	g++ -o math_parser main.cpp parser.cpp lexer.cpp

install:
	mv math_parser /usr/local/bin/math_parser

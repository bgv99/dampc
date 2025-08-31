make:
	gcc src/main.c src/lexer.c src/parser.c src/log.c src/vec.c src/gen.c src/ast.c -o dampc -g
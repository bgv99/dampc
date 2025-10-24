cmake_minimum_required(VERSION 3.20)

project(dampc)

add_executable(dampc src/main.c src/lexer.c src/parser.c src/gen.c src/ast.c src/str.c src/vec.c src/log.c)

target_compile_options(dampc PUBLIC -std=c99 -Wall -Werror -Wextra -g)
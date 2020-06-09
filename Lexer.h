#ifndef INCLUDE_LEXER_H
#define INCLUDE_LEXER_H
#include <string>
#include <vector>

class Lexer {
public:
    Lexer();
    ~Lexer();
    int lex(const std::string& code, std::vector<std::string>& tokens);
private:
    int sanitize(std::string& code);
    int tokenize(const std::string& code, std::vector<std::string> &tokens);
    bool isDelimChar(char c);
    bool isParenthesis(char c);
};
#endif

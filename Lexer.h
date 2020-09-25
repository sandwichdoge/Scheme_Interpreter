#ifndef INCLUDE_LEXER_H
#define INCLUDE_LEXER_H
#include <string>
#include <vector>

enum LEXER_STATE { LEXER_OQUOTE_OWORD, LEXER_OQUOTE_IWORD, LEXER_IQUOTE_IWORD };

class Lexer {
   public:
    Lexer();
    ~Lexer();
    int lex(const std::string& code, std::vector<std::string>& tokens);

   private:
    int sanitize(std::string& code);
    int tokenize(const std::string& code, std::vector<std::string>& tokens);
    bool isDelimChar(char c);
    bool isParenthesis(char c);
    enum LEXER_STATE _state = LEXER_OQUOTE_OWORD;
};
#endif

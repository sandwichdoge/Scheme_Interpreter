#include "Lexer.h"

#include "Utils/Debug.h"
#include "Utils/StringUtils.h"

Lexer::Lexer() {}
Lexer::~Lexer() {}

int Lexer::lex(const std::string& code, std::vector<std::string>& tokens) {
    tokens.clear();
    std::string mutableCode = code;
    if (sanitize(mutableCode) < 0) {
        return -1;
    }
    if (tokenize(mutableCode, tokens) < 0) {
        return -2;
    }
    return 0;
}

int Lexer::sanitize(std::string& code) {
    // Sanitize
    // StringUtils::replace(code, "\n", " ");
    return 0;
}

int Lexer::tokenize(const std::string& code, std::vector<std::string>& tokens) {
    std::size_t wordLen = 0;
    std::size_t wordStart = 0;

    for (std::size_t i = 0; i < code.size(); ++i) {
        char c = code[i];
        switch (_state) {
            case LEXER_OQUOTE_OWORD: {
                if (isParenthesis(c)) {                   // Parenthesis met
                    tokens.push_back(std::string(1, c));  // Store that parenthesis in token list.
                } else if (c == '"') {
                    tokens.push_back(std::string(1, c));  // Store that parenthesis in token list.
                    wordStart = i + 1;
                    wordLen = 0;
                    _state = LEXER_IQUOTE_IWORD;
                } else if (!isDelimChar(c)) {  // Ascii met
                    wordStart = i;
                    wordLen = 1;
                    db("Open word at: " << wordStart);
                    _state = LEXER_OQUOTE_IWORD;
                }
                break;
            }
            case LEXER_OQUOTE_IWORD: {
                if (isParenthesis(c)) {  // Parenthesis met
                    std::string token = code.substr(wordStart, wordLen);
                    db("Saving word [" << token << "], start:" << wordStart << ", len:" << wordLen);
                    tokens.push_back(token);
                    tokens.push_back(std::string(1, c));  // Store that parenthesis in token list.
                    _state = LEXER_OQUOTE_OWORD;
                } else if (isDelimChar(c)) {
                    std::string token = code.substr(wordStart, wordLen);
                    db("Saving word [" << token << "], start:" << wordStart << ", len:" << wordLen);
                    tokens.push_back(token);
                    _state = LEXER_OQUOTE_OWORD;
                } else if (c == '"') {
                    std::string token = code.substr(wordStart, wordLen);
                    db("Saving word [" << token << "], start:" << wordStart << ", len:" << wordLen);
                    tokens.push_back(token);
                    tokens.push_back(std::string(1, c));  // Store that parenthesis in token list.
                    wordStart = i;
                    wordLen = 1;
                    _state = LEXER_IQUOTE_IWORD;
                } else {  // Ascii met
                    wordLen++;
                }
                break;
            }
            case LEXER_IQUOTE_IWORD: {
                if (c == '"') {
                    std::string token = code.substr(wordStart, wordLen);
                    db("Saving word [" << token << "], start:" << wordStart << ", len:" << wordLen);
                    tokens.push_back(token);
                    tokens.push_back(std::string(1, c));
                    _state = LEXER_OQUOTE_OWORD;
                } else {
                    wordLen++;
                }
                break;
            }
        }
    }
    return 0;
}

bool Lexer::isDelimChar(char c) { return (c == ' ' || c == '\t' || c == '\n'); }

bool Lexer::isParenthesis(char c) { return (c == '(' || c == ')'); }
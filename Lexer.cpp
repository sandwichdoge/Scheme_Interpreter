#include "Lexer.h"
#include "Utils/StringUtils.h"
#include "Utils/Debug.h"

Lexer::Lexer() {}
Lexer::~Lexer() {}

int Lexer::lex(const std::string& code, std::vector<std::string>& tokens) {
    std::string mutableCode = code;
    if (sanitize(mutableCode) < 0) {
        return -1;
    }
    if (tokenize(mutableCode, tokens) < 0) {
        return -2;
    }
    for (std::size_t i = 0; i < tokens.size(); ++i) {
        db(tokens[i]);
    }
    return 0;
}

int Lexer::sanitize(std::string& code) {
    // Sanitize
    //StringUtils::replace(code, "\n", " ");
    return 0;
}

// WTF?? TODO: draw a state machine.
int Lexer::tokenize(const std::string& code, std::vector<std::string> &tokens) {
    bool isQuotes = false; // Whether we're in a pair of quotes.
    bool isWord = false;   // Whether we're in a word.
    std::size_t wordLen = 0;
    std::size_t wordStart = 0;
    for (std::size_t i = 0; i < code.size(); ++i) {
        if (code[i] == '"') { // Quotes met
            if (!isWord) {    // Initial value
                tokens.push_back("\"");
                isWord = true;
            } else if (!isQuotes) {
                std::string token = code.substr(wordStart, wordLen);
                tokens.push_back(token);
                tokens.push_back("\"");
                wordLen = 0;
            }
            if (isQuotes) {
                std::string token = code.substr(wordStart, wordLen);
                tokens.push_back(token);
                tokens.push_back("\"");
                isWord = false;
            } else {
                wordStart = i + 1;
            }
            isQuotes = !isQuotes;
            continue;
        }

        if (isQuotes) {
            wordLen++;
        } else {
            if (isParenthesis(code[i])) { // Parenthesis met
                if (isWord) {
                    std::string token = code.substr(wordStart, wordLen);
                    tokens.push_back(token);
                    isWord = false;
                }
                tokens.push_back(code.substr(i, 1));
            }
            else if (isDelimChar(code[i])) {  // Delim char met, i.e end of word
                if (isWord) {
                    std::string token = code.substr(wordStart, wordLen);
                    tokens.push_back(token);
                    isWord = false;
                }
            } else { // Ascii char met
                if (isWord) {  // Already in word
                    wordLen++;
                } else {
                    wordStart = i;
                    isWord = true;
                    wordLen = 1;
                }
            }
        }
        
    }
    return 0;
}

bool Lexer::isDelimChar(char c) { 
    return (c == ' ' || c == '\t' || c == '\n'); 
}

bool Lexer::isParenthesis(char c) {
    return (c == '(' || c == ')');
}
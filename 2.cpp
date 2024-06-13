// Write a program in C or C++ language to
// generate tokens as identifiers, keywords,
// newline, tabs, whitespaces and characters.
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

unordered_set<string> keywords = {"break", "if", "else", "switch", "for", "while", "do",
                                   "int", "float", "string", "char", "continue", "double"};

struct Token {
    string type;
    string value;
};

vector<Token> tokenize(const string& s) {
    string currentToken;
    vector<Token> tokens;
    for (char ch : s) {
        if (isspace(ch)) {
            if (!currentToken.empty()) {
                if (keywords.count(currentToken)) {
                    tokens.push_back({"keyword", currentToken});
                } else {
                    tokens.push_back({"identifier", currentToken});
                }
                currentToken.clear();
            }
            if (ch == '\n') tokens.push_back({"newline", "\\n"});
            else if (ch == '\t') tokens.push_back({"tab", "\\t"});
            else if (ch == ' ') tokens.push_back({"whitespace", " "});
        } else if (isalnum(ch) || ch == '_') {
            currentToken += ch;
        } else {
            if (!currentToken.empty()) {
                if (keywords.count(currentToken)) {
                    tokens.push_back({"keyword", currentToken});
                } else {
                    tokens.push_back({"identifier", currentToken});
                }
                currentToken.clear();
            }
            tokens.push_back({"character", string(1, ch)});
        }
    }
    if (!currentToken.empty()) {
        if (keywords.count(currentToken)) {
            tokens.push_back({"keyword", currentToken});
        } else {
            tokens.push_back({"identifier", currentToken});
        }
    }
    return tokens;
}

int main() {
    string s;
    cout << "Enter an expression: ";
    getline(cin, s);
    vector<Token> tokens = tokenize(s);
    for (const auto& token : tokens) {
        cout << token.type << " " << token.value << endl;
    }
    return 0;
}

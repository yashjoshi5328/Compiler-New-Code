// Write a program in C or C++ language to implement Predictive Parsing Algorithm.

#include <bits/stdc++.h>
using namespace std;
unordered_map<string, unordered_map<string, string>> parseTable = {
    {"E", { {"id","T E'"}, {"(", "T E'"} }},
    {"E'", {{"+", "+ T E'"}, {")", ""}, {"$", ""}}},
    {"T", {{"id", "F T'"}, {"(", "F T'"}}},
    {"T'", {{"*", "* F T'"}, {"+", ""}, {")", ""}, {"$", ""}}},
    {"F", {{"id", "id"}, {"(", "( E )"}}}
};


vector<string> tokenize(string &input){
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while(ss>>token){
        tokens.push_back(token);
    }
    tokens.push_back("$");
    return tokens;
}

bool parse(vector<string> &tokens){
    stack<string> parseStack;
    parseStack.push("$");
    parseStack.push("E");
    
    int index = 0;
    while(!parseStack.empty()){
        string top = parseStack.top();
        string currentToken = tokens[index];
        if(currentToken==top){
            parseStack.pop();
            index++;
        }
        else if(parseTable.find(top)!=parseTable.end() &&  parseTable[top].find(currentToken)!=parseTable[top].end()){
            parseStack.pop();
            string rule = parseTable[top][currentToken];
            if(!rule.empty()){
                vector<string> symbols;
                string symbol;
                stringstream ss(rule);
                while(ss>>symbol){
                    symbols.push_back(symbol);
                }
                for(auto it=symbols.rbegin(); it!=symbols.rend();it++){
                    parseStack.push(*it);
                }
            }
        }
        else{
            return false;
        }
    }
    return index==tokens.size();
}

int main(){
    string input;
    getline(cin, input);
    vector<string> tokens = tokenize(input);
    
    if(parse(tokens)){
        cout<<"parsed succesfully"<<endl;
    }
    else{
        cout<<"Parser rejected the input"<<endl;
        }
}
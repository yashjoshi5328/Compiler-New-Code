#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Define the grammar
struct Production {
    char lhs;
    string rhs;
};

// Define the parser tables
map<pair<int, char>, string> actionTable;
map<pair<int, char>, int> gotoTable;

// Function to initialize the parser tables for the given grammar
void initializeTables() {
    // Action Table
    actionTable[{0, 'a'}] = "s3";
    actionTable[{0, 'b'}] = "s4";
    actionTable[{1, '$'}] = "acc";
    actionTable[{2, 'a'}] = "s3";
    actionTable[{2, 'b'}] = "s4";
    actionTable[{3, 'a'}] = "s3";
    actionTable[{3, 'b'}] = "s4";
    actionTable[{4, 'a'}] = "r3"; // A -> b
    actionTable[{4, 'b'}] = "r3";
    actionTable[{4, '$'}] = "r3";
    actionTable[{5, 'a'}] = "r1"; // S -> AA
    actionTable[{5, 'b'}] = "r1";
    actionTable[{5, '$'}] = "r1";
    actionTable[{6, 'a'}] = "r2"; // A -> aA
    actionTable[{6, 'b'}] = "r2";
    actionTable[{6, '$'}] = "r2";

    // Goto Table
    gotoTable[{0, 'S'}] = 1;
    gotoTable[{0, 'A'}] = 2;
    gotoTable[{2, 'A'}] = 5;
    gotoTable[{3, 'A'}] = 6;
}

// Main parser function
bool parse(const vector<char>& input) {
    stack<int> stateStack;
    stack<char> symbolStack;
    stateStack.push(0);
    int ip = 0;

    while (true) {
        int currentState = stateStack.top();
        char currentInput = input[ip];
        string action = actionTable[{currentState, currentInput}];

        if (action[0] == 's') {
            int nextState = stoi(action.substr(1));
            stateStack.push(nextState);
            symbolStack.push(currentInput);
            ip++;
        } else if (action[0] == 'r') {
            int productionNumber = stoi(action.substr(1));

            // Production rules for the new grammar
            vector<Production> productions = {
                {'S', "AA"},
                {'A', "aA"},
                {'A', "b"}
            };

            Production production = productions[productionNumber - 1];
            for (int i = 0; i < production.rhs.length(); i++) {
                stateStack.pop();
                symbolStack.pop();
            }
            symbolStack.push(production.lhs);
            int gotoState = gotoTable[{stateStack.top(), production.lhs}];
            stateStack.push(gotoState);
        } else if (action == "acc") {
            return true;
        } else {
            return false;
        }
    }
}

int main() {
    initializeTables();

    // Example input: aab$
    vector<char> input = {'a', 'a', 'b', 'b', '$'};

    if (parse(input)) {
        cout << "Input accepted." << endl;
    } else {
        cout << "Input rejected." << endl;
    }

    return 0;
}

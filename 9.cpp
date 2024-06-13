#include <iostream>
#include <string>
#include <stack>
using namespace std;

// Function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to generate three-address code
void generateThreeAddressCode(const string& expression) {
    stack<string> operands;
    stack<char> operators;
    int tempCounter = 1;

    for (char c : expression) {
        if (isalpha(c)) {
            operands.push(string(1, c)); // Convert char to string and push to stack
        } else if (isOperator(c)) {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                string operand2 = operands.top();
                operands.pop();
                string operand1 = operands.top();
                operands.pop();
                string temp = "t" + to_string(tempCounter++);
                cout << temp << " = " << operand1 << " " << op << " " << operand2 << endl;
                operands.push(temp);
            }
            operators.push(c);
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                char op = operators.top();
                operators.pop();
                string operand2 = operands.top();
                operands.pop();
                string operand1 = operands.top();
                operands.pop();
                string temp = "t" + to_string(tempCounter++);
                cout << temp << " = " << operand1 << " " << op << " " << operand2 << endl;
                operands.push(temp);
            }
            operators.pop(); // Pop '('
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();
        string operand2 = operands.top();
        operands.pop();
        string operand1 = operands.top();
        operands.pop();
        string temp = "t" + to_string(tempCounter++);
        cout << temp << " = " << operand1 << " " << op << " " << operand2 << endl;
        operands.push(temp);
    }
}

int main() {
    string expression;
    cout << "Enter the arithmetic expression: ";
    getline(cin, expression);
    cout << "Generated Three-Address Code:" << endl;
    generateThreeAddressCode(expression);
    return 0;
}

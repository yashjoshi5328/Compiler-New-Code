/*
|Input:
Enter number of productions: 5
Enter productions (e.g., E=TR|T, with ep for epsilon):
E=TR
R=+TR|ep
T=FY
Y=*FY|ep
F=(E)|id

*/
#include<bits/stdc++.h>
using namespace std;

unordered_map<char, vector<string>> grammar;
unordered_map<char, unordered_set<char>> first;
unordered_map<char, unordered_set<char>> follow;
unordered_set<char> nonTerminals;

void computeFirst(char symbol) {
    if (!first[symbol].empty()) return;
    for (const string &prod : grammar[symbol]) {
        for (char ch : prod) {
            if (isupper(ch)) {
                if (ch != symbol) {
                    computeFirst(ch);
                    first[symbol].insert(first[ch].begin(), first[ch].end());
                }
                if (first[ch].find('e') == first[ch].end()) break;
            } else {
                first[symbol].insert(ch);
                break;
            }
        }
    }
}

void computeFollow() {
    follow[*nonTerminals.begin()].insert('$');
    bool changed = true;
    while (changed) {
        changed = false;
        for (auto it = grammar.begin(); it != grammar.end(); ++it) {
            char nt = it->first;
            const vector<string> &prods = it->second;
            for (const string &prod : prods) {
                for (size_t i = 0; i < prod.size(); ++i) {
                    if (isupper(prod[i])) {
                        size_t oldSize = follow[prod[i]].size();
                        if (i + 1 < prod.size()) {
                            char next = prod[i + 1];
                            if (isupper(next)) {
                                follow[prod[i]].insert(first[next].begin(), first[next].end());
                                follow[prod[i]].erase('e');
                            } else {
                                follow[prod[i]].insert(next);
                            }
                        }
                        if (i + 1 == prod.size() || (isupper(prod[i + 1]) && first[prod[i + 1]].count('e'))) {
                            follow[prod[i]].insert(follow[nt].begin(), follow[nt].end());
                        }
                        if (follow[prod[i]].size() > oldSize) changed = true;
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cout << "Enter productions (e.g., E=TR|T, with ep for epsilon):" << endl;
    cin.ignore();
    
    for (int i = 0; i < n; ++i) {
        string prod;
        getline(cin, prod);
        char nonTerminal = prod[0];
        string production = prod.substr(2);
        stringstream ss(production);
        string rule;
        while (getline(ss, rule, '|')) {
            grammar[nonTerminal].push_back(rule);
        }
        nonTerminals.insert(nonTerminal);
    }

    for (char nt : nonTerminals) computeFirst(nt);
    computeFollow();

    cout << "FIRST sets:" << endl;
    for (char nt : nonTerminals) {
        cout << nt << ": { ";
        for (char ch : first[nt]) cout << ch << " ";
        cout << "}" << endl;
    }

    cout << "FOLLOW sets:" << endl;
    for (char nt : nonTerminals) {
        cout << nt << ": { ";
        for (char ch : follow[nt]) cout << ch << " ";
        cout << "}" << endl;
    }

    return 0;
}

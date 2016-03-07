#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdio>
#include <vector>

#include "Node.h"

using namespace std;

bool done = false;

void solveR(Node& n) {
    if (done) return;
    if (n.isSolved()) {
        done = true;
        n.printNode();
        return;
    }

    vector<Node> candidates = n.getCandidates();
    for (int k = 0; k < candidates.size(); k++)  solveR(candidates[k]);
    candidates.clear();
}

int main() {
    string input = "";
    cout << "Enter a Sudoku Grid:\n" << endl;
    cin >> input;
    int arr[81];
    for (int k = 0; k < 81; k++)
        if (input[k] != '.') arr[k] = input[k]-'0'; //Convert char to int
        else arr[k] = 0;


    Node n = Node(arr);
    if (!n.isValid() || input.length() != 81) {
        cout << "Invalid sudoku puzzle." << endl;
        return -1;
    }

    n.printNode();


    clock_t start;
    double dur;
    start = clock();

    solveR(n);

    dur = (clock()-start)/(double)CLOCKS_PER_SEC;
    cout << dur << "s" << endl;
    if (!done)
        cout << "Invalid sudoku puzzle." << endl;

    return 0;
}



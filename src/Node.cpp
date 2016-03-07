#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(const int* p)
{
    for (int k = 0; k < 81; k++)
        grid[k/9][k%9] = p[k];
    solved = false;
}

bool Node::isSolved() const
{
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            if (grid[r][c] == 0)
                return false;
    return true;
}

bool Node::isValid() const
{
    int cur, r_t, c_t;
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            cur = grid[r][c];
            if (cur == 0) continue;

            for (int k = 0; k < 9; k++){
                r_t = (r-r%3) + k/3;
                c_t = (c-c%3) + k%3;
                if ((grid[r][k] == cur && k != c) || (grid[k][c] == cur && r != k)
                    || (grid[r_t][c_t] == cur && r_t != r && c_t != c))
                    return false;
            }
        }
    }
    return true;
}

vector<Node> Node::getCandidates() const
{
    vector<Node> ans; //Candidates values for empty cell

    cell next_c = getMostConstrainedCell();
    set<int> p_vals = getPossibilitiesForCell(next_c.r, next_c.c); //possible values for next_c

    for (int k : p_vals){
        Node n = Node(this -> getGrid());
        n.setGridVal(next_c.r, next_c.c, k);
        ans.push_back(n);
    }

    return ans;
}

cell Node::getMostConstrainedCell() const
{
    int num_p[9][9] = {0};
    int min_r = -1, min_c = -1;

    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            if (grid[r][c] == 0){
                min_r = r, min_c = c;
                goto brk;
            }

    brk:
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            if (grid[r][c] != 0) continue; //No possibilities: cell is occupied
            num_p[r][c] = getNumPossibilitiesForCell(r,c);
            if (num_p[r][c] == 1) { return {r, c}; } //Only 1 value possible. Choose this one
            if (num_p[r][c] < num_p[min_r][min_c]) { min_r = r, min_c = c; }
        }
    }

    return {min_r, min_c};
}

int Node::getNumPossibilitiesForCell(int r, int c) const
{
    if (grid[r][c] != 0) //If cell is occupied, it has 0 possibilities for other numbers
        return 0;

    bool taken[9] = { false };
    int r_t, c_t;

    for (int k = 0; k < 9; k++){
        if (grid[r][k] != 0) { taken[grid[r][k]-1] = true; } //check row
        if (grid[k][c] != 0) { taken[grid[k][c]-1] = true; } //check col

        //check 3x3 grid
        r_t = (r-r%3) + k/3;
        c_t = (c-c%3) + k%3;

        if (grid[r_t][c_t] != 0) { taken[grid[r_t][c_t]-1] = true; }
    }

    int num_possible = 9;
    for (int k = 0; k < 9; k++)
        if (taken[k]) { --num_possible; }

    return num_possible;
}

set<int> Node::getPossibilitiesForCell(int r, int c) const
{
    set<int> possb;
    if (grid[r][c] != 0){ return possb; } //Return empty set if cell is taken

    bool taken[9] = { false };
    int r_t, c_t;

    for (int k = 0; k < 9; k++){
        if (grid[r][k] != 0) { taken[grid[r][k]-1] = true; } //check row
        if (grid[k][c] != 0) { taken[grid[k][c]-1] = true; } //check col

        //check 3x3 grid
        r_t = (r-r%3) + k/3;
        c_t = (c-c%3) + k%3;

        if (grid[r_t][c_t] != 0) { taken[grid[r_t][c_t]-1] = true; }
    }

    for (int k = 0; k < 9; k++) { if (!taken[k]) { possb.insert(k+1); } }
    return possb;
}

void Node::printNode() const
{
    cout << "+-------+-------+-------+" << endl;

    for (int r = 0; r < 9; r++){
        cout << "| ";
        for (int c = 0; c < 9; c++){
            if (grid[r][c]) { cout << grid[r][c] << " "; }
            else {cout << "  ";}
            if ((c+1)%3==0) { cout << "| "; }
        }
        cout << endl;
        if ((r+1)%3==0) { cout << "+-------+-------+-------+" << endl; }
    }
}

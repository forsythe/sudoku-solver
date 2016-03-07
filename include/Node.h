#ifndef NODE_H
#define NODE_H
#include <vector>
#include <set>

struct cell
{
    int r, c;
};

class Node
{
    public:
        Node(int*);
        void printNode();
        bool isSolved();
        bool isValid();

        inline int* getGrid() { return grid[0]; }; //It's OK for this to be shallow, since constructor deep copies!
        inline void setGridVal(int r, int c, int new_val){ grid[r][c] = new_val; };
        std::vector<Node> getCandidates();

    protected:
    private:
        int grid[9][9];
        bool solved;

        cell getMostConstrainedCell();
        int getNumPossibilitiesForCell(int r, int c);
        std::set<int> getPossibilitiesForCell(int r, int c);

};

#endif // NODE_H

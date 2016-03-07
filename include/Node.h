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
        Node(const int*);
        void printNode() const;
        bool isSolved() const;
        bool isValid() const;

        const int* getGrid() const { return grid[0]; }; //It's OK for this to be shallow, since constructor deep copies!
        void setGridVal(int r, int c, int new_val){ grid[r][c] = new_val; };
        std::vector<Node> getCandidates() const;

    protected:
    private:
        int grid[9][9];
        bool solved;

        cell getMostConstrainedCell() const;
        int getNumPossibilitiesForCell(int r, int c) const;
        std::set<int> getPossibilitiesForCell(int r, int c) const;

};

#endif // NODE_H

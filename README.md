### Summary
A Sudoku solver which relies on best first search. The "best" option is chosen by filling in a cell which has the fewest possible values. Solves most easy grids under 0.1 seconds, and difficult ones under 1.5 seconds. 

Input: String of 81 characters representing legal 9x9 sudoku grid, using "0" or "." to represent an empty cell.  
Output: Filled 9x9 sudoku grid with time taken to solve.  

### Example
Input:
```
4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......
```
Output:
```
+-------+-------+-------+
| 4 1 7 | 3 6 9 | 8 2 5 |
| 6 3 2 | 1 5 8 | 9 4 7 |
| 9 5 8 | 7 2 4 | 3 1 6 |
+-------+-------+-------+
| 8 2 5 | 4 3 7 | 1 6 9 |
| 7 9 1 | 5 8 6 | 4 3 2 |
| 3 4 6 | 9 1 2 | 7 5 8 |
+-------+-------+-------+
| 2 8 9 | 6 4 3 | 5 7 1 |
| 5 7 3 | 2 9 1 | 6 8 4 |
| 1 6 4 | 8 7 5 | 2 9 3 |
+-------+-------+-------+
0.018s
```

### How it works
The method `solveR` accepts a `node` object, which represents a 9x9 sudoku grid. A set of candidate moves (nodes with 1 additional cell filled in, compared to the original node) is generated based on the method `Node::getCandidates()`. This method works by first finding the most constrained cell in the current node (cell with least possible values) with `Node::getMostConstrainedCell()`. Second, it calls `Node::getPossibilitiesForCell(int r, int c)` to find out what possible values can go into this cell. Lastly, it returns a `vector<Node>` where each node holds a different possible value for the aformentioned most constrained cell. `solveR` then recursively checks every node in the vector until a valid solution is found.

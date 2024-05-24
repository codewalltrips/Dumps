/*Given an n x n integer matrix grid, return the minimum sum of a falling path with non-zero shifts.

A falling path with non-zero shifts is a choice of exactly one element from each row of grid such that no two elements chosen in adjacent rows are in the same column.

 

Example 1:


Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
Output: 13
Explanation: 
The possible falling paths are:
[1,5,9], [1,5,7], [1,6,7], [1,6,8],
[2,4,8], [2,4,9], [2,6,7], [2,6,8],
[3,4,8], [3,4,9], [3,5,7], [3,5,9]
The falling path with the smallest sum is [1,5,7], so the answer is 13.
Example 2:

Input: grid = [[7]]
Output: 7
 

Constraints:

n == grid.length == grid[i].length
1 <= n <= 200
-99 <= grid[i][j] <= 99
test case 1 [[1,2,3],[4,5,6],[7,8,9]] expected output 13
test case 2 [[7]] expected output 7*/



int minFallingPathSum(int** grid, int gridSize, int* gridColSize) 
{
    if (gridSize == 1) {
        return grid[0][0]; // Return the only element in the grid if it's a single element
    }
    int INT_MAX;
    for (int i = gridSize - 2; i >= 0; i--) {
        for (int j = 0; j < *gridColSize; j++) {
            int minVal = INT_MAX;
            for (int k = 0; k < *gridColSize; k++) {
                if (k != j) {
                    minVal = fmin(minVal, grid[i + 1][k]);
                }
            }
            grid[i][j] += minVal;
        }
    }
    
    int minSum = INT_MAX;
    for (int j = 0; j < *gridColSize; j++) {
        minSum = fmin(minSum, grid[0][j]);
    }
    
    return minSum;
}


/*
There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.

 

Example 1:


Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: The tree is shown above.
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.
Hence, answer[0] = 8, and so on.
Example 2:


Input: n = 1, edges = []
Output: [0]
Example 3:


Input: n = 2, edges = [[1,0]]
Output: [1,1]
 

Constraints:

1 <= n <= 3 * 104
edges.length == n - 1
edges[i].length == 2
0 <= ai, bi < n
ai != bi
The given input represents a valid tree.*/

#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

int* sumOfDistancesInTree(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize) {
    // Initialize the adjacency list
    Node** g = (Node**)calloc(n, sizeof(Node*));
    for (int i = 0; i < edgesSize; i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->val = b;
        newNode->next = g[a];
        g[a] = newNode;
        newNode = (Node*)malloc(sizeof(Node));
        newNode->val = a;
        newNode->next = g[b];
        g[b] = newNode;
    }

    // Initialize the result array
    int* ans = (int*)malloc(n * sizeof(int));
    *returnSize = n;

    // Perform the first DFS traversal
    int* count = (int*)calloc(n, sizeof(int));
    int* pd_0 = (int*)calloc(n, sizeof(int));
    dfs(0, g, -1, 1, pd_0, count, n);

    // Perform the second DFS traversal
    int* pd_all = (int*)malloc(n * sizeof(int));
    memcpy(pd_all, pd_0, n * sizeof(int));
    dfs2(0, g, -1, pd_all, n, count);

    // Find the maximum sum of distances
    for (int i = 0; i < n; i++) {
        ans[i] = pd_all[i];
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        Node* curr = g[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g);
    free(count);
    free(pd_0);
    free(pd_all);

    return ans;
}

void dfs(int s, Node** g, int p, int d, int* pd_0, int* count, int n) {
    count[s] = 1;
    pd_0[s] = 0;
    for (Node* curr = g[s]; curr; curr = curr->next) {
        if (curr->val != p) {
            dfs(curr->val, g, s, d + 1, pd_0, count, n);
            count[s] += count[curr->val];
            pd_0[s] += pd_0[curr->val] + count[curr->val];
        }
    }
}

void dfs2(int s, Node** g, int p, int* pd_all, int n, int* count) {
    for (Node* curr = g[s]; curr; curr = curr->next) {
        if (curr->val != p) {
            pd_all[curr->val] = pd_all[s] - count[curr->val] + (n - count[curr->val]);
            dfs2(curr->val, g, s, pd_all, n, count);
        }
    }
}

/*There is a standard numeric keypad on a mobile phone. You can only press the current button or buttons that are directly up, left, right, or down from it (for ex if you press 5, then pressing 2, 4, 6 & 8 are allowed). Diagonal movements and pressing the bottom row corner buttons (* and #) are prohibited.



Given a number n, find the number of possible unique sequences of length n that you can create by pressing buttons. You can start from any digit.

Examples

Input: n = 1
Output: 10
Explanation: Number of possible numbers are 10 (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)  
Input: n = 2
Output: 36
Explanation: Possible numbers: 00, 08, 11, 12, 14, 22, 21, 23, 25 and so on. If we start with 0, valid numbers will be 00, 08 (count: 2). If we start with 1, valid numbers will be 11, 12, 14 (count: 3). If we start with 2, valid numbers  will be 22, 21, 23,25 (count: 4). If we start with 3, valid numbers will be 33, 32, 36 (count: 3). If we start with 4, valid numbers will be 44,41,45,47 (count: 4). If we start with 5, valid numbers will be 55,54,52,56,58 (count: 5) and so on.
Expected Time Complexity: O(n)
Expected Auxiliary Space: O(n)

Constraints:
1 ≤ n ≤ 25

*/
//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {
  public:
    long long getCount(int n) {
        if (n == 1) return 10;

        vector<vector<int>> moves = {
            {0, 8},      // 0 can move to 0 and 8
            {1, 2, 4},   // 1 can move to 1, 2, 4
            {2, 1, 3, 5},// 2 can move to 2, 1, 3, 5
            {3, 2, 6},   // 3 can move to 3, 2, 6
            {4, 1, 5, 7},// 4 can move to 4, 1, 5, 7
            {5, 2, 4, 6, 8}, // 5 can move to 5, 2, 4, 6, 8
            {6, 3, 5, 9},// 6 can move to 6, 3, 5, 9
            {7, 4, 8},   // 7 can move to 7, 4, 8
            {8, 0, 5, 7, 9}, // 8 can move to 8, 0, 5, 7, 9
            {9, 6, 8}    // 9 can move to 9, 6, 8
        };

        vector<vector<long long>> dp(n + 1, vector<long long>(10, 0));

        // Initialize for sequences of length 1
        for (int i = 0; i < 10; ++i) {
            dp[1][i] = 1;
        }

        // Build DP table
        for (int len = 2; len <= n; ++len) {
            for (int digit = 0; digit < 10; ++digit) {
                dp[len][digit] = 0;
                for (int prev : moves[digit]) {
                    dp[len][digit] += dp[len - 1][prev];
                }
            }
        }

        // Sum up all ways to form sequences of length n
        long long result = 0;
        for (int digit = 0; digit < 10; ++digit) {
            result += dp[n][digit];
        }

        return result;
    }
};

//{ Driver Code Starts.
int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        Solution ob;
        cout << ob.getCount(n) << "\n";
    }
    return 0;
}

// } Driver Code Ends

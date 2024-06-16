/*A peak in an array arr is an element that is greater than its previous and next element in arr.

You are given an integer array nums and a 2D integer array queries.

You have to process queries of two types:

queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
queries[i] = [2, indexi, vali], change nums[indexi] to vali.
Return an array answer containing the results of the queries of the first type in order.
Notes:

The first and the last element of an array or a subarray cannot be a peak.
 

Example 1:

Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]

Output: [0]

Explanation:

First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].

Second query: The number of peaks in the [3,1,4,4,5] is 0.

Example 2:

Input: nums = [4,1,4,2,1,5], queries = [[2,2,4],[1,0,2],[1,0,4]]

Output: [0,1]

Explanation:

First query: nums[2] should become 4, but it is already set to 4.

Second query: The number of peaks in the [4,1,4] is 0.

Third query: The second 4 is a peak in the [4,1,4,2,1].

 

Constraints:

3 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= queries.length <= 105
queries[i][0] == 1 or queries[i][0] == 2
For all i that:
queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105*/

#include <vector>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        vector<int> peaks(n, 0);
        
        // Function to check if an index is a peak
        auto isPeak = [&](int i) {
            if (i <= 0 || i >= n - 1) return false;
            return nums[i] > nums[i - 1] && nums[i] > nums[i + 1];
        };
        
        // Initial peak calculation
        for (int i = 1; i < n - 1; ++i) {
            peaks[i] = isPeak(i) ? 1 : 0;
        }
        
        // Segment tree to store peak counts
        vector<int> segTree(4 * n, 0);
        
        // Function to build the segment tree
        function<void(int, int, int)> buildSegTree = [&](int node, int start, int end) {
            if (start == end) {
                segTree[node] = peaks[start];
            } else {
                int mid = (start + end) / 2;
                buildSegTree(2 * node + 1, start, mid);
                buildSegTree(2 * node + 2, mid + 1, end);
                segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
            }
        };
        
        // Function to update the segment tree
        function<void(int, int, int, int)> updateSegTree = [&](int node, int start, int end, int idx) {
            if (start == end) {
                segTree[node] = peaks[idx];
            } else {
                int mid = (start + end) / 2;
                if (idx <= mid) {
                    updateSegTree(2 * node + 1, start, mid, idx);
                } else {
                    updateSegTree(2 * node + 2, mid + 1, end, idx);
                }
                segTree[node] = segTree[2 * node + 1] + segTree[2 * node + 2];
            }
        };
        
        // Function to query the segment tree
        function<int(int, int, int, int, int)> querySegTree = [&](int node, int start, int end, int l, int r) {
            if (r < start || l > end) return 0;
            if (l <= start && r >= end) return segTree[node];
            int mid = (start + end) / 2;
            int leftQuery = querySegTree(2 * node + 1, start, mid, l, r);
            int rightQuery = querySegTree(2 * node + 2, mid + 1, end, l, r);
            return leftQuery + rightQuery;
        };
        
        // Build the initial segment tree
        buildSegTree(0, 0, n - 1);
        
        vector<int> result;
        
        for (const auto& query : queries) {
            if (query[0] == 2) {
                // Update query: queries[i] = [2, indexi, vali]
                int index = query[1];
                int value = query[2];
                
                // Update the value in nums
                nums[index] = value;
                
                // Update peaks and segment tree for index and its neighbors
                for (int i = max(1, index - 1); i <= min(n - 2, index + 1); ++i) {
                    peaks[i] = isPeak(i) ? 1 : 0;
                    updateSegTree(0, 0, n - 1, i);
                }
            } else if (query[0] == 1) {
                // Count peaks query: queries[i] = [1, li, ri]
                int li = query[1];
                int ri = query[2];
                if (li == ri || li + 1 == ri) {
                    result.push_back(0);
                } else {
                    result.push_back(querySegTree(0, 0, n - 1, li + 1, ri - 1));
                }
            }
        }
        
        return result;
    }
};

'''There are n people and 40 types of hats labeled from 1 to 40.

Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.

Return the number of ways that the n people wear different hats to each other.

Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: hats = [[3,4],[4,5],[5]]
Output: 1
Explanation: There is only one way to choose hats given the conditions. 
First person choose hat 3, Second person choose hat 4 and last one hat 5.
Example 2:

Input: hats = [[3,5,1],[3,5]]
Output: 4
Explanation: There are 4 ways to choose hats:
(3,5), (5,3), (1,3) and (1,5)
Example 3:

Input: hats = [[1,2,3,4],[1,2,3,4],[1,2,3,4],[1,2,3,4]]
Output: 24
Explanation: Each person can choose hats labeled from 1 to 4.
Number of Permutations of (1,2,3,4) = 24.
 

Constraints:

n == hats.length
1 <= n <= 10
1 <= hats[i].length <= 40
1 <= hats[i][j] <= 40
hats[i] contains a list of unique integers.'''

class Solution(object):
    def numberWays(self, hats):
        """
        :type hats: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(hats)
        
        # Map each hat to the list of people who prefer it
        from collections import defaultdict
        hat_to_people = defaultdict(list)
        for person, hat_list in enumerate(hats):
            for hat in hat_list:
                hat_to_people[hat].append(person)
        
        # Dynamic Programming table
        dp = [0] * (1 << n)
        dp[0] = 1  # One way to assign hats when no one is assigned
        
        # Iterate over all hats from 1 to 40
        for hat in range(1, 41):
            if hat not in hat_to_people:
                continue
            new_dp = dp[:]  # Copy current dp state
            for mask in range(1 << n):
                for person in hat_to_people[hat]:
                    if mask & (1 << person) == 0:  # If person is not yet assigned a hat
                        new_dp[mask | (1 << person)] += dp[mask]
                        new_dp[mask | (1 << person)] %= MOD
            dp = new_dp  # Update dp with new states
        
        return dp[(1 << n) - 1]  # Return the number of ways for all people to be assigned a hat

# Example usage
solution = Solution()
print(solution.numberWays([[3,4],[4,5],[5]]))  # Output: 1
print(solution.numberWays([[3,5,1],[3,5]]))  # Output: 4
print(solution.numberWays([[1,2,3,4],[1,2,3,4],[1,2,3,4],[1,2,3,4]]))  # Output: 24

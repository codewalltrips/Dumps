'''An attendance record for a student can be represented as a string where each character signifies whether the student was absent, late, or present on that day. The record only contains the following three characters:

'A': Absent.
'L': Late.
'P': Present.
Any student is eligible for an attendance award if they meet both of the following criteria:

The student was absent ('A') for strictly fewer than 2 days total.
The student was never late ('L') for 3 or more consecutive days.
Given an integer n, return the number of possible attendance records of length n that make a student eligible for an attendance award. The answer may be very large, so return it modulo 109 + 7.

 

Example 1:

Input: n = 2
Output: 8
Explanation: There are 8 records with length 2 that are eligible for an award:
"PP", "AP", "PA", "LP", "PL", "AL", "LA", "LL"
Only "AA" is not eligible because there are 2 absences (there need to be fewer than 2).
Example 2:

Input: n = 1
Output: 3
Example 3:

Input: n = 10101
Output: 183236316 
 

Constraints:

1 <= n <= 105 '''



class Solution(object):
    def checkRecord(self, n):
        MOD = 10**9 + 7
        
        # dp[i][j][k] will be the number of valid sequences of length i with j 'A's and ending with k consecutive 'L's.
        dp = [[[0]*3 for _ in range(2)] for _ in range(n+1)]
        
        dp[0][0][0] = 1  # One valid sequence of length 0

        for i in range(1, n+1):
            for A in range(2):
                for L in range(3):
                    # Ending with 'P'
                    dp[i][A][0] = (dp[i][A][0] + dp[i-1][A][L]) % MOD
                    # Ending with 'A'
                    if A > 0:
                        dp[i][A][0] = (dp[i][A][0] + dp[i-1][A-1][L]) % MOD
                    # Ending with 'L'
                    if L > 0:
                        dp[i][A][L] = (dp[i][A][L] + dp[i-1][A][L-1]) % MOD
        
        # Sum all valid sequences of length n
        result = 0
        for A in range(2):
            for L in range(3):
                result = (result + dp[n][A][L]) % MOD
        
        return result

# Example usage
solution = Solution()
print(solution.checkRecord(2))  # Output: 8
print(solution.checkRecord(1))  # Output: 3
print(solution.checkRecord(10101))  # Output: 183236316

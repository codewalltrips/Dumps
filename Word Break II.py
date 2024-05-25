#Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

#Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

#Example 1:

#Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
#Output: ["cats and dog","cat sand dog"]
#Example 2:

#Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
#Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
#Explanation: Note that you are allowed to reuse a dictionary word.
#Example 3:

#Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
#Output: []
 

#Constraints:

#1 <= s.length <= 20
#1 <= wordDict.length <= 1000
#1 <= wordDict[i].length <= 10
#s and wordDict[i] consist of only lowercase English letters.
#All the strings of wordDict are unique.
#Input is generated in a way that the length of the answer doesn't exceed 105.


class Solution(object):
    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: List[str]
        """
        # Convert the wordDict to a set for fast look-up
        wordSet = set(wordDict)
        
        # Dictionary to store the results of subproblems
        memo = {}

        def backtrack(start):
            if start in memo:
                return memo[start]
            
            results = []
            if start == len(s):
                results.append("")
            
            for end in range(start + 1, len(s) + 1):
                word = s[start:end]
                if word in wordSet:
                    sub_results = backtrack(end)
                    for sub in sub_results:
                        if sub:
                            results.append(word + " " + sub)
                        else:
                            results.append(word)
            
            memo[start] = results
            return results
        
        return backtrack(0)

# Example usage:
sol = Solution()
print(sol.wordBreak("catsanddog", ["cat", "cats", "and", "sand", "dog"]))
print(sol.wordBreak("pineapplepenapple", ["apple", "pen", "applepen", "pine", "pineapple"]))
print(sol.wordBreak("catsandog", ["cats", "dog", "sand", "and", "cat"]))

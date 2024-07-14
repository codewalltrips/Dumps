/*Given a string formula representing a chemical formula, return the count of each atom.

The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.

One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.

For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
Two formulas are concatenated together to produce another formula.

For example, "H2O2He3Mg4" is also a formula.
A formula placed in parentheses, and a count (optionally added) is also a formula.

For example, "(H2O2)" and "(H2O2)3" are formulas.
Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.

The test cases are generated so that all the values in the output fit in a 32-bit integer.

 

Example 1:

Input: formula = "H2O"
Output: "H2O"
Explanation: The count of elements are {'H': 2, 'O': 1}.
Example 2:

Input: formula = "Mg(OH)2"
Output: "H2MgO2"
Explanation: The count of elements are {'H': 2, 'Mg': 1, 'O': 2}.
Example 3:

Input: formula = "K4(ON(SO3)2)2"
Output: "K4N2O14S4"
Explanation: The count of elements are {'K': 4, 'N': 2, 'O': 14, 'S': 4}.
 

Constraints:

1 <= formula.length <= 1000
formula consists of English letters, digits, '(', and ')'.
formula is always valid.*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
#include <map>
#include <functional>
using namespace std;

class Solution {
public:
    string countOfAtoms(string formula) {
        int n = formula.size();
        int i = 0;

        function<unordered_map<string, int>(int&)> parse = [&](int& i) {
            unordered_map<string, int> countMap;
            while (i < n) {
                if (formula[i] == '(') {
                    i++;
                    auto subCount = parse(i);
                    int count = 1;
                    int start = i;
                    while (i < n && isdigit(formula[i])) i++;
                    if (start < i) count = stoi(formula.substr(start, i - start));
                    for (auto& kv : subCount) {
                        countMap[kv.first] += kv.second * count;
                    }
                } else if (formula[i] == ')') {
                    i++;
                    break;
                } else {
                    int start = i;
                    i++; 
                    while (i < n && islower(formula[i])) i++; 
                    string element = formula.substr(start, i - start);
                    int count = 1;
                    start = i;
                    while (i < n && isdigit(formula[i])) i++;
                    if (start < i) count = stoi(formula.substr(start, i - start));
                    countMap[element] += count;
                }
            }
            return countMap;
        };

        auto counts = parse(i);
        map<string, int> sortedCounts(counts.begin(), counts.end());
        string result;
        for (auto& kv : sortedCounts) {
            result += kv.first;
            if (kv.second > 1) result += to_string(kv.second);
        }
        return result;
    }
};

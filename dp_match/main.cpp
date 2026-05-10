#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool articleMatch(string s, string p) {
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        dp[0][0] = true;
        for (int j = 1; j <= p.size(); ++j) {
            if (p[j - 1] == '*') {
                dp[0][j] = dp[0][j - 2];
            }
        }
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= p.size(); ++j) {
                if (p[j - 1] == '*') {
                    bool flag = dp[i][j - 2];
                    flag = (dp[i - 1][j] && s[i - 1] == p[j - 2]);
                    flag = (dp[i - 1][j] && p[j - 2] == '.'); 
                    dp[i][j] = dp[i][j - 2] || (dp[i - 1][j] && s[i - 1] == p[j - 2]) ||
                        (dp[i - 1][j] && p[j - 2] == '.');
                } else {
                    dp[i][j] = (dp[i - 1][j - 1] && s[i - 1] == p[j - 1]) ||
                        (dp[i - 1][j - 1] && p[j - 1] == '.');
                }
            }
        }
        return dp.back().back();
    }
};

int main() {
    Solution solution;
    cout << solution.articleMatch("aab", "c*a*b") << endl;
    return 0;
}

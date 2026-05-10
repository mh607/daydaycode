#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while(n != 0) {
            res++;
            n &= n - 1;
        }
        return res;
    }
};

int main() {
    Solution solution;
    cout << solution.hammingWeight(11) << endl;
    return 0;
}

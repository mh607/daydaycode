#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int encryptionCalculate(int dataA, int dataB) {
        while(dataB != 0)
        {
            int c = (unsigned int)(dataA & dataB) << 1;
            dataA ^= dataB;
            dataB = c;
        }
        return dataA;
    }
};

int main() {
    Solution solution;
    cout << solution.encryptionCalculate(5, 7) << endl;
    return 0;
}

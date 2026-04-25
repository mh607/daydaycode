#include <iostream>
#include <string>
#include <vector>

int kmp(std::string& s, std::string& t)
{
    int m = t.size();
    std::vector<int> next(m);
    next[0] = -1;
    int i = 0;
    int k = -1;
    while (i < m) {
        if (k == -1 || t[i] == t[k]) {
            ++i;
            ++k;
            if (t[i] == t[k]) {
                next[i] = next[k];
            } else {
                next[i] = k;
            }
        } else {
            k = next[k];
        }
    }
    i = 0;
    k = 0;
    int n = s.size();
    while(i < n && k < m) {
        if (k == -1 || s[i] == t[k]) {
            ++i;
            ++k;
        } else {
            k = next[k];
        }
    }
    if (k >= t.size()) {
        return (i - t.size());
    }
    return -1;
}

// aaaaabaaaaac aaaaac
int main() {
    std::string s{"aaaaabaaaaac"}, t{"aaaaac"};
    std::cout << kmp(s, t) << std::endl;
    return 0;
}

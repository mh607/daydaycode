#include <iostream>
#include <vector>

void maopao_sort(std::vector<int>& vec)
{
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

int main() {
    std::vector<int> vec {65, 58, 95, 10, 57, 62, 13, 106, 78, 23, 85};
    maopao_sort(vec);
    for (const auto value:vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}

#include <iostream>
#include <vector>

void quick_sort(std::vector<int>& vec, int start, int end)
{
    int i = start;
    int j = end;
    if (i >= j) {
        return;
    }
    int key = vec[i];
    while (i < j) {
        while (vec[j] >= key && j > i) {
            --j;
        }
        while (vec[i] <= key && j > i) {
            ++i;
        }
        if (i < j) {
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[start], vec[i]);
    quick_sort(vec, start, i - 1);
    quick_sort(vec, i + 1, end);
}

int main() {
    std::vector<int> vec {65, 58, 95, 10, 57, 62, 13, 106, 78, 23, 85};
    quick_sort(vec, 0, vec.size() - 1);
    for (const auto value:vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}

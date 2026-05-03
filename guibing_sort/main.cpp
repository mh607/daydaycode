#include <iostream>
#include <vector>

void guibing_sort(std::vector<int>& vec, int start, int end)
{
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    guibing_sort(vec, start, mid);
    guibing_sort(vec, mid + 1, end);
    int temp[end - start + 1];
    for (int k = 0; k < end - start + 1; ++k) {
        temp[k] = vec[start + k];
    }
    int i = start;
    int j = mid + 1;
    for (int k = start; k <= end; ++k) {
        if (i > mid) {
            vec[k] = temp[j - start];
            ++j;
        } else if (j > end) {
            vec[k] = temp[i - start];
            ++i;
        } else if (temp[i - start] <= temp[j - start]) {
            vec[k] = temp[i - start];
            ++i;
        } else {
            vec[k] = temp[j - start];
            ++j;
        }
    }
}

int main() {
    std::vector<int> vec {65, 58, 95, 10, 57, 62, 13, 106, 78, 23, 85};
    guibing_sort(vec, 0, vec.size() - 1);
    for (const auto value:vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    return 0;
}

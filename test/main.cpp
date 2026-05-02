#include <iostream>
#include "common.h"

int main() {
    fstream in("../data/input.txt");
    if (!in) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }
    vector<string> arr;
    ReadArray1(in, arr);
    vector<TreeNode> nodes(arr.size());
    TreeNode* root = nullptr;
    BuildTree(root, arr, nodes);
    return 0;
}

#include "common.h"

int StringToInt(const string &s) {
    int num = 0;
    stringstream ss(s);
    ss >> num;
    return num;
}

void ReadArray1(fstream &in, vector<string> &arr) {
    string line;
    getline(in, line);
    stringstream ss(line);
    string word;
    while (getline(ss, word, ',')) {
        arr.push_back(word);
    }
}

void BuildTree(TreeNode* &root, vector<string> &arr, vector<TreeNode> &nodes) {
    if (arr.empty()) return;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (arr[i] == "null") continue;
        nodes[i].val = StringToInt(arr[i]);
        size_t leftIndex = 2 * i + 1;
        size_t rightIndex = 2 * i + 2;
        if (leftIndex < nodes.size()) {
            nodes[i].left = &nodes[leftIndex];
        }
        if (rightIndex < nodes.size()) {
            nodes[i].right = &nodes[rightIndex];
        }
    }
    root = &nodes[0];
}
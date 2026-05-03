#include <iostream>
#include "common.h"
#include <queue>

TreeNode* head;
TreeNode* pre;

void dfs(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    dfs(root->left);
    if (pre == nullptr) {
        head = root;
    } else {
        pre->right = root;
    }
    root->left = pre;
    pre = root;
    dfs(root->right);
}

TreeNode* treeToList(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    head = nullptr;
    pre = nullptr;
    dfs(root);
    pre->right = head;
    head->left = pre;
    return head;
}

int main() {
    fstream in("../data/input.txt");
    if (!in) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }
    vector<string> arr;
    ReadArray1(in, arr);
    vector<TreeNode> nodes1(arr.size());
    TreeNode* root1 = nullptr;
    BuildTree(root1, arr, nodes1);
    treeToList(root1);
    return 0;
}

#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
int StringToInt(const string &s);
void ReadArray1(fstream &in, vector<string> &arr);
void BuildTree(TreeNode* &root, vector<string> &arr, vector<TreeNode> &nodes);
#endif // COMMON_H
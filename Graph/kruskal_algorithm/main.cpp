/*
Kruskal算法实现最小生成树（MST）
算法步骤：
1. 将所有边按权重排序
2. 初始化并查集，每个顶点一个集合
3. 遍历排序边，如果两顶点不在同一集合，添加边并合并集合
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 边结构体
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w) : u(u), v(v), weight(w) {}
};

// 并查集
class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int size) {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // 路径压缩
        }
        return parent[x];
    }
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) return false;
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

// Kruskal算法
vector<Edge> kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });
    UnionFind uf(V);
    vector<Edge> mst;
    for (auto& edge : edges) {
        if (uf.unite(edge.u, edge.v)) {
            mst.push_back(edge);
        }
    }
    return mst;
}

int main() {
    // 示例图
    int V = 7; // 顶点数
    vector<Edge> edges = {
        {0, 1, 2},
        {0, 2, 4},
        {0, 3, 1},
        {1, 3, 3},
        {1, 4, 10},
        {2, 3, 2},
        {2, 5, 5},
        {3, 4, 7},
        {3, 5, 8},
        {3, 6, 4},
        {4, 6, 6},
        {5, 6, 1}
    };

    vector<Edge> mst = kruskal(V, edges);

    cout << "最小生成树的边：" << endl;
    for (auto& edge : mst) {
        cout << edge.u + 1 << " - " << edge.v + 1 << " : " << edge.weight << endl;
    }

    return 0;
}

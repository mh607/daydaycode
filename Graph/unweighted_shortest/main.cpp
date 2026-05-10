/*
无权图的最短路径问题可以使用广度优先搜索（BFS）来解决。BFS适用于无权图，因为它会逐层遍历图，确保在找到目标节点时已经经过了最少的边数。
*/
#include <iostream>
#include <queue>

using namespace std;
struct Graph
{
    /* data */
    int V; // 顶点数
    vector<vector<int>> adj; // 邻接表
    vector<vector<int>> result; // 存储结果
    Graph(int V) : V(V) {
        adj.resize(V);
        result.resize(V, vector<int>(2, -1)); // 初始化结果矩阵为-1
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v); // 有向图
    }
    vector<vector<int>> bfs(int start) {
        queue<int> q;
        q.push(start);
        result[start][0] = 0; // 起点距离为0

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (result[v][0] == -1) { // 如果v未访问
                    result[v][0] = result[u][0] + 1; // 更新v的距离
                    result[v][1] = u; // 记录v的前驱节点
                    q.push(v); // 将v加入队列
                }
            }
        }
        return result; // 返回从start到所有节点的距离
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 0);
    g.addEdge(2, 5);
    g.addEdge(3, 2);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 6);
    g.addEdge(6, 5);
    vector<vector<int>> result = g.bfs(2);
    for (int i = 0; i < result.size(); i++) {
        cout << "Node: " << i + 1 << ", Distance: " << result[i][0] << ", Predecessor: " << result[i][1] + 1 << endl;
    }
    return 0;
}

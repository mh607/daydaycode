/*
有权图的最短路径问题可以使用Dijkstra算法来解决。Dijkstra算法是一种贪心算法，适用于边权非负的图。它通过不断选择当前距离最短的节点来更新其邻居节点的距离，直到所有节点的最短路径都被确定。
*/
#include <iostream>
#include <queue>

using namespace std;
struct Graph
{
    /* data */
    int V; // 顶点数
    vector<vector<pair<int, int>>> adj; // 邻接表，存储邻居节点和边权
    vector<pair<int, int>> result; // 存储结果
    Graph(int V) : V(V) {
        adj.resize(V);
        result.resize(V, {INT_MAX, -1}); // 初始化结果矩阵为-1
    }
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight}); // 有向图
    }
    vector<pair<int, int>> dijkstra(int start) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // 最小堆
        pq.push({0, start}); // 起点距离为0
        result[start].first = 0; // 起点距离为0

        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();

            if (dist > result[u].first) continue; // 如果当前距离大于已记录的距离，跳过

            for (auto [v, weight] : adj[u]) {
                if (result[v].first > dist + weight) { // 如果找到更短的路径
                    result[v].first = dist + weight; // 更新v的距离
                    result[v].second = u; // 记录v的前驱节点
                    pq.push({result[v].first, v}); // 将v加入优先队列
                }
            }
        }
        return result; // 返回从start到所有节点的距离和前驱节点
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 10);
    g.addEdge(2, 0, 4);
    g.addEdge(2, 5, 5);
    g.addEdge(3, 2, 2);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 8);
    g.addEdge(3, 6, 4);
    g.addEdge(4, 6, 1);
    g.addEdge(6, 5, 1);
    vector<pair<int, int>> result = g.dijkstra(2);
    for (int i = 0; i < result.size(); i++) {
        cout << "Node: " << i + 1 << ", Distance: " << result[i].first << ", Predecessor: " << result[i].second + 1 << endl;
    }
    return 0;
}

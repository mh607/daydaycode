/*
最大流算法是用于解决网络流问题的一类算法，旨在找到一个流网络中从源点到汇点的最大流量。
这里实现 Dinic 算法：
1. 通过 BFS 构造分层图
2. 在分层图上使用 DFS 寻找阻塞流
3. 重复直到无法找到增广路径
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

struct Edge {
    int to;
    int rev;
    int cap;
};

class Dinic {
public:
    Dinic(int n) : graph(n), level(n), iter(n) {}

    void addEdge(int u, int v, int cap) {
        graph[u].push_back(Edge{v, (int)graph[v].size(), cap});
        graph[v].push_back(Edge{u, (int)graph[u].size() - 1, 0});
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        const int INF = numeric_limits<int>::max();
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
        return flow;
    }

private:
    vector<vector<Edge>> graph;
    vector<int> level;
    vector<int> iter;

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& e : graph[u]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int &i = iter[u]; i < (int)graph[u].size(); ++i) {
            Edge &e = graph[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
};

int main() {
    // 示例图：顶点 0 为源点，顶点 5 为汇点
    int V = 6;
    Dinic dinic(V);
    dinic.addEdge(0, 1, 10);
    dinic.addEdge(0, 2, 10);
    dinic.addEdge(1, 2, 2);
    dinic.addEdge(1, 3, 4);
    dinic.addEdge(1, 4, 8);
    dinic.addEdge(2, 4, 9);
    dinic.addEdge(3, 5, 10);
    dinic.addEdge(4, 3, 6);
    dinic.addEdge(4, 5, 10);

    int s = 0;
    int t = 5;
    int max_flow = dinic.maxFlow(s, t);

    cout << "最大流为: " << max_flow << endl;
    return 0;
}

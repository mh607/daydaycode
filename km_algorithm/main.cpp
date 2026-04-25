#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

const int INF = 1e9;

struct KM {
    int n;
    vector<vector<int>> w;
    vector<int> lx, ly;
    vector<int> match_y;
    vector<int> match_x;
    vector<int> slack;
    vector<int> prev_y;
    vector<bool> vx, vy;

    KM(int n): n(n) {
        w.assign(n, vector<int>(n, 0));
        lx.resize(n);
        ly.assign(n, 0);
        match_y.assign(n, -1);
        match_x.assign(n, -1);
        slack.resize(n);
        prev_y.resize(n);
        vx.resize(n);
        vy.resize(n);
    }

    void addEdge(int u, int v, int weight) {
        w[u][v] = weight;
    }

    // 返回找到的增广路径终点 y
    int bfs(int start) {
        fill(slack.begin(), slack.end(), INF);
        fill(vx.begin(), vx.end(), false);
        fill(vy.begin(), vy.end(), false);
        fill(prev_y.begin(), prev_y.end(), -1);

        queue<int> q;
        q.push(start);
        vx[start] = true;

        while (true) {
            // BFS 扩展
            while (!q.empty()) {
                int x = q.front(); q.pop();

                for (int y = 0; y < n; y++) {
                    if (vy[y]) continue;

                    int delta = lx[x] + ly[y] - w[x][y];

                    if (delta == 0) {
                        vy[y] = true;
                        prev_y[y] = x;

                        if (match_y[y] == -1) {
                            return y; // 找到增广路径
                        }

                        int next_x = match_y[y];
                        if (!vx[next_x]) {
                            q.push(next_x);
                        }
                    } else {
                        if (slack[y] > delta) {
                            slack[y] = delta;
                            prev_y[y] = x;
                        }
                    }
                }
            }

            // 调整顶标
            int d = INF;
            for (int y = 0; y < n; y++) {
                if (!vy[y]) d = min(d, slack[y]);
            }

            for (int i = 0; i < n; i++) {
                if (vx[i]) lx[i] -= d;
                if (vy[i]) ly[i] += d;
                else slack[i] -= d;
            }

            // 用 slack == 0 的边继续扩展
            for (int y = 0; y < n; y++) {
                if (!vy[y] && slack[y] == 0) {
                    vy[y] = true;

                    if (match_y[y] == -1) {
                        return y;
                    }

                    int next_x = match_y[y];
                    if (!vx[next_x]) {
                        q.push(next_x);
                    }
                }
            }
        }
    }

    void augment(int y) {
        // 沿 prev_y 回溯增广
        while (y != -1) {
            int x = prev_y[y];
            int next_y = match_x[x];
            match_y[y] = x;
            match_x[x] = y;
            y = next_y;
        }
    }

    int solve() {
        // 初始化 lx
        for (int i = 0; i < n; i++) {
            lx[i] = *max_element(w[i].begin(), w[i].end());
        }

        for (int i = 0; i < n; i++) {
            int y = bfs(i);
            augment(y);
        }

        int res = 0;
        for (int j = 0; j < n; j++) {
            if (match_y[j] != -1) {
                std::cout << "Match: x:" << match_y[j] << " -> y:" << j << " (weight: " << w[match_y[j]][j] << ")" << std::endl;
                res += w[match_y[j]][j];
            } 
        }
        return res;
    }
};

int main() {
    int n = 3;
    KM km(n);
    km.addEdge(0, 0, 10);
    km.addEdge(0, 1, 19);
    km.addEdge(0, 2, 8);
    km.addEdge(1, 0, 10);
    km.addEdge(1, 1, 18);
    km.addEdge(1, 2, 7);
    km.addEdge(2, 0, 13);
    km.addEdge(2, 1, 16);
    km.addEdge(2, 2, 9);

    cout << "Maximum weight matching: " << km.solve() << endl;
    return 0;
}
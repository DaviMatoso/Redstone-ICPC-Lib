#include <bits/stdc++.h>
using namespace std;

int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

int isvalid(int x, int y, int n, int m) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

void bfs (vector<vector<int>>& graph, vector<vector<bool>>& visited, pair<int,int>& v) {
    int n =graph.size();
    int m = graph[0].size();
    queue<pair<int,int>> q;
    visited[v.first][v.second] = true;
    q.push({v.first, v.second});

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        FOR (i, 4) {
            int ax = x +dx[i];
            int ay = y +dy[i];

            if (isvalid(ax,ay,n,m) && !visited[ax][ay]) {
                visited[ax][ay] = true;
                q.push({ax, ay});
            }
        }
    }
}

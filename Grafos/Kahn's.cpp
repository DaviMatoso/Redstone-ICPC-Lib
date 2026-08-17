#include <bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>>& adj;



vector<int> toposort() {
    vector<int> deg(n, 0);
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            deg[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> ord;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.push_back(u);
        
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    
    return ord;
}


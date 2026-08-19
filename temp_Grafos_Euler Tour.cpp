#include <bits/stdc++.h>


ll vals[N];
int tin[N], tout[N];
vector<vector<int>> adj(N);
int timer = 0;

void euler(int node, int prev) {
    tin[node] = timer++;
    for(int v : adj[node]) {
        if(v != prev) {
            euler(v, node);
        }
    }
    tout[node] = timer;
}

bool ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

// Pré-processamento de LCA usando Seg Tree
// queries em O(log N) com pré-processamento em O(N)

const int N = 100000;

int tin[N], euler_list[2*N];
vector<vector<int>> adj(N);
int timer = 0;

int seg_lca[8*N];

void euler(int node, int prev) {
    tin[node] = timer;
    euler_list[timer++] = node;
    for(int v : adj[node]) {
        if(v != prev) {
            euler(v, node);
            euler_list[timer++] = node;
        }
    }
}

int join(int x, int y) {
    if(x == -1) {
        return y;
    }
    if(y == -1) {
        return x;
    }
    return (tin[x] < tin[y] ? x : y);
}

void build(int l = 0, int r = timer-1, int idx = 0) {
    if(l == r) {
        seg_lca[idx] = euler_list[l];
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, 2*idx+1);
    build(mid+1, r, 2*idx+2);
    seg_lca[idx] = join(seg_lca[2*idx+1], seg_lca[2*idx+2]);
}

int query(int L, int R, int l = 0, int r = timer-1, int idx = 0) {
    if(R < l || L > r) {
        return -1;
    }
    if(L <= l && r <= R) {
        return seg_lca[idx];
    }
    int mid = (l+r)/2;
    return join(query(L, R, l, mid, 2*idx+1), query(L, R, mid+1, r, 2*idx+2));
}

int lca(int u, int v) {
    if(tin[u] > tin[v]) {
        swap(u, v);
    }
    return query(tin[u], tin[v]);
}
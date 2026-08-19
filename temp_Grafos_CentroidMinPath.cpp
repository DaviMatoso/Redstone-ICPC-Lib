#include <bits/stdc++.h>
 
using namespace std;
 
#define ll long long
 
const int MAXN = 2e5+5;
vector<int> adj[MAXN];
bool rem[MAXN];
int subtree_size[MAXN], parents[MAXN];
int K; // caminho de tamanho K
ll ans = 0; // contagem de caminhos com tamanho K
 
int cnt[MAXN];
 
int get_sub_size(int v, int p = -1) {
    subtree_size[v] = 1;
    for(int u : adj[v]) {
        if(u == p || rem[u]) {
            continue;
        }
        subtree_size[v] += get_sub_size(u, v);
    }
    return subtree_size[v];
}
 
int get_centroid(int v, int tree_size, int p = -1) {
    for(int u : adj[v]) {
        if(u == p || rem[u]) {
            continue;
        }
        if(subtree_size[u]*2 > tree_size) {
            return get_centroid(u, tree_size, v);
        }
    }
    return v;
}
 
void get_distances(int v, int p, int dist, vector<int>& distances) {
    if(dist > K) {
        return;
    }
    distances.push_back(dist);
    for(int u : adj[v]) {
        if(u == p || rem[u]) {
            continue;
        }
        get_distances(u, v, dist+1, distances);
    }
}
 
void process_centroid(int centroid) {
    vector<int> used;
    cnt[0] = 1;
    used.push_back(0);
    for(int u : adj[centroid]) {
        if(rem[u]) {
            continue;
        }
        vector<int> curr;
        get_distances(u, centroid, 1, curr);
 
        for(int d : curr) {
            if(K - d >= 0) {
                ans += cnt[K - d];
            }
        }
        for(int d : curr) {
            if(cnt[d] == 0) {
                used.push_back(d);
            }
            cnt[d]++;
        }
    }
    for(int d : used) {
        cnt[d] = 0;
    }
}
 
int decompose(int v, int p = -1) {
    int tree_size = get_sub_size(v);
    int centroid = get_centroid(v, tree_size);
    process_centroid(centroid);
    rem[centroid] = true; parents[centroid] = p; 
    for(int u : adj[centroid]) {
        if(!rem[u]) {
            decompose(u);
        }
    }
    return centroid;
}
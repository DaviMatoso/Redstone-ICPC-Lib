#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second



int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};



int n, m;
vector<vector<int>> adj;
int timer;

// for the normal graph
vector<bool> visited;
vector<int> tin, low, points;
vector<bool> is_cutpoint;


// for the grid
vector<vector<bool>> visGrid;
vector<vector<pair<int,int>>> times;
vector<pair<int,int>> pointsGrid;
vector<vector<bool>> is_cutpointGrid;

//find bridges
vector<pair<int, int>> bridges;

//////////////// - setup - //////////////////



void dfs_bridges(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs_bridges(to, v);
            low[v] = min(low[v], low[to]);
            
            if (low[to] > tin[v]) {
                bridges.push_back({min(v, to), max(v, to)});
            }
        }
    }
}




void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children=0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1 && !is_cutpoint[v]) {
                points.push_back(v); //v is a cutpoint
                is_cutpoint[v] = true;
            }
            ++children;
        }
    }
    if(p == -1 && children > 1 ) {
        points.push_back(v); //v (the root of the dfs) is a cutpoint
        is_cutpoint[v] = true;
    }
}






bool check(int x, int y) { return x >= 0 && x < n && y >= 0 && y < m && adj[x][y]; }

void dfsG(pair<int,int> v, pair<int,int> p={-1,-1}) {
    int& vf = v.ff;
    int& vs = v.ss;
    
    visGrid[vf][vs] = true;
    times[vf][vs] = {timer, timer}, timer++;
    int children=0;
    for (int i = 0; i < 4; i++) {
        int ax = dx[i] + vf;
        int ay = dy[i] + vs;

        if (!check(ax, ay) || (ax == p.ff && ay == p.ss)) continue;
        
        if (visGrid[ax][ay]) times[vf][vs].ss = min(times[vf][vs].ss, times[ax][ay].ff);
        else {
            dfsG({ax, ay}, v);
            times[vf][vs].ss = min(times[vf][vs].ss, times[ax][ay].ss);

            if (!is_cutpointGrid[vf][vs] && times[ax][ay].ss >= times[vf][vs].ff && (p.ff != -1)) {
                pointsGrid.push_back(v);
                is_cutpointGrid[vf][vs] = true;
            }
            ++children;
        }
    }
    if (!is_cutpointGrid[vf][vs] && p.ff == -1 && children > 1) {
        pointsGrid.push_back(v);
        is_cutpointGrid[vf][vs] = true;
    }
}

void find_cutpoints() {
    timer = 0;
    visited.assign(n, false);
    is_cutpoint.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    points.clear();
    
    /*
    visGrid.assign(n, vector<bool>(m, false));
    times.assign(n, vector<pair<int,int>>(m, {-1,-1}));
    is_cutpointGrid.assign(n, vector<bool>(m, false));
    */

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs (i); 
        }
    }
}


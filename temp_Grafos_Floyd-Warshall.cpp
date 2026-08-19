#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int MAXN = 5e2;
const int INF = 1e18;

int n;
ll g[MAXN][MAXN];

void floyd() 
{
  for (int k = 0; k < n; ++k) 
    for (int i = 0; i < n; ++i) 
      for (int j = 0; j < n; ++j) 
          if (g[i][k] < INF && g[k][j] < INF)
              g[i][j] = min(g[i][j], g[i][k] + g[k][j]); 
}
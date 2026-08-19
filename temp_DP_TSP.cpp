#include <bits/stdc++.h>


const int MOD = 1e9 + 7;

int n;
int costs[10][10];
int dp[1<<10][10];

void tsp_iter() {    
    const int inf = 2e9;
    for(int mask = 0; mask < (1<<n); mask++) {
        for(int i = 0; i < n; i++) {
            dp[mask][i] = inf;
        }
    }
    dp[1][0] = 0;
    for(int mask = 1; mask < (1<<n); mask++) {
        for(int i = 0; i < n; i++) {
            if(mask & (1<<i)) { // visitando
                for(int j = 0; j < n; j++) {
                    if(mask & (1<<j)) { // já visitado
                        continue;
                    }
                    // atualiza o custo mínimo para o estado
                    dp[mask ^ (1<<j)][j] = min(dp[mask ^ (1<<j)][j], dp[mask][i] + costs[i][j]);
                }
            }
        }
    }
    int best = inf;
    for(int i = 1; i < n; i++) {
        best = min(best, dp[(1<<n) - 1][i] + costs[i][0]);
    }
    cout << best << "\n";
}



int n;
int matches[21][21];
ll dp[1<<21];

void tsp_iter() {
    if (n == 1) {
        cout << matches[0][0] << "\n";
        return;
    }
    dp[0] = 1;
    for(int mask = 0; mask < (1<<n); mask++) {
        int i = __builtin_popcount(mask);
        if(i >= n) {
            continue;
        }
        for(int j = 0; j < n; j++) {
            if(mask & (1<<j)) {
                continue;
            }
            if(matches[i][j] == 0) {
                continue;
            }
            dp[mask ^ (1<<j)] += dp[mask] % MOD;
        }
    }
    cout << dp[(1<<n)-1] % MOD << "\n";
}
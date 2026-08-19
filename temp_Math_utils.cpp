#include <bits/stdc++.h>
using namespace std;

#define ll long long int //LATEX_IGNORED_LINE
#define tiii tuple<int,int,int> //LATEX_IGNORED_LINE
#define pii pair<ll,ll> //LATEX_IGNORED_LINE
#define rep(i,n) for (int i = 0; i < n; i++) //LATEX_IGNORED_LINE
#define ll long long
#define i128 __int128_t


const int MOD = 1e9 + 7; //LATEX_IGNORED_LINE



ll gcd_ll(ll a, ll b) {
    while (b != 0) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

ll lcm_ll(ll a, ll b) {
    return a / gcd_ll(a, b) * b;
}

// Bit manipulation utilities
ll count_set_bits(ll n) {
    return __popcount<ll>(n); // __builtin_popcount(n);
}

inline ll safe_mod(ll x) {
    return (x % MOD + MOD) % MOD;
}


#define ll long long
#define i128 __int128_t

// Usando i128 pra evitar overflow no lcm
i128 lcmgcd(ll a, ll b) {
    return (i128)a/gcd(a, b) * b;
}
// Dps checa se o lcm é maior que 1e18 e decide o que fazer (ignora ou outra coisa)

// -----------------------------------------------

// Cuidado com re-hashing do map e unordered_map
// Usar .reserve

// -----------------------------------------------

// Estratégia de random shuffle para algoritmos randomizados

void random_shuffle(vector<int>& vec, int n) {
    for(int i = 0; i < n; i++) {
        int j = rand() % (i+1);
        swap(vec[i], vec[j]);
    }
}
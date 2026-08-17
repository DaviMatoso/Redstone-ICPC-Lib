#define ll long long
#pragma once //LATEX_IGNORED_LINE
ll mod = 1e9 + 7;

ll fexp(ll b, ll p){
	ll ans = 1;
	while(p){
		if(p&1) ans = ans * b % mod;
		b = b * b % mod;
		p >>= 1;
	}
	return ans;
}
// O(Log P) // b - Base // p - Potência

Matrix<ll> Matfexp(Matrix<ll>& b, ll p){
    Matrix<ll> ans(b.n);
    FOR (i,0, b.n) ans.mat[i][i] = 1;

    while(p) {
        if(p&1) ans = ans * b;
        b = b * b;
        p >>= 1;
    }
    return ans;
}

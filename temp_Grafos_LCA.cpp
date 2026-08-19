#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5 + 5;
const int MAXLG = 20;

vector<int> g[MAXN];
int bl[MAXLG][MAXN], lvl[MAXN];

void dfs(int u, int p, int l=0){
	lvl[u] = l;
	bl[0][u] = p;

	for(auto v : g[u]) if(v != p)
		dfs(v, u, l+1);
}

void buildBL(int N){
	for(int i=1; i<MAXLG; i++)
		for(int u=0; u<N; u++)
			bl[i][u] = bl[i-1][bl[i-1][u]];	
}

int lca(int u, int v){
	if(lvl[u] < lvl[v]) swap(u, v);

	for(int i=MAXLG-1; i>=0; i--)
		if(lvl[u] - (1<<i) >= lvl[v])
			u = bl[i][u];
	
	if(u == v) return u;

	for(int i=MAXLG-1; i>=0; i--)
		if(bl[i][u] != bl[i][v])
			u = bl[i][u],
			v = bl[i][v];

	return bl[0][u];
}

// K steps
int n;
const int LOG = 31;
const int MAXN = 2e5 + 5;

int up[LOG][MAXN];
void bin_lift() {
    for(int i = 1; i < LOG; i++) {
        for(int j = 0; j < n; j++) {
            up[i][j] = up[i-1][up[i-1][j]];
        }
    }
}

int kSteps(int v, int k) {
    for(int i = 0; i < LOG; i++) {
        if(k & (1LL << i)) {
            v = up[i][v];
        }
    }
    return v;
}

/*LATEX_DESC_BEGIN***************************
	**LCA** - Lowest Common Ancestor - **Binary Lifting** - O(Log N) - Build O(N Log N)
Encontrar o menor ancestral comum entre dois vértices em uma árvore enraizada
IMPORTANTE! O algoritmo está 0-indexado 
   -> chame dfs(root, root) para calcular o pai e a altura de cada vértice
   -> chame buildBL() para criar a matriz do Binary Lifting
   -> chame lca(u, v) para encontrar o menor ancestral comum
   bl[i][u] -> Binary Lifting com o (2^i)-ésimo pai de u
   lvl[u]   -> Altura ou level de U na árvore
*****************************LATEX_DESC_END*/
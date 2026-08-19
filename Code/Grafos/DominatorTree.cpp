#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn = 1e5;
int anc[maxn], par[maxn], pmin[maxn];
int sdom[maxn], idom[maxn];
int tin[maxn], tout[maxn];
vector<int> g[maxn];
vector<int> gr[maxn];
vector<int> tree[maxn];
vector<int> bucket[maxn];
vector<int> order;

int tt=0;
void dfs(int u){
	tin[u] = tt++;
	sdom[u] = pmin[u] = u;
	order.push_back(u);

	for(auto v : g[u]) 
		if(tin[v] == -1) 
			dfs(v), par[v] = u;
}

int sfind(int v){
	if(anc[v] == -1) return v;
	if(anc[anc[v]] != -1){
		int u = sfind(anc[v]);
		if(tin[sdom[u]] < tin[sdom[pmin[v]]]) pmin[v] = u;
		anc[v] = anc[u];
	}
	return pmin[v];
}

void treefs(int u){
	tin[u] = ++tt;
	for(auto v : tree[u]) 
		treefs(v);
	tout[u] = tt;
}

bool dominates(int u, int v){
	return tin[u] <= tin[v] && tin[v] <= tout[u];
}

void build(int n, int s){
	memset(anc, -1, sizeof anc);
	memset(tin, -1, sizeof tin);
	
	dfs(s);
	
	reverse(begin(order), end(order)); order.pop_back();
	
	auto smin = [&](int u, int v){ 
		return tin[sdom[u]] < tin[sdom[v]] ? sdom[u] : sdom[v]; 
	};

	for(auto w : order){     
		for(auto v : gr[w]) sdom[w] = smin(w, sfind(v));
		anc[w] = par[w];
		bucket[sdom[w]].push_back(w);
		
		for(auto v : bucket[par[w]]){
			int u = sfind(v);
			idom[v] = (u == v) ? sdom[v] : u;
		} 
		bucket[anc[w]].clear();
	}

	reverse(begin(order), end(order));
	
	for(auto u : order) 
		if(idom[u] != sdom[u]) 
			idom[u] = idom[idom[u]];
	
	idom[s] = -1;
	for(auto i : order) tree[idom[i]].push_back(i);
	treefs(s);
	// edgeDominator(order);
}

auto edgeDominator(vector<int>&nodes){
	vector<pair<int, int>> edges;
	for(auto w : nodes){
		int cnt = 0, okok = true;
		for(auto x : gr[w]) if(x == par[w]) cnt++; else okok &= dominates(w, x);
		if(okok && cnt == 1) edges.push_back({par[w], w});
	}
	return edges;
}

/*LATEX_DESC_BEGIN***************************
**Dominator Tree** & **Edge Dominator**

Seja S um nó de um grafo direcionado, um vértice U domina V sse todo caminho de S para V passa por U.
A definição é semelhante para aresta. 
S sempre será a raiz da dominator Tree e a relação é transitiva.

- Relacionado: **Strong Bridges** e **Strong Cut Points**
Vértice ou Aresta que, se removido, aumenta a quantidade de SCCs.

Seja G um SCC e GR seu grafo reverso, podemos calcular as Strong Bridges e Strong Cut Points usando Dominators e EdgeDominators.
Seja S a raíz escolhida, calcule os dominators partindo de S em G. Depois troque G e Gr e recalcule.
	build(n, 0); getDom(); for(int u=0; u<n; u++) swap(g[u], gr[u]); build(n, 0); getDom();
Os strong dominators serão a união dos dois conjuntos. 
A única excessão é S, que sempre será um dominator por ser a raiz, ele deve ser considerado a parte.
Se G não for um SCC, use tarjan pra encontrar os SCCs e isole cada chamada do Build e da DFS a um SCC.
*****************************LATEX_DESC_END*/
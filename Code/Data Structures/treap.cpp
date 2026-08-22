#include <bits/stdc++.h>
using namespace std;

/* Implicit Treap (Range Update, Range Query, Reverse, Structural Move)
 * Complexidade: O(log N) para updates, queries, insert, erase e move.
 * Memória: O(N)
 * Requisitos:
 * - NODE deve ter: static merge(L, R), apply(TAG, sz) e construtor identidade.
 * - TAG deve ter: compose(TAG) e construtor identidade.
 */

/* --- Exemplo de NODE e TAG (Soma e Multiplicacao com Modulo) ---
const ll MOD = 1e9 + 7;
struct Tag {
    ll mul = 1, add = 0;
    void compose(const Tag& t) {
        add = (add * t.mul + t.add) % MOD;
        mul = (mul * t.mul) % MOD;
    }
};

struct Node {
    ll val = 0;
    Node(ll v = 0) : val(v) {}
    static Node merge(const Node& l, const Node& r) {
        return Node((l.val + r.val) % MOD);
    }
    void apply(const Tag& t, int sz) {
        val = (val * t.mul + t.add * sz) % MOD;
    }
};
*/

template<typename NODE, typename TAG>
struct ImplicitTreap {
    struct TreeNode {
        int l = 0, r = 0;
        int y, c = 1;
        bool rev = 0;
        NODE val, aggr;
        TAG lazy;
        TreeNode() : y(rand()) {}
        TreeNode(NODE v) : y(rand()), val(v), aggr(v) {}
    };

    vector<TreeNode> tr;
    int root = 0;

    ImplicitTreap() {
        tr.emplace_back(); // tr[0] -> dummy NULL node
        tr[0].c = 0; 
    }

    int new_node(NODE val) {
        tr.push_back(TreeNode(val));
        return tr.size() - 1;
    }

    void recalc(int u) {
        if (!u) return;
        int l = tr[u].l, r = tr[u].r;
        tr[u].c = 1 + tr[l].c + tr[r].c;
        tr[u].aggr = tr[u].val;
        if (l) tr[u].aggr = NODE::merge(tr[l].aggr, tr[u].aggr);
        if (r) tr[u].aggr = NODE::merge(tr[u].aggr, tr[r].aggr);
    }

    void push(int u) {
        if (!u) return;
        int l = tr[u].l, r = tr[u].r;
        
        if (tr[u].rev) {
            if (l) { tr[l].rev ^= 1; swap(tr[l].l, tr[l].r); }
            if (r) { tr[r].rev ^= 1; swap(tr[r].l, tr[r].r); }
            tr[u].rev = 0;
        }
        
        if (l) {
            tr[l].val.apply(tr[u].lazy, 1);
            tr[l].aggr.apply(tr[u].lazy, tr[l].c);
            tr[l].lazy.compose(tr[u].lazy);
        }
        if (r) {
            tr[r].val.apply(tr[u].lazy, 1);
            tr[r].aggr.apply(tr[u].lazy, tr[r].c);
            tr[r].lazy.compose(tr[u].lazy);
        }
        tr[u].lazy = TAG();
    }

    pair<int, int> split(int u, int k) {
        if (!u) return {0, 0};
        push(u);
        int l_size = tr[tr[u].l].c;
        if (l_size >= k) {
            auto [L, R] = split(tr[u].l, k);
            tr[u].l = R;
            recalc(u);
            return {L, u};
        } else {
            auto [L, R] = split(tr[u].r, k - l_size - 1);
            tr[u].r = L;
            recalc(u);
            return {u, R};
        }
    }

    int merge(int l, int r) {
        if (!l || !r) return l ? l : r;
        push(l); push(r);
        if (tr[l].y > tr[r].y) {
            tr[l].r = merge(tr[l].r, r);
            recalc(l);
            return l;
        } else {
            tr[r].l = merge(l, tr[r].l);
            recalc(r);
            return r;
        }
    }

    //// -----

    void insert(int pos, NODE val) {
        auto [L, R] = split(root, pos);
        root = merge(merge(L, new_node(val)), R);
    }

    void erase(int pos) {
        auto [L, R1] = split(root, pos);
        auto [M, R] = split(R1, 1);
        root = merge(L, R);
    }

    void update(int l, int r, const TAG& tag) {
        auto [L, R1] = split(root, l);
        auto [M, R] = split(R1, r - l + 1);
        if (M) {
            tr[M].val.apply(tag, 1);
            tr[M].aggr.apply(tag, tr[M].c);
            tr[M].lazy.compose(tag);
        }
        root = merge(L, merge(M, R));
    }

    NODE query(int l, int r) {
        auto [L, R1] = split(root, l);
        auto [M, R] = split(R1, r - l + 1);
        NODE res = M ? tr[M].aggr : NODE();
        root = merge(L, merge(M, R));
        return res;
    }

    void reverse_range(int l, int r) {
        auto [L, R1] = split(root, l);
        auto [M, R] = split(R1, r - l + 1);
        if (M) {
            tr[M].rev ^= 1;
            swap(tr[M].l, tr[M].r);
        }
        root = merge(L, merge(M, R));
    }

    void move_range(int l, int r, int dest) {
        auto [L, R1] = split(root, l);
        auto [M, R] = split(R1, r - l + 1);
        int without_m = merge(L, R);
        auto [new_L, new_R] = split(without_m, dest);
        root = merge(new_L, merge(M, new_R));
    }

    // void traverse(int u, vector<NODE>& res) {
    //     if (!u) return;
        
    //     push(u); 
        
    //     traverse(tr[u].l, res);
    //     res.push_back(tr[u].val);
    //     traverse(tr[u].r, res);
    // }
};



/*LATEX_DESC_BEGIN***************************
-> **Implicit Treap - Lazy Propagation** com:
        - Query & Update em Range
        - Reversal (Reverse array segment)
        - Move (Cut and Paste segments)
        - Insert & Erase O(log N) no meio do array
        - 0-indexed
Query/Update/Reverse: O(log N)
Memory: O(N)
*****************************LATEX_DESC_END*/
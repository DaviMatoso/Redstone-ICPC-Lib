int main() {
    ios_base::sync_with_stdio(0); cin.tie(nullptr);
    vector<ll> cat_nums(11);
    cat_nums[0] = 1;
    for(int i = 0; i < 10; i++) {
        cat_nums[i+1] = cat_nums[i] * ((2*i+2)*(2*i+1))/((i+2)*(i+1));
    }
    return 0;
}

/* Alguns exemplos de como usar os números de Catalan 

1. Cat(n) counts the number of distinct binary trees with n vertices, e.g. for n = 3:

          *    *   *   *   *
         /    /   / \   \   \
        *    *   *   *   *   *
       /      \         /     \
      *        *       *       *

2. Cat(n) counts the number of expressions containing n pairs of parentheses which are
correctly matched, e.g. for n = 3, we have: ()()(), ()(()), (())(), ((())), and (()()).

3. Cat(n) counts the number of different ways n + 1 factors can be completely parenthesized, e.g. for n = 3 and 3 + 1 = 4 factors: {a, b, c, d}, we have: (ab)(cd), a(b(cd)),
((ab)c)d, (a(bc))(d), and a((bc)d).

4. Cat(n) counts the number of ways a convex polygon (see Section 7.3) of n + 2 sides
can be triangulated. See Figure 5.1, left.

5. Cat(n) counts the number of monotonic paths along the edges of an n x n grid, which
do not pass above the diagonal. A monotonic path is one which starts in the lower
left corner, finishes in the upper right corner, and consists entirely of edges pointing
rightwards or upwards. See Figure 5.1, right and also see Section 4.7.1.

*/ 

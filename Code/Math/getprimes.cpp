#include <bits/stdc++.h>
using namespace std;
#define FOR(i,j,n) for(int i = j; i < n; i++)
#define br '\n'


int cntprimes(int n) {
    int ans = 1;
    for (int i = 2; i*i <= n; i++) {
        int cnt = 0;

        while (n % i == 0) {
            n /= i;
            cnt++;
        }

        if (cnt > 0) ans *= cnt+1;
    }

    if (n > 1) ans *= 2;
    return ans;
}
// O(sqrt(n))


 vector<pair<int,int>> getprimes(int n) {
    vector<pair<int,int>> primes;
    for (int i = 2; i*i <= n; i++) {
        int cnt = 0;

        while (n % i == 0) {
            n /= i;
            cnt++;
        }
      
        if (cnt > 0) primes.push_back({i, cnt});
    }
   
    if (n > 1) primes.push_back({n, 1});
    return primes;
}
// O(sqrt(n))


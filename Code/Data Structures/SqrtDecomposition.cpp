#include <bits/stdc++.h>

using namespace std;

struct sqrt_decomp {
  int n, block_size, num_blocks;  
  vector<int> a; 
  vector<long long> b;

  sqrt_decomp() {}
  sqrt_decomp(vector<int>& arr) : n(arr.size()), block_size(sqrt(n) + 1), a(arr) {
    num_blocks = (n + block_size - 1) / block_size;
    b.assign(num_blocks, 0);
    
    for (int i = 0; i < n; i++) {
        b[i / block_size] += a[i];
    }
  }

  void update(int pos, int val) {
    b[pos / block_size] += (long long)val - a[pos]; 
    a[pos] = val;                                   
  }

  long long query(int l, int r) {
    long long sum = 0; 
    int b_l = l / block_size, b_r = r / block_size;

    if (b_l == b_r) {
      for (int i = l; i <= r; i++) sum += a[i]; 
    } 
    else {
      for (int i = l; i <= block_size * (b_l + 1) - 1; i++) sum += a[i]; 
      for (int i = block_size * b_r; i <= r; i++) sum += a[i];           
      for (int i = b_l + 1; i <= b_r - 1; i++) sum += b[i];              
    }
    return sum;
  }
};

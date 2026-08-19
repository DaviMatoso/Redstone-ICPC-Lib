struct sqrt_decomp{
  int n, len;  vi a, b;
  sqrt_decomp(){}
  sqrt_decomp(vi& arr): n(arr.size()), len(sqrt(n) + 1), a(arr), b(len){
    for(int i = 0; i < n; i++) b[i / len] += a[i];
  }

  void update(int pos, int val){
    b[pos / len] += val - a[pos];  // Block update
    a[pos] = val;                  // Point update
  }

  ll query(int l, int r) {
    ll sum = 0; 
    int b_l = l / len, b_r = r / len;

    if (b_l == b_r) {
      for (int i = l; i <= r; i++) sum += a[i]; 
    } 
    else {
      for (int i = l; i <= len * (b_l + 1) - 1; i++) sum += a[i]; 
      for (int i = len * b_r; i <= r; i++) sum += a[i];           
      for (int i = b_l + 1; i <= b_r - 1; i++) sum += b[i];              
    }
    return sum;
  }
};

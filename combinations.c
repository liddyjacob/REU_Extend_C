
int powersize(int size){ return 1 << size; } 

void powerset(int n,unsigned set[][n]){
  unsigned bit, i, j;
  for(i = 0; i < powersize(n); ++i){
    for (bit = (1 << (n - 1)), j = 0; j < n; ++j, bit>>=1){
      set[i][j] = (bit&i) ? 1 : 0;
    }
  }
}

#include "../gtools.h"
//#include <vector>
// 1 is red
// 0 is blue

int pn_recursive(n, gmat, numv, vi, vj, color, path)
int n, gmat[][SIZE], numv , vi, vj, color, path[SIZE];
{
  path[vi] = 1;
  unsigned i;

  if (n == 1) {return gmat[vi][vj] == color;}

  for (i = 1; i < numv; ++i){
    if (path[i]){ continue;}
    if (!(gmat[vi][i] == color )) {continue;}
    if (pn_recursive(n - 1, gmat, numv, i, vj, color, path)){

      for (int k = 0; k < numv; ++k){
        if (path[k]){ printf("->%d", path[k]);}
      }
      return 1;
      
    }
  }

  path[vi] = 0;

  return 0;
        
}


int find_pn(n, gmat, numv, vi, vj, color)
int n, gmat[][SIZE], numv , vi, vj,color;
{
  unsigned i;
  int path[SIZE];
  for (i = 0; i < numv; ++i){
    path[i] = 0;
  }

  path[vi] = 1;
  path[vj] = 1;
  path[0]  = 1;

  return pn_recursive(n, gmat, numv, vi, vj, color, path);
}

int cn_in_mat(n, gmat, numv , color)
int n, gmat[][SIZE], numv , color;
{
  unsigned i, j;
  for (i = 1; i < numv; ++i){
    if (gmat[0][i] == color){
      for (j = i + 1; j < numv; ++j){
        if (gmat[0][j] == color){ 
          if (find_pn(n - 2, gmat, numv, i, j, color)) { return 1; } 
        }
      }
    }
  }
  
  return 0;
}

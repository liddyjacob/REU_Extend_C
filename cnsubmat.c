#include "../gtools.h"
#include "omp.h"
//#include <vector>
// 1 is red
// 0 is blue

int pn_recursive(n, mat, numv, vi, vj, color, path)
int n, mat[][SIZE], numv , vi, vj, color, path[SIZE];
{
  unsigned i;

  if (n == 1) {return mat[vi][vj] == color;}

  for (i = 1; i < numv; ++i){
    if (path[i]){ continue;}
    if (!(mat[vi][i] == color )) {continue;}
    path[i] = 1;
    if (pn_recursive(n - 1, mat, numv, i, vj, color, path)){ 
      return 1;
    }
    path[i] = 0;
  }

  return 0;
        
}


int find_pn(n, mat, numv, vi, vj, color)
int n, mat[][SIZE], numv , vi, vj,color;
{
  unsigned i;
  int path[SIZE];
  for (i = 0; i < numv; ++i){
    path[i] = 0;
  }

  path[vi] = 1;
  path[vj] = 1;
  path[0]  = 1;

  return pn_recursive(n, mat, numv, vi, vj, color, path);
}

int cn_in_mat(n, mat, numv , color)
int n, mat[][SIZE], numv , color;
{ 
  unsigned i, j; 
  for (i = 1; i < numv; ++i){
    if (mat[0][i] == color){
      for (j = i + 1; j < numv; ++j){
        if (mat[0][j] == color){ 
          if (find_pn(n - 2, mat, numv, i, j, color)) { 
            return 1;
          }
        } 
      }
    }
  }

  return 0;
}

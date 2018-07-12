/* compile with
gcc -O4 -o findkn ../gtools.o findkn.c  
*/
#define SIZE 40

#include "omp.h"
#include "../gtools.h"
#include "combinations.c"
//#include "knsubmat.c"
#include "cnsubmat.c"

/*******************************************************************************/
int no_spots(int gmat[][SIZE], unsigned spots[], int spotsize, int color){
  unsigned i, j;
  for (i = 0; i < spotsize - 1; ++i){
    for (j = i + 1; j < spotsize; ++j){
      int s1 = spots[i];
      int s2 = spots[j];
      //if (s1 == s2) {fprintf(stderr, "Repeat!\n");}

      if (gmat[s1][s2] != color) {return 0;}
    }
  }
  return 1;
}


int kn_in_mat(n, gmat, numv , color, knlab, lab)
int n, gmat[][SIZE], numv , color, knlab[], lab;
{
  if (n == 3) return cn_in_mat(n, gmat, numv, color);
  if (n >= 7) return 1;
  if (n == 4){
    // NEED TO CHECK FOR 4 CONNECTIONS, NOT 5
    if (numv < 4) {return 0;}
    unsigned h, i, j, k;
    for (h = 0; h < numv - 3; ++h){
      if (knlab[h] != 0) {continue;} 
      for (i = h + 1; i < numv - 2; ++i){
        if ((gmat[h][i] != color) || (knlab[i] != 0)) {continue;}
          for (j = i + 1; j < numv - 1; ++j){
            if ((gmat[h][j] != color) || (knlab[j] != 0)) {continue;}
            for (k = j + 1; k < numv; ++k){
              if  ((gmat[h][k] != color) || (knlab[k] != 0)) {continue;}
             // Check all possible combinations of i, j, k, l, m:
            unsigned potent_k3[3] = {i, j, k};
            if (no_spots(gmat, potent_k3, 3, color)) {
              knlab[i] = lab;
              knlab[j] = lab;
              knlab[k] = lab;
              knlab[h] = lab;
              return 1;
            } 
          }
        }
      }
    }
  }
  if (n == 5){
    // NEED TO CHECK FOR 4 CONNECTIONS, NOT 5
    if (numv < 5) {return 0;}
    unsigned h, i, j, k, l;
    for (h = 0; h < numv - 4; ++h){
      if (knlab[h] != 0) {continue;} 
      for (i = h + 1; i < numv - 3; ++i){
        if ((gmat[h][i] != color) || (knlab[i] != 0)) {continue;}
          for (j = i + 1; j < numv - 2; ++j){
            if ((gmat[h][j] != color) || (knlab[j] != 0)) {continue;}
            for (k = j + 1; k < numv - 1; ++k){
              if  ((gmat[h][k] != color) || (knlab[k] != 0)) {continue;}
              for (l = k + 1; l < numv; ++l){
                if  ((gmat[h][l] != color) || (knlab[l] != 0)) {continue;}
            
              // Check all possible combinations of i, j, k, l, m:
              unsigned potent_k3[4] = {i, j, k, l};
              if (no_spots(gmat, potent_k3, 4, color)) {
                  knlab[i] = lab;
                  knlab[j] = lab;
                  knlab[k] = lab;
                  knlab[h] = lab;
                  knlab[l] = lab;
                  return 1;
                }
              }
          }
        }
      }
    }
  }

  if (n == 6){
    // NEED TO CHECK FOR 4 CONNECTIONS, NOT 5
    if (numv < 6) {return 0;}
    unsigned h, i, j, k, l, m;
    for (h = 0; h < numv - 5; ++h){
      if (knlab[h] != 0) {continue;} 
      for (i = h + 1; i < numv - 4; ++i){
        if ((gmat[h][i] != color) || (knlab[i] != 0)) {continue;}
          for (j = i + 1; j < numv - 3; ++j){
            if ((gmat[h][j] != color) || (knlab[j] != 0)) {continue;}
            for (k = j + 1; k < numv - 2; ++k){
              if  ((gmat[h][k] != color) || (knlab[k] != 0)) {continue;}
              for (l = k + 1; l < numv - 1; ++l){
                if  ((gmat[h][l] != color) || (knlab[l] != 0)) {continue;}
                 for (m = l + 1; m < numv ; ++m){
                  if  ((gmat[h][m] != color) || (knlab[m] != 0)) {continue;}
              // Check all possible combinations of i, j, k, l, m:
              unsigned potent_k5[5] = {i, j, k, l, m};
              if (no_spots(gmat, potent_k5, 5, color)) {
                  knlab[i] = lab;
                  knlab[j] = lab;
                  knlab[k] = lab;
                  knlab[h] = lab;
                  knlab[l] = lab;
                  knlab[m] = lab;
                  return 1;
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}

void swaprows(G, i, j, n)
int G[][SIZE], i, j, n;
{
  int v;
  int temp;
  for(v = 0; v < n; ++v){
    if ((i == v) || (j == v)) continue;
    
    temp = G[v][i];
    G[v][i] = G[v][j];
    G[v][j] = temp;
    G[i][v] = G[v][i];
    G[j][v] = G[v][j];
  }
}

void printarr(outfile, G, n)
FILE *outfile;
int G[], n;
{
    int i,j, ecount;
    ecount = 0;
    fprintf(outfile, "  ");
    for (i = 0; i < n; ++i){

      fprintf(outfile, "%d ", G[i]); 
      //if (i < 10) fprintf(outfile, " ", i);

    }
    fprintf(outfile, "\n");
}


void printmat(outfile, G, n)
FILE *outfile;
int G[][SIZE], n;
{
    int i,j, ecount;
    ecount = 0;
    fprintf(outfile, "  ");
    for (i = 0; i < n; ++i){

      //fprintf(outfile, "%d ", i); 
      //if (i < 10) fprintf(outfile, " ", i);

    }
    fprintf(outfile, "\n");

    for (i = 0; i < n; ++i){

      //fprintf(outfile, "%d ", i);
      //if (i < 10) fprintf(outfile, " ", i);
      
      for (j = 0; j < n; ++j){
        fprintf(outfile, "%d ", G[i][j]);
        if (G[i][j] == 1) {ecount++;}
        
      }
      
      fprintf(outfile, "\n");
    }
    //fprintf(outfile, "\n^ecount: %d\n", ecount);

}


int outdegree(v, G, n, low, high)
int v, G[][SIZE], n, low, high;
{

  int i;
  int deg = 0;
  for (i = 0; i < low; ++i){
    if (G[v][i] == 1){ ++deg; }
  }

  for (i = high; i < n; ++i){
    if (G[v][i] == 1){ ++deg; }
  }

  return deg;
}


void tikzprint(outfile, G, n)
FILE* outfile;
int G[][SIZE], n;
{

  int i, j, low, high, index, i2, j2;
  int groups[4][SIZE];
  char gchars[4][4][4] = {
    {"AA", "AB", "AC", "AD"},
    {"BA", "BB", "BC", "BD"},
    {"CA", "CB", "CC", "CD"},
    {"DA", "DB", "DC", "DD"}
  };
  int gpnum[4];


  groups[0][0] = -1;
  groups[1][1] = -1;
  groups[2][2] = -1;
  groups[3][3] = -1;


  for (i = 0; i < 4; ++i){
    low = i * n / 4;
    high = ((i + 1) * n) / 4;
    index = 0;
    for (j = low; j < high ; ++j){
      //fprintf(outfile, "%d -> %d\n", low, high);
      //fprintf(outfile, "\tOutdegree of %d: %d\n", j, outdegree(j, G, n, low, high));
      //fprintf(outfile, "\tGroups[%d][%d] = %d\n", i, i, groups[i][i]);
      if ((groups[i][i] == -1) && (outdegree(j, G, n, low, high) == 0)){
        groups[i][i] = j;
      } else {
        // Does not account for more than 4 vertices.
        // Should check outdegree when there are more than 5 vertices.
        if (index == i) {++index;} // Bug is here
        groups[i][index] = j;
        ++index;
      }
      //fprintf(outfile, "\tgroups[%d][%d] = %d\n", i, index - 1, groups[i][index - 1]);
    }
  }

 for (i = 0; i < 4; ++i){
    low = i * n / 4;
    high = ((i + 1) * n) / 4;
 
    for (j = 0; j < 4; ++j){
      for (i2 = 0; i2 < 4; ++i2){
        if (i2 == i) {continue;}
        for (j2 = 0; j2 < 4; ++j2){
          int v1 = groups[i][j];
          int v2 = groups[i2][j2];
          //char c1 = gchars[i][j];
          //char c2 = gchars[i2][j2];
          if (G[v1][v2] == 1) {
            int temp = groups[i][j]; 
            groups[i][j] = groups[i][i2];
            groups[i][i2] = temp;
            temp = groups[i2][j2];
            groups[i2][j2] = groups[i2][i];
            groups[i2][i] = temp;
          }  
        }
      }
    }
  }

  fprintf(outfile, "\\begin{scope}[every node/.style={circle,draw, fill, inner sep = 0, minimum size=3pt}]\n");

  for (i = 0; i < 4; ++i){
    low = i * n / 4;
    high = ((i + 1) * n) / 4;
    for (j = 0; j < 4; ++j){
      int v1 = groups[i][j];
      if (outdegree(v1, G, n, low, high) >= 2){
        int temp = groups[i][j]; 
        groups[i][j] = groups[i][i];
        groups[i][i] = temp;
        
        char cord[4];
          strcpy(cord, gchars[i][i]);
        fprintf(outfile, "    \\node (%s) at (cord%s) {}; \n", cord, cord);
      
      } else if (outdegree(v1, G, n, low, high) == 0){
        groups[i][j] = -1;
      } else {
        char cord[4];
          strcpy(cord, gchars[i][j]);
        fprintf(outfile, "    \\node (%s) at (cord%s) {}; \n", cord, cord);
      }

    }
  }

  fprintf(outfile, "\\end{scope}\n");


  //printmat(outfile, groups, 4);
 
 
  for ( i = 0; i < 4; ++i){
    for (j = 0; j < 4; ++j){
      for (i2 = i + 1; i2 < 4; ++i2){
        for (j2 = 0; j2 < 4; ++j2){
          int v1 = groups[i][j];
          int v2 = groups[i2][j2];
          if (v1 == -1 || v2 == -1) continue;
          char c1[4];
            strcpy(c1, gchars[i][j]);
          char c2[4];
            strcpy(c2, gchars[i2][j2]); 

          if (G[v1][v2] == 1) {fprintf(outfile, "\\draw (%s) -- (%s);\n", c1 , c2);}
        }
      }
    }
  }
  
  
  
  //printarr(outfile, group1, 4);
  //printarr(outfile, group2, 4);
  //printarr(outfile, group3, 4);


  //for (i = 0; i < 4; ++i){



  //} 
}

void writemat(outfile,G,n)
FILE *outfile;
int G[][SIZE], n;
{
   graph h[MAXN*MAXM];
   int i, j, m;

   m = 1;
   EMPTYSET(h,m*(size_t)n);
   for (i = 0; i < n; ++i)
   for (j = 0; j < n; ++j)
   if (G[i][j]) {
    	ADDELEMENT(GRAPHROW(h,i,m),j);
		ADDELEMENT(GRAPHROW(h,i,m),j);
	   	}
   writeg6(outfile,h,m,n);
}

void gtomat(g, n, G)
graph *g;
int n, G[SIZE][SIZE];
{
  unsigned i, j, k, bit, row;

  for (i=0;i<n;i++) {
    row = g[i]>>(WORDSIZE-n);
    for (bit=(1<<(n-1)),j=0;j<n;j++,bit>>=1) {
      /* Save graph in matrix form */
      G[i][j] = (bit&row) ? 1 : 0; 
    }
	}
}
/*******************************************************************************/



int
main(int argc, char *argv[])
{

  if (argc != 2){ 
    fprintf(stderr, "Usage: findkn <n>\n");
    exit(1);
  }

  char bluestr[8];
    strcpy(bluestr, argv[1]);

  int bluen;
    char bnc[7];
    memcpy(bnc, &bluestr[0], 7);
    bluen = atoi(bnc);

  fprintf(stderr, "Blue info: Num = {%d}\n", bluen);


  graph *g;
  int i;
  unsigned m, n, j, k, bit, row;
  int gmat[SIZE][SIZE];
  int knlab[SIZE], list[SIZE];

  int codetype;
  FILE *infile, *outfile;

  infile = opengraphfile(NULL,&codetype,0,1);
  outfile = stdout;// fopen("out.g6","w");

  if (infile == NULL)
  {
      fprintf(stderr,"Error: Can't open input file\n");
      exit(1);
  }

  while ((g = readg(infile,NULL,0,&m,&n)) != NULL)
  {
    
    gtomat(g, n, gmat);
    
    /* Extend g by one vertex */
    for (i=0; i < n; ++i){
      knlab[i] = 0;
    }
    for (i=1; kn_in_mat(bluen, gmat, n, 1, knlab, i); ++i);
    //for (i=0; i < n ;++i){
    //  printf("%d ", knlab[i]);
    //}
    //printf("\n");

    //printmat(outfile, gmat, n);
    //Rearrange Matrix:
    for (i = 0; i < n - 1; ++i){
      for (j = i + 1; j < n; ++j){
        int minj = i;
        if (knlab[minj] > knlab[j]){
          minj = j;
        }
        if (i != minj){
          int temp = knlab[i];
          knlab[i] = knlab[minj];
          knlab[minj] = temp;
          swaprows(gmat, i, minj, n);
        }
      }
    }
    //for (i=0; i < n ;++i){
    //  printf("%d ", knlab[i]);
    //}
    //printf("\n");


    printf("\n\n");
    tikzprint(outfile, gmat, n);
    printf("\n\n");
    //printmat(outfile, gmat, n);
    //writemat(outfile, gmat, n);
    
    
    
    free(g);   /* After you finished with the graph */
  
    /* Write g */
		//writemat(outfile,hmat,n+1);
  }
  fclose(outfile);
}

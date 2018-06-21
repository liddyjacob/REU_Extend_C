/* compile with
gcc -O4 -o addvg ../gtools.o addvg.c  
*/
#define SIZE 40

#include "../gtools.h"
#include "combinations.c"
//#include "knsubmat.c"
#include "cnsubmat.c"

/*******************************************************************************/
int kn_in_mat(n, gmat, numv , color)
int n, gmat[][SIZE], numv , color;
{
  return 1;
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

  if (argc != 3){ 
    fprintf(stderr, "Usage: addvg <RED SUBGRAPH> <BLUE SUBGRAPH>\n");
    exit(1);
  }

  char redstr[8];
    strcpy(redstr, argv[1]);
  char bluestr[8];
    strcpy(bluestr, argv[2]);

  char redtype = redstr[0];
  char bluetype = bluestr[0];

  int redn;
    char rnc[7];
    memcpy(rnc, &redstr[1], 7);
    redn = atoi(rnc);

  int bluen;
    char bnc[7];
    memcpy(bnc, &bluestr[1], 7);
    bluen = atoi(bnc);

  graph *g;
  unsigned m, n, i, j, k, bit, row;
  int gmat[SIZE][SIZE];
  int hmat[SIZE][SIZE], list[SIZE];

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
    for (i=0; i < n ;i++){
      for (j=0; j < n ;j++){ 
        hmat[i+1][j+1] = gmat[i][j];
      }
    }

    for (i = 0; i < powersize(n); ++i){
      for (bit = (1<<(n-1)), j = 0; j < n; bit>>=1, ++j){
        hmat[0][j + 1] = (bit&i) ? 1 : 0;
        hmat[j + 1][0] = (bit&i) ? 1 : 0;
      } 
      /* Now deal with this hmat */

      if (redtype == 'K'){ 
        if (kn_in_mat(redn, hmat, n + 1, 1)) continue;
      }
      if (redtype == 'C'){ 
        if (cn_in_mat(redn, hmat, n + 1, 1)) continue; 
      }

      if (bluetype == 'K'){ 
        if (kn_in_mat(bluen, hmat, n + 1, 0)) continue;
      }
      if (bluetype == 'C'){ 
        if (cn_in_mat(bluen, hmat, n + 1, 0)) continue; 
      }
 
      writemat(outfile, hmat, n+1);
    }

    /* Write g */
		//writemat(outfile,hmat,n+1);

    free(g);   /* After you finished with the graph */
  }
  fclose(outfile);
}

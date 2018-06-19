/* compile with
gcc -O4 -o delvg ../gtools.o delvg.c  
*/
#define SIZE 40

#include "../gtools.h"
#include "combinations.h"


/*******************************************************************************/
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
  unsigned i, j, bit, row;

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

    /* Consider all possibilities of edges: */




    /* Write g */
		writemat(outfile,hmat,n+1);

    free(g);   /* After you finished with the graph */
  }
  fclose(outfile);
}

/* compile with
gcc -O4 -o starg ../gtools.o scritg.c  
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


int kn_in_mat(n, gmat, numv , color)
int n, gmat[][SIZE], numv , color;
{
  if (n == 3) return cn_in_mat(n, gmat, numv, color); 
  if (n > 7) {return 0;}
  if (n == 6){
    // NEED TO CHECK FOR 4 CONNECTIONS, NOT 5
    if (numv < 6) {return 0;}
    unsigned i, j, k, l, m;
    for (i = 1; i < numv - 4; ++i){
      if (gmat[0][i] != color) {continue;}
      for (j = i + 1; j < numv - 3; ++j){
        if (gmat[0][j] != color) {continue;}
        for (k = j + 1; k < numv - 2; ++k){
          if (gmat[0][k] != color) {continue;}
          for (l = k + 1; l < numv - 1; ++l){
            if (gmat[0][l] != color) {continue;}
              for (m = l + 1; m < numv ; ++m){
                if (gmat[0][m] != color) {continue;}
                // Check all possible combinations of i, j, k, l, m:
                unsigned potent_k5[5] = {i, j, k, l, m};
                if (no_spots(gmat, potent_k5, 5, color)) {return 1;} 
              } 
          }
        }
      }
    }
  }
 
  if (n == 5){
    // NEED TO CHECK FOR 4 CONNECTIONS, NOT 5
    if (numv < 5) {return 0;}
    unsigned i, j, k, l, m;
    for (i = 1; i < numv - 3; ++i){
      if (gmat[0][i] != color) {continue;}
      for (j = i + 1; j < numv - 2; ++j){
        if (gmat[0][j] != color) {continue;}
        for (k = j + 1; k < numv - 1; ++k){
          if (gmat[0][k] != color) {continue;}
          for (l = k + 1; l < numv; ++l){
            if (gmat[0][l] != color) {continue;}
              // Check all possible combinations of i, j, k, l, m:
            unsigned potent_k4[4] = {i, j, k, l};
            if (no_spots(gmat, potent_k4, 4, color)) {return 1;} 
            
          }
        }
      }
    }
  }
  return 0;
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

  fprintf(stderr, "Red info:  Type = {%c}; Num = {%d}\n", redtype, redn);
  fprintf(stderr, "Blue info: Type = {%c}; Num = {%d}\n", bluetype, bluen);


  graph *g;
  unsigned starcount, m, n, i, j, k, bit, row;
  int critnum = 0;
  int gmat[SIZE][SIZE];
  int chmat[SIZE][SIZE], hmat[SIZE][SIZE], list[SIZE];

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
    printf("Current graph: \n");
    writemat(outfile, gmat, n);
    printf("\n");

    /* Extend g by one vertex */
    for (i=0; i < n ;i++){
      for (j=0; j < n ;j++){ 
        hmat[i+1][j+1] = gmat[i][j];
        chmat[i+1][j+1] = gmat[i][j];
      }
    }

    //#pragma omp parallel for

    for (i = 0; i < powersize(n); ++i){
      for (bit = (1<<(n-1)), j = 0; j < n; bit>>=1, ++j){
        hmat[0][j + 1] = (bit&i) ? 1 : 0;
        hmat[j + 1][0] = (bit&i) ? 1 : 0;
      } 
      /* Now deal with this hmat */

      for (k = 0; k < powersize(n); ++k){
        for (bit = (1<<(n-1)), j = 0; j < n; bit>>=1, ++j){
          chmat[0][j + 1] = (bit&k) ? hmat[0][j+1] : 2;
          chmat[j + 1][0] = (bit&k) ? hmat[j+1][0] : 2;
        }
        
        starcount = n;
        for (j = 1; j < n + 1; ++j){
          if (chmat[0][j] == 2) {--starcount;}
        }

        if (starcount <= critnum) {continue;}
      
        if (redtype == 'K'){ 
          if (kn_in_mat(redn, chmat, n + 1, 1)) continue;
        }
        if (redtype == 'C'){ 
          if (cn_in_mat(redn, chmat, n + 1, 1)) continue; 
        }

        
        if (bluetype == 'K'){ 
          if (kn_in_mat(bluen, chmat, n + 1, 0)) continue;
        }
        if (bluetype == 'C'){ 
          if (cn_in_mat(bluen, chmat, n + 1, 0)) continue; 
        }


        printf("Star number: %d/%d\n", starcount, n);
        critnum = starcount;
        writemat(outfile, hmat, n + 1);
        for (j = 1; j < n + 1; ++j){
          if (chmat[0][j] == 2){printf("No edge between 0 and %d\n", j);}
        } 
        

      }
     //writemat(outfile, hmat, n+1);
    }

    /* Write g */
		//writemat(outfile,hmat,n+1);

    free(g);   /* After you finished with the graph */
  }
  fclose(outfile);
}

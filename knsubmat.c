#include "../nauty26r11/gtools.h"

int kn_in_mat(n, gmat, numv, color)
int n, gmat[][SIZE], numv, color;
{
//look at neighbors of vertex 0
// see if neighbors form k_4
// make an array to put neighbors in
//


	int i;
	int j;

    int neighbors[numv-1];
     for (i =0; i<numv-1; i++){
       neighbors[i] = 0;
     }

// now check for neighbors of vertex 0
// check row 0 of matrix and see which columns are nonzero
// start at vertex 1
// count index of neighbors
int count = 0;
for (i = 1; i<=numv; i++){
    if (gmat[0][i] != 0){
          neighbors[count] = i;
          count++;
    }
}
//printf("filled in %d elements to neighbor array \n", count);

// now check for complete graph among the vertices in neighbors array
// instead of iterating over entire size of neighborhood, will take n-subsets and check each
//

unsigned int N = 1<< n; 
int evercomplete = 0; //check if there is at least one complete graph
int complete = 1; //check if a specific subgraph is complete
int subset[n];
for (i = 0; i<n; i++){
	subset[i]=0;
}
int ncount = 0;
int x;
for (x=0; x<N; x++){
	if (nbits(x) == n){
// make subset
//
		for (i = 0; i<count; i++){
			unsigned bit = 1 << i;
			if(x & bit){
				subset[ncount] = neighbors[i];
				ncount++;
			}
		}

// now check that everything in subset is complete

		for (i = 0; i<n; i++){
			for (j = 0; j<n; j++){
				if ((i !=j) && (gmat[subset[i]][subset[j]] == 0)) { //if any pair doesn't have an edge
				complete = 0;
				}
			}
		}
	}
	if (complete){
		evercomplete = 1;
	}
}

printf("Is there a complete graph? %d \n", evercomplete);
return evercomplete;
}

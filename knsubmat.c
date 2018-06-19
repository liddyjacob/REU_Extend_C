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
int complete = 1;
for (i = 0; i<count; i++){
	for (j = 0; j<count; j++){
		if ((i !=j) && (gmat[neighbors[i]][neighbors[j]] == 0)) { //if any pair doesn't have an edge
			complete = 0;
		}
	}
}

printf("Is there a complete graph? %d \n", complete);
return complete;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[]) {
  int i,j,m,n,l;
  int thread_count;				/*variable which stores number of threads*/
  double **A, *b, *x, *c;
  double start, end;

  if (argc != 4) {
    fprintf(stderr, "Usage: %s <thread_count> <n> <l>\n", argv[0]);
    exit(0);
  }
  thread_count = atoi(argv[1]);
  n = atoi(argv[2]);							// size of array
  l = atoi(argv[3]);							// number of iterations

  A = (double **)malloc(n*sizeof(double*)); 				// coefficients
  for (i=0; i<n; i++)
    A[i] = (double *)malloc(n*sizeof(double));
  b = (double *)malloc(n*sizeof(double)); 				// righ hand size constants
  x = (double *)malloc(n*sizeof(double));
  c = (double *)malloc(n*sizeof(double)); 				// temp?

  start = omp_get_wtime();                                              // time at the start of parallel routines
  
    /* init A, b, x */

//#pragma omp parallel num_threads(thread_count) private(i)
  for (i=0; i<n; i++)
    x[i] = 0.5000;
  /* ??? */
 start = omp_get_wtime();
#pragma omp parallel for num_threads(thread_count) private(i,j) 	/* parallelizes the following outer for loop according to number of threads */
	  for (i=0; i<n; i++) {						/* private(i,j) clause ensures that variables i and j would be local to the outer for loop */
		  b[i] = 2.0*n;						/* So, even though i and j are global variables by definiton, their behaviour inside the */
		  for (j=0; j<n; j++) A[i][j] = 1.0;								                     /*for loops can be localised */
		  A[i][i] = n + 1.0;
	  }

  //memset(x, 0, n*sizeof(double));
  /* done init */

  m=1;

 line:
#pragma omp parallel for num_threads(thread_count) private(i,j)
	  for(i=0;i<n;i++) {
		  c[i]=b[i];
		  for(j=0;j<n;j++) { 
			  if(i!=j) {
				  c[i]=c[i]-(A[i][j]*x[j]);
			  }
		  }
	  }
end = omp_get_wtime();

//#pragma omp parallel num_threads(thread_count) private(i,j)
  for(i=0;i<n;i++) {
    x[i]=c[i]/A[i][i];
  }
  m++;

//end = omp_get_wtime();

  if(m<=l) {
    goto line;
  }

  else {
	  printf("work took %f seconds\n",end-start);
	  printf("\nThe Solution is : \n");
    for(i=0;i<n;i++) {
      printf("\nx(%d) = %f\n",i,x[i]);
    }
  }

  free(A); free(b); free(x); free(c);
}

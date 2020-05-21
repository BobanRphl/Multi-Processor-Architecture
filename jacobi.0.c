#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
  int i,j,m,n,l;
  int thread_count;
  double **A, *b, *x, *c;

  if (argc != 4) {
    fprintf(stderr, "Usage: %s <thread_count> <n> <l>\n", argv[0]);
    exit(0);
  }
  thread_count = atoi(argv[1]);
  n = atoi(argv[2]);
  l = atoi(argv[3]);

  A = (double **)malloc(n*sizeof(double*)); /* coefficients */
  for (i=0; i<n; i++)
    A[i] = (double *)malloc(n*sizeof(double));
  b = (double *)malloc(n*sizeof(double)); /* righ hand size constants */
  x = (double *)malloc(n*sizeof(double));
  c = (double *)malloc(n*sizeof(double)); /* temp? */

  /* init A, b, x */
  for (i=0; i<n; i++)
    x[i] = 1.0; /* ??? */

  srandom(1);

  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      if (i != j)
	A[i][j] = random()/((double) RAND_MAX);
      else
	A[i][j] = n/10.0;
    }
  }

  for (i=0; i < n; i++) {
    b[i] = 0;
    for (j=0; j<n; j++) 
      b[i] += A[i][j]*x[j];
  }
  
  memset(x, 0, n*sizeof(double));
  /* done init */

  m=1;
 line:
  for(i=0;i<n;i++) {
    c[i]=b[i];
    for(j=0;j<n;j++) {
      if(i!=j) {
	c[i]=c[i]-A[i][j]*x[j];
      }
    }
  }
  for(i=0;i<n;i++) {
    x[i]=c[i]/A[i][i];
  }
  m++;
  if(m<=l) {
    goto line;
  }
  else {
    printf("\nThe Solution is : \n");
    for(i=0;i<n;i++) {
      printf("\nx(%d) = %f\n",i,x[i]);
    }
  }

  free(A); free(b); free(x); free(c);
}

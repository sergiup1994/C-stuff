#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <sys/time.h>
#include "string.h"
#include "limits.h"


int main(){
  //variable initialization
  int block_size =1;
  int n = 2;
  int i, j, k, block_k, block_j;
  double *mat_A, *mat_B, *mat_C;

  //dynamic array
  mat_A= (double*)malloc(n*n*sizeof(double));
  mat_B= (double*)malloc(n*n*sizeof(double));
  mat_C= (double*)malloc(n*n*sizeof(double));

  //matrix initalization with variables
  for (i =0; i<n*n; i++){
       mat_A[i] = 4.;
       mat_B[i] = 4.;
       mat_C[i] = 0.0;

  }


  double x = 0.0;

  //bechmark
  struct timeval tv1, tv2;
  struct timezone tz;
  gettimeofday(&tv1, &tz);
  
  //kij blocked algorithm
   for (block_k = 0; block_k < n; block_k += block_size) {
    for (i = 0; i < n; i ++) {
        for (block_j = 0; block_j < n; block_j += block_size) {

            for (k = block_k; k < ((block_k+block_size)>n?n: (block_k+block_size)); k++) {
                x = mat_A[i*n+k];
                for (j =  block_j; j < (( block_j+block_size)>n?n: ( block_j+block_size)); j++) {
                   mat_C[i*n +j] += x * mat_B[k*n + j];
                }

            }
        }
     }
   }
   gettimeofday(&tv2, &tz);
   double elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
   /*
   for(i=0; i<n; i++){
      for(j=0; j<n; j++){
          printf("matrix result %f\n ", mat_C[i*n +j]);

      }
   }
   */

   printf("execution time: %lf", elapsed);





   return  0;

}


   

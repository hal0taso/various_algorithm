#include <stdio.h>
#include <stdlib.h>

#define N 0x100


void mergesort(int left, int right, int *A)
{
  int k, n, n1, n2, mid;
  int A1[N], A2[N];

  /* n is size of A */
  n = right - left + 1;

  if (n > 1){
    mid = left + (n -1) / 2;
    
    mergesort(left, mid, A);
    mergesort(mid +1, right, A);
    
    n1 = mid - left + 1;
    for ( k = left; k <= mid; k++){
      A1[k-left] = A[k];
    }
    
    n2 = right - mid;
    for ( k = mid + 1; k <= right; k++){
      A2[k - mid -1] = A[k];
    }

    merge(A1, n1, A2, n2, left, A)
  }

  return;
  
}

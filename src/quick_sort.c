#include <stdio.h>
#include <stdlib.h>

void quick_sort(int a[], int left, int right);
void swap(int a[], int i, int j);
void show(int a[], int n);
void main(void);

void quick_sort(int a[], int left, int right){
  int i, j;
  int pivot;

  i = left;
  j = right;

  pivot = a[(left + right) / 2];

  while(1){
    while(a[i] < pivot){
      i ++;
    }
    while(a[j] > pivot){
      j --;
    }
    if (i >= j){
      break;
    }

    swap(a, i, j);
    i ++;
    j --;
  }
  show(a, sizeof(a)/sizeof(a[0]));

  if (left < i -1){
    quick_sort(a, left, i - 1);
  }
  if (j + 1 < right){
    quick_sort(a, j + 1, right);
  }
}


//void swap(int a[], int i, int j){
//  
//}

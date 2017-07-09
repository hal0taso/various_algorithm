#include <stdio.h>
#include <stdlib.h>

void quick_sort(int a[], int left, int right);
void swap(int a[], int i, int j);
void show_data(int a[], int n);
int main(int argc, char *argv[]);

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
  show_data(a, sizeof(a)/sizeof(int));

  if (left < i -1){
    quick_sort(a, left, i - 1);
  }
  if (j + 1 < right){
    quick_sort(a, j + 1, right);
  }
}


void swap(int a[], int i, int j){

  int tmp;

  tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

// show n data in array
void show_data(int a[], int n){
  
  for(int i = 0; i < n; i ++){
    printf("%d ", a[i]);
  }
  putchar('\n');
}

int main(int argc, char *argv[]){
  
  int a[argc-1];
  
  for (int i = 1; i < argc; i ++){
    a[i-1] = atoi(argv[i]);
  }

  /*
    in osx, argc returns number of argument incuding argv[0]
    printf("%d\n", argc);
  */
  
  printf("[*] Before sort:\n");
  show_data(a, argc-1);

  printf("[*] Sorting...\n");
  quick_sort(a, 0, argc-1);

  printf("[*] After sort:\n");
  show_data(a, argc-1);

  return 0;
}

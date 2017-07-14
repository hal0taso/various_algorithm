#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

*/
static void
array_random_number(int *array, unsigned int size, unsigned int digit)
{
  int i;

  srand((unsigned int) time(NULL));
  for (i = 0; i < size; i ++){
    array[i] = rand() % digit;
  }
}

/*

*/
static void
array_print(int *array, unsigned int size)
{
  int i = 0;

  for ( i = 0; i < size; i ++){
    printf("%d ", array[i]);
  }
  putchar('\n');

}


/*

*/
static void swap(int *i, int *j)
{
  int tmp;

  tmp = *i;
  *i = *j;
  *j = tmp;
}


/*

*/
static void down_heap(int *array, int left, int right)
{
  int child;
  int parent = left;
  int tmp = array[left];
  int cl, cr;


  /* loop while it has child */
  while(parent < (right + 1) / 2){
    cl = parent * 2 + 1; // left child
    cr = cl + 1;         // right child

    /* choose larger child */
    if((cr <= right) && (array[cr] > array[cl])){
      child = cr;
    }else{
      child = cl;
    }

    /* if child is larger than parent, exchange with parent */
    if ( tmp >= array[child]) break;
    array[parent] = array[child];
    parent = child;
  }
  array[parent] = tmp;
}


/*

 */
void heap_sort(int *array, unsigned int size)
{
  int i;

  /* create heap tree */
  for (i  = (size - 1) / 2; i >= 0; i --){
    down_heap(array, i, size -1);
  }

  /* sort */
  for (i = size - 1; i > 0; i --){
    /* exchange root and tail element */
    swap(&array[0], &array[i]);
    
    /* create heap tree without root*/
    down_heap(array, 0, i -1);
    printf("[heap] :");
    array_print(array, i);
  }
}

int main(void)
{
  int data[15];
  array_random_number(data, sizeof(data)/sizeof(int), 100);

  printf("[before]:");
  array_print(data, sizeof(data)/sizeof(int));

  heap_sort(data, sizeof(data)/sizeof(int));

  printf("[after] :");
  array_print(data, sizeof(data)/sizeof(int));

  return 0;
}

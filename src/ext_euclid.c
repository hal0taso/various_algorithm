#include <stdio.h>
#include <stdlib.h>

#define N 0x10000

long long int ext_euclid(long long int arg_a, long long int arg_b,
               long long int *ptr_x, long long int *ptr_y)
{
  /* array of each loop a, b*/
  long long int a[N];
  a[0] = arg_a;
  a[1] = arg_b;

  long long int x[N];
  x[0] = 1;
  x[1] = 0;
  
  long long int y[N];
  y[0] = 0;
  y[1] = 1;

  long long int q;
  
  long long int d;

  long long int i = 1;

  while(a[i] != 0){
    a[i+1] = a[i-1] % a[i];
    q = (a[i-1] - a[i+1])/a[i];
    if (0 <= a[i+1] && a[i+1] < a[i]){
      x[i+1] = x[i-1] - q * x[i];
      y[i+1] = y[i-1] - q * y[i];
      i ++;
    }
  }

  *ptr_x = x[i-1];
  *ptr_y = y[i-1];
  d = a[i-1];

  return d;
}


int main(int argc, char *argv[]){

  if (argc != 3){
    perror("usage: ./ext_euclid a b");
    exit(1);
  }

  long long int a = atoll(argv[1]);
  long long int b = atoll(argv[2]);

  long long int x;
  long long int y;

  long long int d;

  printf("%lld, %lld", a, b);
  
  d = ext_euclid(a, b, &x, &y);

  printf("gcd(a,b) = %lld\n", d);
  printf("%lld * %lld + %lld * %lld = %lld\n", a, b, x, y, d);

  return 0;

}

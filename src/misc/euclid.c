#include <stdio.h>
#include <stdlib.h>

#define N 0x10000

/*
  Euclid
 */
int euclid(long long int a, long long int b)
{
  long long int x[N];
  
  x[0] = a;
  x[1] = b;

  int i = 1;

  while (x[i] != 0){
    x[i+1] = x[i-1] % x[i];
    if(x[i+1] < x[i] || x[i+1] < -1*x[i]){
      i ++;
    }
  }

  return x[i-1];
}



int main(int argc, char *argv[])
{
  if (argc != 3){
    puts("Euclidean Algorithm:");
    puts("[*] return gdc(a,b) = d");
    perror("[!] usage: ./euclid a b");
    exit(1);
  }

  long long int a = atoi(argv[1]);
  long long int b = atoi(argv[2]);

  long long int d;
  
  d = euclid(a, b);
  printf("gcd(a, b) = %lld\n", d);
  
  return 0;
}

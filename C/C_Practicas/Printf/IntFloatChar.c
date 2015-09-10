#include <stdio.h>

int main(void){

  int a = -1;
  float b = 1;
  char c = 65;

  printf("Int a= %d\n", a);
  printf("Int unsigned a= %u\n", ~((unsigned int)a));
  printf("Float f b = %f\n", b);
  printf("Float e b = %e\n", b);
  printf("Char hhd c = %hhd\n", c);
  printf("Char c c = %c\n", c);
  return 0;
}

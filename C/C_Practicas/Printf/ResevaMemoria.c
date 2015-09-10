#include <stdio.h>

int main(void){

  int a = 0;
  int b = a + 1024;
  int c = -512;
  //Warnings 
  
  printf("Dirección de A = 0: %u \n", (unsigned int)&a);
  printf("Dirección de B = 1024: %u \n", (unsigned int)&b);
  printf("Dirección de B = -512: %u \n", (unsigned int)&c);
  return 0;  
}

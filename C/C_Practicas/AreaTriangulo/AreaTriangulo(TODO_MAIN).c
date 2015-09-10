#include <stdio.h>
#include <math.h>

int main(void){
  float a,b,c,d,e,f,area;
  printf("Favor de dar 3 puntos con el siguiente formato: (a,b) (c,d) (e,f)\n");
  scanf("(%f,%f) (%f,%f) (%f,%f)", &a,&b,&c,&d,&e,&f);
  if((f-b)*(c-a) == (d-b)*(e-a)){
    printf("No es un triangulo por lo tanto su área es de 0 u²\n");
  }else{
    area = (fabs ( ((a * (d-f)) + (-b * (c-e)) + ((c * f) - (e * d)) ) /2 ));
    printf("El área del tríangulo es %f u²\n",area);
  }
}

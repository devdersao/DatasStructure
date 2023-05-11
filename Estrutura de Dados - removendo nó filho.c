#include<stdio.h>
typedef struct no{
  int valor;
  struct no* esq;
  struct no* dir;
}no;



int main() {
  no y,d,r,e;
  no x;
  
  r.valor=10;
  e.valor=5;
  d.valor=15;
  x.valor=7;
  y.valor=9;
  
  r.esq = &e;
  r.dir = &d;
  
  e.dir = &x;
  
  d.esq = &y;
  
  //remover
  r.esq=&x;
  r.dir=&y;
  
	printf("%i",r.valor);//so pra tirar o warning
  
  
  return 0;
}

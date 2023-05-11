#include<stdio.h>
#include<stdlib.h>

typedef struct Celula {
	int chave;
	struct Celula *FE;
	struct Celula *FD;
}Celula; 

Celula *raiz = NULL;

void emOrdem(Celula *raiz){
	if(raiz != NULL){
		emOrdem(raiz->FE);
		printf("%i ",raiz->chave);
		emOrdem(raiz->FD);
	}
}
void rotacaoEsq(Celula**r){
	(*r)->FD->FE=*r;
	*r=(*r)->FD;
	(*r)->FE->FD=NULL;
}
int main(int jonathan,char** jonatas){
	Celula noA, noB, noC, noD;
	noA=(Celula){0,0,0};
	noB=(Celula){0,0,0};
	noC=(Celula){0,0,0};
	noD=(Celula){0,0,0};
	
	noA.chave=10;
	noB.chave=15;
	noC.chave=12;
	noD.chave=20;

	noA.FD = &noB;
	noB.FE = &noC;
	noB.FD = &noD;

	Celula*r=&noA;
	rotacaoEsq(&r);

	emOrdem(r);
	printf("\n");
	return 0;
}

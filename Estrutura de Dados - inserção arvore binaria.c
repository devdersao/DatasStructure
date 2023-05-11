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
void insere(Celula * r, int valor){
	Celula * novo= (Celula*) malloc(sizeof(Celula));
	
	novo->chave = valor;
	novo->FD = NULL;
	novo->FE = NULL;
	
	if(raiz == NULL){
		raiz = novo;
		return;
	}
	
	Celula *atual = r;
	Celula *ant = NULL;
	
	while(atual != NULL){
		ant = atual;
		if(valor == atual->chave){
			free(novo);
			return;
		}
		if(valor > atual->chave){
			atual = atual->FD;
		}else{
			atual = atual->FE;
		}
	}
	if(valor > ant->chave){
		ant->FD = novo;
	}else{
		ant->FE = novo;
	}
	return ;
}
int main(){
	int numero=0;
	while(numero >= 0){
		scanf("%i",&numero);
		if(numero >= 0){
		insere(raiz,numero);
		}
	}
	emOrdem(raiz);
	printf("\n");
	return 0;
}

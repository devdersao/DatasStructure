#include<stdio.h>
#include<stdlib.h>

typedef struct Celula {
	int chave;
	struct Celula *FE;
	struct Celula *FD;
}Celula; 

Celula *raiz = NULL;
int maisDireita(Celula* r){
	for(Celula* aux=r;aux!=NULL;aux=aux->FD){
		if(aux->FD==NULL)return aux->chave;
	}
	return 0;
}
int maisEsquerda(Celula* r){
	for(Celula* aux=r;aux!=NULL;aux=aux->FE){
		if(aux->FE==NULL)return aux->chave;
	}
	return 0;
}
void sucAnt(Celula *r,int valor){
	if(raiz == NULL){
		printf("o sucant morreu\n");
		return;
	}
	
	Celula *atual = r;
	
	while(atual != NULL){
		if(valor == atual->chave){
			printf("%i %i\n",maisDireita(atual->FE),maisEsquerda(atual->FD));
			return;
		}
		if(valor > atual->chave){
			atual = atual->FD;
		}else{
			atual = atual->FE;
		}
	}
	printf("o sucant morreu\n");
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
	scanf("%i",&numero);
	sucAnt(raiz,numero);
	return 0;
}

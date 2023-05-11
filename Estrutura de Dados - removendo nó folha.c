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
int ehFolha(Celula*r){
	return (r->FD==NULL)&&(r->FE==NULL);
}
void removeNo(Celula* r,int n){
	Celula *aux=r;
	Celula *ant=NULL;
	while(aux!=NULL){
		if(n>aux->chave){
			ant=aux;
			aux=aux->FD;
		}
		else if(n<aux->chave){
			ant=aux;
			aux=aux->FE;
		}
		else{
			if(ehFolha(aux)){
				if(ant->FE==aux){
					ant->FE=NULL;
				}else if(ant->FD==aux){
					ant->FD=NULL;
				}
			}else if(aux->FD&&aux->FE){
				//trapaca
				aux->FE->FD=aux->FD;
				ant->FD=aux->FE;
			}else if(aux->FD){
				if(ant->FE==aux){
					ant->FE=aux->FD;
				}else if(ant->FD==aux){
					ant->FD=aux->FD;
				}
			}else{
				if(ant->FE==aux){
					ant->FE=aux->FE;
				}else if(ant->FD==aux){
					ant->FD=aux->FE;
				}
			}
			free(aux);
			return;
		}
	}
	printf("NAO TEM O NO PORRA\n");
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
	removeNo(raiz,numero);
	emOrdem(raiz);
	printf("\n");
	return 0;
}

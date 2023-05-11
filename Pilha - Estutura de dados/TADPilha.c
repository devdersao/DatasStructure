#include "TADPilha.h"
void criaPilha( Pilha *P){
P->base = NULL;
P->topo = NULL;
}

void Inserir( Pilha *P, int n){
Celula * nova = (Celula*)malloc(sizeof(Celula));
nova -> valor = n;
    if(P->base==NULL){
        P->base = nova;
        P->topo = nova;
    }else{
        nova->proximo=P->topo;
        P->topo=nova;
    }
}
void Remover (Pilha *P){
    Celula *aux = P->topo;
    if(aux->proximo==NULL){
        P->topo=NULL;
        P->base=NULL;
        free(aux);
    }else{
        P->topo=aux->proximo;
        free(aux);
    }
}
int Tamanho( Pilha *P){
    Celula *aux=P->topo;
    int c=0;
    if(P->topo==NULL){
        return 0;

    }else{
        while(aux != NULL){
            c++;
           aux = aux->proximo;
        }
        return c;
    }

}

int Busca(Pilha *P, int n){
    Celula *aux;
    int cont;
    aux = P->base;
    while(aux != NULL && aux->valor != n){
       cont++;
       aux = aux->proximo;
    }
    return cont;
}
void Imprime( Pilha *P){
    Celula *aux;
    aux = P->topo;
    while(aux != NULL){
        printf("%i",aux);
    }
}

void Menu (Pilha *P){
    int opcao;
    int v;
    printf("\n-1 - Sair\n");
    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Buscar\n");
    printf("4 - Tamanho\n");
    printf("5 - Imprimir\n");
    switch(opcao){
        case -1:
                exit(1);
                break;            
        case 1:
            printf("Insira o valor!\n");
            scanf("%i",&v);
            Inserir(P,v);
            break;
        case 2:
            Remover(P);
            break;
        case 3:
            printf("Qual o Numero que você quer buscar ?");
            scanf("i%",&v);
            Busca(P,v);
            break;
        case 4:
            printf("%i",Tamanho(P));
            break;
        case 5:
            Imprime(P);
            break;
    }
}
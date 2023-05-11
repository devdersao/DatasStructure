#include <stdio.h>
#include <stdlib.h>
struct Celula {
    int valor;
    struct Celula* proximo;
};
typedef struct Celula Celula;

struct Pilha {
    Celula* topo;
    Celula* base;
};

typedef struct Pilha Pilha;

// FUNCAO PARA INICIALIZAR O TOPO
void criaPilha( Pilha *P); 
// FUNCAO PARA INSERIR UM ELEMENTO NA PILHA (INSERIR NO TOPO)
void Inserir( Pilha *P, int n);
// FUNCAO PARA REMOVER UM ELEMENTO DA PILHA ( REMOVE APENAS DO TOPO)
void Remover(Pilha *P);
// FUNCAO PARA MOSTRAR O TAMANHO DA PILHA
int Tamanho(Pilha *P);
// FUNCAO DE BUSCA PARA MOSTRAR A POSICAO DO ELEMENTO DESEJADO, NA PILHA, SE EXISTIR
int Busca(Pilha *P, int n);
//FUNCAO PARA IMPRIMIR TODOS OS ELEMENTOS DA PILHA
void Imprime(Pilha *P);
// FUNCAO PARA MOSTRAR NA TELA O MENU COM AS OPERACOES PARA/COM A PILHA
void Menu(Pilha *P);
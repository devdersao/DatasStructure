#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef struct SNo {
    char Nome[30];
    int idade;
    char tipo[2];
    char fatorRh[15];
    float qtdSangue;
    struct SNo *FE;
    struct SNo *FD;
}SNo;

SNo *Raiz = NULL;

void PrintNo(SNo*R){
	printf("%s,%d,%s,%s,%.2f\n",
	R->Nome,R->idade,R->tipo,R->fatorRh,R->qtdSangue);
}
// funcao para percorrer a arvore usando a estrategia em-Ordem
void emOrdem(SNo *R){
    if(R!=NULL){ //cp
        emOrdem(R->FE);
        printf("%s, %d, %s, %s, %.2f\n",R->Nome,R->idade,R->tipo,R->fatorRh,R->qtdSangue);
        emOrdem(R->FD);
    }
}

// funcao para inserir em uma arvore ABB
void insere(SNo *R, char *nome, int idade,char tipo[], char fatorRh[], float quantidade, SNo *Pai) {

    if(R == NULL) { // condicao de parada
        SNo *Novo = (SNo *)malloc(sizeof(SNo));
        strcpy(Novo->Nome,nome);
        Novo->idade = idade;
        strcpy(Novo->tipo,tipo);
        strcpy(Novo->fatorRh,fatorRh);
        Novo->qtdSangue = quantidade;
        Novo->FD = NULL;
        Novo->FE = NULL;
        if(Pai == NULL) {
            Raiz = Novo;
            return;
        }
        else if(idade >= Pai->idade)
            Pai->FD = Novo;
        else if(idade < Pai->idade)
            Pai->FE = Novo;
    }
    else if(idade >= R->idade) { //anda direita
        insere(R->FD, nome, idade, tipo, fatorRh, quantidade, R);
    }
    else if(idade < R->idade) { //anda esquerda
        insere(R->FE, nome, idade, tipo, fatorRh, quantidade, R);
    }
    else {
        printf("Os elementos que estao na arvore!\n");
    }
}

// funcao para ler do arquivo
void leArquivo(char * nome_arquivo) {
    FILE * ent;
    int l=1;
    SNo temp;
    //garantir que a string de tamanho 2 SNo.tipo é terminada nula
    temp.tipo[1]='\0';
    ent = fopen(nome_arquivo,"r");
    if(ent == NULL) {
        printf("Verifique o nome e o caminho do arquivo!\n");
        exit(-1);
    }
    char buff[256];
    //para cada linha do arquivo até o final
    while((fgets(buff,256,ent))){
        if(strlen(buff)==255){
            printf("Erro, a linha de um arquivo nao pode ultrapassar 256 caracteres\n");
            exit(-1);
        }
    	//captura um a string no max 30 caracteres, um inteiro, um caracter, outra string max 8 chars, e um float
    	int n;
		int res=sscanf(buff,"%30[^,],%i,%c,%8[^,],%f\n%n",temp.Nome,&temp.idade,temp.tipo,temp.fatorRh,&temp.qtdSangue,&n);
		//se o scanf capturar 5 variávei, ou seja, a linha tem um formato válido
		if(res==5&&buff[n]=='\0'){
			PrintNo(&temp);
			insere(Raiz,temp.Nome,temp.idade,temp.tipo,temp.fatorRh,temp.qtdSangue,NULL);
		}
        else{
            printf("linha %i do arquivo tem um formato incorreto e foi ignorada\n",l);
        }
        l++;
    }
    fclose(ent);
}
//Busca por fatorRh
void buscaFatorRh(SNo *R, char *fatorh){
	if(R==NULL){
		return;
	}
	if(strcmp(R->fatorRh,fatorh)==0){
		PrintNo(R);
	}
	buscaFatorRh(R->FD,fatorh);
	buscaFatorRh(R->FE,fatorh);
}
//Busca por Nome
SNo * buscaNome(SNo *R, char *nome){
	if(R==NULL){
		return NULL;
	}
	if(strcmp(R->Nome,nome)==0){
		return R;
	}
	SNo *AE=buscaNome(R->FD,nome);
   	SNo *AD=buscaNome(R->FE,nome);
	if(AD != NULL){
		return AD;
	}
	if(AE != NULL){
		return AE;
	}
	return NULL;
}
//Busca por idade.
SNo * buscaIdade(SNo *R ,int idade){
	if(R==NULL){
		printf("\nUsuario nao encontrado\n");
		return R;
	}
	if(R!=NULL){
		if(idade > R->idade){
			return buscaIdade(R->FD,idade);			
		}else if(idade < R->idade){
			return buscaIdade(R->FE,idade);
		}
		else{
			PrintNo(R);
		}		
	}
	return R;
}

//pegar o maior No
SNo *getPaiMaior(SNo *R,SNo *Pai) {
    if(R == NULL) // arvore vazia
        return NULL;
    if(R->FD == NULL) //olha FD se esta NULL
        return Pai;
    return getPaiMaior(R->FD,R); // anda com o R
}


//Função pra remover o Nó.
SNo * RemoveIdade(SNo *R , int idade , SNo *Pai){
	if(R==NULL){
		return NULL;
	}else if(idade >= R->idade){
		if(idade==R->idade){
		if(R->FD != NULL && R->FE != NULL){// se Atual tiver filho esquerdo e direito.
				if(Pai== NULL){
				
				return R;
			}
			if(Pai->FD ==R){
				
			}else{
				Pai->FE = R->FE;
			}
		}else if(R->FE != NULL){//Se o Atual tiver um filho esquerdo
			SNo *temp = getPaiMaior(R->FE,R);
			if(Pai== NULL){
				if(temp == R){
					Raiz = temp->FE;
				}else{
					Raiz = temp->FD;
					temp->FD = NULL;	
				}
				return R;
			}
			if(Pai->FD ==R){
				if(temp == R){
					Pai->FD = temp->FE;
				}
				else{
					Pai->FD = temp->FD;
					temp->FD = NULL;
				}
			}else{
				if(temp == R){
					Pai->FE = temp->FE;
				}
				else{
					Pai->FE = temp->FD;
					temp->FD = NULL;
				}
			}
			if(R->idade == R->FD->idade){
				free(R); // Nao pode retornar mais que um valor na funcao 
				return RemoveIdade(Pai->FD,idade,Pai);
			}
			return R;		
			}
		else if(R->FD != NULL){// Se o atual tiver um filho direito
			if(Pai == NULL){
				Raiz = R->FD;
				return R;
			}
			if(Pai->FD ==  R){
				Pai->FD = R->FD;
			}else{
				Pai->FE = R->FD;
			}	
			if(R->idade == R->FD->idade){
				free(R); // Nao pode retornar mais que um valor na funcao 
				return RemoveIdade(Pai->FD,idade,Pai);
			}
			return R;
		}
		else{// Se o Atual for Folha
			if(Pai == NULL ){
				Raiz = NULL;
				return R;
			}
			if(Pai->FD == R){
				Pai->FD = NULL;
			}else{
				Pai->FE = NULL;
			}
				return R;
			}
		}
		return RemoveIdade(R->FD,idade,R);
	}else if(idade < R->idade){
		return RemoveIdade(R->FE,idade,R);
	}
	return NULL;
}
float QuantSangue( SNo *R,char *type, float qtd){
	if(R==NULL){
		return qtd;//retornar se for null
	}
	if(strcmp(R->tipo,type)==0){
		qtd+=R->qtdSangue;	//comparando o tipo da string passada por parametro para conferir no no e fazer a soma
	}
	float qe=QuantSangue(R->FE,type,qtd);
	return QuantSangue(R->FD,type,qe);// retornando pra Main
}
int main(int argc, char **argv) {
    char nomeArquivo[20];
	int opcao,Escolha=0;
    printf("Qual o nome do arquivo: ");
    scanf("%s",nomeArquivo);
    leArquivo(nomeArquivo);
	while(opcao!=7){
		printf("---------------------------------\n");
		printf("| Qual opcao voce deseja realizar |\n");
		printf("---------------------------------\n");
		printf("Inserir Usuario [1] \n");
	    printf("Buscar Usuario[2] \n");
		printf("Remover Usuario[3] \n");
		printf("Vizualisar os Usuarios[4] \n");
		printf("Ver a quantidade de um determinado tipo de sangue digite [5] \n");
		printf("Atualizar o cadastro do Usuario[6]\n");
		printf("Sair[7]\n");
		scanf("%i",&opcao);
		switch(opcao){
			case 1:{
				#ifdef _WIN32
					system("cls");
				#endif
				#ifdef __APPLE__
					system("clear");
				#endif
				SNo temp;
				printf("Insira os dados na seguinte ordem para o cadastro!\n");
				printf("Nome:");
				//Fgets pega o \n e preciso retirar usando strlen
				getchar();
				scanf("%[^\n]s",temp.Nome);
				printf("Idade:");
				scanf("%i",&temp.idade);
				
				printf("Tipo Sanuineo:");
				scanf("%s",temp.tipo);
				
				printf("FatorRh:");
				scanf("%s",temp.fatorRh);
				
				printf("Quantidade de sangue Doada:");
				scanf("%f",&temp.qtdSangue);
				#ifdef _WIN32
					system("cls");
				#endif
				#ifdef __APPLE__
					system("clear");
				#endif
				
				printf("O Usuario a Seguir foi inserido no startUp\n");
				PrintNo(&temp);
				insere(Raiz,temp.Nome,temp.idade,temp.tipo,temp.fatorRh,temp.qtdSangue,NULL);
				break;
			}
			case 2:{
				SNo temp;
				printf("Por qual Forma voce deseja Buscar o paciente\n");
				printf("Por nome Digite [1]\n");
				printf("Por idade Digite [2]\n");
				printf("Por FatorRh Digite [3]\n");
				scanf("%i",&Escolha);
				if(Escolha == 1){
					printf("Digite o Nome que deseja buscar:");
					getchar();
					scanf("%[^\n]s",temp.Nome);
					SNo * name = buscaNome(Raiz,temp.Nome);
					if(name == NULL){
						printf("Nao existe esse nome\n");
					}else{
						PrintNo(name);
					}
				}else if(Escolha == 2){
					printf("Digite a Idade que deseja buscar:");
					scanf("%i",&temp.idade);
					buscaIdade(Raiz,temp.idade);
				}else if(Escolha == 3){
					
					printf("Digite o FatorRh que deseja buscar:");
					getchar();
					
					fgets(temp.fatorRh,30,stdin);
					int t=strlen(temp.fatorRh);
					if(t !=30){
						temp.fatorRh[t-1]='\0';
					}
						buscaFatorRh(Raiz,temp.fatorRh);
					if(temp.fatorRh == NULL){
						printf("Nao existe fator na arvore\n");
					}
				}
				
				break;
			}
			case 3:{
				SNo *aux;
				SNo temp;
				printf("Digite a idade da pessoa que deseja remover\n");
				scanf("%i",&temp.idade);
				aux = RemoveIdade(Raiz,temp.idade,NULL);
				if(aux == NULL){
					printf("Essa idade nao existe \n");
				}else{
					printf("O Usuario a seguido foi removido com sucesso\n");
					PrintNo(aux);
				}
				break;
			}
			case 4:{
				emOrdem(Raiz);
				break;
			}
			case 5:{
				float total=0,qtd=0;
				char tipo[2];
				printf("Digite Qual tipo de sangue voce deseja buscar o total\n");
				getchar();
				scanf("%[^\n]s",tipo);
				if(strcmp(tipo,"A")==0){
					total =	QuantSangue(Raiz,tipo,qtd);
					printf("A Quantidade total de sangue doado do tipo [A] e :%.2f\n",total);
				}
				else if(strcmp(tipo,"B")==0){
					total = QuantSangue(Raiz,tipo,qtd);
					printf("A Quantidade total de sangue doado do tipo [B] e :%.2f\n",total);
				}
				else if(strcmp(tipo,"O")==0){
					total = QuantSangue(Raiz,tipo,qtd);
					printf("A Quantidade total de sangue doado do tipo [O] e :%.2f\n",total);			
				}else{
					printf("Erro Tipo Invalido\n");
				}
					break;
				}
			case 6:{
				SNo temp;
				SNo *aux;

				printf("Digite  idade do usuario que voce deseja atualizar\n");
				scanf("%i",&temp.idade);			
				// Buscar o No.
				aux = RemoveIdade(Raiz,temp.idade,NULL);
				if(aux == NULL){
					printf("Usuario nao encontrado\n");
					break;
				}
				//Alterar nome 
				printf("\nNome atual :%s\n",aux->Nome);
				printf("\nvoce deseja modificar o nome do usuario ?\n");
				int n;
				printf("\nDigite [1] pra Sim [2] Pra Nao\n");
				scanf("%i",&n);
				if(n==1){
					printf("\nDigite o Nome do usuario\n");
					scanf(" %[^\n]s",temp.Nome);
					strcpy(aux->Nome,temp.Nome);
					n=0;
				}				
				//Alterar Idade
				printf("\nIdade atual :%i\n",aux->idade);
				printf("voce deseja modificar a idade do usuario ?\n");

				printf("\nDigite [1] pra Sim [2] Pra Nao\n");
				scanf("%i",&n);
				if(n==1){
					printf("\nDigite a nova idade do usuario\n");
					scanf("%i",&temp.idade);
					aux->idade = temp.idade;
					getchar();
					n=0;
				}
				//Alterar tipo sanguineo
				printf("\nTipo sanguineo atual :%s\n",aux->tipo);
				printf("\nvoce deseja modificar o tipo sanguineo do usuario ?\n");
	
				printf("\nDigite [1] pra Sim [2] Pra Nao\n");
				scanf("%i",&n);
				if(n==1){
					printf("\nDigite o novo tipo sanguineo\n");
					scanf(" %[^\n]s",temp.tipo);
					strcpy(aux->tipo,temp.tipo);
					n=0;
				}
				//Alterar fator Rh
				printf("\nfator Rh atual :%s\n",aux->fatorRh);
				printf("\nvoce deseja modificar o Fator Rh do usuario ?\n");
	
				printf("\nDigite [1] pra Sim [2] Pra Nao\n");
				scanf("%i",&n);
				if(n==1){
					printf("\nDigite o fator Rh do usuario\n");
					scanf(" %[^\n]s",temp.fatorRh);
					strcpy(aux->fatorRh,temp.fatorRh);
					n=0;
				}
				//Alterar Quantidade de sangue.
				printf("\nQuantidade de sangue atual :%.2f\n",aux->qtdSangue);
				printf("\nvoce deseja modificar a Quantidade de sangue do usuario ?\n");
	
				printf("\nDigite [1] pra Sim [2] Pra Nao\n");
				scanf("%i",&n);
				if(n==1){
					printf("\nDigite a nova qtd de sangue doada\n");
					scanf("%f",&temp.qtdSangue);
					getchar();
					aux->qtdSangue = temp.qtdSangue;
					n=0;
				}
				
				insere(Raiz,aux->Nome,aux->idade,aux->tipo,aux->fatorRh,aux->qtdSangue,NULL);
				free(aux);
				break;
			}
			case 7:{
				exit(1);
				break;
			}
			getchar();
		}
	}
	return 0;
}

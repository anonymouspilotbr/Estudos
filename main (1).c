#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXSIZE 10


typedef struct Aluno {
    char nome[20];
    int matricula;
    float nota;
} Aluno;


typedef struct ListaAlunos {
    Aluno alunos[MAXSIZE];
    int numElem;
} ListaAlunos;


void preencheAluno(Aluno* ptrAluno, 
                   int matricula,
                   float nota,
                   char* nome){
    (*ptrAluno).matricula = matricula;
    (*ptrAluno).nota = nota;
    strcpy((*ptrAluno).nome, nome);
}

void inicializaLista(ListaAlunos* listaAlunos){
    listaAlunos->numElem = 0;
}

void exibeLista(ListaAlunos* listaAlunos){
    int index;
    printf("Exibindo lista...\n\n");
    for(index = 0; index < listaAlunos->numElem;index++){
        printf("Aluno %d\n", index);
        printf("Nome: %s\n", listaAlunos->alunos[index].nome);
        printf("Matricula: %d\n", listaAlunos->alunos[index].matricula);
        printf("Nota: %.1f\n\n", listaAlunos->alunos[index].nota);
    }
}

void menu(ListaAlunos* listaAlunos){
  int i, op, matBusca, posBusca;
  char nomeBusca[30], R;
  do{
    menu:
    printf("O que deseja fazer a seguir?\n");
    printf("1 - Buscar aluno por nome\n");
    printf("2 - Buscar aluno por matricula\n");
    printf("3 - Buscar aluno por posicao na lista\n");
    fflush(stdin);
    scanf(" %d",&op);
    switch (op){
      case 1:
        system("clear");
        printf("Digite o nome do aluno para busca: ");
        scanf("%s",nomeBusca);
        for(i = 0; i < listaAlunos->numElem; i++){
          if(strcmp(nomeBusca, listaAlunos->alunos[i].nome)==0){
            printf("\nO aluno foi encontrado na posicao %d\n\n", i);
            printf("Aluno %d\n", i);
            printf("Nome: %s\n", listaAlunos->alunos[i].nome);
            printf("Matricula: %d\n", listaAlunos->alunos[i].matricula);
            printf("Nota: %.1f\n\n", listaAlunos->alunos[i].nota);
          }else{
          }
        }
        break;
      case 2:
        system("clear");
        printf("Digite a matricula do aluno para busca: ");
        scanf("%d",&matBusca);
        for(i = 0; i < listaAlunos->numElem; i++){
          if(matBusca == listaAlunos->alunos[i].matricula){
            printf("\nO aluno foi encontrado na posicao %d\n\n", i);
            printf("Aluno %d\n", i);
            printf("Nome: %s\n", listaAlunos->alunos[i].nome);
            printf("Matricula: %d\n", listaAlunos->alunos[i].matricula);
            printf("Nota: %.1f\n\n", listaAlunos->alunos[i].nota);
          }else{
          }
        }
        break;
      case 3:
        system("clear");
        busca:
        printf("Digite a posicao desejada: ");
        scanf("%d",&posBusca);
        i = posBusca;
        if(i > listaAlunos->numElem || i < 0){
          printf("ERRO: Posicao invalida. Tente novamente.\n\n");
          goto busca;
        }else{
          printf("Aluno %d\n", i);
            printf("Nome: %s\n", listaAlunos->alunos[i].nome);
            printf("Matricula: %d\n", listaAlunos->alunos[i].matricula);
            printf("Nota: %.1f\n\n", listaAlunos->alunos[i].nota);
        }
        break;
      default:
        printf("ERRO: Opcao invalida. Digite um numero de 1 a 3.\n\n");
        goto menu;
        break;
    }
    fflush(stdin);
    printf("Deseja fazer outra busca? [S/N]: ");
    scanf(" %c",&R);
  }while(R!='N');
}

bool insereAlunoNaLista(ListaAlunos* listaAlunos, 
                        Aluno aluno,
                        int posicao){
    if((listaAlunos->numElem >= MAXSIZE) || 
       (posicao < 0) || 
       (posicao > MAXSIZE) ||
       (posicao > listaAlunos->numElem)){
        printf("Insercao em posicao invalida!!!\n");
        return false;
    }
  for (int i = 0; i < listaAlunos->numElem; i++) {
        if (aluno.matricula == listaAlunos->alunos[i].matricula) {
            printf("Matricula ja existe na lista. Insercao nao                  realizada.\n");
            return false;
        }
    }
     if (posicao > listaAlunos->numElem) {
        posicao = listaAlunos->numElem; 
    }

    int index;
    for(index = listaAlunos->numElem; index > posicao; index--){
        listaAlunos->alunos[index] = listaAlunos->alunos[index-1];
    }
    listaAlunos->alunos[posicao] = aluno;
    listaAlunos->numElem++;
    return true;
}

bool excluiElementoDaLista(ListaAlunos* listaAlunos, int posicao){
    if((listaAlunos->numElem >= MAXSIZE) || 
       (posicao < 0) || 
       (posicao > MAXSIZE) ||
       (posicao > listaAlunos->numElem)){
        printf("Exclusao em posicao invalida!!!\n");
        return false;
    }
    
    memset(&listaAlunos->alunos[posicao], 0, sizeof(Aluno));

    int index;
    for(index = posicao; index < listaAlunos->numElem - 1;index++){
        listaAlunos->alunos[index] = listaAlunos->alunos[index+1];
    }
    listaAlunos->numElem--;
    return true;
}


int main(){

    ListaAlunos listaAlunos;
    inicializaLista(&listaAlunos);

    Aluno aluno0, aluno1, aluno2;
    preencheAluno(&aluno0, 15424242, 9.5, "Joao");
    preencheAluno(&aluno1, 10101011, 10, "Ana");
    preencheAluno(&aluno2, 22222222, 7, "Bia");

    insereAlunoNaLista(&listaAlunos, aluno0, 0);
    insereAlunoNaLista(&listaAlunos, aluno1, 0);
    insereAlunoNaLista(&listaAlunos, aluno2, 1);
    
    exibeLista(&listaAlunos);
    printf("Excluindo elemento.............\n");
    excluiElementoDaLista(&listaAlunos, 1);
    exibeLista(&listaAlunos);
    printf("nao foi apagado %s\n\n", listaAlunos.alunos[2].nome);

    menu(&listaAlunos);

    
  
    return 0;
}
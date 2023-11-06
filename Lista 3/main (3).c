#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE 50

typedef struct Livro {
    char autor[100];
    char titulo[100];
} Livro;

// CODIGO PARA CRIAR E OPERAR FILA

typedef struct Fila {
  int capacidade;
  Livro *dados;
  int primeiro;
  int ultimo;
  int nItens; 
} Fila;

void criarFila(Fila *f) { 
  f->capacidade = CAPACIDADE;
  f->dados = (Livro*) malloc (f->capacidade * sizeof(Livro));
  f->primeiro = 0;
  f->ultimo = -1;
  f->nItens = 0; 
}

void salvarNoArquivo(Fila *f, const char* arquivo) {
    FILE* file = fopen(arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    
  for (int i = f->primeiro; i <= f->ultimo; i++) {
    fprintf(file, "%s;%s\n", f->dados[i].titulo, f->dados[i].autor);
  }

  fclose(file);
}

void inserir(Fila *f, Livro l) {
  if (f->nItens < f->capacidade) {
      if (f->ultimo == f->capacidade - 1) {
          f->ultimo = -1;
      }

      f->ultimo++;
      f->dados[f->ultimo] = l;
      f->nItens++;
  } else {
      printf("Fila cheia. Capacidade: 50 livros.\n");
  }
}

Livro removerPorTitulo(Fila *f, const char *titulo) {
    Livro livroRemovido;
    int i = f->primeiro;
    int encontrado = 0;

    while (i <= f->ultimo && !encontrado) {
        if (strcmp(f->dados[i].titulo, titulo) == 0) {
            livroRemovido = f->dados[i];
            encontrado = 1;
        } else {
            i++;
        }
    }
    if (encontrado) {
        for (int j = i; j < f->ultimo; j++) {
            f->dados[j] = f->dados[j + 1];
        }
        f->ultimo--;
        f->nItens--;
    } else {
        printf("Livro com o título \"%s\" não encontrado na fila.\n", titulo);
    }
    return livroRemovido;
}

int estaVazia(Fila *f) { 
  return (f->nItens==0);
}

int estaCheia(Fila *f) { 
  return (f->nItens == f->capacidade);
}

void mostrarFila(Fila *f){
  int i;
    for (int i = f->primeiro; i <= f->ultimo; i++) {
        printf("Autor: %s, Titulo: %s\n", f->dados[i].autor, f->dados[i].titulo);
    }
  printf("\n");
}

// CODIGO PARA CRIAR E OPERAR PILHA

typedef struct Pilha {
  int topo; 
  int capa;
  int capacidade;
  Livro *pElem;
}Pilha;

void criarPilha(struct Pilha *p){
   p->topo = -1;
   p->capacidade = CAPACIDADE;
   p->pElem = (Livro*)malloc(p->capacidade * sizeof(Livro));
   if (p->pElem == NULL) {
       printf("Erro na alocação de memória para a pilha.\n");
       exit(1);
   }
}

int pilhaVazia (struct Pilha *p){
   if( p-> topo == -1 )
      return 1;   
   else
      return 0;  
}

int pilhaCheia (struct Pilha *p){
  if (p->topo == p->capa - 1)
    return 1;
  else
    return 0;
}

void empilhar(struct Pilha *p, Livro l, const char* arquivo) {
    if (p->topo < p->capacidade - 1) {
        if (strlen(l.autor) > 0 && strlen(l.titulo) > 0) {
            for (int i = p->topo; i >= 0; i--) {
                p->pElem[i + 1] = p->pElem[i];
            }
            p->pElem[0] = l;
            p->topo++;

            FILE* fPilha = fopen(arquivo, "w");
            if (fPilha == NULL) {
                printf("Erro ao abrir o arquivo da pilha.\n");
                exit(1);
            }

            for (int i = 0; i <= p->topo; i++) {
                fprintf(fPilha, "%s;%s\n", p->pElem[i].titulo, p->pElem[i].autor);
            }

            fclose(fPilha);
        } else {
            printf("Livro vazio. Não é possível empilhar.\n");
        }
    } else {
        printf("Pilha cheia. Capacidade: 50 livros.\n");
    }
}


void removerLivroPorTituloDaPilha(Pilha *p, const char* arquivo) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível remover.\n");
        return;
    }

    char titulo[100];
    printf("Digite o título do livro a ser removido: ");
    getchar();
    fgets(titulo, sizeof(titulo), stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    int indice = -1; 

    for (int i = 0; i <= p->topo; i++) {
        if (strcmp(p->pElem[i].titulo, titulo) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Livro com o título \"%s\" não encontrado na pilha.\n", titulo);
    } else {
        Livro livroRemovido = p->pElem[indice];
        for (int i = indice; i < p->topo; i++) {
            p->pElem[i] = p->pElem[i + 1];
        }
        p->topo--;

        FILE* fPilha = fopen(arquivo, "w");
        if (fPilha == NULL) {
            printf("Erro ao abrir o arquivo da pilha.\n");
            exit(1);
        }

        for (int i = 0; i <= p->topo; i++) {
            fprintf(fPilha, "%s;%s\n", p->pElem[i].titulo, p->pElem[i].autor);
        }

        fclose(fPilha);

        printf("Livro removido da pilha: Autor: %s, Título: %s\n", livroRemovido.autor, livroRemovido.titulo);
    }
}

Livro retornatopo(struct Pilha *p) {
    if (!pilhaVazia(p)) {
        return p->pElem[p->topo];
    } else {
        Livro livroVazio;
        strcpy(livroVazio.autor, "");
        strcpy(livroVazio.titulo, "");
        return livroVazio;
    }
}

void salvarPilhaNoArquivo(struct Pilha *p, const char* arquivo) {
    FILE* fPilha = fopen(arquivo, "w");
    if (fPilha == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    for (int i = 0; i <= p->topo; i++) {
        fprintf(fPilha, "%s;%s\n", p->pElem[i].titulo, p->pElem[i].autor);
    }

    fclose(fPilha);
}

void limparTela(){
  printf("\033[H\033[J");
}

int main() {
  int op;
  char autor[100], titulo[100];
  Fila f;
  Pilha p;
  
  criarFila(&f);
  criarPilha(&p);

  FILE* file = fopen("fila_de_livros.txt", "r");
  if (file != NULL) {
      while (fscanf(file, "%99[^;];%99[^\n]\n", titulo, autor) == 2) {
          Livro livro;
          strcpy(livro.titulo, titulo);
          strcpy(livro.autor, autor);
          if (!estaCheia(&f)) { 
            inserir(&f, livro);
        }
      }
      fclose(file);
  } else {
      printf("Fila vazia!\n");
  }

  FILE* fPilha = fopen("pilha_de_livros.txt", "r");
  if (fPilha != NULL) {
      Livro livroPilhaReversa[CAPACIDADE];
      int i = 0;

      while (fscanf(fPilha, "%99[^;];%99[^\n]\n", titulo, autor) == 2) {
          Livro livroP;
          strcpy(livroP.titulo, titulo);
          strcpy(livroP.autor, autor);
          livroPilhaReversa[i] = livroP;
          i++;
      }
      fclose(fPilha);

      for (int j = i - 1; j >= 0; j--) {
          empilhar(&p, livroPilhaReversa[j], "pilha_de_livros.txt");
      }
  } else {
      printf("Pilha vazia!\n");
  }
  
  do{
    printf("\nMenu:\n");
    printf("1. Exibir fila de livros\n");
    printf("2. Inserir livro na fila\n");
    printf("3. Inserir livro na pilha\n");
    printf("4. Remover livro da fila\n");
    printf("5. Remover livro da pilha\n");
    printf("6. Sair\n");
    scanf(" %d", &op);
    
    switch(op){
      case 1:
        limparTela();
        if(estaVazia(&f)){
          printf("Fila vazia!\n");
        }else if(estaCheia(&f)){
          printf("Fila cheia. Capacidade: 50 livros.\n");
        }else{
          printf("Fila de livros:\n");
          mostrarFila(&f);
        }
        break;
      case 2:
        limparTela();
        printf("Digite o nome do autor: ");
        getchar();
        fgets(autor, sizeof(autor), stdin);
        autor[strcspn(autor, "\n")] = '\0';

        printf("Digite o titulo do livro: ");
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = '\0'; 

        Livro livro;
        strcpy(livro.autor, autor);
        strcpy(livro.titulo, titulo);
        inserir(&f, livro);
        break;
      case 3:
        limparTela();
        printf("Digite o nome do autor: ");
        getchar();
        fgets(autor, sizeof(autor), stdin);
        autor[strcspn(autor, "\n")] = '\0';

        printf("Digite o titulo do livro: ");
        fgets(titulo, sizeof(titulo), stdin);
        titulo[strcspn(titulo, "\n")] = '\0'; 

        if (strlen(autor) > 0 && strlen(titulo) > 0) {
            Livro livroP;
            strcpy(livroP.autor, autor);
            strcpy(livroP.titulo, titulo);

            if (!pilhaCheia(&p)) {
                empilhar(&p, livroP, "pilha_de_livros.txt");
                printf("Livro empilhado com sucesso!\n");
            } else {
                printf("Pilha cheia. Capacidade: 50 livros.\n");
            }
        } else {
            printf("Entrada invalida. Tente novamente.\n");
        }
        break;
      case 4:
        limparTela();
        if (!estaVazia(&f)) {
            printf("Digite o título do livro a ser removido: ");
            getchar();
            fgets(titulo, sizeof(titulo), stdin);
            titulo[strcspn(titulo, "\n")] = '\0';

            Livro livroRemovido = removerPorTitulo(&f, titulo);
            if (strcmp(livroRemovido.titulo, "") != 0) {
                printf("Livro removido: Autor: %s, Título: %s\n", livroRemovido.autor, livroRemovido.titulo);
            }
        } else {
            printf("Fila vazia. Não é possível remover.\n");
        }
        break;
      case 5:
        limparTela();
        removerLivroPorTituloDaPilha(&p, "pilha_de_livros.txt");
        break;
      case 6:
        salvarNoArquivo(&f, "fila_de_livros.txt");
        salvarPilhaNoArquivo(&p, "pilha_de_livros.txt");
        break;
      default:
        limparTela();
        printf("ERRO: Opcao invalida. Tente novamente.\n");
        break;
    }
  } while (op != 6);
  
  free(f.dados);
  free(p.pElem);
  return 0;
}
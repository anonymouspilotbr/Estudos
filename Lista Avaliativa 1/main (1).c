#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Album {
    char nome[100];
    struct Album* prox;
};

struct Artista {
    char nome[100];
    char genero[100];
    char local[100];
    int  numAlbuns;
    struct Album* albuns;
    struct Artista* prox;
};

void imprimirArtista(struct Artista* artista) {
    printf("Nome: %s\n", artista->nome);
    printf("Genero: %s\n", artista->genero);
    printf("Local: %s\n", artista->local);

    struct Album* albumAtual = artista->albuns;
    while (albumAtual != NULL) {
        printf("Album: %s\n", albumAtual->nome);
        albumAtual = albumAtual->prox;
    }
    printf("===========\n");
}

void liberarMemoria(struct Artista* lista) {
    while (lista != NULL) {
        struct Album* albumAtual = lista->albuns;
        while (albumAtual != NULL) {
            struct Album* proximoAlbum = albumAtual->prox;
            free(albumAtual);
            albumAtual = proximoAlbum;
        }
        struct Artista* proximoArtista = lista->prox;
        free(lista);
        lista = proximoArtista;
    }
}

struct Artista* lerArtistasDoArquivo(const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    struct Artista* lista = NULL;
    struct Artista* ultimoArtista = NULL;
    struct Album* ultimoAlbum = NULL;

    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strlen(linha) - 1] = '\0';  

        if (strcmp(linha, "==========") == 0) {
            struct Artista* novoArtista = (struct Artista*)malloc(sizeof(struct Artista));
            if (novoArtista == NULL) {
                printf("Erro ao alocar memoria para o artista.\n");
                exit(1);
            }
            novoArtista->albuns = NULL;
            novoArtista->prox = NULL;

            if (ultimoArtista == NULL) {
                lista = novoArtista;
            } else {
                ultimoArtista->prox = novoArtista;
            }
            ultimoArtista = novoArtista;
            ultimoAlbum = NULL;
        } else {
            if (ultimoArtista == NULL) {
                printf("Erro: formato invalido do arquivo.\n");
                exit(1);
            }
            if (ultimoArtista->nome[0] == '\0') {
                strcpy(ultimoArtista->nome, linha);
            } else if (ultimoArtista->genero[0] == '\0') {
                strcpy(ultimoArtista->genero, linha);
            } else if (ultimoArtista->local[0] == '\0') {
                strcpy(ultimoArtista->local, linha);
            } else {
                struct Album* novoAlbum = (struct Album*)malloc(sizeof(struct Album));
                if (novoAlbum == NULL) {
                    printf("Erro ao alocar memoria para o album.\n");
                    exit(1);
                }
                strcpy(novoAlbum->nome, linha);
                novoAlbum->prox = NULL;

                if (ultimoAlbum == NULL) {
                    ultimoArtista->albuns = novoAlbum;
                } else {
                    ultimoAlbum->prox = novoAlbum;
                }
                ultimoAlbum = novoAlbum;
            }
        }
    }

    fclose(arquivo);
    return lista;
}

void salvarArtistasNoArquivo(const char* nomeArquivo, struct Artista* lista) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    struct Artista* artistaAtual = lista;
    while (artistaAtual != NULL) {
        fprintf(arquivo, "==========\n");
        fprintf(arquivo, "%s\n", artistaAtual->nome);
        fprintf(arquivo, "%s\n", artistaAtual->genero);
        fprintf(arquivo, "%s\n", artistaAtual->local);

        struct Album* albumAtual = artistaAtual->albuns;
        while (albumAtual != NULL) {
            fprintf(arquivo, "%s\n", albumAtual->nome);
            albumAtual = albumAtual->prox;
        }

        artistaAtual = artistaAtual->prox;
    }

    fclose(arquivo);
}

void adicionarAlbum(struct Artista *artista, const char *nomeAlbum) {
    struct Album *novoAlbum = (struct Album *)malloc(sizeof(struct Album));
    if (novoAlbum == NULL) {
        printf("Erro ao alocar memoria para o album.\n");
        exit(1);
    }

    strcpy(novoAlbum->nome, nomeAlbum);
    novoAlbum->prox = NULL;

    if (artista->albuns == NULL) {
        artista->albuns = novoAlbum;
    } else {
        struct Album *ultimoAlbum = artista->albuns;
        while (ultimoAlbum->prox != NULL) {
            ultimoAlbum = ultimoAlbum->prox;
        }
        ultimoAlbum->prox = novoAlbum;
    }
}

void liberarArtista(struct Artista *artista) {
    struct Album *albumAtual = artista->albuns;
    while (albumAtual != NULL) {
        struct Album *proximoAlbum = albumAtual->prox;
        free(albumAtual);
        albumAtual = proximoAlbum;
    }

    free(artista);
}

int compararArtistasPorNome(const void* a, const void* b) {
    return strcmp((*(struct Artista**)a)->nome, (*(struct Artista**)b)->nome);
}

void ordenarArtistasPorNome(struct Artista** lista) {
    int numElementos = 0;
    struct Artista* atual = *lista;
    while (atual != NULL) {
        numElementos++;
        atual = atual->prox;
    }

    struct Artista** arrayArtistas = malloc(numElementos * sizeof(struct Artista*));
    if (arrayArtistas == NULL) {
        printf("Erro ao alocar memória para ordenação.\n");
        exit(1);
    }

    atual = *lista;
    for (int i = 0; i < numElementos; i++) {
        arrayArtistas[i] = atual;
        atual = atual->prox;
    }

    qsort(arrayArtistas, numElementos, sizeof(struct Artista*), compararArtistasPorNome);

    *lista = arrayArtistas[0];
    for (int i = 0; i < numElementos - 1; i++) {
        arrayArtistas[i]->prox = arrayArtistas[i + 1];
    }
    arrayArtistas[numElementos - 1]->prox = NULL;

    free(arrayArtistas);
}

void adicionarArtista(struct Artista **lista, int *numArtistas){
   struct Artista *novoArtista = (struct Artista *)malloc(sizeof(struct Artista));
    if (novoArtista == NULL) {
        printf("Erro ao alocar memória para o novo artista.\n");
        exit(1);
    }

    char nomeArtista[100];
    char generoMusical[100];
    char localArtista[100];
    int numAlbuns;
  
    printf("*** ADICIONAR NOVO ARTISTA ***\n");
    printf("Digite o nome do artista: ");
    fgets(nomeArtista, sizeof(nomeArtista), stdin);
    nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
  
    printf("Digite o genero musical: ");
    fgets(generoMusical, sizeof(generoMusical), stdin);
    generoMusical[strcspn(generoMusical, "\n")] = '\0';
    
    printf("Digite o local do artista: ");
    fgets(localArtista, sizeof(localArtista), stdin);
    localArtista[strcspn(localArtista, "\n")] = '\0';
    
    printf("Quantos albuns esse artista possui? ");
    scanf("%d", &numAlbuns);
    getchar();

    novoArtista->albuns = NULL;
    novoArtista->prox = NULL;
    novoArtista->numAlbuns = numAlbuns;
    strcpy(novoArtista->nome, nomeArtista);
    strcpy(novoArtista->genero, generoMusical);
    strcpy(novoArtista->local, localArtista);

    for (int i = 0; i < numAlbuns; i++) {
        char nomeAlbum[100];
        printf("Digite o nome do album %d: ", i + 1);
        fgets(nomeAlbum, sizeof(nomeAlbum), stdin);
        nomeAlbum[strcspn(nomeAlbum, "\n")] = '\0';

        adicionarAlbum(novoArtista, nomeAlbum);
    }

    if (*lista == NULL) {
        *lista = novoArtista;
    } else {
        struct Artista *atual = *lista;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novoArtista;
    }

    (*numArtistas)++;

    system("clear");
    printf("Artista adicionado com sucesso.\n\n");

    salvarArtistasNoArquivo("artistas.txt", *lista);
}

void removerArtista(struct Artista **lista, int *numArtistas){
  char nomeArtista[100];
  
  printf("*** REMOVER ARTISTA ***\n");
  printf("Digite o nome do artista que deseja remover: ");
  fgets(nomeArtista, sizeof(nomeArtista), stdin);
  nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
  system("clear");

  struct Artista *anterior = NULL;
  struct Artista *atual = *lista;

  while (atual != NULL) {
      if (strcmp(atual->nome, nomeArtista) == 0) {
          if (anterior == NULL) {
              *lista = atual->prox;
          } else {
              anterior->prox = atual->prox;
          }
          liberarArtista(atual);
          printf("Artista removido com sucesso.\n");
          (*numArtistas)--;
          return; 
      }

      anterior = atual;
      atual = atual->prox;
    }
    printf("Artista com o nome '%s' não encontrado.\n", nomeArtista);
    salvarArtistasNoArquivo("artistas.txt", *lista);
}

void editarArtista(struct Artista **lista, int *numArtistas){
  char nomeArtista[100];
  char novoNome[100];
  char novoGenero[100];
  char novoLocal[100];
  char nomeAlbum[100];
  char novoNomeAlbum[100];
  int op;
  
  printf("*** EDITAR ARTISTA ***\n");
  printf("Digite o nome do artista que deseja editar: ");
  fgets(nomeArtista, sizeof(nomeArtista), stdin);
  nomeArtista[strcspn(nomeArtista, "\n")] = '\0';

  struct Artista *atual = *lista;

    while (atual != NULL) {
        if (strcmp(atual->nome, nomeArtista) == 0) {
          printf("O que deseja editar?\n");
          printf("1. Nome do Artista\n");
          printf("2. Genero Musical\n");
          printf("3. Local do Artista\n");
          printf("4. Nome do Album\n");
          scanf("%d",&op);
          getchar();
        
          switch(op){
            case 1:
              printf("Digite o novo nome do artista: ");
              fgets(novoNome, sizeof(novoNome), stdin);
              novoNome[strcspn(novoNome, "\n")] = '\0';
              strcpy(atual->nome, novoNome);
              break;
            case 2:
              printf("Digite o genero musical do artista: ");
              fgets(novoGenero, sizeof(novoGenero), stdin);
              novoGenero[strcspn(novoGenero, "\n")] = '\0';
              strcpy(atual->genero, novoGenero);
              break;
            case 3:
              printf("Digite o novo local do artista: ");
              fgets(novoLocal, sizeof(novoLocal), stdin);
              novoLocal[strcspn(novoLocal, "\n")] = '\0';
              strcpy(atual->local, novoLocal);
              break;
            case 4:
              {
              int encontrouArtista = 0;
                printf("Digite o nome do album que deseja editar: ");
                fgets(nomeAlbum, sizeof(nomeAlbum), stdin);
                nomeAlbum[strcspn(nomeAlbum, "\n")] = '\0';
                
                struct Artista *atual = *lista;
                while (atual != NULL) {
                    if (strcmp(atual->nome, nomeArtista) == 0) {
                        encontrouArtista = 1;
                        break;
                    }
                    atual = atual->prox;
                }
        
                if (encontrouArtista) {
                    struct Album *albumAtual = atual->albuns;
                    while (albumAtual != NULL) {
                        if (strcmp(albumAtual->nome, nomeAlbum) == 0) {
                            printf("Digite o novo nome do album: ");
                            fgets(novoNomeAlbum, sizeof(novoNomeAlbum), stdin);
                            novoNomeAlbum[strcspn(novoNomeAlbum, "\n")] = '\0';
        
                            strcpy(albumAtual->nome, novoNomeAlbum);
                            printf("Nome do album editado com sucesso.\n");
                            break;
                        }
                        albumAtual = albumAtual->prox;
                    }
        
                    if (albumAtual == NULL) {
                        printf("Album com o nome '%s' nao encontrado para este artista.\n", nomeAlbum);
                    }
                } else {
                    printf("Artista com o nome '%s' nao encontrado.\n", nomeArtista);
                }
              break;
            }
            default:
              printf("Opcao invalida. Tente novamente.\n");
          }
          printf("Artista editado com sucesso.\n");
          return;
        }
        atual = atual->prox;
    }
    printf("Artista com o nome '%s' não encontrado.\n", nomeArtista);
    salvarArtistasNoArquivo("artistas.txt", *lista);
}

struct Artista* obterArtistaPorIndice(struct Artista* lista, int indice) {
    int i = 0;
    struct Artista* atual = lista;

    while (atual != NULL) {
        if (i == indice) {
            return atual;
        }
        atual = atual->prox;
        i++;
    }

    return NULL;  
}

void buscarArtistaBinario(struct Artista* lista, const char* nome) {

    int numArtistas = 0;
    struct Artista* atual = lista;
    while (atual != NULL) {
        numArtistas++;
        atual = atual->prox;
    }

    int inicio = 0;
    int fim = numArtistas - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        struct Artista* artistaMeio = obterArtistaPorIndice(lista, meio);

        int comparacao = strcmp(artistaMeio->nome, nome);

        if (comparacao == 0) {
            imprimirArtista(artistaMeio);
            return;
        } else if (comparacao < 0) {
            inicio = meio + 1;  
        } else {
            fim = meio - 1;  
        }
    }

    printf("Artista com o nome '%s' não encontrado.\n", nome);
}

void buscarAlbumSequencial(struct Artista* lista, const char* nomeArtista, const char* nomeAlbum) {
    struct Artista* atual = lista;

    while (atual != NULL) {
        if (strcmp(atual->nome, nomeArtista) == 0) {
            struct Album* albumAtual = atual->albuns;
            while (albumAtual != NULL) {
                if (strcmp(albumAtual->nome, nomeAlbum) == 0) {
                    printf("Álbum encontrado:\n");
                    printf("Artista: %s\n", atual->nome);
                    printf("Nome do álbum: %s\n", albumAtual->nome);
                    return;
                }
                albumAtual = albumAtual->prox;
            }
            printf("Álbum '%s' não encontrado para o artista '%s'.\n", nomeAlbum, nomeArtista);
            return;
        }
        atual = atual->prox;
    }

    printf("Artista com o nome '%s' não encontrado.\n", nomeArtista);
}

int main() {
    struct Artista* listaArtistas = lerArtistasDoArquivo("artistas.txt");
    int opcao;
    int numArtistas;
    char nomeArtista[100];
    char nomeAlbum[100];

    ordenarArtistasPorNome(&listaArtistas);
    printf("Lista de Artistas:\n");
    struct Artista* artistaAtual = listaArtistas;
    while (artistaAtual != NULL) {
        imprimirArtista(artistaAtual);
        artistaAtual = artistaAtual->prox;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Inserir artista\n");
        printf("2. Remover artista\n");
        printf("3. Editar artista\n");
        printf("4. Buscar artista\n");
        printf("5. Buscar album\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  

        switch (opcao) {
            case 1:  
                system("clear");
                adicionarArtista(&listaArtistas, &numArtistas);
                break;

            case 2:  
                system("clear");
                removerArtista(&listaArtistas, &numArtistas);
                break;

            case 3:  
                system("clear");
                editarArtista(&listaArtistas, &numArtistas);
                break;

            case 4:  
                system("clear");
                printf("*** BUSCAR ARTISTA ***\n");
                printf("Qual artista deseja buscar? ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';
                
                buscarArtistaBinario(listaArtistas, nomeArtista);
                break;

            case 5:  
                system("clear");
                printf("*** BUSCAR ALBUM ***\n");
                printf("Qual o nome do artista do album? ");
                fgets(nomeArtista, sizeof(nomeArtista), stdin);
                nomeArtista[strcspn(nomeArtista, "\n")] = '\0';

                printf("Digite o nome do album para a busca: ");
                fgets(nomeAlbum, sizeof(nomeAlbum), stdin);
                nomeAlbum[strcspn(nomeAlbum, "\n")] = '\0';
                
                buscarAlbumSequencial(listaArtistas, nomeArtista, nomeAlbum);
                
                break;

            case 6:
                system("clear");
                printf("Obrigado por usar esse programa.\n");
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    salvarArtistasNoArquivo("artistas.txt", listaArtistas);
    liberarMemoria(listaArtistas);

    return 0;
}

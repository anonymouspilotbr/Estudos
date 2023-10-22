#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica {
    char artista[100];
    char musica[100];
} Music;

typedef struct Play {
    struct Musica data;
    struct Play* prox;
    struct Play* ant;
} Play;

Play* criarNo(char artista[100], char musica[100]) {
    Play* novoNo = (Play*)malloc(sizeof(Play));
    strcpy(novoNo->data.artista, artista);
    strcpy(novoNo->data.musica, musica);
    novoNo->prox = novoNo->ant = NULL;
    return novoNo;
}

void inserirFinal(Play** cabeca, char artista[100], char musica[100]) {
    Play* novoNo = criarNo(artista, musica);
    if (*cabeca == NULL) {
        novoNo->prox = novoNo->ant = novoNo;
        *cabeca = novoNo;
    } else {
        Play* cauda = (*cabeca)->ant;
        cauda->prox = novoNo;
        novoNo->prox = *cabeca;
        novoNo->ant = cauda;
        (*cabeca)->ant = novoNo;
    }
}

void mostrarAtual(Play* atual) {
    if (atual != NULL) {
        printf("Musica Atual:\nArtista: %s\nMusica: %s\n", atual->data.artista, atual->data.musica);
    } else {
        printf("Nao ha musicas na playlist.\n");
    }
}

Play* proxMusica(Play* atual) {
    if (atual != NULL) {
        return atual->prox;
    } else {
        return NULL;
    }
}

Play* musicaAnt(Play* atual) {
    if (atual != NULL) {
        return atual->ant;
    } else {
        return NULL;
    }
}

void salvarNoArquivo(Play* cabeca, const char* arquivo) {
    FILE* file = fopen(arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    Play* atual = cabeca;
    do {
        fprintf(file, "%s;%s\n", atual->data.artista, atual->data.musica);
        atual = atual->prox;
    } while (atual != cabeca);

    fclose(file);
}

void adicionarMusica(Play** cabeca, char artista[100], char musica[100]) {
    inserirFinal(cabeca, artista, musica);
    salvarNoArquivo(*cabeca, "musicas.txt");
    printf("\nMusica adicionada a playlist:\nArtista: %s\nMusica: %s\n\n", artista, musica);
}

void removerMusica(Play** cabeca, Play** atual, char artista[100], char musica[100]) {
    Play* remover = *cabeca;
    if (*atual != NULL) {
        remover = *atual;
    }

    if (*cabeca != NULL) {
        do {
            if (strcmp(remover->data.artista, artista) == 0 && strcmp(remover->data.musica, musica) == 0) {
                if (remover == *atual) {
                    *atual = remover->prox;
                }
                if (remover->prox == remover) {
                    *cabeca = NULL;
                } else {
                    remover->ant->prox = remover->prox;
                    remover->prox->ant = remover->ant;
                    if (remover == *cabeca) {
                        *cabeca = remover->prox;
                    }
                }
                free(remover);
                salvarNoArquivo(*cabeca, "musicas.txt");
                printf("\nMusica removida da playlist.\n\n");
                return;
            }
            remover = remover->prox;
        } while (remover != *cabeca);
    }

    printf("Musica nao encontrada na playlist.\n");
}

void mostrarPlaylist(Play* cabeca) {
    if (cabeca == NULL) {
        printf("Nao ha musicas na playlist.\n");
        return;
    }

    Play* atual = cabeca;
    printf("Playlist por ordem de registro:\n\n");
    do {
        printf("Artista: %s, Musica: %s\n", atual->data.artista, atual->data.musica);
        atual = atual->prox;
    } while (atual != cabeca);
    printf("\n");
}

void trocarNos(Play** a, Play** b) {
    Play* temp = (*a)->ant;
    (*a)->ant = (*b)->ant;
    (*b)->ant = temp;

    temp = (*a)->prox;
    (*a)->prox = (*b)->prox;
    (*b)->prox = temp;

    if ((*a)->prox == *a) {
        (*a)->prox = *b;
        (*a)->ant = *b;
    }

    if ((*b)->prox == *b) {
        (*b)->prox = *a;
        (*b)->ant = *a;
    }
}

int comparaNos(const void* a, const void* b) {
    Play* noA = *(Play**)a;
    Play* noB = *(Play**)b;
    return strcmp(noA->data.musica, noB->data.musica);
}

void ordenarPorNome(Play** cabeca) {
    if (*cabeca == NULL || (*cabeca)->prox == *cabeca) {
        return;  
    }

    int count = 0;
    Play* atual = *cabeca;
    do {
        count++;
        atual = atual->prox;
    } while (atual != *cabeca);

    Play** nodeArray = (Play**)malloc(count * sizeof(Play*));

    atual = *cabeca;
    for (int i = 0; i < count; i++) {
        nodeArray[i] = atual;
        atual = atual->prox;
    }

    qsort(nodeArray, count, sizeof(Play*), comparaNos);

    for (int i = 0; i < count; i++) {
        nodeArray[i]->ant = (i > 0) ? nodeArray[i - 1] : nodeArray[count - 1];
        nodeArray[i]->prox = (i < count - 1) ? nodeArray[i + 1] : nodeArray[0];
    }

    *cabeca = nodeArray[0];

    free(nodeArray);
}

void mostrarPlaylistOrdenada(Play* cabeca) {
    if (cabeca == NULL) {
        printf("Nao ha musicas na playlist.\n");
        return;
    }

    Play* atual = cabeca;
    printf("Playlist ordenada por nome da musica:\n\n");
    do {
        printf("Artista: %s, Musica: %s\n", atual->data.artista, atual->data.musica);
        atual = atual->prox;
    } while (atual != cabeca);
    printf("\n");
}


Play* buscarMusica(Play* cabeca, char artista[100], char musica[100]) {
    if (cabeca == NULL) {
        return NULL; 
    }

    Play* atual = cabeca;
    do {
        if (strcmp(atual->data.artista, artista) == 0 && strcmp(atual->data.musica, musica) == 0) {
            return atual;
        }
        atual = atual->prox;
    } while (atual != cabeca);

    return NULL;
}

void mostrarMusica(Play* noDaMusica) {
    if (noDaMusica != NULL) {
        printf("\nMusica Encontrada:\nArtista: %s\nMusica: %s\n\n", noDaMusica->data.artista, noDaMusica->data.musica);
    } else {
        printf("Musica nao encontrada na playlist.\n");
    }
}

int main() {
    Play* playlist = NULL;
    Play* atual = NULL;
    char artista[100];
    char musica[100];
    char op;

    FILE* file = fopen("musicas.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    while (fscanf(file, "%99[^;];%99[^\n]\n", artista, musica) == 2) {
        inserirFinal(&playlist, artista, musica);
        if (atual == NULL) {
            atual = playlist;
        }
    }
    fclose(file);

    mostrarAtual(atual);

    do {
        printf("\nMenu:\n");
        printf("1. Proxima Musica\n");
        printf("2. Musica Anterior\n");
        printf("3. Adicionar Musica\n");
        printf("4. Remover Musica\n");
        printf("5. Mostrar playlist\n");
        printf("6. Ordenar playlist por ordem alfabetica\n");
        printf("7. Buscar musica\n");
        printf("8. Sair\n");
        printf("Opcao: ");
        scanf(" %c", &op);

        switch (op) {
            case '1':
                system("clear");
                atual = proxMusica(atual);
                break;
            case '2':
                system("clear");
                atual = musicaAnt(atual);
                break;
            case '3':
                system("clear");
                printf("Digite o nome do artista: ");
                getchar();
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = '\0';
              
                printf("Digite o nome da musica: ");
                fgets(musica, sizeof(musica), stdin);
                musica[strcspn(musica, "\n")] = '\0';  
              
                adicionarMusica(&playlist, artista, musica);
                atual = playlist;
                break;
            case '4':
                system("clear");
                printf("Digite o nome do artista: ");
                getchar();
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = '\0';
              
                printf("Digite o nome da musica que quer remover: ");
                fgets(musica, sizeof(musica), stdin);
                musica[strcspn(musica, "\n")] = '\0';  
              
                removerMusica(&playlist, &atual, artista, musica);
                break;
            case '5':
                system("clear");
                mostrarPlaylist(playlist);
                break;
            case '6':
                system("clear");
                ordenarPorNome(&playlist);
                mostrarPlaylistOrdenada(playlist);
                break;
            case '7':
                system("clear");
                printf("Digite o nome do artista: ");
                getchar(); 
                fgets(artista, sizeof(artista), stdin);
                artista[strcspn(artista, "\n")] = '\0';

                printf("Digite o nome da musica para buscar: ");
                fgets(musica, sizeof(musica), stdin);
                musica[strcspn(musica, "\n")] = '\0';

                Play* musicaEncontrada = buscarMusica(playlist, artista, musica);
                mostrarMusica(musicaEncontrada);
                break;
            case '8':
                break;
            default:
                printf("Opcao Invalida. Tente novamente.\n");
        }

        mostrarAtual(atual);
    } while (op != '8');

    return 0;
}

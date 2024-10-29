#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dicionario.h"

Lista* inicializar(){
    return NULL;
}

void inserir_traducao(Lista** l, char *port, char *ing){
    Lista *novo = (Lista *) malloc(sizeof(Lista));
    if (novo==NULL)
    {
        printf("Erro de alocacao de memoria!");
        return;
    }
    strcpy(novo->dado.portugues, port);
    strcpy(novo->dado.ingles, ing);
    novo->prox = NULL;
    if (*l == NULL) {
        *l = novo;
    } else {
        Lista *aux = *l;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }        
}

void remover_traducao(Lista** l, char *palavra){
    if (*l==NULL)
    {
        printf("Lista vazia!\n");
        return;
    }
    Lista* aux= *l;
    Lista* ant = NULL;
    while (aux != NULL && (strcmp(aux->dado.portugues, palavra) != 0 || strcmp(aux->dado.ingles, palavra) != 0))
    {
        ant = aux;
        aux = aux->prox;
    }
    if (aux==NULL)
    {
        printf("Termo nao encontrado!");
        return;
    }
    if (ant == NULL) {
        *l = aux->prox;
    } else {
        ant->prox = aux->prox;
    }   
    free(aux);
    printf("Termo removido com sucesso!\n");     
}

void buscar_traducao(Lista *l, char *txt) {
    if (l==NULL)
    {
        printf("Dicionario vazio!");
        return;
    }
    Lista* aux = l;
    while (aux != NULL) {
        if (strcmp(aux->dado.portugues, txt) == 0 || strcmp(aux->dado.ingles, txt) == 0) {
            printf("Portugues: %s - Ingles: %s\n", aux->dado.portugues, aux->dado.ingles);
            return;
        }
        aux = aux->prox;
    }   
    printf("Termo nao encontrado!");
}

void traducao_texto(Lista *l, char *txt){
    char *palavras[10];
    int i=0;

    char *ptrpalavra = strtok(txt," ");
    while (ptrpalavra != NULL)
    {
        palavras[i]=ptrpalavra;
        ptrpalavra = strtok(NULL, " ");
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        buscar_traducao(l, palavras[j]);
    }
}

void liberarLista(Lista* l){
    Lista* aux;
    while (l!=NULL)
    {
        aux = l;
        l = l->prox;
        free(aux);
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Limpa o buffer de entrada
}

int main(){
    Lista *dicionario = inicializar();
    char port[50], ing[50], texto[200], palavra[50];;
    int opcao;
    

    do {
        printf("\nMenu:\n");
        printf("1. Inserir traducao\n");
        printf("2. Remover traducao\n");
        printf("3. Buscar traducao\n");
        printf("4. Traduzir texto\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            case 1:
                printf("Digite a palavra em portugues: ");
                fgets(port, sizeof(port), stdin);
                port[strcspn(port, "\n")] = '\0';

                printf("Digite a traducao em ingles: ");
                fgets(ing, sizeof(ing), stdin);
                ing[strcspn(ing, "\n")] = '\0';

                inserir_traducao(&dicionario, port, ing);
                printf("Traducao inserida com sucesso!\n");
                break;

            case 2:
                printf("Digite a palavra em portugues para remover: ");
                fgets(palavra, sizeof(palavra), stdin);
                palavra[strcspn(palavra, "\n")] = '\0';

                remover_traducao(&dicionario, palavra);
                break;

            case 3:
                printf("Digite a palavra para buscar (portugues ou ingles): ");
                fgets(port, sizeof(port), stdin);
                port[strcspn(port, "\n")] = '\0';

                buscar_traducao(dicionario, port);
                break;

            case 4:
                printf("Digite o texto a ser traduzido: ");
                fgets(texto, sizeof(texto), stdin);
                texto[strcspn(texto, "\n")] = '\0';

                traducao_texto(dicionario, texto);
                break;

            case 5:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 5);

    liberarLista(dicionario);
    return 0;
    
}
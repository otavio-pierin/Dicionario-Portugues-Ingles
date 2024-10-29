#ifndef DICIONARIO_H
#define DICIONARIO_H

typedef struct traducao
{
    char portugues[50];
    char ingles[50];
}Traducao;

typedef struct Lista
{
    Traducao dado;
    struct Lista *prox;
}Lista;

Lista* inicializar();
void inserir_traducao(Lista** l, char *port, char *ing);
void remover_traducao(Lista** l, char *palavra);
void buscar_traducao(Lista* l, char *txt);
void traducao_texto(Lista* l, char *txt);
void liberarLista(Lista* l);

#endif
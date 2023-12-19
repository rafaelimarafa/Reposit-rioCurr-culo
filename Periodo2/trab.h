#ifndef TRAB_H
#define TRAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NO
{
    char str[50];
    int valor;
    struct NO *esq;
    struct NO *dir;
} NO;

typedef struct NO *ABP;

NO *alocarNO()
{
    return (NO *)malloc(sizeof(NO));
}

void liberarNO(NO *q)
{
    free(q);
}

ABP *criaABP()
{
    ABP *raiz = (ABP *)malloc(sizeof(ABP));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int estaVazia(ABP *raiz)
{
    if (raiz == NULL)
        return 0;
    return (*raiz == NULL);
}

int insereRec(NO **raiz, char *str, int valor)
{
    if (*raiz == NULL)
    {
        NO *novo = alocarNO();
        if (novo == NULL)
            return 0;
        strcpy(novo->str, str);
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
    }
    else
    {
        if (!strcmp((*raiz)->str, str))
        {
            printf("Elemento Existente!\n");
            return 0;
        }
        if (strcmp(str, (*raiz)->str) < 0)
            return insereRec(&(*raiz)->esq, str, valor);
        else if (strcmp(str, (*raiz)->str) > 0)
            return insereRec(&(*raiz)->dir, str, valor);
    }
    return 1;
}

int insereElem(ABP *raiz, char *str, int valor)
{
    if (raiz == NULL)
        return 0;
    return insereRec(raiz, str, valor);
}

void em_ordem(NO *raiz)
{
    if (raiz != NULL)
    {
        em_ordem(raiz->esq);
        printf("[%s, %d] ", raiz->str, raiz->valor);
        em_ordem(raiz->dir);
    }
}

void imprime(ABP *raiz)
{
    if (raiz == NULL)
        return;
    if (estaVazia(raiz))
    {
        printf("Arvore Vazia!\n");
        return;
    }
    printf("\nEm Ordem: ");
    em_ordem(*raiz);
    printf("\n");
}

int pesquisaRec(NO **raiz, char *str)
{
    if (*raiz == NULL)
    {
        printf("Palavra %s NAO encontrado!\n", str);
        return 0;
    }
    if (strcmp((*raiz)->str, str) == 0)
    {
        printf("Palavra %s encontrada, valor: %d\n", str, (*raiz)->valor);
        return 1;
    }
    if (strcmp((*raiz)->str, str) > 0)
    {
        return pesquisaRec(&(*raiz)->esq, str);
    }
    else
        return pesquisaRec(&(*raiz)->dir, str);
}

typedef struct Hash
{
    ABP **tabela;
} Hash;

Hash *criaHash(int t)
{
    Hash *h;
    h = (Hash *)malloc(sizeof(Hash));
    if (h != NULL)
    {
        h->tabela = (ABP **)malloc(26 * sizeof(ABP *));
        if (h->tabela == NULL)
            return NULL;
        int i;
        for (i = 0; i < t; i++)
            h->tabela[i] = NULL;
    }
    return h;
}

int insereHashABP(Hash *h, char *str, int valor)
{
    if (h == NULL)
        return 0;
    int pos = str[0] - 'a';
    if (h->tabela[pos] == NULL)
        h->tabela[pos] = criaABP();
    insereElem(h->tabela[pos], str, valor);
    return 1;
}

void imprimeHash(Hash *h)
{
    if (h == NULL)
        return;
    int i;
    for (i = 0; i < 26; i++)
    {
        if (h->tabela[i] == NULL)
            printf("NULL\n");
        else
            imprime(h->tabela[i]);
    }
}

int buscaHashABP(Hash *h, char *str)
{
    if (h == NULL)
        return 0;
    int pos = str[0] - 'a';
    if (h->tabela[pos] == NULL)
    {
        return 0;
    }
    return pesquisaRec(h->tabela[pos], str);
}

#endif
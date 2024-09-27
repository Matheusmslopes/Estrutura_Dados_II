/*Nome: Matheus Muruci de Souza Lopes*/

#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 0
#define PRETO 1

struct Node
{
    int valor;
    int cor;
    struct Node *esquerda;
    struct Node *direita;
    struct Node *pai;
};

typedef struct Node No;

/* Função pra criar um novo nó vermelho com o valor fornecido */
No *CriarNode(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->cor = VERMELHO;
    novoNo->esquerda = novoNo->direita = novoNo->pai = NULL;
    return novoNo;
}

/* Função para fazer a rotação a esquerda*/
void RotacaoEsquerda(No **raiz, No *noRotacionado)
{
    No *noAuxiliar = noRotacionado->direita;
    noRotacionado->direita = noAuxiliar->esquerda;
    if (noAuxiliar->esquerda != NULL)
        noAuxiliar->esquerda->pai = noRotacionado;
    noAuxiliar->pai = noRotacionado->pai;
    if (noRotacionado->pai == NULL)
        *raiz = noAuxiliar;
    else if (noRotacionado == noRotacionado->pai->esquerda)
        noRotacionado->pai->esquerda = noAuxiliar;
    else
        noRotacionado->pai->direita = noAuxiliar;
    noAuxiliar->esquerda = noRotacionado;
    noRotacionado->pai = noAuxiliar;
}

/* Função para fazer a rotação a direita*/
void RotacaoDireita(No **raiz, No *noRotacionado)
{
    No *noAuxiliar = noRotacionado->esquerda;
    noRotacionado->esquerda = noAuxiliar->direita;
    if (noAuxiliar->direita != NULL)
        noAuxiliar->direita->pai = noRotacionado;
    noAuxiliar->pai = noRotacionado->pai;
    if (noRotacionado->pai == NULL)
        *raiz = noAuxiliar;
    else if (noRotacionado == noRotacionado->pai->direita)
        noRotacionado->pai->direita = noAuxiliar;
    else
        noRotacionado->pai->esquerda = noAuxiliar;
    noAuxiliar->direita = noRotacionado;
    noRotacionado->pai = noAuxiliar;
}

/* Função para corrigir a árvore RedBlack após a inserção de um nó */
void CorrigirViolacao(No **raiz, No *noAjustado)
{
    while (noAjustado != *raiz && noAjustado->pai->cor == VERMELHO)
    {
        if (noAjustado->pai == noAjustado->pai->pai->esquerda)
        {
            No *tio = noAjustado->pai->pai->direita;
            if (tio != NULL && tio->cor == VERMELHO)
            {
                noAjustado->pai->cor = PRETO;
                tio->cor = PRETO;
                noAjustado->pai->pai->cor = VERMELHO;
                noAjustado = noAjustado->pai->pai;
            }
            else
            {
                if (noAjustado == noAjustado->pai->direita)
                {
                    noAjustado = noAjustado->pai;
                    RotacaoEsquerda(raiz, noAjustado);
                }
                noAjustado->pai->cor = PRETO;
                noAjustado->pai->pai->cor = VERMELHO;
                RotacaoDireita(raiz, noAjustado->pai->pai);
            }
        }
        else
        {
            No *tio = noAjustado->pai->pai->esquerda;
            if (tio != NULL && tio->cor == VERMELHO)
            {
                noAjustado->pai->cor = PRETO;
                tio->cor = PRETO;
                noAjustado->pai->pai->cor = VERMELHO;
                noAjustado = noAjustado->pai->pai;
            }
            else
            {
                if (noAjustado == noAjustado->pai->esquerda)
                {
                    noAjustado = noAjustado->pai;
                    RotacaoDireita(raiz, noAjustado);
                }
                noAjustado->pai->cor = PRETO;
                noAjustado->pai->pai->cor = VERMELHO;
                RotacaoEsquerda(raiz, noAjustado->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

/* Função para inserir um novo nó na árvore RedBlack */
void Inserir(No **raiz, int valor)
{
    No *novoNo = CriarNode(valor);
    No *noPai = NULL;
    No *noAtual = *raiz;

    while (noAtual != NULL)
    {
        noPai = noAtual;
        if (novoNo->valor < noAtual->valor)
            noAtual = noAtual->esquerda;
        else
            noAtual = noAtual->direita;
    }
    novoNo->pai = noPai;
    if (noPai == NULL)
        *raiz = novoNo;
    else if (novoNo->valor < noPai->valor)
        noPai->esquerda = novoNo;
    else
        noPai->direita = novoNo;

    CorrigirViolacao(raiz, novoNo);
}

/* Função para buscar um nó com o valor fornecido na árvore RedBlack */
No *Buscar(No *raiz, int valor)
{
    while (raiz != NULL && valor != raiz->valor)
    {
        if (valor < raiz->valor)
            raiz = raiz->esquerda;
        else
            raiz = raiz->direita;
    }
    return raiz;
}

/* Encontra o nó com o menor valor(mais a esquerda) da subárvore a direita */
No *Minimo(No *no)
{
    while (no->esquerda != NULL)
        no = no->esquerda;
    return no;
}

/* Função para corrigir a árvore RedBlack depois da remoção de um nó */
void CorrigirRemocao(No **raiz, No *noAjustado)
{
    while (noAjustado != *raiz && noAjustado->cor == PRETO)
    {
        if (noAjustado == noAjustado->pai->esquerda)
        {
            No *noIrmao = noAjustado->pai->direita;
            if (noIrmao->cor == VERMELHO)
            {
                noIrmao->cor = PRETO;
                noAjustado->pai->cor = VERMELHO;
                RotacaoEsquerda(raiz, noAjustado->pai);
                noIrmao = noAjustado->pai->direita;
            }
            if ((noIrmao->esquerda == NULL || noIrmao->esquerda->cor == PRETO) &&
                (noIrmao->direita == NULL || noIrmao->direita->cor == PRETO))
            {
                noIrmao->cor = VERMELHO;
                noAjustado = noAjustado->pai;
            }
            else
            {
                if (noIrmao->direita == NULL || noIrmao->direita->cor == PRETO)
                {
                    noIrmao->esquerda->cor = PRETO;
                    noIrmao->cor = VERMELHO;
                    RotacaoDireita(raiz, noIrmao);
                    noIrmao = noAjustado->pai->direita;
                }
                noIrmao->cor = noAjustado->pai->cor;
                noAjustado->pai->cor = PRETO;
                if (noIrmao->direita != NULL)
                    noIrmao->direita->cor = PRETO;
                RotacaoEsquerda(raiz, noAjustado->pai);
                noAjustado = *raiz;
            }
        }
        else
        {
            No *noIrmao = noAjustado->pai->esquerda;
            if (noIrmao->cor == VERMELHO)
            {
                noIrmao->cor = PRETO;
                noAjustado->pai->cor = VERMELHO;
                RotacaoDireita(raiz, noAjustado->pai);
                noIrmao = noAjustado->pai->esquerda;
            }
            if ((noIrmao->direita == NULL || noIrmao->direita->cor == PRETO) &&
                (noIrmao->esquerda == NULL || noIrmao->esquerda->cor == PRETO))
            {
                noIrmao->cor = VERMELHO;
                noAjustado = noAjustado->pai;
            }
            else
            {
                if (noIrmao->esquerda == NULL || noIrmao->esquerda->cor == PRETO)
                {
                    noIrmao->direita->cor = PRETO;
                    noIrmao->cor = VERMELHO;
                    RotacaoEsquerda(raiz, noIrmao);
                    noIrmao = noAjustado->pai->esquerda;
                }
                noIrmao->cor = noAjustado->pai->cor;
                noAjustado->pai->cor = PRETO;
                if (noIrmao->esquerda != NULL)
                    noIrmao->esquerda->cor = PRETO;
                RotacaoDireita(raiz, noAjustado->pai);
                noAjustado = *raiz;
            }
        }
    }
    noAjustado->cor = PRETO;
}

/* Função para realizar a troca dos nós*/
void SubstituirNo(No **raiz, No *noOriginal, No *noSubstituto)
{
    if (noOriginal->pai == NULL)
        *raiz = noSubstituto;
    else if (noOriginal == noOriginal->pai->esquerda)
        noOriginal->pai->esquerda = noSubstituto;
    else
        noOriginal->pai->direita = noSubstituto;
    if (noSubstituto != NULL)
        noSubstituto->pai = noOriginal->pai;
}

/* Função para remover um nó com o valor fornecido da árvore RedBlack */
void Remover(No **raiz, int valor)
{
    No *noRemover = Buscar(*raiz, valor);
    if (noRemover == NULL)
        return;

    No *noSubstituto = noRemover;
    int corOriginal = noSubstituto->cor;
    No *noAjustado;

    if (noRemover->esquerda == NULL)
    {
        noAjustado = noRemover->direita;
        SubstituirNo(raiz, noRemover, noRemover->direita);
    }
    else if (noRemover->direita == NULL)
    {
        noAjustado = noRemover->esquerda;
        SubstituirNo(raiz, noRemover, noRemover->esquerda);
    }
    else
    {
        noSubstituto = Minimo(noRemover->direita);
        corOriginal = noSubstituto->cor;
        noAjustado = noSubstituto->direita;
        if (noSubstituto->pai == noRemover)
        {
            if (noAjustado != NULL)
                noAjustado->pai = noSubstituto;
        }
        else
        {
            SubstituirNo(raiz, noSubstituto, noSubstituto->direita);
            noSubstituto->direita = noRemover->direita;
            noSubstituto->direita->pai = noSubstituto;
        }
        SubstituirNo(raiz, noRemover, noSubstituto);
        noSubstituto->esquerda = noRemover->esquerda;
        noSubstituto->esquerda->pai = noSubstituto;
        noSubstituto->cor = noRemover->cor;
    }
    free(noRemover);
    if (corOriginal == PRETO)
        CorrigirRemocao(raiz, noAjustado);
}

void EmOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        EmOrdem(raiz->esquerda);
        if (raiz->cor == VERMELHO)
            printf("%d RED\n", raiz->valor);
        else
            printf("%d BLK\n", raiz->valor);
        EmOrdem(raiz->direita);
    }
}

void ImprimeArvoreRB(No *raiz, int b)
{
    if (raiz != NULL)
    {
        ImprimeArvoreRB(raiz->direita, b + 1);
        for (int i = 0; i < b; i++)
            printf("       ");
        if (raiz->cor == VERMELHO)
            printf("\033[31m%d\033[0m\n\n", raiz->valor);
        else
            printf("%d\n\n", raiz->valor);
        ImprimeArvoreRB(raiz->esquerda, b + 1);
    }
}

int main()
{
    No *raiz = NULL;
    int vetor[] = {12, 31, 20, 17, 11, 8, 3, 24, 15, 33};
    int tam = sizeof(vetor) / sizeof(vetor[0]);

    for (int i = 0; i < tam; i++){
        Inserir(&raiz, vetor[i]);
    }


    printf("Árvore Red-Black após inserções:\n");
    ImprimeArvoreRB(raiz, 3);
    EmOrdem(raiz);
    
    int noBuscado = 8;
    No *resultadoBusca = Buscar(raiz, noBuscado);

    if (resultadoBusca != NULL){
        printf("\nValor %d encontrado na árvore!\n", noBuscado);
    }
    else{
        printf("\nValor %d não encontrado na árvore!\n", noBuscado);
    }

    Remover(&raiz, 20);
    printf("\nÁrvore Red-Black após remoção do valor 20:\n");
    ImprimeArvoreRB(raiz, 3);
    EmOrdem(raiz);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int chave, prioridade;
    struct Node *esquerda, *direita;
} Node;

Node* NovoNo(int chave) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->chave = chave;
    temp->prioridade = rand() % 100;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

Node* RotacaoDireita(Node* No) {
    Node* auxilixar = No->esquerda;
    Node* temp = auxilixar->direita;
    
    auxilixar->direita = No;
    No->esquerda = temp;
    
    return auxilixar;
}

Node* RotacaoEsquerda(Node* No) {
    Node* auxiliar = No->direita;
    Node* temp = auxiliar->esquerda;
    
    // Rotação
    auxiliar->esquerda = No;
    No->direita = temp;
    
    return auxiliar;
}

Node* InserirNo(Node* raiz, int chave) {
    if (!raiz)
        return NovoNo(chave);

    if (chave <= raiz->chave) {
        raiz->esquerda = InserirNo(raiz->esquerda, chave);

        if (raiz->esquerda && raiz->esquerda->prioridade > raiz->prioridade)
            raiz = RotacaoDireita(raiz);
    } else {
        raiz->direita = InserirNo(raiz->direita, chave);

        if (raiz->direita && raiz->direita->prioridade > raiz->prioridade)
            raiz = RotacaoEsquerda(raiz);
    }

    return raiz;
}

Node* RemoverNo(Node* raiz, int chave) {
    if (!raiz)
        return raiz;

    if (chave < raiz->chave)
        raiz->esquerda = RemoverNo(raiz->esquerda, chave);
    else if (chave > raiz->chave)
        raiz->direita = RemoverNo(raiz->direita, chave);
    else {
        if (!raiz->esquerda) {
            Node* temp = raiz->direita;
            free(raiz);
            raiz = temp;
        } else if (!raiz->direita) {
            Node* temp = raiz->esquerda;
            free(raiz);
            raiz = temp;
        } else {
            if (raiz->esquerda->prioridade > raiz->direita->prioridade) {
                raiz = RotacaoDireita(raiz);
                raiz->direita = RemoverNo(raiz->direita, chave);
            } else {
                raiz = RotacaoEsquerda(raiz);
                raiz->esquerda = RemoverNo(raiz->esquerda, chave);
            }
        }
    }

    return raiz;
}

void printTreap(Node* raiz, int espaco) {
    int COUNT = 10;

    if (raiz == NULL)
        return;

    espaco += COUNT;

    printTreap(raiz->direita, espaco);

    printf("\n");
    for (int i = COUNT; i < espaco; i++)
        printf(" ");
    printf("%d (P:%d)\n", raiz->chave, raiz->prioridade);

    printTreap(raiz->esquerda, espaco);
}

int main() {
    srand(time(0)); 

    Node* raiz = NULL;
    
    raiz = InserirNo(raiz, 50);
    raiz = InserirNo(raiz, 30);
    raiz = InserirNo(raiz, 20);
    raiz = InserirNo(raiz, 40);
    raiz = InserirNo(raiz, 70);
    raiz = InserirNo(raiz, 60);
    raiz = InserirNo(raiz, 80);

    printf("Visualização da árvore Treap:\n");
    printTreap(raiz, 0);

    return 0;
}
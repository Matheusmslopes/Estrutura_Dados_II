// Nome: Matheus Muruci de Souza Lopes

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int chave, prioridade;
    struct Node *esquerda, *direita;
} Node;

// Função para criar um novo nó. A chave é definida pelo usuário e a prioridade é aleatoria
Node* NovoNo(int chave) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->chave = chave;
    temp->prioridade = rand() % 100;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

// Função de rotação a direita para garantir que a propriedade de heap seja mantida
Node* RotacaoDireita(Node* No) {
    Node* auxiliar = No->esquerda;
    Node* temp = auxiliar->direita;
    
    auxiliar->direita = No;
    No->esquerda = temp;
    
    return auxiliar;
}

// Função de rotação a esquerda para garantir que a propriedade de heap seja mantida
Node* RotacaoEsquerda(Node* No) {
    Node* auxiliar = No->direita;
    Node* temp = auxiliar->esquerda;
    
    auxiliar->esquerda = No;
    No->direita = temp;
    
    return auxiliar;
}

// Função para inserir um nó
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

// Função para buscar um nó pela chave
Node* BuscarNo(Node* raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    if (chave < raiz->chave)
        return BuscarNo(raiz->esquerda, chave);
    else
        return BuscarNo(raiz->direita, chave);
}

// Função para remover um nó 
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
    int qntd, valor;

    // Solicita ao usuário a quantidade de nós a ser inserida na Treap.
    printf("Digite a quantidade de nós a ser inserido: ");
    scanf("%i", &qntd);

    for (int i = 0; i < qntd; i++) {
        printf("Qual o valor do nó n°%i: ", i + 1);
        scanf("%i", &valor);
        raiz = InserirNo(raiz, valor);
    }

    // Exibe a árvore Treap após todas as inserções.
    printf("\nÁrvore Treap após inserções:\n");
    printTreap(raiz, 0);

    // Opção de busca de um nó na árvore
    printf("\nDeseja buscar um nó? (1 para Sim, 0 para Não): ");
    int opcao_busca;
    scanf("%d", &opcao_busca);

    if (opcao_busca == 1) {
        printf("Digite a chave para buscar: ");
        scanf("%d", &valor);
        Node* resultado = BuscarNo(raiz, valor);
        if (resultado)
            printf("Nó encontrado: %d (Prioridade: %d)\n", resultado->chave, resultado->prioridade);
        else
            printf("Nó com chave %d não encontrado.\n", valor);
    }

    // Opção de remoção de um nó da Treap.
    printf("\nDeseja remover um nó? (1 para Sim, 0 para Não): ");
    int opcao_remocao;
    scanf("%d", &opcao_remocao);

    if (opcao_remocao == 1) {
        printf("Digite a chave para remover: ");
        scanf("%d", &valor);
        raiz = RemoverNo(raiz, valor);
        printf("\nÁrvore Treap após remoção:\n");
        printTreap(raiz, 0);
    }

    return 0;
}
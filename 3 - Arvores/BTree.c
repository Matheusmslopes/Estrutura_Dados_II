// Nome: Matheus Muruci de Souza Lopes

#include <stdio.h>
#include <stdlib.h>

// Ordem da árvore
#define GrauArvore 4 

struct Node *CriarNode(int folha);
struct Node *Inserir(struct Node *raiz, int chave);
void InserirEmNaoCheio(struct Node *node, int chave);
void SepararFilho(struct Node *pai, int index);
struct Node *Buscar(struct Node *node, int chave);
void PrintTree(struct Node *node, int level);

struct Node {
    int numChave;
    int folha;
    int chave[GrauArvore - 1];
    struct Node *filho[GrauArvore];
};

struct Node *CriarNode(int folha) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->folha = folha;
    node->numChave = 0;
    for (int i = 0; i < GrauArvore; i++)
        node->filho[i] = NULL;
    return node;
}

struct Node *Inserir(struct Node *raiz, int chave) {
    if (raiz == NULL) {
        raiz = CriarNode(1);
        raiz->chave[0] = chave;
        raiz->numChave = 1;
    } else {
        if (raiz->numChave == GrauArvore - 1) {
            struct Node *novaRaiz = CriarNode(0);
            novaRaiz->filho[0] = raiz;
            SepararFilho(novaRaiz, 0);
            int i = 0;
            if (chave > novaRaiz->chave[0]) {
                i++;
            }
            InserirEmNaoCheio(novaRaiz->filho[i], chave);
            raiz = novaRaiz;
        } else {
            InserirEmNaoCheio(raiz, chave);
        }
    }
    return raiz;
}

void InserirEmNaoCheio(struct Node *node, int chave) {
    int i = node->numChave - 1;

    if (node->folha) { 
        while (i >= 0 && chave < node->chave[i]) {
            node->chave[i + 1] = node->chave[i]; 
            i--;
        }
        node->chave[i + 1] = chave; 
        node->numChave++; 
    } else {
        while (i >= 0 && chave < node->chave[i]) {
            i--;
        }
        i++;
        if (node->filho[i]->numChave == GrauArvore - 1) { 
            SepararFilho(node, i);
            if (chave > node->chave[i]) {
                i++;
            }
        }
        InserirEmNaoCheio(node->filho[i], chave);
    }
}

void SepararFilho(struct Node *pai, int index) {
    struct Node *filho = pai->filho[index];  
    struct Node *node = CriarNode(filho->folha);

    for (int i = 0; i < GrauArvore / 2 - 1; i++) {
        node->chave[i] = filho->chave[i + GrauArvore / 2];
    }
    if (!filho->folha) {
        for (int i = 0; i < GrauArvore / 2; i++) {
            node->filho[i] = filho->filho[i + GrauArvore / 2]; 
        }
    }
    filho->numChave = GrauArvore / 2 - 1; 
    node->numChave = GrauArvore / 2 - 1; 

    for (int i = pai->numChave; i > index; i--) {
        pai->filho[i + 1] = pai->filho[i]; 
    }
    pai->filho[index + 1] = node; 

    for (int i = pai->numChave - 1; i >= index; i--) {
        pai->chave[i + 1] = pai->chave[i]; 
    }
    pai->chave[index] = filho->chave[GrauArvore / 2 - 1]; 
    pai->numChave++;
}

// Função para buscar uma chave na árvore B
struct Node *Buscar(struct Node *node, int chave) {
    int i = 0;
    while (i < node->numChave && chave > node->chave[i]) {
        i++;
    }
    
    if (i < node->numChave && node->chave[i] == chave) {
        return node;
    }
    
    if (node->folha) {
        return NULL;
    }
    
    
    return Buscar(node->filho[i], chave);
}

void PrintTree(struct Node *node, int level) {
    if (node == NULL) return;

    for (int i = 0; i < level; i++) {
        printf("   ");
    }

    printf("|");
    for (int i = 0; i < node->numChave; i++) {
        printf(" %i ", node->chave[i]);
    }
    printf("|\n");

    if (!node->folha) {
        for (int i = 0; i <= node->numChave; i++) {
            PrintTree(node->filho[i], level + 1);
        }
    }
}

int main() {
    struct Node *raiz = NULL;
    int qntd, valor, chave;

    // Solicita a quantidade de nós que o usuário deseja inserir
    printf("Quantos nós você quer inserir: ");
    scanf("%i", &qntd);

    // Insere os valores fornecidos pelo usuário na árvore B
    for (int i = 0; i < qntd; i++) {
        printf("Qual o valor do nó n°%i: ", i + 1);
        scanf("%i", &valor);
        raiz = Inserir(raiz, valor);
    }

    printf("\nÁrvore B após inserções:\n");
    PrintTree(raiz, 0);

    // Realiza a busca pelo nó que o usuário desejar
    printf("\nDigite o valor do nó que deseja buscar: ");
    scanf("%i", &chave);
    if (Buscar(raiz, chave) != NULL) {
        printf("Nó %i encontrado.\n", chave);
    } else {
        printf("Nó %i não encontrado.\n", chave);
    }

    return 0;
}
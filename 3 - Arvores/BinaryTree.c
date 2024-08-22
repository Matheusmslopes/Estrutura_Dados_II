#include <stdio.h>
#include <stdlib.h>

struct Node {
  int info;
  struct Node *direita;
  struct Node *esquerda;
};

struct Node *CriarNode(int valor) {
  struct Node *NovoNode = (struct Node *)malloc(sizeof(struct Node));

  if (NovoNode == NULL) {
    printf("Erro ao criar novo nó");
    exit(1);
  }

  NovoNode->info = valor;
  NovoNode->direita = NULL;
  NovoNode->esquerda = NULL;

  return NovoNode;
}

struct Node *encontrarMinimo(struct Node *raiz) {
  struct Node *minimo = raiz;
  while (minimo->esquerda != NULL) {
    minimo = minimo->esquerda;
  }
  return minimo;
}

struct Node *Inserir(struct Node *raiz, int valor) {
  if (raiz == NULL) {
    raiz = CriarNode(valor);
  } else {
    if (valor >= raiz->info) {
      raiz->direita = Inserir(raiz->direita, valor);
    } else {
      raiz->esquerda = Inserir(raiz->esquerda, valor);
    }
  }
  return raiz;
}

struct Node *Pesquisar(struct Node *raiz, int valor) {
  struct Node *Pesquisado = raiz;
  if (raiz == NULL) {
    printf("Arvore não existe");
    exit(1);
  }
  while (Pesquisado != NULL) {
    if (Pesquisado->info == valor) {
      printf("O nó de valor %d foi encontrado \n", valor);
      return Pesquisado;
    } else if (valor > Pesquisado->info) {
      Pesquisado = Pesquisado->direita;
    } else {
      Pesquisado = Pesquisado->esquerda;
    }
  }
  return Pesquisado;
}

struct Node *Deletar(struct Node *raiz, int valor) {
  struct Node *Deletado = raiz;
  if (raiz == NULL) {
    printf("Arvore não existe");
    exit(1);
  }

  if (valor < raiz->info) {
    raiz->esquerda = Deletar(raiz->esquerda, valor);
  } else if (valor > raiz->info) {
    raiz->direita = Deletar(raiz->direita, valor);
  } else {
    struct Node *tmp;

    if (raiz->direita == NULL) {
      tmp = raiz->esquerda;
      free(tmp);
      //printf("Deletou \n");
    } else if (raiz->esquerda == NULL) {
      tmp = raiz->direita;
      free(tmp);
      //printf("Deletou 2 \n");
    } else {
      tmp = encontrarMinimo(raiz->direita);
      raiz->info = tmp->info;
      raiz->direita = Deletar(raiz->direita, tmp->info);
      //printf("Deletou 3 \n");
    }
  }
  return raiz;
}

int main(void) {
  struct Node *raiz = NULL;

  int qntd;

  printf("Quantos nós você quer inserir: ");
  scanf("%i", &qntd);

  for (int i = 0; i < qntd; i++) {
    raiz = Inserir(raiz, i + 1);
  }

  Pesquisar(raiz, 3);
  Deletar(raiz, 10);
  return 0;
}
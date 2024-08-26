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
    printf("Erro ao criar novo nó \n");
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
    printf("Arvore não existe \n");
    return NULL;
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
  printf("O nó de valor %d não foi encontrado \n", valor);
  return Pesquisado;
}

struct Node *Deletar(struct Node *raiz, int valor) {
  if (raiz == NULL) {
    printf("Arvore não existe \n");
    return NULL;
  }

  if (valor < raiz->info) {
    raiz->esquerda = Deletar(raiz->esquerda, valor);
  } else if (valor > raiz->info) {
    raiz->direita = Deletar(raiz->direita, valor);
  } else {
    if (raiz->direita == NULL) {
      struct Node *tmp = raiz->esquerda;
      free(raiz);
      printf("o nó com valor %i foi deletado \n", valor);
      return tmp;
    } else if (raiz->esquerda == NULL) {
      struct Node *tmp = raiz->direita;
      free(raiz);
      printf("o nó com valor %i foi deletado \n", valor);
      return tmp;
    } else {
      struct Node *tmp = encontrarMinimo(raiz->direita);
      raiz->info = tmp->info;
      raiz->direita = Deletar(raiz->direita, tmp->info);
      printf("o nó com valor %i foi deletado \n", valor);
    }
    printf("Não foi encontrado o nó com valor %i para ser deletado \n", valor);
  }
  return raiz;
}

int main(void) {
  struct Node *raiz = NULL;

  int qntd, valor, pesquisar, deletar;

  printf("Quantos nós você quer inserir: ");
  scanf("%i", &qntd);

  for (int i = 0; i < qntd; i++) {
    printf("Qual o valor do nó n°%i: ", i + 1);
    scanf("%i", &valor);
    raiz = Inserir(raiz, valor);
  }

  printf("Qual nó você deseja pesquisar: ");
  scanf("%i", &pesquisar);

  Pesquisar(raiz, pesquisar);

  printf("Qual nó você deseja deletar: ");
  scanf("%i", &deletar);

  Deletar(raiz, deletar);

  return 0;
}
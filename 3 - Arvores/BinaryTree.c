/*Nome: Matheus Muruci de Souza Lopes*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura criada para
struct Node {
  int info;
  struct Node *direita;
  struct Node *esquerda;
};

// Função para criar um nó
struct Node *CriarNode(int valor) {
  struct Node *NovoNode = (struct Node *)malloc(sizeof(struct Node));

  if (NovoNode == NULL) {
    printf("Erro ao criar novo nó \n");
    return NULL;
  }

  NovoNode->info = valor;
  NovoNode->direita = NULL;
  NovoNode->esquerda = NULL;

  return NovoNode;
}

// Função para encontrar o nó com o menor valor da subarvore(Nesse caso ta pegando o valor mais a esquerda da subarvore a direita)
struct Node *encontrarMinimo(struct Node *raiz) {
  struct Node *minimo = raiz;
  while (minimo->esquerda != NULL) {
    minimo = minimo->esquerda;
  }
  return minimo;
}

// Função para inserir um valor na árvore
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

// Função para pesquisar um nó na árvore
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

// Função para deletar um nó da árvore
struct Node *Deletar(struct Node *raiz, int valor) {
  if (raiz == NULL) {
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
      return tmp;
    } else if (raiz->esquerda == NULL) {
      struct Node *tmp = raiz->direita;
      free(raiz);
      return tmp;
    } else {
      struct Node *tmp = encontrarMinimo(raiz->direita);
      raiz->info = tmp->info;
      raiz->direita = Deletar(raiz->direita, tmp->info);
    }
  }
  return raiz;
}

/*
Ambas as funções void imprimeNo(int c, int b)  e void mostraArvore(struct
Node *a, int b) foram pegas diretamente do diretório original do professor Gustavo
(https://github.com/gnrochabr/Estrutura_Dados_II/blob/main/3%20-%20Arvores/BinaryTree.c),
servindo apenas com o intuito de mostrar a árvore antes e depois do processo de exclusão. Na função void mostraArvore(struct Node *a, int b) Foram realizadas apenas mudanças para adequar o nome de uma variável e da struct.
*/

// Função auxiliar para imprimir um caractere precedido por uma quantidade específica de espaços
void imprimeNo(int c, int b) {
  int i;
  for (i = 0; i < b; i++)
    printf("   ");
  printf("%i\n", c);
}

// Função para exibir a árvore no formato esquerda-raiz-direita segundo Sedgewick
void mostraArvore(struct Node *a, int b) {
  if (a == NULL) {
    return;
  }
  mostraArvore(a->direita, b + 1);
  imprimeNo(a->info, b); // Convertendo para caractere para imprimir
  mostraArvore(a->esquerda, b + 1);
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

  // Serve para mostrar a árvore antes do processo de exclusão
  printf("\nAntes: \n");
  mostraArvore(raiz, 3);
  
  Deletar(raiz, deletar);

  // Serve para mostrar a árvore depois do processo de exclusão
  printf("\nDepois: \n");
  mostraArvore(raiz, 3);

  return 0;
}
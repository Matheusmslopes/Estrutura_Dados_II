/* Nome: Matheus Muruci de Souza Lopes */

#include <stdio.h>
#include <stdlib.h>

// Estrutura criada para representar um nó de uma árvore AVL
struct Node {
  int info;
  int altura;
  struct Node *esquerda;
  struct Node *direita;
};

typedef struct Node *AVL;

/*=====================================================================
                              Criação
======================================================================*/

// Função para criar uma nova árvore
AVL *CriarAVL() {
  AVL *raiz = (AVL *)malloc(sizeof(AVL));

  if (raiz != NULL)
    *raiz = NULL;

  return raiz;
}

// Função para criar um novo nó
struct Node *CriarNode(int valor) {
  struct Node *novoNode = (struct Node *)malloc(sizeof(struct Node));

  if (novoNode == NULL) {
    printf("Erro ao criar novo nó \n");
    return NULL;
  }

  novoNode->info = valor;
  novoNode->direita = NULL;
  novoNode->esquerda = NULL;
  novoNode->altura = 0;

  return novoNode;
}

/*=====================================================================
                             Verificação
======================================================================*/

// Função para saber a altura de um nó
int AlturaNode(struct Node *node) {
  if (node == NULL)
    return -1;
  else
    return node->altura;
}

//  Função para saber o fator de balanceamento
int FatorBalanceamento(struct Node *node) {
  if (node == NULL) {
    return 0;
  }
  return (AlturaNode(node->esquerda) - AlturaNode(node->direita));
}

// Função para saber qual maior altura que um nó vai ter.
int AlturaMaxima(int altura1, int altura2) {
  if (altura1 > altura2) {
    return altura1;
  } else {
    return altura2;
  }
}

// Função para encontrar o nó com o menor valor da subarvore(Nesse caso ta
// pegando o valor mais a esquerda da subarvore a direita)
struct Node *EncontrarMenor(struct Node *raiz) {
  struct Node *minimo = raiz;
  while (minimo->esquerda != NULL) {
    minimo = minimo->esquerda;
  }
  return minimo;
}

// Função para encontrar o nó com o maior valor da subarvore(Nesse caso ta
// pegando o valor mais a direita da subarvore a esquerda)
struct Node *EncontrarMaior(struct Node *raiz) {
  struct Node *maximo = raiz;
  while (maximo->direita != NULL) {
    maximo = maximo->direita;
  }
  return maximo;
}

/*=====================================================================
                            Rotação
======================================================================*/

struct Node *RotacaoSimplesEsquerda(struct Node *node) {
  struct Node *auxiliar;

  auxiliar = node->direita;
  node->direita = auxiliar->esquerda;
  auxiliar->esquerda = node;

  node->altura =
      AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita)) + 1;
  auxiliar->altura = AlturaMaxima(AlturaNode(auxiliar->direita),
                                  AlturaNode(auxiliar->esquerda)) +
                     1;

  return auxiliar;
}

struct Node *RotacaoSimplesDireita(struct Node *node) {
  struct Node *auxiliar;

  auxiliar = node->esquerda;
  node->esquerda = auxiliar->direita;
  auxiliar->direita = node;

  node->altura =
      AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita)) + 1;
  auxiliar->altura =
      AlturaMaxima(AlturaNode(auxiliar->esquerda), node->altura) + 1;

  return auxiliar;
}

// Rotação dupla a direita
struct Node *RotacaoLR(struct Node *node) {
  node->esquerda = RotacaoSimplesEsquerda(node->esquerda);
  return RotacaoSimplesDireita(node);
}

// Rotação dupla a esquerda
struct Node *RotacaoRL(struct Node *node) {
  node->direita = RotacaoSimplesDireita(node->direita);
  return RotacaoSimplesEsquerda(node);
}

/*=====================================================================
                            Inserção
======================================================================*/

struct Node *Inserir(struct Node *node, int valor) {
  // Inserção
  if (node == NULL) {
    return CriarNode(valor);
  }

  if (valor < node->info) {
    node->esquerda = Inserir(node->esquerda, valor);
  } else if (valor > node->info) {
    node->direita = Inserir(node->direita, valor);
  } else {
    return node;
  }

  // Atualiza a altura do nó pai
  node->altura =
      AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita)) + 1;

  // Balanceamento
  int fatorBalanceamentoNode = FatorBalanceamento(node);

  if (fatorBalanceamentoNode > 1 && valor < node->esquerda->info) {
    return RotacaoSimplesDireita(node);
  }
  if (fatorBalanceamentoNode < -1 && valor > node->direita->info) {
    return RotacaoSimplesEsquerda(node);
  }
  if (fatorBalanceamentoNode > 1 && valor > node->esquerda->info) {
    return RotacaoLR(node);
  }
  if (fatorBalanceamentoNode < -1 && valor < node->direita->info) {
    return RotacaoRL(node);
  }

  return node;
}

/*=====================================================================
                            Remoção
======================================================================*/

struct Node *Deletar(struct Node *node, int valor) {
  // Caso base
  if (node == NULL) {
    return node;
  }

  if (valor < node->info) {
    node->esquerda = Deletar(node->esquerda, valor);
  } else if (valor > node->info) {
    node->direita = Deletar(node->direita, valor);
  } else {
    // Nó com um ou nenhum filho
    if ((node->esquerda == NULL) || (node->direita == NULL)) {
      struct Node *auxiliar;

      if (node->esquerda != NULL) {
        auxiliar = node->esquerda;
      } else {
        auxiliar = node->direita;
      }

      if (auxiliar == NULL) {
        auxiliar = node;
        node = NULL;
      } else {
        *node = *auxiliar;
      }
      free(auxiliar);
    } else {
      // Nó com dois filhos: pega o menor valor da subárvore à direita
      struct Node *auxiliar = EncontrarMenor(node->direita);

      node->info = auxiliar->info;

      node->direita = Deletar(node->direita, auxiliar->info);
    }
  }

  if (node == NULL) {
    return node;
  }

  // Atualizar a altura do nó
  node->altura =
      1 + AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita));

  // Balancear o nó
  int fatorBalanceamentoNode = FatorBalanceamento(node);

  if (fatorBalanceamentoNode > 1 && FatorBalanceamento(node->esquerda) >= 0) {
    return RotacaoSimplesDireita(node);
  }

  if (fatorBalanceamentoNode > 1 && FatorBalanceamento(node->esquerda) < 0) {
    return RotacaoLR(node);
  }

  if (fatorBalanceamentoNode < -1 && FatorBalanceamento(node->direita) <= 0) {
    return RotacaoSimplesEsquerda(node);
  }

  if (fatorBalanceamentoNode < -1 && FatorBalanceamento(node->direita) > 0) {
    return RotacaoRL(node);
  }

  return node;
}

/*=====================================================================
                            Busca
======================================================================*/

struct Node *Pesquisar(struct Node *node, int valor) {
  if (node == NULL)
    return node;

  if (node->info == valor) {
    return node;
  } else if (valor < node->info) {
    return Pesquisar(node->esquerda, valor);
  } else {
    return Pesquisar(node->direita, valor);
  }
}

/*=====================================================================
                            Visualização
======================================================================*/

/*Ambas as funções void imprimeNo(int c, int b)  e void mostraArvore(struct
Node *a, int b) foram pegas diretamente do diretório original do professor
Gustavo
(https://github.com/gnrochabr/Estrutura_Dados_II/blob/main/3%20-%20Arvores/BinaryTree.c),
servindo apenas com o intuito de mostrar a árvore. Na função void
mostraArvore(struct Node *a, int b) Foram realizadas apenas mudanças para
adequar o nome de uma variável e da struct.*/

void imprimeNo(int c, int b) {
  for (int i = 0; i < b; i++) {
    printf("   ");
  }
  printf("%i\n", c);
}

void mostraArvore(struct Node *a, int b) {
  if (a != NULL) {
    mostraArvore(a->direita, b + 1);
    imprimeNo(a->info, b);
    mostraArvore(a->esquerda, b + 1);
  }
}

/*=====================================================================
                            Main
======================================================================*/

int main() {
  AVL *raizAVL = CriarAVL();

  // No final da main tem um código comentado que roda sem inserção do usuário

  // Bloco para inserção dos nós na árvore
  int qntd, valor;

  printf("Digite a quantidade de nós a ser inserido: ");
  scanf("%i", &qntd);

  // Inserção dos valores digitados pelo usuário.
  for (int i = 0; i < qntd; i++) {
    printf("Qual o valor do nó n°%i: ", i + 1);
    scanf("%i", &valor);
    *raizAVL = Inserir(*raizAVL, valor);
  }

  printf("\nÁrvore Original:\n\n");
  mostraArvore(*raizAVL, 0);

  // Bloco para fazer a pesquisa de algum nó na árvore
  int valorParaBuscar;
  printf("Qual o valor do nó para ser pesquisado: ");
  scanf("%i", &valorParaBuscar);
  struct Node *pesquisado = Pesquisar(*raizAVL, valorParaBuscar);

  if (pesquisado != NULL) {
    printf("\nValor %d encontrado na árvore!\n", valorParaBuscar);
  } else {
    printf("\nValor %d não encontrado na árvore.\n", valorParaBuscar);
  }

  // Bloco para excluir algum nó da árvore
  int valorParaDeletar;
  printf("Qual o valor do nó para ser deletado: ");
  scanf("%i", &valorParaDeletar);

  struct Node *deletado = Deletar(*raizAVL, valorParaDeletar);

  if (deletado != NULL) {
    printf("\nValor %d deletado da árvore!\n", valorParaDeletar);
  } else {
    printf("\nValor %d não encontrado na árvore.\n", valorParaDeletar);
  }

  mostraArvore(*raizAVL, 0);

  /*

  int vetor[12] = {30, 24, 20, 35, 27, 33, 38, 25, 22, 34, 40, 29};

  for (int i = 0; i < 12; i++) {
      *raizAVL = Inserir(*raizAVL, vetor[i]);
  }

  printf("\nÁrvore Original:\n\n");
  mostraArvore(*raizAVL, 0);

  int valorParaBuscar = 33;
  struct Node *resultado = Pesquisar(*raizAVL, valorParaBuscar);

  if (resultado != NULL) {
      printf("\nValor %d encontrado na árvore!\n", valorParaBuscar);
  } else {
      printf("\nValor %d não encontrado na árvore.\n", valorParaBuscar);
  }

  *raizAVL = Deletar(*raizAVL, 30);

  printf("\nDepois da remoção do 30:\n\n");
  mostraArvore(*raizAVL, 0);

  *raizAVL = Deletar(*raizAVL, 27);

  printf("\nDepois da remoção do 27:\n\n");
  mostraArvore(*raizAVL, 0); */

  return 0;
}
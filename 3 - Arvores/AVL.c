#include <stdio.h>
#include <stdlib.h>

struct Node{
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

int AlturaNode(struct Node *node){
  if (node == NULL)
    return -1;
  else
    return node->altura;
}

int FatorBalanceamento(struct Node *node){
  if (node == NULL){
    return 0;
  }
  return (AlturaNode(node->esquerda) - AlturaNode(node->direita));
}

int AlturaMaxima(int altura1, int altura2){
  if (altura1 > altura2){
    return altura1;
  } 
  else {
    return altura2;
  }
}

// Função para encontrar o nó com o menor valor da subarvore(Nesse caso ta pegando o valor mais a esquerda da subarvore a direita)
struct Node *EncontrarMenor(struct Node *raiz) {
  struct Node *minimo = raiz;
  while (minimo->esquerda != NULL) {
    minimo = minimo->esquerda;
  }
  return minimo;
}

// Função para encontrar o nó com o maior valor da subarvore(Nesse caso ta pegando o valor mais a direita da subarvore a esquerda)
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

  node->altura = AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita)) + 1;
  auxiliar->altura = AlturaMaxima(AlturaNode(auxiliar->direita), node->altura) + 1;

  return auxiliar;
}

struct Node *RotacaoSimplesDireita(struct Node *node) {
  struct Node *auxiliar;

  auxiliar = node->esquerda;
  node->esquerda = auxiliar->direita;
  auxiliar->direita = node;

  node->altura = AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita)) + 1;
  auxiliar->altura = AlturaMaxima(node->altura, AlturaNode(auxiliar->esquerda)) + 1;

  return auxiliar;
}

struct Node *RotacaoLR(struct Node *node) {
  node->esquerda = RotacaoSimplesEsquerda(node->esquerda);
  return RotacaoSimplesDireita(node);
}

struct Node *RotacaoRL(struct Node *node) {
  node->direita = RotacaoSimplesDireita(node->direita);
  return RotacaoSimplesEsquerda(node);
}

/*=====================================================================
                            Inserção
======================================================================*/

struct Node *Inserir(struct Node *node, int valor){
  // Inserção
  if (node == NULL){
    return CriarNode(valor);
  }

  if (valor == node->info){
    return node;
  } 
  else if (valor < node->info) {
    node->esquerda = Inserir(node->esquerda, valor);
  }
  else {
    node->direita = Inserir(node->direita, valor);
  }

  // Balanceamento
   node->altura = AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita)) + 1;

    int fatorBalanceamentoNode = FatorBalanceamento(node);

    if (fatorBalanceamentoNode > 1) {
      if (node->info < node->esquerda->info)
        return RotacaoSimplesEsquerda(node);
      else
        return RotacaoLR(node);
    } else if (fatorBalanceamentoNode < -1) {
      if (node->info > node->direita->info)
        return RotacaoSimplesDireita(node);
      else
        return RotacaoRL(node);
    }

    return node;
//}
}

/*=====================================================================
                            Remoção
======================================================================*/

struct Node *RemoverNode(struct Node *node) {
  struct Node *auxiliar;

  if (node->esquerda == NULL)
    auxiliar = node->direita;
  else {
    auxiliar = EncontrarMaior(node->esquerda);

    if (node->direita != NULL) {
      struct Node *auxiliar2 = node->esquerda;

      if (auxiliar != auxiliar2) {
        auxiliar2->direita = auxiliar->esquerda;
        auxiliar->esquerda = auxiliar2;
      }

      auxiliar->direita = node->direita;
    }
  }

  free(node);
  return auxiliar;
}

struct Node *Deletar(struct Node *node, int valor){
  // Remoção
  if (valor < node->info)
    node->esquerda = Deletar(node->esquerda, valor);
  else if (valor > node->info)
    node->direita = Deletar(node->direita, valor);
  else
    return RemoverNode(node);

  // Balanceamento a cada remoção
  node->altura = AlturaMaxima(AlturaNode(node->esquerda), AlturaNode(node->direita)) + 1;

  int fatorBalanceamentoNode = FatorBalanceamento(node);

  if (fatorBalanceamentoNode > 1) {
    if (node->info < node->esquerda->info)
      return RotacaoSimplesEsquerda(node);
    else
      return RotacaoLR(node);
  } else if (fatorBalanceamentoNode < -1) {
    if (node->info > node->direita->info)
      return RotacaoSimplesEsquerda(node);
    else
      return RotacaoRL(node);
  }

  return node;
}

/*=====================================================================
                            Busca
======================================================================*/

struct Node *Pesquisar(struct Node *node, int valor){
  if (node == NULL)
    return node;

  if (node == valor){
    return node;
  }
  else if (valor < node->info){
    return Pesquisar(node->esquerda, valor);
  }
  else{
    return Pesquisar(node->direita, valor);
  }
}

/*=====================================================================
                            Visualização
======================================================================*/

/*Ambas as funções void imprimeNo(int c, int b)  e void mostraArvore(struct
Node *a, int b) foram pegas diretamente do diretório original do professor Gustavo
(https://github.com/gnrochabr/Estrutura_Dados_II/blob/main/3%20-%20Arvores/BinaryTree.c),
servindo apenas com o intuito de mostrar a árvore. Na função void mostraArvore(struct Node *a, int b) Foram realizadas apenas mudanças para adequar o nome de uma variável e da struct.*/

// Função auxiliar para imprimir um caractere precedido por uma quantidade específica de espaços
void imprimeNo(int c, int b){
    int i;
    for (i = 0; i < b; i++) // Loop para imprimir espaços proporcionais à profundidade
        printf("   ");
    printf("%i\n", c); // Imprime o valor do nó com a devida indentação
}

// Função para exibir a árvore no formato esquerda-raiz-direita segundo Sedgewick
void mostraArvore(struct Node *a, int b){
    if (a != NULL) // Verifica se o nó atual não é nulo
    {
        // Chama a função recursivamente para percorrer a subárvore direita
        mostraArvore(a->direita, b + 1);
        // Imprime o nó atual com um espaçamento proporcional à sua profundidade
        imprimeNo(a->info, b);
        // Chama a função recursivamente para percorrer a subárvore esquerda
        mostraArvore(a->esquerda, b + 1);
    }
}

/*=====================================================================
                            Main
======================================================================*/

int main(){
  AVL *raizAVL = CriarAVL();

  int vetor[6] = {30, 9, 45, 27, 3, 18};

  //int vetor[12] = {30, 24, 20, 35, 27, 33, 38, 25, 22, 34, 40, 29};

  for (int i = 0; i < 6; i++) {
    *raizAVL = Inserir(*raizAVL, vetor[i]);
  }
  
  printf("\nÁrvore Original:\n\n");
  mostraArvore(*raizAVL, 0);

  *raizAVL = Deletar(*raizAVL, 30);

  printf("\ndepois da remoção do 30:\n\n");
  mostraArvore(*raizAVL, 0);

  *raizAVL = Deletar(*raizAVL, 27);

  printf("\ndepois da remoção do 27:\n\n");
  mostraArvore(*raizAVL, 0);

  return 0;
}
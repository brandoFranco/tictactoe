/*
 *
 * Universidade de Brasilia- UnB
 * Departamento de Ciencia da Computacao- CIC-UnB
 * Disciplina: Estruturas de Dados
 * Professor:
 * Turma D
 * Periodo: 2018/1
 *
 * Projeto 3
 * Autor: Brando Franco
 * Matricula:
 *
 *
 *
 *
 *
 * Arquivo de cabecalho contendo a definicao de estrutura no de uma arvore de jogos de um jogo da velha e os prototipos de funcoes para a sua manipulacao.
 *
 *
 *
 *
 *
 *
 */


#define _GAME_TREE_


/*
 *
 * Definicao de estrutura node que representa uma jogada em uma arvore de jogos.
 * Contendo o campo board, o tabuleiro no instante daquela jogada, um campo payoff, representando uma recompensa daquela jogada,
 * e um vetor de ponteiros, sons, representando cada possivel jogada posterior.
 *
 */

typedef struct node
{
	int board[9];
	int payoff;
	struct node * sons[9];
}
node;


// Funcao que verifica se o jogo chegou ao fim.
int won( node * );

// Funcao que verifica de quem sera a proxima vez.
int turn( node * );

// Funcao que cria um ponteira para o inicio da arvore de jogos.
node *newTree( int * );

// Funcao que insere nos a arvore de jogos, representando a insercao de possiveis jogadas.
void insert( node * );

// Funcao que atribui payoffs, recompensas a cada jogada, utilizando algoritmo minmax e backtracking.
void minMax( node *, int );

// Funcao que destroe a arvore, liberando assim memoria.
void liberar( node * );

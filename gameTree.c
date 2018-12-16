/*
 *
 * Universidade de Brasilia- UnB
 * Departamento de Ciencia da Computacao- CIC-UnB
 * Disciplina: Estruturas de Dados
 * Professor:
 * Turma
 * Periodo:
 *
 * Projeto 3
 * Autor: Brando Franco
 * Matricula:
 *
 *
 *
 *
 *
 *
 * Arquivo contendo as definicoes das funcoes para criacao e manipulacao de uma arvore de jogos de um jogo da velha.
 *
 *
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "gameTree.h"





/*
 *
 * Funcao que verifica se e o fim do jogo.
 * Caso seja, atribui payoffs.
 * Vitoria [+1], Derrota [-1], Empate [0].
 *
 */

int
won( node *ptr )
{

	if( (ptr -> board[0] == ptr -> board[1] ) && (ptr -> board[0] == ptr -> board[2]) && ( ptr -> board[0] == 0 || ptr -> board[0] == 1 ))
	{

		if( ptr -> board[0] == 0 )

			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;
			return 1;
	}

	if( (ptr -> board[0] == ptr -> board[3] ) && (ptr -> board[0] == ptr -> board[6]) && ( ptr -> board[0] == 0 ||  ptr -> board[0] == 1 ))
	{

		if( ptr -> board[0] == 0 )
			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;

			return 1;
	}
	if( (ptr -> board[2] == ptr -> board[5] ) && (ptr -> board[2] == ptr -> board[8]) && ( ptr -> board[2] == 0 ||  ptr -> board[2] == 1 ))
	{

		if( ptr -> board[2] == 0 )
			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;

		return 1;
	}
	if( (ptr -> board[6] == ptr -> board[7] ) && (ptr -> board[6] == ptr -> board[8]) && ( ptr -> board[6] == 0 ||  ptr -> board[6] == 1 ))
	{

		if( ptr -> board[6] == 0 )
			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;

		return 1;
	}
	if( (ptr -> board[4] == ptr -> board[0] ) && (ptr -> board[4] == ptr -> board[8]) && ( ptr -> board[4] == 0 ||  ptr -> board[4] == 1 ))
	{

		if( ptr -> board[4] == 0 )
			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;

		return 1;
	}
	if( (ptr -> board[4] == ptr -> board[2] ) && (ptr -> board[4] == ptr -> board[6]) && ( ptr -> board[4] == 0 ||  ptr -> board[4] == 1 ))
	{

		if( ptr -> board[4] == 0 )
			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;

		return 1;
	}
	if( (ptr -> board[4] == ptr -> board[1] ) && (ptr -> board[4] == ptr -> board[7]) && ( ptr -> board[4] == 0 ||  ptr -> board[4] == 1 ))
	{

		if( ptr -> board[4] == 0 )
			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;


		return 1;
	}
	if( (ptr -> board[4] == ptr -> board[3] ) && (ptr -> board[4] == ptr -> board[5]) && ( ptr -> board[4] == 0 ||  ptr -> board[4] == 1 ))
	{

		if( ptr -> board[4] == 0 )
			ptr -> payoff = 1;

		else
			ptr -> payoff = -1;

		return 1;
	}

	int c = 1;
       	for( int i = 0; i < 9 ; i++ )
		if( ptr -> board[i] == -1 )
			c = 0;

		if( c == 1 )
        	{
                	ptr -> payoff = 0;
                	return 1;
       		}
		else
			return 0;

}


/*
 *
 * Funcao que verifica de quem e a proxima vez.
 *
 */

int
turn( node *ptr )
{
	int a = 0;
	int b = 0;

	for( int i = 0; i < 9; i++ )
	{
		if( ptr -> board[i] == 0 )
			a++;

		else if( ptr -> board[i] == 1 )
			b++;
	}

	if( a == b )
		return 0;

	else if( a > b )
		return 1;

}





/*
 *
 * Funcao que recebe um vetor, representando o tabuleiro naquele instante do jogo e cria um
 * ponteiro para o inicio da arvore de jogos.
 *
 *
 */

node *newTree( int *current )
{
	node *ptr = ( node * ) malloc( sizeof( node ) );

	for( int i = 0; i < 9; i++ )
		ptr -> board[i] = current[i];

	return ptr;
}



/*
 *
 * Funcao que insere todas as proximas jogadas a arvore do jogo.
 *
 */

void
insert( node *ptr )
{

	if( ptr == NULL )
		return;
	else
	{
		if( won(ptr) )
		{

			for( int i = 0; i < 9; i++ )
				ptr -> sons[i] = NULL;
		}
		else
		{
			for( int i = 0; i < 9; i++ )
			{
				if(ptr -> board[i] != -1 )
					ptr -> sons[i] = NULL;
				else
				{
					ptr -> sons[i] = (node *) malloc( sizeof( node ) );
					for( int j = 0; j < 9; j++ )
						ptr -> sons[i] -> board[j] = ptr -> board[j];


					ptr -> sons[i] -> board[i] = turn( ptr );

				}
			}

			for( int i = 0; i < 9; i++ )
				insert( ptr -> sons[i] );
		}
	}
}






/*
 *
 * Funcao que utiliza do algoritmo minmax e o backtracking para atribuir payoffs a cada jogada da arvore de jogos.
 *
 *
 */

void
minMax( node *ptr, int comecar )
{
	if( won( ptr ))
		return;

	else
	{

		for( int i = 0; i < 9; i++ )
			if( ptr -> sons[i] != NULL )
				minMax( ptr -> sons[i], comecar);

		int count = 0;
		int minimo;
		int maximo;
		for( int i = 0; i < 9; i++ )
		{
			if( ptr -> sons[i] != NULL )
			{
				if( count == 0 )
				{
					minimo = ptr -> sons[i] -> payoff;
					maximo = ptr -> sons[i] -> payoff;
					count = 1;
				}
				else
				{
					if( ptr -> sons[i] -> payoff < minimo )
						minimo = ptr -> sons[i] -> payoff;

					if( ptr -> sons[i] -> payoff > maximo )
						maximo = ptr -> sons[i] -> payoff;
				}

			}
		}
		if( comecar )
		{
			if( turn( ptr ) )
				ptr -> payoff = minimo;

			else
				ptr -> payoff = maximo;
		}
		else
		{
			if( turn( ptr ) )
				ptr -> payoff = minimo;
			else
				ptr -> payoff = maximo;
		}
	}

}




/*
 *
 * Funcao que destroe a arvore, liberando assim memoria.
 *
 */

void
liberar( node *ptr )
{
	if( ptr == NULL )
		return;
	else
	{
		for( int i = 0; i < 9; i++ )
			liberar( ptr -> sons[i] );

		node *ptr2;
		ptr2 = ptr;
		ptr = NULL;
		free(ptr2);
	}
}

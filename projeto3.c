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
 * O objetivo era criar um programa capaz de jogar um jogo da velha de forma "inteligente", que jogasse de forma "perfeita",
 * perfeita no sentido de nunca perder. Em que o resultado fosse apenas o programa ganhar ou empatar.
 * E que se fosse possivel colocar o programa para jogar consigo mesmo, o resultado seria sempre empate.
 *
 * Assim sendo, o jogo foi dividido em duas modalidades, uma na qual o jogador humano joga com o programa,
 * na outra o programa joga consigo mesmo, como numa demonstracao.
 * Nao se sabe qual sera a jogada do adversario, humano ou programa, mas com base na sua escolha, o programa decide qual a
 * melhor jogada a se fazer depois.
 *
 * Sobre a implementacao. Foi construida toda a arvore do jogo, com todas as possibilidades, levando em conta os casos em que
 * algum jogador ganha em poucas jogadas. Foram utilizadas algumas funcoes auxiliares.
 * Como uma funcao para verificar o fim do jogo ( folha ), e atribuir valores de payoffs.
 * Vitoria [+1], Derrota [-1] e Empate [0].
 * Foi feito o Backtracking dos nos folhas ate a raiz da arvore, utilizando um algoritmo de MinMax para atribuir payoffs aos demais nos.
 *
 * Na modalidade do jogo em que humano joga contra programa, foi implementado uma especie de revezamento, em que ora humano comeca, ora programa.
 * No caso do humano comecar, a arvore foi construida a partir deste ponto, para diminuir o espaco necessario para criar a arvore,
 * e aumentar a rapidez de processamento.
 * No caso da programa comecar, foi optado por o programa comecar de forma aleatoria, pois cada posicao existem chances de ganhar.
 * Essa escolha foi feita para que o jogo nao fique sempre repetitivo.
 * Em seguida espera-se a jogada do humano e so depois constroe a arvore. Diminuindo ainda mais o espaco necessario e aumentando a rapidez de processamento.
 *
 * Na modalidade do jogo em que o programa joga contra o proprio programa, e como se fossem dois humanos diferentes jogando um contra o outro,
 * nao se sabe qual sera a proxima jogada do outro, e a escolha da melhor jogada e baseada na jogada anterior do adversario.
 * O objetivo era fazer ele jogar consigo mesmo, e que se de fato o programa e "um perfeito jogador", jogar contra um outro "perfeito jogador",
 * resultaria sempre em empate. E isso foi verificado em muitos testes.
 * O jogo nao e sempre repetido, e com base na jogada do adversaria, e escolhida a melhor jogada a se fazer.
 *
 *
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>



// Evitar multiplos includes.
#ifdef _GAME_TREE_

#else
#include "gameTree.h"

#endif



//Prototipos de funcoes auxiliares.
void clear( void );
int start( void );
void draw( int * );





int
main( void )
{

	int modality;
	int posicion;
	modality = start();

	/*
	 * Modalidade Computador X Computador
	 */
	if( modality )
	{
		int numberPlays;
		printf("\nEscolha a quantidade de partidas que gostaria de assistir: ");
		scanf("%d",&numberPlays);

		for( int i = 0; i < numberPlays; i++ )
		{

			clear();
			printf("\nPartida %d\n",i);
			sleep(2);
        	        int boardInic[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // Tabuleiro inicial, o valor -1 representa uma casa vazia.
                	draw(boardInic);
			sleep(2);
			srand(time(NULL));
			int x = rand()%9; // Primeira jogada de forma aleatoria, para ele nao comecar sempre o mesmo jogo.
			boardInic[x] = 0;
                	draw(boardInic);
			sleep(1);

			node *ptr = newTree( boardInic );
			node *play = ptr;
			insert( play );
			minMax( play, 1);
			int vez = 1; // Variavel responsavel pela vez de cada jogador.
			while( !won( play ) )
			{
				if( vez )
				{
					for( int i = 0; i < 9; i++ )
					{
						if( play -> sons[i] != NULL )
						{
							if( play -> sons[i] -> payoff == play -> payoff )
							{
								play = play -> sons[i];
								break;
							}
						}
					}
					draw( play -> board );
					vez = 0;
					sleep(1);

				}
				else
				{

					for( int i = 0; i < 9; i++ )
        	                        {
        	                             	if( play -> sons[i] != NULL )
	                                        {

							int count = 0;
							for( int j = 0; j < 9; j++ )
                        	                        	if( play -> sons[i] -> board[j] == play -> board[j] )
                	                                        	count++;
								if( count == 9 )
								{
									play = play -> sons[i];
									break;
								}
                                		 }
                               		}
						draw( play -> board );
						vez = 1;
						sleep(1);

				}
			}
				// Impressao do resultado de cada partida.
				printf("\n\nResultado:\n");
				if( play -> payoff == 1 )
                                        printf("Vitoria Computador 1!\n");
                                else if( play -> payoff == -1 )
                                        printf("Vitoria Computador 2!\n");
                                else if( play -> payoff == 0 )
                                        printf("Empate!\n");

			sleep(2);
			liberar(ptr); // Libera memoria.
		}
	}


	/*
	 * Modalidade Computador X Humano.
	 */
	else
	{


		int numberPlays, choice;
		printf("Escolha a quantidade de partidas: ");
		scanf("%d",&numberPlays);
		int comecar = 1;

		int vh = 0;
		int vm = 0;
		int velha = 0;

		for( int i = 0; i < numberPlays; i++)
		{
                	if( comecar )
               	 	{

				clear();
				int boardInic[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
				draw(boardInic);
				printf("\n\n\nVoce comecara a partida.\n\n");
				printf("Escolha uma posicao [0-8]:\n");
				do
				{
					scanf("%d",&choice);
					if( choice < 0 || choice > 8 )
						printf("Por favor, escolha um numero em 0 e 8.\n");
				}
				while( choice < 0 || choice > 8 );

				boardInic[choice] = 0;
				draw(boardInic);

				node *ptr = newTree( boardInic );
				node *play = ptr;
				insert( play );
				minMax( play,comecar);
				int vez = 1;
				while( !won( play ) )
				{
					if( vez )
					{
						for( int i = 0; i < 9; i++ )
						{
							if( play -> sons[i] != NULL )
							{
								if( play -> sons[i] -> payoff == play -> payoff )
								{
									play = play -> sons[i];
									break;
								}
							}
						}
						sleep(1);
						draw( play -> board );
						vez = 0;
					}
					else
					{
						printf("\nEscolha uma posicao [0-8]:\n");
                				do
                				{
                        				scanf("%d",&choice);
                        				if( choice < 0 || choice > 8 )
                                				printf("Por favor, escolha um numero em 0 e 8.\n");
							if( boardInic[choice] != -1 )
								printf("Local ja preenchido. Por favor escolha outro.\n");
                				}
                				while( choice < 0 || choice > 8 || play->board[choice] != -1);

                				play -> board[choice] = 0;
						draw(play->board);

						for( int i = 0; i < 9; i++ )
                                		{
                                        		if( play -> sons[i] != NULL )
                                        		{
								node *aux;
								int count = 0;
								for( int j = 0; j < 9; j++ )
                                                			if( play -> sons[i] -> board[j] == play -> board[j] )
                                                        			count++;
								if( count == 9 )
								{
									play = play -> sons[i];
									break;
								}
                                	        	}
                               		 	}

						vez = 1;

					}
				}
				// Impressao do resultado de cada partida.
				if( play -> payoff == 1 )
				{
					printf("\n\nVoce ganhou esta partida!\n");
					vh++;
				}
				else if( play -> payoff == -1 )
				{
					printf("\n\nEu ganhei esta partida!\n");
					vm++;
				}
				else if( play -> payoff == 0 )
				{
					printf("\n\nEmpatamos! Deu Velha!\n");
					velha++;
				}

				sleep(2);
				comecar = 0;
			}
			else
                	{
				clear();
                                int boardInic[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
                                draw(boardInic);
				printf("\n\nEu comeco dessa vez!!\n");
				printf("\nPensando...\n\n");
				sleep(2);
				srand(time(NULL));
				int x = rand()%9;
				boardInic[x] = 0;
                                draw(boardInic);
				printf("Escolha uma posicao [0-8]:\n");
				do
				{
					scanf("%d",&choice);
					if( choice < 0 || choice > 8 )
						printf("Por favor, escolha um numero em 0 e 8.\n");
				}
				while( choice < 0 || choice > 8 || boardInic[choice] != -1);

				boardInic[choice] = 1;
				draw(boardInic);
				sleep(1);

				node *ptr = newTree( boardInic );
				node *play = ptr;
				insert( play );
				minMax( play, comecar);
				int vez = 1;
				while( !won( play ) )
				{
					if( vez )
					{
						for( int i = 0; i < 9; i++ )
						{
							if( play -> sons[i] != NULL )
							{
								if( play -> sons[i] -> payoff == play -> payoff )
								{
									play = play -> sons[i];
									break;
								}
							}
						}
						draw( play -> board );
						vez = 0;
					}
					else
					{
						printf("Escolha uma posicao [0-8]:\n");
                				do
                				{
                        				scanf("%d",&choice);
                        				if( choice < 0 || choice > 8 )
                                				printf("Por favor, escolha um numero em 0 e 8.\n");
							if( boardInic[choice] != -1 )
								printf("Local ja preenchido. Por favor escolha outro.\n");
                				}
                				while( choice < 0 || choice > 8 || play->board[choice] != -1);

                				play -> board[choice] = 1;
						draw(play->board);
						sleep(1);

						for( int i = 0; i < 9; i++ )
                                		{
                                        		if( play -> sons[i] != NULL )
                                        		{
								node *aux;
								int count = 0;
								for( int j = 0; j < 9; j++ )
                                                			if( play -> sons[i] -> board[j] == play -> board[j] )
                                                        			count++;
								if( count == 9 )
								{
									play = play -> sons[i];
									break;
								}
                                	        	}
                               		 	}

						vez = 1;

					}
				}
				// Impressao do resultado de cada partida.
				if( play -> payoff == 1 )
                                {
				        printf("\n\nEu ganhei esta partida!\n");
					vm++;
				}
                                else if( play -> payoff == -1 )
				{
                                        printf("\n\nVoce ganhou esta partida!\n");
					vh++;
				}
                                else if( play -> payoff == 0 )
				{
                                        printf("\n\nEmpatamos! Deu Velha!\n");
					velha++;
				}

                                sleep(2);
				comecar = 1;
				liberar(ptr); // Libera memoria.

               		 }


		}
	// Impressao do resultado final.
	printf("\nResultado Final:\n\n");
	printf("Quantidade de partidas: %d\n",numberPlays);
	printf("Vitoria Humano: %d\n",vh);
	printf("Vitoria Computador: %d\n",vm);
	printf("Empates( Velha ): %d\n",velha);
	}


	return 0;

}




/*
 *
 * Funcao que limpa a tela e desenha o letreiro do nome do jogo.
 *
 */

void
clear(void)
{

	printf("\033[2J");
	printf("\033[%d;%dH", 0, 0);

	for( int i = 0; i <164; i++ )
		    printf("*");
    	printf("\n");

	for( int i = 0; i <164; i++ )
		printf("-");
	printf("\n\n");

	printf("     _   _____   _____   _____     _____       ___      _     _   _____   _       _   _       ___       _____   _   __   _       ___   _____    ___   _____\n");
	printf("    | | /  _  \\ /  ___| /  _  \\   |  _  \\     /   |    | |   / / | ____| | |     | | | |     /   |     |  _  \\ | | |  \\ | |     /   | |  _  \\  |_  | /  _  \\\n");
	printf("    | | | | | | | |     | | | |   | | | |    / /| |    | |  / /  | |__   | |     | |_| |    / /| |     | |_| | | | |   \\| |    / /| | | |_| |    | | | | | | \n");
	printf(" _  | | | | | | | |  _  | | | |   | | | |   / / | |    | | / /   |  __|  | |     |  _  |   / / | |     |  _  | | | | |\\   |   / / | | |  _  /    | | | |/| | \n");
	printf("| |_| | | |_| | | |_| | | |_| |   | |_| |  / /  | |    | |/ /    | |___  | |___  | | | |  / /  | |     | |_| | | | | | \\  |  / /  | | | | \\ \\    | | | |_| | \n");
	printf("\\_____/ \\_____/ \\_____/ \\_____/   |_____/ /_/   |_|    |___/     |_____| |_____| |_| |_| /_/   |_|     |_____/ |_| |_|  \\_| /_/   |_| |_|  \\_\\   |_| \\_____/ \n");

	printf("\n\n");

	for( int i = 0; i <164; i++ )
		printf("-");
	printf("\n");

	for( int i = 0; i <164; i++ )
		printf("*");
	printf("\n\n\n");

}



/*
 *
 * Funcao que mostrar a tela inicial do jogo.
 *
 */

int
start(void)
{

    	clear();

	printf("\t\tBEM-VINDO AO JOGO DA VELHA BINARIO!!!\n\n");

	printf("\nREGRAS:\n\n");
	printf("1- Neste jogo os simbolos sao 0's e 1's.\n");
	printf("2- O 0 sempre comeca.\n");
	printf("3- Vence quem completar uma linha, coluna ou diagonal do tabuleiro primeiro.\n");
	printf("4- O jogo podera resultar em vitoria para algum dos lados, ou acabar em empate, o que dizemos que deu 'Velha'.\n");
	printf("5- Para escolher o local de preenchimento, escolha um numero entre [0-8] que represente a regiao escolhida, siga o desenho abaixo:\n\n");
	printf("\t     |   |  \n");
	printf("\t   0 | 1 | 2 \n");
	printf("\t---------------\n");
        printf("\t   3 | 4 | 5 \n");
	printf("\t---------------\n");
        printf("\t   6 | 7 | 8 \n");
	printf("\t     |   |  \n");


	printf("\n6- Escolha entre iniciar uma partida contra o computador ou fazer uma demonstracao, na qual o computador jogara contra si mesmo.\n");
	printf("\n7- Caso escolha iniciar uma partida contra o computador, digite quantas partidas voce gostaria de jogar.\n");
	printf("O computador e o humano revesarao entre que comecara cada partida.\n");
	printf("No final do numero de partidas verems quem se saiu melhor no total de partidas, o computador , você ou a Velha.\n\n\n");
	printf("\nMODALIDADE:\n\n");
	printf("0 - Humano X Computador\n");
	printf("1 - Computador X Computador( Demonstracao )\n\n\n");

	int modality;
	printf("Digite a modalidade : ");
	do
	{
		scanf("%d",&modality);
		if( modality != 0 && modality != 1 )
			printf("Por favor, digite 0 para iniciar uma partida contra o computador e 1 para demonstracao.\n");
	}
	while( modality != 0 && modality != 1 );


	return modality;

}

/*
 *
 * Funcao que desenha o tabuleiro do jogo.
 *
 */


void
draw( int *board )
{

	clear();
	printf("\t    |   |  \n");

	if( board[0] == -1 )
        	printf("\t %c",32);
	else
		printf("\t %c",board[0] + 48);

	if( board[1] == -1 )
		printf("  | %c",32);
        else
		printf("  | %c",board[1] + 48);

	if( board[2] == -1 )
                printf(" | %c \n",32);
        else
                printf(" | %c \n",board[2] + 48);

        printf("\t---------------\n");


	if( board[3] == -1 )
        	printf("\t %c",32);
	else
		printf("\t %c",board[3] + 48);

	if( board[4] == -1 )
		printf("  | %c",32);
        else
		printf("  | %c",board[4] + 48);

	if( board[5] == -1 )
                printf(" | %c \n",32);
        else
                printf(" | %c \n",board[5] + 48);

        printf("\t---------------\n");


	if( board[6] == -1 )
        	printf("\t %c",32);
	else
		printf("\t %c",board[6] + 48);

	if( board[7] == -1 )
		printf("  | %c",32);
        else
		printf("  | %c",board[7] + 48);

	if( board[8] == -1 )
                printf(" | %c \n",32);
        else
                printf(" | %c \n",board[8] + 48);

	printf("\t    |   |  \n");



}

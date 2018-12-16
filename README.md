# tictactoeIA
O objetivo era criar um programa capaz de jogar um jogo da velha de forma "inteligente", que jogasse de forma "perfeita",
perfeita no sentido de nunca perder. Em que o resultado fosse apenas o programa ganhar ou empatar.
E que se fosse possivel colocar o programa para jogar consigo mesmo, o resultado seria sempre empate.
 
Assim sendo, o jogo foi dividido em duas modalidades, uma na qual o jogador humano joga com o programa,
na outra o programa joga consigo mesmo, como numa demonstracao.
Nao se sabe qual sera a jogada do adversario, humano ou programa, mas com base na sua escolha, o programa decide qual a
melhor jogada a se fazer depois.
 
Sobre a implementacao. Foi construida toda a arvore do jogo, com todas as possibilidades, levando em conta os casos em que
algum jogador ganha em poucas jogadas. Foram utilizadas algumas funcoes auxiliares.
Como uma funcao para verificar o fim do jogo ( folha ), e atribuir valores de payoffs.
Vitoria [+1], Derrota [-1] e Empate [0].
Foi feito o Backtracking dos nos folhas ate a raiz da arvore, utilizando um algoritmo de MinMax para atribuir payoffs aos demais nos.
 
Na modalidade do jogo em que humano joga contra programa, foi implementado uma especie de revezamento, em que ora humano comeca, ora programa.
No caso do humano comecar, a arvore foi construida a partir deste ponto, para diminuir o espaco necessario para criar a arvore,
e aumentar a rapidez de processamento.
No caso da programa comecar, foi optado por o programa comecar de forma aleatoria, pois cada posicao existem chances de ganhar.
Essa escolha foi feita para que o jogo nao fique sempre repetitivo.
Em seguida espera-se a jogada do humano e so depois constroe a arvore. Diminuindo ainda mais o espaco necessario e aumentando a rapidez de processamento.
 
Na modalidade do jogo em que o programa joga contra o proprio programa, e como se fossem dois humanos diferentes jogando um contra o outro,
nao se sabe qual sera a proxima jogada do outro, e a escolha da melhor jogada e baseada na jogada anterior do adversario.
O objetivo era fazer ele jogar consigo mesmo, e que se de fato o programa e "um perfeito jogador", jogar contra um outro "perfeito jogador",
resultaria sempre em empate. E isso foi verificado em muitos testes. 
O jogo nao e sempre repetido, e com base na jogada do adversaria, e escolhida a melhor jogada a se fazer.

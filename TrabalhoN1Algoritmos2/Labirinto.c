// Desenvolvido originalmente por Alessandro João Brassanini
// Data: 19 de Abril de 2022
//---------------------//------------------------//-----------------//
// Alterado/Melhorado por Gabriel Couto Ricardo
// Data: 10 de Abril de 2026 

/*
Uso de matriz bidimensional (10x10) para armazenar o cenário.
Laços de repetição para imprimir o labirinto a cada rodada.
Condicionais para validar os movimentos e impedir atravessar paredes.
Leitura de teclado com scanf para capturar as direções.
Verificação de vitória quando o jogador chega na saída.

OBS: A linguagem C padrão ANSI não possui suporte nativo para controle
de som (frequência/duração). Pesquisei e vi que daria pra usar uma biblioteca do Windows
que daria mais controle e sons diferentes, mas daí deixaria de ser padrão ANSI... Foi utilizado o caractere "\a" 
para simular efeitos sonoros, podendo variar conforme o terminal. testei no online gdb por exemplo e lá só tem o beep simples

Regras:
@ - posição atual do jogador.
0 - caminho livre.
X - parede (não pode atravessar).
! - Bomba (tira muitos pontos)
O - saída (objetivo do jogo).

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 10

// cores do joguinho 
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// beep --- autoexplicativo kkk 
void beep()
{
    printf("\a");
}

// delay simples
void delay()
{
    long i;
    for(i=0;i<200000000;i++);
}

// limpa a tela
void limparTela()
{
    int i;
    for(i=0;i<35;i++)
        printf("\n");
}

// aqui são os sons, nada muito relevante pra comentar
void somMovimento()
{
    beep();
}

void somParede()
{
    beep();
    delay();
    beep();
    beep();
    beep();
    beep();
    delay();
    beep();
}

void musicaVitoria()
{
    int i;

    // repete 3 vezes o ritmo
    for(i=0;i<3;i++)
    {
        beep();
        beep();
        delay();
        beep();
        beep();
        beep();
        delay();
        beep();
        delay();
        beep();
        beep();
        beep();
        delay();
        beep();
        beep();
        delay();
        beep();
        delay();
        beep();
        beep();
        beep();
        beep();
    }

    delay();

    for(i=0;i<2;i++)
    {
        beep();
        delay();
    }
}

void musicaMorte()
{
    beep();
    delay();

    beep();
    delay();

    beep();
    beep();
    beep();
    beep();
    beep();
    beep();
    beep();
    beep();
    beep();
    beep();

    beep();
    delay();

    beep();
    delay();
}

// tela da vitória mostrando os passos, pontos e um banner de vitoria
void telaVitoria(int passos, int pontos)
{
    
    limparTela();

    printf(GREEN);
    printf("\n\n");
    printf("########################################\n");
    printf("#                                      #\n");
    printf("#            VOCE VENCEU !!!           #\n");
    printf("#                                      #\n");
    printf("########################################\n");
    printf(RESET);

    printf("\nPassos totais: %d\n",passos);
    printf("Pontuacao final: %d\n\n",pontos);

    musicaVitoria();
}

// tela de morte por perder os pontos
void telaDerrota()
{
    limparTela();

    printf(RED);
    printf("\n\n");
    printf("########################################\n");
    printf("#                                      #\n");
    printf("#              VOCE MORREU             #\n");
    printf("#                                      #\n");
    printf("########################################\n");
    printf(RESET);

    printf("\nVoce ficou sem pontos!\n");

    musicaMorte();
}

void mostrarLabirinto(int lab[N][N], int x, int y)
{
    int i,j;

    // linha de colunas
    printf("     ");
    for(j=0;j<N;j++)
        printf("%d ", j);

    printf("\n");
    printf("     --------------------\n");

    // Percorre todas as linhas do labirinto
    for(i=0;i<N;i++)
    {
        printf(" %d | ", i);
        
         // Percorre todas as colunas da linha atual
        for(j=0;j<N;j++)
        {
            // Se a posição atual for a do jogador mostra ele como @ e coloca a cor dele como azul
            if(i==x && j==y)
                printf(BLUE "@ " RESET);

            // Se for uma parede representa ela como um X vermelho
            else if(lab[i][j]==1)
                printf(RED "X " RESET);
            
            // se for a saída, representa ela com um O verde pra chamar atenção. 
            else if(lab[i][j]==-1)
                printf(GREEN "O " RESET);
            
            // Se for bomba (lascou) representa como um ! amarelo
            else if(lab[i][j]==2)
                printf(YELLOW "! " RESET);

            // Caminho livre 
            else
                printf(". ");
        }

        printf("\n");
    }
}
// valida se o movimento é possível 
int validarMovimento(int lab[N][N], int x, int y)
{
    if(x < 0 || x >= N || y < 0 || y >= N)
        return 0;

    if(lab[x][y] == 1)
        return 0;

    return 1;
}

// geração do cenário 10x10 definindo paredes, caminhos livres e a saída.
int main()
{
    int labirinto[N][N] =
    {
        {0,1,0,0,0,0,1,0,0,0},
        {0,1,0,1,1,0,1,0,1,0},
        {0,0,0,1,0,0,0,0,1,0},
        {1,1,0,1,0,1,1,0,1,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,1,1,1,0,1,0,1,1,0},
        {0,0,0,1,0,0,0,1,0,0},
        {1,1,0,1,1,1,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,0,1,1,0,-1}
    };

    // definindo as bombas (pensei em fazer isso aqui usando o random, mas testei e vi que as vezes ele deixa o jogo impossível...)
    labirinto[2][4] = 2;
    labirinto[6][2] = 2;
    labirinto[8][5] = 2;

    int x=0,y=0;
    int passos=0;
    int pontos=100;

    char comando;
    
    // tela inicial
    while(1)
    {
        limparTela();

        printf("LABIRINTO 10x10\n");
        printf("W cima | S baixo | A esquerda | D direita\n");
        printf("@ jogador | X parede | O saida | ! armadilha\n\n");

        printf("Passos: %d\n",passos);
        printf("Pontos: %d\n",pontos);
        printf("Posicao: (%d,%d)\n",x,y);

        mostrarLabirinto(labirinto,x,y);

        // Verifica se chegou ao fim do labirinto
        if(labirinto[x][y]==-1)
        {
            telaVitoria(passos,pontos);
            break;
        }

        // derrota. você morre
        if(pontos <= 0)
        {
            telaDerrota();
            break;
        }

        printf("\nMovimento: ");
        scanf(" %c",&comando);

        comando = toupper(comando);

        int novoX=x;
        int novoY=y;
        
        // comandos de controle do personagem
        if(comando=='W') novoX--;
        else if(comando=='S') novoX++;
        else if(comando=='A') novoY--;
        else if(comando=='D') novoY++;
        else
        {
            printf("Comando invalido!\n");
            delay();
            continue;
        }

        // verifica se o movimento é válido
        if(validarMovimento(labirinto,novoX,novoY))
        {
            x=novoX;
            y=novoY;
            
            // se o movimento for válido, acrescenta 1 ao número de passos para informar ao dim do jogo
            passos++;
            somMovimento();
            
            // Se caiu na armadilha tira 100 pontos do joghador, ou seja, morre.
            if(labirinto[x][y]==2)
            {
                printf("Voce caiu em uma armadilha e uma bomba explodiu. Já era!\n");
                pontos -= 100;
                delay();
            }
        }
        
        // Se não caiu em uma armadilha e não andou em um caminho livre, só pode ter batido na parede. -50 pontos
        else
        {
            printf("Bateu na parede!\n");
            pontos -= 50;
            somParede();
            delay();
        }
    }

    return 0;
}

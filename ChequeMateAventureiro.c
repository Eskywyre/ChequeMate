/*
  Projeto ChequeMate - Nivel Aventureiro
  Continuidade do simulador de movimentos de xadrez em C.

  Objetivo: implementar o movimento do Cavalo em "L",
  usando loops aninhados (for + while).
*/

#include <stdio.h>
#include <ctype.h>

#define N 8  // tabuleiro 8x8

// verifica se a posicao esta dentro do tabuleiro
int dentro_tabuleiro(int linha, int coluna) {
    return (linha >= 0 && linha < N && coluna >= 0 && coluna < N);
}

// preenche o tabuleiro com pontos
void limpar_tabuleiro(char t[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            t[i][j] = '.';
}

// mostra o tabuleiro
void mostrar_tabuleiro(char t[N][N]) {
    puts("\n  a b c d e f g h");
    for (int i = N - 1; i >= 0; i--) {
        printf("%d ", i + 1);
        for (int j = 0; j < N; j++) printf("%c ", t[i][j]);
        printf(" %d\n", i + 1);
    }
    puts("  a b c d e f g h\n");
}

/* --- Nivel Novato --- */

void torre_for(char t[N][N], int l, int c) {
    for (int i = 0; i < N; i++) {
        t[l][i] = '*';
        t[i][c] = '*';
    }
}

void bispo_while(char t[N][N], int l, int c) {
    int i = 1;
    while (l + i < N && c + i < N) { t[l + i][c + i] = '*'; i++; }
    i = 1; while (l - i >= 0 && c - i >= 0) { t[l - i][c - i] = '*'; i++; }
    i = 1; while (l + i < N && c - i >= 0) { t[l + i][c - i] = '*'; i++; }
    i = 1; while (l - i >= 0 && c + i < N) { t[l - i][c + i] = '*'; i++; }
}

void rainha_do_while(char t[N][N], int l, int c) {
    int direcoes[8][2] = {
        {1,0},{-1,0},{0,1},{0,-1},
        {1,1},{1,-1},{-1,1},{-1,-1}
    };
    for (int i = 0; i < 8; i++) {
        int x = l, y = c;
        do {
            x += direcoes[i][0];
            y += direcoes[i][1];
            if (dentro_tabuleiro(x, y)) t[x][y] = '*';
        } while (dentro_tabuleiro(x, y));
    }
}

/* --- Nivel Aventureiro --- */
/*
   Movimento do Cavalo: 2 casas para baixo e 1 para a esquerda.
   Aqui usei um for para as duas casas para baixo
   e um while para a casa para a esquerda (loops aninhados).
*/

void cavalo_aninhado(char t[N][N], int l, int c) {
    int passos_baixo = 2;
    int passos_esquerda = 1;

    for (int i = 0; i < passos_baixo; i++) {
        int nova_linha = l - (i + 1);
        if (dentro_tabuleiro(nova_linha, c)) {
            t[nova_linha][c] = '*';
            printf("Baixo\n");
        }

        int j = 0;
        while (j < passos_esquerda && i == passos_baixo - 1) { // esquerda so depois do segundo passo
            int nova_coluna = c - (j + 1);
            if (dentro_tabuleiro(nova_linha, nova_coluna)) {
                t[nova_linha][nova_coluna] = '*';
                printf("Esquerda\n");
            }
            j++;
        }
    }
}

/* --- Programa principal --- */

int main() {
    char tabuleiro[N][N];
    limpar_tabuleiro(tabuleiro);

    printf("=== Projeto ChequeMate - Nivel Aventureiro ===\n");
    printf("Movimento do Cavalo: 2 para baixo e 1 para a esquerda.\n\n");

    int l = 4, c = 4; // posicao inicial do cavalo
    tabuleiro[l][c] = 'C';

    cavalo_aninhado(tabuleiro, l, c);

    printf("\nTabuleiro final:\n");
    mostrar_tabuleiro(tabuleiro);

    printf("Fim da simulacao.\n");
    return 0;
}
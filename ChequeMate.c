/*
  Projeto ChequeMate — Simulador de Movimentos de Xadrez em C

  Objetivo: usar estruturas de repeticao e recursividade
  para simular os movimentos basicos das pecas (Torre, Bispo, Rainha e Cavalo).

  Modulos:
  - Novato: usa for, while e do-while.
  - Aventureiro: loops aninhados (Cavalo).
  - Mestre: recursividade (Rainha em modo avancado).
*/

#include <stdio.h>
#include <ctype.h>

#define N 8  // Tamanho do tabuleiro (8x8)

// Verifica se a posicao esta dentro do tabuleiro
static int dentro_do_tabuleiro(int linha, int coluna) { return linha>=0 && linha<N && coluna>=0 && coluna<N; }

// Limpa o tabuleiro, preenchendo tudo com ponto
static void limpar_tabuleiro(char t[N][N]){
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) t[i][j]='.';
}

// Mostra o tabuleiro no terminal
static void mostrar_tabuleiro(char t[N][N]){
    puts("\n  a b c d e f g h");
    for(int i=N-1; i>=0; i--){
        printf("%d ", i+1);
        for(int j=0;j<N;j++) printf("%c ", t[i][j]);
        printf(" %d\n", i+1);
    }
    puts("  a b c d e f g h\n");
}

// Converte algo tipo "e4" em coordenadas (linha, coluna)
static int converter_posicao(const char *s, int *linha, int *coluna){
    if(!s || !isalpha(s[0]) || !isdigit(s[1])) return 0;
    int c = tolower(s[0]) - 'a';
    int l = (s[1]-'1');
    if(!dentro_do_tabuleiro(l,c)) return 0;
    *linha = l; *coluna = c; return 1;
}

/* --- MODULO NOVATO --- */

// Torre (anda em linha reta) — usando FOR
static void torre_for(char t[N][N], int l, int c){
    for(int i=0;i<N;i++){ t[l][i]='*'; t[i][c]='*'; }
}

// Bispo (anda na diagonal) — usando WHILE
static void bispo_while(char t[N][N], int l, int c){
    int i=1;
    while(l+i<N && c+i<N){ t[l+i][c+i]='*'; i++; }
    i=1; while(l-i>=0 && c-i>=0){ t[l-i][c-i]='*'; i++; }
    i=1; while(l+i<N && c-i>=0){ t[l+i][c-i]='*'; i++; }
    i=1; while(l-i>=0 && c+i<N){ t[l-i][c+i]='*'; i++; }
}

// Rainha — mistura tudo, usando DO-WHILE
static void rainha_do_while(char t[N][N], int l, int c){
    int direcoes[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    for(int i=0;i<8;i++){
        int x=l, y=c;
        do { x+=direcoes[i][0]; y+=direcoes[i][1]; if(dentro_do_tabuleiro(x,y)) t[x][y]='*'; }
        while(dentro_do_tabuleiro(x,y));
    }
}

/* --- MODULO AVENTUREIRO --- */

// Cavalo — usa loops aninhados
static void cavalo_aninhado(char t[N][N], int l, int c){
    int movimentos[8][2]={{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
    for(int i=0;i<8;i++){
        int x=l+movimentos[i][0], y=c+movimentos[i][1];
        if(dentro_do_tabuleiro(x,y)) t[x][y]='*';
    }
}

/* --- MODULO MESTRE --- */

// Movimento recursivo — usado pra varrer a rainha ate o limite
static void movimento_recursivo(char t[N][N], int l, int c, int dl, int dc){
    int nl=l+dl, nc=c+dc;
    if(!dentro_do_tabuleiro(nl,nc)) return;
    t[nl][nc]='*';
    movimento_recursivo(t,nl,nc,dl,dc);
}

static void rainha_recursiva(char t[N][N], int l, int c){
    int direcoes[8][2]={{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    for(int i=0;i<8;i++) movimento_recursivo(t,l,c,direcoes[i][0],direcoes[i][1]);
}

// --- Funcao principal ---
int main(){
    char tabuleiro[N][N], peca, pos[3];
    int modoMestre;

    printf("=== Projeto ChequeMate ===\n");
    printf("Pecas: T (Torre), B (Bispo), Q (Rainha), C (Cavalo)\n");
    printf("Exemplo de uso: Q e4 1 (Rainha na casa e4, modo Mestre ligado)\n\n");

    while(1){
        limpar_tabuleiro(tabuleiro);
        printf("Digite a peca, a posicao e o modo (0 normal, 1 Mestre): ");
        if(scanf(" %c %2s %d", &peca, pos, &modoMestre) < 2) break;

        int l,c;
        if(!converter_posicao(pos,&l,&c)){ printf("Posicao invalida!\n"); continue; }

        tabuleiro[l][c]='P'; // marca a peca
        switch(tolower(peca)){
            case 't': torre_for(tabuleiro,l,c); break;
            case 'b': bispo_while(tabuleiro,l,c); break;
            case 'q': modoMestre ? rainha_recursiva(tabuleiro,l,c) : rainha_do_while(tabuleiro,l,c); break;
            case 'c': cavalo_aninhado(tabuleiro,l,c); break;
            default: printf("Peca invalida!\n"); continue;
        }
        mostrar_tabuleiro(tabuleiro);
    }

    printf("\nEncerrando o jogo. Obrigado por jogar!\n");
    return 0;
}
/*
  Projeto ChequeMate - Nivel Mestre
  Objetivo: recursividade (Torre, Bispo, Rainha) e loops complexos (Cavalo).
  Observacao: comentarios curtos e práticos, sem acentos para evitar problemas de encoding.
*/

#include <stdio.h>

#define N 8

/* util: checa limites e imprime direcao basica */
int dentro(int l, int c) { return l >= 0 && l < N && c >= 0 && c < N; }

void print_direcao(int dl, int dc) {
    if (dl < 0)  printf("Baixo\n");
    if (dl > 0)  printf("Cima\n");
    if (dc < 0)  printf("Esquerda\n");
    if (dc > 0)  printf("Direita\n");
}

/* -------- recursividade: avanca em uma direcao ate sair -------- */
/* Marca com '*' so para visualizar; foco do desafio e imprimir direcao por casa. */
void avanca_rec(char t[N][N], int l, int c, int dl, int dc) {
    int nl = l + dl, nc = c + dc;
    if (!dentro(nl, nc)) return;
    t[nl][nc] = '*';
    print_direcao(dl, dc);
    avanca_rec(t, nl, nc, dl, dc);
}

/* -------- Torre recursiva: 4 raios -------- */
void torre_recursiva(char t[N][N], int l, int c) {
    avanca_rec(t, l, c,  1,  0);  // cima
    avanca_rec(t, l, c, -1,  0);  // baixo
    avanca_rec(t, l, c,  0,  1);  // direita
    avanca_rec(t, l, c,  0, -1);  // esquerda
}

/* -------- Bispo recursivo: 4 diagonais -------- */
void bispo_recursivo(char t[N][N], int l, int c) {
    avanca_rec(t, l, c,  1,  1);  // cima-direita
    avanca_rec(t, l, c,  1, -1);  // cima-esquerda
    avanca_rec(t, l, c, -1,  1);  // baixo-direita
    avanca_rec(t, l, c, -1, -1);  // baixo-esquerda
}

/* -------- Rainha recursiva: 8 direcoes -------- */
void rainha_recursiva(char t[N][N], int l, int c) {
    avanca_rec(t, l, c,  1,  0);
    avanca_rec(t, l, c, -1,  0);
    avanca_rec(t, l, c,  0,  1);
    avanca_rec(t, l, c,  0, -1);
    avanca_rec(t, l, c,  1,  1);
    avanca_rec(t, l, c,  1, -1);
    avanca_rec(t, l, c, -1,  1);
    avanca_rec(t, l, c, -1, -1);
}

/* -------- Bispo com loops aninhados --------
   Loop externo controla direcao vertical (dv), interno a horizontal (dh).
   Para cada combinacao de diagonal, uso um while para avançar passo a passo.
*/
void bispo_loops_aninhados(char t[N][N], int l, int c) {
    for (int dv = -1; dv <= 1; dv += 2) {          // -1 (baixo), +1 (cima)
        for (int dh = -1; dh <= 1; dh += 2) {      // -1 (esq), +1 (dir)
            int nl = l, nc = c;
            while (1) {
                nl += dv; nc += dh;
                if (!dentro(nl, nc)) break;
                t[nl][nc] = '*';
                print_direcao(dv, 0);
                print_direcao(0, dh);
            }
        }
    }
}

/* -------- Cavalo com loops complexos --------
   Movimento pedido: 2 para cima e 1 para a direita (em L).
   Usei for com duas variaveis e condicoes, more de controle com continue/break.
   Imprimo direcao por etapa: "Cima", "Cima", "Direita".
*/
void cavalo_loops(char t[N][N], int l, int c) {
    int up_steps = 2, right_steps = 1;
    int nl = l, nc = c;

    for (int i = 0, feito = 0; i < up_steps + right_steps; i++) {
        if (i < up_steps) {
            int proxl = nl + 1;          // cima (linha cresce)
            if (!dentro(proxl, nc)) { break; }
            nl = proxl; t[nl][nc] = '*'; printf("Cima\n");
            if (nl == l) continue;       // exemplo de continue (nao dispara aqui, mas mantem a ideia)
        } else {
            int prox = i - up_steps;     // comeca a contar os 1 passo a direita
            if (prox >= right_steps) break;
            int proxc = nc + 1;          // direita (coluna cresce)
            if (!dentro(nl, proxc)) break;
            nc = proxc; t[nl][nc] = '*'; printf("Direita\n");
        }
        if (nl == l + up_steps && nc == c + right_steps) { // cheguei no L
            // exemplo de break: encerro quando completei o L
            break;
        }
    }
}

/* -------- util: limpar/mostrar -------- */
void limpar(char t[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            t[i][j] = '.';
}

void mostrar(char t[N][N]) {
    puts("\n  a b c d e f g h");
    for (int i = N - 1; i >= 0; i--) {
        printf("%d ", i + 1);
        for (int j = 0; j < N; j++) printf("%c ", t[i][j]);
        printf(" %d\n", i + 1);
    }
    puts("  a b c d e f g h");
}

/* -------- main: executa cada parte separada por linha em branco -------- */
int main(void) {
    char T[N][N];

    /* Torre recursiva */
    limpar(T);
    int lt = 3, ct = 3; T[lt][ct] = 'T';
    printf("TORRE (recursiva)\n");
    torre_recursiva(T, lt, ct);
    mostrar(T);
    puts("");

    /* Bispo recursivo */
    limpar(T);
    int lb = 4, cb = 4; T[lb][cb] = 'B';
    printf("BISPO (recursiva)\n");
    bispo_recursivo(T, lb, cb);
    mostrar(T);
    puts("");

    /* Bispo com loops aninhados */
    limpar(T);
    lb = 2; cb = 2; T[lb][cb] = 'B';
    printf("BISPO (loops aninhados)\n");
    bispo_loops_aninhados(T, lb, cb);
    mostrar(T);
    puts("");

    /* Rainha recursiva */
    limpar(T);
    int lq = 1, cq = 6; T[lq][cq] = 'Q';
    printf("RAINHA (recursiva)\n");
    rainha_recursiva(T, lq, cq);
    mostrar(T);
    puts("");

    /* Cavalo com loops complexos: 2 para cima, 1 para direita */
    limpar(T);
    int lk = 3, ck = 3; T[lk][ck] = 'C';
    printf("CAVALO (loops complexos: 2 cima, 1 direita)\n");
    cavalo_loops(T, lk, ck);
    mostrar(T);

    printf("\nFim da simulacao.\n");
    return 0;
}
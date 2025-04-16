#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5 // Usaremos uma matriz 5x5 para cada habilidade

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++)
        for (int j = 0; j < TAM_TABULEIRO; j++)
            tabuleiro[i][j] = 0;
}

// Verifica se o navio pode ser posicionado
int podePosicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 0) c += i; // horizontal
        else if (orientacao == 1) l += i; // vertical
        else if (orientacao == 2) { l += i; c += i; } // diagonal principal
        else if (orientacao == 3) { l += i; c -= i; } // diagonal secundária

        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO || tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

// Posiciona o navio
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        if (orientacao == 0) c += i;
        else if (orientacao == 1) l += i;
        else if (orientacao == 2) { l += i; c += i; }
        else if (orientacao == 3) { l += i; c -= i; }

        tabuleiro[l][c] = 3; // valor do navio
    }
}

// Gera matriz de habilidade em formato de cone
void gerarCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int meio = TAM_HABILIDADE / 2;
            if (j >= meio - i && j <= meio + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade em formato de cruz
void gerarCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade em formato de octaedro (losango)
void gerarOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica a matriz de habilidade ao tabuleiro, centrando no ponto de origem
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[TAM_HABILIDADE][TAM_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int l = origemLinha - offset + i;
            int c = origemColuna - offset + j;

            if (l >= 0 && l < TAM_TABULEIRO && c >= 0 && c < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[l][c] == 0)
                    tabuleiro[l][c] = 5; // valor da habilidade
            }
        }
    }
}

// Exibe o tabuleiro com representação visual
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            char simbolo;

            if (tabuleiro[i][j] == 0) simbolo = '~'; // água
            else if (tabuleiro[i][j] == 3) simbolo = 'N'; // navio
            else if (tabuleiro[i][j] == 5) simbolo = '*'; // habilidade

            printf("%c ", simbolo);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Navios
    int navios[4][3] = {
        {1, 1, 0}, // horizontal
        {0, 8, 1}, // vertical
        {6, 0, 2}, // diagonal principal
        {1, 7, 3}  // diagonal secundária
    };

    for (int i = 0; i < 4; i++) {
        int l = navios[i][0];
        int c = navios[i][1];
        int o = navios[i][2];
        if (podePosicionarNavio(tabuleiro, l, c, o))
            posicionarNavio(tabuleiro, l, c, o);
    }

    // Habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    gerarCone(cone);
    gerarCruz(cruz);
    gerarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cone, 4, 4);      // ponto de origem (4,4)
    aplicarHabilidade(tabuleiro, cruz, 7, 7);      // ponto de origem (7,7)
    aplicarHabilidade(tabuleiro, octaedro, 2, 5);  // ponto de origem (2,5)

    exibirTabuleiro(tabuleiro);

    return 0;
}

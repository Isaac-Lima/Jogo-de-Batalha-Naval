#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para verificar se é possível posicionar um navio
// orientacao: 0 = horizontal, 1 = vertical, 2 = diagonal principal, 3 = diagonal secundária
int podePosicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        // Ajusta as coordenadas conforme a orientação
        if (orientacao == 0) c += i;            // horizontal
        else if (orientacao == 1) l += i;       // vertical
        else if (orientacao == 2) { l += i; c += i; }  // diagonal principal
        else if (orientacao == 3) { l += i; c -= i; }  // diagonal secundária

        // Verifica limites do tabuleiro
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO)
            return 0;

        // Verifica sobreposição
        if (tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;

        // Define as coordenadas de cada parte do navio
        if (orientacao == 0) c += i;
        else if (orientacao == 1) l += i;
        else if (orientacao == 2) { l += i; c += i; }
        else if (orientacao == 3) { l += i; c -= i; }

        tabuleiro[l][c] = 3;
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Coordenadas e orientações dos navios (pré-definidos)
    // Formato: linha, coluna, orientação
    int navios[4][3] = {
        {2, 1, 0},  // horizontal
        {0, 7, 1},  // vertical
        {5, 0, 2},  // diagonal principal
        {1, 8, 3}   // diagonal secundária
    };

    // Tenta posicionar cada navio
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        int orientacao = navios[i][2];

        if (podePosicionarNavio(tabuleiro, linha, coluna, orientacao)) {
            posicionarNavio(tabuleiro, linha, coluna, orientacao);
        } else {
            printf("Erro ao posicionar o navio %d. Coordenadas inválidas ou sobreposição.\n", i + 1);
        }
    }

    // Exibe o tabuleiro com os navios
    exibirTabuleiro(tabuleiro);

    return 0;
}

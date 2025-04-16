#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para inicializar o tabuleiro com 0 (água)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para verificar se o navio pode ser posicionado no tabuleiro sem ultrapassar os limites
int podePosicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int orientacao) {
    // orientacao 0 = horizontal, 1 = vertical
    if (orientacao == 0) {
        if (coluna + TAM_NAVIO > TAM_TABULEIRO) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha][coluna + i] != 0) return 0;
        }
    } else {
        if (linha + TAM_NAVIO > TAM_TABULEIRO) return 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linha + i][coluna] != 0) return 0;
        }
    }
    return 1;
}

// Função para posicionar o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int orientacao) {
    if (orientacao == 0) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    } else {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    // Inicializa o tabuleiro
    inicializarTabuleiro(tabuleiro);

    // Coordenadas dos navios (pré-definidas no código)
    int linhaHorizontal = 2;
    int colunaHorizontal = 4;
    int linhaVertical = 5;
    int colunaVertical = 7;

    // Verifica e posiciona navio horizontal
    if (podePosicionarNavio(tabuleiro, linhaHorizontal, colunaHorizontal, 0)) {
        posicionarNavio(tabuleiro, linhaHorizontal, colunaHorizontal, 0);
    } else {
        printf("Erro: navio horizontal fora do tabuleiro ou sobreposição.\n");
    }

    // Verifica e posiciona navio vertical
    if (podePosicionarNavio(tabuleiro, linhaVertical, colunaVertical, 1)) {
        posicionarNavio(tabuleiro, linhaVertical, colunaVertical, 1);
    } else {
        printf("Erro: navio vertical fora do tabuleiro ou sobreposição.\n");
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}

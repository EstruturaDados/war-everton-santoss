// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ---------- FUNÇÕES ---------- */
Territorio* cadastrarTerritorios(int quantidade);
void exibirTerritorios(Territorio* territorios, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* territorios);

/* ---------- FUNÇÃO PRINCIPAL ---------- */
int main() {
    srand(time(NULL)); // Garante aleatoriedade nos ataques

    int n;
    printf("=== Simulação de Batalha entre Territórios ===\n\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica de memória para o vetor de territórios
    Territorio* territorios = (Territorio*) malloc(n * sizeof(Territorio));
    if (territorios == NULL) {
        printf("Erro: falha ao alocar memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", territorios[i].nome);

        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\n=== Territórios Cadastrados ===\n");
    exibirTerritorios(territorios, n);

    int opcao;
    do {
        printf("\nDeseja simular um ataque? (1 - Sim / 0 - Não): ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int iAtacante, iDefensor;

            printf("\nEscolha o território ATACANTE (0 a %d): ", n - 1);
            scanf("%d", &iAtacante);

            printf("Escolha o território DEFENSOR (0 a %d): ", n - 1);
            scanf("%d", &iDefensor);

            // Validação das escolhas
            if (iAtacante == iDefensor) {
                printf("Um território não pode atacar a si mesmo!\n");
                continue;
            }
            if (strcmp(territorios[iAtacante].cor, territorios[iDefensor].cor) == 0) {
                printf("Não é possível atacar um território da mesma cor!\n");
                continue;
            }

            atacar(&territorios[iAtacante], &territorios[iDefensor]);

            printf("\n=== Estado Atual dos Territórios ===\n");
            exibirTerritorios(territorios, n);
        }

    } while (opcao != 0);

    // Libera a memória alocada
    liberarMemoria(territorios);

    printf("\nMemória liberada e programa finalizado.\n");
    return 0;
}

/* ---------- IMPLEMENTAÇÃO DAS FUNÇÕES ---------- */

/**
 * Exibe todos os territórios cadastrados
 */
void exibirTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("----------------------\n");
    }
}

/**
 * Função que simula um ataque entre dois territórios
 * Usa rand() para gerar "dados" de 1 a 6.
 */
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) está atacando %s (%s)!\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Resultado do ataque
    if (dadoAtacante > dadoDefensor) {
        printf(">>> %s venceu a batalha!\n", atacante->nome);

        // Transferência de controle
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // defensor recebe metade das tropas
        atacante->tropas /= 2; // atacante perde metade das tropas

    } else {
        printf(">>> %s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}
void liberarMemoria(Territorio* territorios) {
    free(territorios);
}

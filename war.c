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

// ---------- Estrutura principal ----------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ---------- Protótipos ----------
Territorio* cadastrarTerritorios(int quantidade);
void exibirTerritorios(Territorio* territorios, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void atribuirMissao(char* destino, char* missoes[], int totalMissoes);
int verificarMissao(char* missao, Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* territorios, char* missaoJogador1, char* missaoJogador2);

// ---------- Função Principal ----------
int main() {
    srand(time(NULL)); 
    int n;
    printf("=== Simulação de Batalha com Missões ===\n\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica de territórios
    Territorio* territorios = (Territorio*) malloc(n * sizeof(Territorio));
    if (!territorios) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro de territórios
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", territorios[i].nome);
        printf("Cor do exército: ");
        scanf("%s", territorios[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Missoes disponíveis
    char* missoes[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar metade dos territorios do mapa",
        "Manter 5 territorios com mais de 10 tropas cada",
        "Conquistar pelo menos um territorio de cada cor"
    };
    int totalMissoes = 5;

    // Atribuir missão dinamicamente para dois jogadores
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    printf("\n=== Missões Secretas Atribuídas ===\n");
    printf("Jogador 1: %s\n", missaoJogador1);
    printf("Jogador 2: %s\n", missaoJogador2);
    printf("----------------------------------\n");

    // Loop de turnos
    int turno = 1;
    int vencedor = 0;
    while (!vencedor) {
        printf("\n=== TURNO %d ===\n", turno);
        exibirTerritorios(territorios, n);

        int iAtacante, iDefensor;
        printf("\nJogador %d, escolha o território ATACANTE (0 a %d): ", (turno % 2) ? 1 : 2, n - 1);
        scanf("%d", &iAtacante);
        printf("Escolha o território DEFENSOR (0 a %d): ", n - 1);
        scanf("%d", &iDefensor);

        // Validações
        if (iAtacante == iDefensor) {
            printf("Um território não pode atacar a si mesmo!\n");
            continue;
        }
        if (strcmp(territorios[iAtacante].cor, territorios[iDefensor].cor) == 0) {
            printf("Você não pode atacar um território da mesma cor!\n");
            continue;
        }

        atacar(&territorios[iAtacante], &territorios[iDefensor]);

        // Verificação silenciosa de missão
        if (turno % 2) {
            if (verificarMissao(missaoJogador1, territorios, n)) {
                printf("\n🏆 Jogador 1 CUMPRIU sua missão: %s!\n", missaoJogador1);
                vencedor = 1;
            }
        } else {
            if (verificarMissao(missaoJogador2, territorios, n)) {
                printf("\n🏆 Jogador 2 CUMPRIU sua missão: %s!\n", missaoJogador2);
                vencedor = 2;
            }
        }

        turno++;
    }

    printf("\n=== FIM DE JOGO ===\n");
    printf("VENCEDOR: Jogador %d!\n", vencedor);

    liberarMemoria(territorios, missaoJogador1, missaoJogador2);
    return 0;
}

// ---------- Funções Auxiliares ----------

// Exibe os territórios
void exibirTerritorios(Territorio* territorios, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritório %d:\n", i);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("----------------------\n");
    }
}

// Função de ataque (simula dados de 1 a 6)
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n%s (%s) está atacando %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(">>> %s conquistou o território!\n", atacante->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf(">>> %s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// Sorteia uma missão e copia para o destino
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Verifica se a missão foi cumprida (lógica simples)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de verificação simples:
    if (strstr(missao, "vermelha")) {
        // Missão: eliminar todos da cor vermelha
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0; // Ainda há inimigos vermelhos
            }
        }
        return 1; // Todos eliminados
    }

    if (strstr(missao, "3 territorios")) {
        // Missão: ter 3 territórios consecutivos da mesma cor
        for (int i = 0; i < tamanho - 2; i++) {
            if (strcmp(mapa[i].cor, mapa[i + 1].cor) == 0 &&
                strcmp(mapa[i].cor, mapa[i + 2].cor) == 0) {
                return 1;
            }
        }
    }

    // Outras missões podem ser expandidas futuramente
    return 0;
}

// Libera memória alocada dinamicamente
void liberarMemoria(Territorio* territorios, char* missaoJogador1, char* missaoJogador2) {
    free(territorios);
    free(missaoJogador1);
    free(missaoJogador2);
}

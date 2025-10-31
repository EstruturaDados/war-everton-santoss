// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
#include <string.h>

struct Territorio {
    char nome[30];   
    char cor[10];    
    int tropas;      
};

int main() {
    
    struct Territorio territorios[5];

    
    int i;

    printf("=== Cadastro de Territórios ===\n\n");

    
    for (i = 0; i < 5; i++) {
        printf("Cadastro do Território %d\n", i + 1);

        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome); 

        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor); 

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n"); 
    }

    
    printf("\n=== Territórios Cadastrados ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }

    return 0;
}
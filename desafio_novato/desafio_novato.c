#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERRITORIO 5
#define TAM_STRING 30

struct territorio {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int quantidade;
};

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    struct territorio terra[MAX_TERRITORIO];
    int totalTerritorio = 0;
    int opcao;

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Cadastrar território\n");
        printf("2 - Listar territórios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                printf("\n--- Cadastro do Território ---\n");

                if (totalTerritorio < MAX_TERRITORIO) {
                    printf("Digite o nome do território: ");
                    fgets(terra[totalTerritorio].nome, TAM_STRING, stdin);
                    terra[totalTerritorio].nome[strcspn(terra[totalTerritorio].nome, "\n")] = '\0';

                    printf("Digite a cor do Exército: ");
                    fgets(terra[totalTerritorio].cor, TAM_STRING, stdin);
                    terra[totalTerritorio].cor[strcspn(terra[totalTerritorio].cor, "\n")] = '\0';

                    printf("Digite a quantidade de tropas: ");
                    scanf("%d", &terra[totalTerritorio].quantidade);
                    limparBufferEntrada();

                    // Exibir o território recém-cadastrado
                    printf("\n--- Território Cadastrado ---\n");
                    printf("Nome: %s\n", terra[totalTerritorio].nome);
                    printf("Cor: %s\n", terra[totalTerritorio].cor);
                    printf("Quantidade de tropas: %d\n", terra[totalTerritorio].quantidade);

                    totalTerritorio++; // Incrementar após exibir

                } else {
                    printf("Território cheio! Não é possível cadastrar mais territórios!\n");
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2:
                printf("\n--- Lista de territórios cadastrados ---\n");

                if (totalTerritorio == 0) {
                    printf("Nenhum território foi cadastrado.\n");
                } else {
                    for (int i = 0; i < totalTerritorio; i++) {
                        printf("\nTerritório %d:\n", i + 1);
                        printf("Nome: %s\n", terra[i].nome);
                        printf("Cor: %s\n", terra[i].cor);
                        printf("Quantidade de tropas: %d\n", terra[i].quantidade);
                    }
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }

    } while (opcao != 0);

    return 0;
}
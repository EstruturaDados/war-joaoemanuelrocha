#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_STRING 30
#define QTD_MISSOES 5
#define MAX_JOGADORES 2

typedef struct {
    char nome[TAM_STRING];
    char cor[TAM_STRING];
    int quantidade;
} Territorio;

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Digite o nome do território: ");
        fgets(mapa[i].nome, TAM_STRING, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Digite a cor do Exército: ");
        fgets(mapa[i].cor, TAM_STRING, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].quantidade);
        limparBufferEntrada();
    }
}

// Função para exibir territórios
void exibirTerritorios(Territorio* mapa, int total) {
    printf("\n--- Lista de territórios ---\n");
    for (int i = 0; i < total; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Quantidade de tropas: %d\n", mapa[i].quantidade);
    }
}

// Função para simular um ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nErro: Não é permitido atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->quantidade < 2) {
        printf("\nErro: O território atacante precisa ter pelo menos 2 tropas para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\nDados de batalha:\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor); // muda a cor
        defensor->quantidade = atacante->quantidade / 2;
        atacante->quantidade = atacante->quantidade / 2;
    } else {
        printf("\nO defensor venceu a batalha!\n");
        atacante->quantidade -= 1;
    }

    printf("\nEstado após a batalha:\n");
    printf("Atacante: %s | Tropas: %d | Cor: %s\n", atacante->nome, atacante->quantidade, atacante->cor);
    printf("Defensor: %s | Tropas: %d | Cor: %s\n", defensor->nome, defensor->quantidade, defensor->cor);
}

// Função que sorteia e atribui uma missão a um jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Função para verificar se uma missão foi cumprida (lógica simplificada)
int verificarMissao(char* missao, Territorio* mapa, int total) {
    // Exemplo: missão "Conquistar 3 territórios seguidos"
    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        int contador = 1;
        for (int i = 1; i < total; i++) {
            if (strcmp(mapa[i].cor, mapa[i - 1].cor) == 0) {
                contador++;
                if (contador == 3) return 1;
            } else {
                contador = 1;
            }
        }
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].quantidade > 0) {
                return 0;
            }
        }
        return 1;
    }
    // Outras missões podem ser adicionadas aqui...
    return 0;
}

// Função para exibir a missão (uma vez)
void exibirMissao(const char* missao) {
    printf("\n--- SUA MISSÃO ---\n");
    printf("%s\n", missao);
}

// Função para liberar a memória
void liberarMemoria(Territorio* mapa, char** missoesJogadores, int totalJogadores) {
    free(mapa);
    for (int i = 0; i < totalJogadores; i++) {
        free(missoesJogadores[i]);
    }
    free(missoesJogadores);
}

int main() {
    srand(time(NULL));

    // Missões disponíveis
    char* missoesDisponiveis[QTD_MISSOES] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar todos os territorios com mais de 5 tropas",
        "Conquistar pelo menos 2 territorios de cada cor",
        "Manter controle de 4 territorios ate o fim do jogo"
    };

    int totalTerritorio, opcao;
    printf("Digite o número total de territórios a serem cadastrados: ");
    scanf("%d", &totalTerritorio);
    limparBufferEntrada();

    // Alocação do mapa
    Territorio* mapa = (Territorio*) calloc(totalTerritorio, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Alocação e atribuição de missões
    char** missoesJogadores = (char**) malloc(MAX_JOGADORES * sizeof(char*));
    for (int i = 0; i < MAX_JOGADORES; i++) {
        missoesJogadores[i] = (char*) malloc(100 * sizeof(char));
        atribuirMissao(missoesJogadores[i], missoesDisponiveis, QTD_MISSOES);
    }

    cadastrarTerritorios(mapa, totalTerritorio);

    // Exibe missão apenas uma vez
    for (int i = 0; i < MAX_JOGADORES; i++) {
        printf("\nJogador %d, ", i + 1);
        exibirMissao(missoesJogadores[i]);
    }

    do {
        printf("\n--- MENU ---\n");
        printf("1 - Listar territórios\n");
        printf("2 - Atacar território\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, totalTerritorio);
                printf("\nPressione Enter para continuar...");
                getchar();
                break;

            case 2: {
                if (totalTerritorio < 2) {
                    printf("É necessário ter pelo menos dois territórios cadastrados.\n");
                    break;
                }

                exibirTerritorios(mapa, totalTerritorio);
                int iAtacante, iDefensor;

                printf("\nEscolha o número do território atacante: ");
                scanf("%d", &iAtacante);
                printf("Escolha o número do território defensor: ");
                scanf("%d", &iDefensor);
                limparBufferEntrada();

                if (iAtacante < 1 || iAtacante > totalTerritorio || iDefensor < 1 || iDefensor > totalTerritorio) {
                    printf("Índice inválido.\n");
                    break;
                }

                if (iAtacante == iDefensor) {
                    printf("Um território não pode atacar a si mesmo.\n");
                    break;
                }

                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);

                // Verifica missões após ataque
                for (int i = 0; i < MAX_JOGADORES; i++) {
                    if (verificarMissao(missoesJogadores[i], mapa, totalTerritorio)) {
                        printf("\n🎉 Jogador %d venceu cumprindo a missão:\n%s\n", i + 1, missoesJogadores[i]);
                        liberarMemoria(mapa, missoesJogadores, MAX_JOGADORES);
                        return 0;
                    }
                }

                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            }

            case 0:
                printf("\nSaindo do sistema...\n");
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missoesJogadores, MAX_JOGADORES);
    return 0;
}

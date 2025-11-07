#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Protótipos das funções
Territorio* cadastrarTerritorios(int quantidade);
void exibirTerritorios(Territorio* mapa, int quantidade);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);
void limparBuffer();

int main() {
    // Inicializar a semente para números aleatórios
    srand(time(NULL));

    int quantidade;
    Territorio* mapa = NULL;

    printf("=== SIMULACAO DE BATALHA ENTRE TERRITORIOS ===\n\n");

    // Solicitar quantidade de territórios
    printf("Digite o numero total de territorios: ");
    scanf_s("%d", &quantidade);
    limparBuffer();

    if (quantidade <= 0) {
        printf("Erro: Quantidade deve ser maior que zero!\n");
        return 1;
    }

    // Cadastrar territórios
    mapa = cadastrarTerritorios(quantidade);
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("\n=== TERRITORIOS CADASTRADOS ===\n");
    exibirTerritorios(mapa, quantidade);

    // Loop principal de ataques
    int continuar = 1;
    while (continuar) {
        printf("\n=== FASE DE ATAQUE ===\n");

        // Exibir territórios disponíveis para ataque
        printf("\nTerritorios disponiveis:\n");
        for (int i = 0; i < quantidade; i++) {
            printf("%d. %s (%s) - %d tropas\n",
                i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }

        // Selecionar atacante
        int idxAtacante, idxDefensor;
        printf("\nSelecione o territorio ATACANTE (numero): ");
        scanf_s("%d", &idxAtacante);
        limparBuffer();
        idxAtacante--; // Ajustar para índice do vetor

        if (idxAtacante < 0 || idxAtacante >= quantidade) {
            printf("Territorio invalido!\n");
            continue;
        }

        // Selecionar defensor
        printf("Selecione o territorio DEFENSOR (numero): ");
        scanf_s("%d", &idxDefensor);
        limparBuffer();
        idxDefensor--; // Ajustar para índice do vetor

        if (idxDefensor < 0 || idxDefensor >= quantidade) {
            printf("Territorio invalido!\n");
            continue;
        }

        // Validar ataque
        if (idxAtacante == idxDefensor) {
            printf("Erro: Um territorio nao pode atacar a si mesmo!\n");
            continue;
        }

        if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
            printf("Erro: Nao pode atacar um territorio da mesma cor!\n");
            continue;
        }

        if (mapa[idxAtacante].tropas <= 1) {
            printf("Erro: Territorio atacante precisa de pelo menos 2 tropas para atacar!\n");
            continue;
        }

        // Realizar ataque
        printf("\n=== INICIANDO ATAQUE ===\n");
        printf("%s (%s) esta atacando %s (%s)!\n",
            mapa[idxAtacante].nome, mapa[idxAtacante].cor,
            mapa[idxDefensor].nome, mapa[idxDefensor].cor);

        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

        // Exibir situação após o ataque
        printf("\n=== SITUACAO APOS O ATAQUE ===\n");
        exibirTerritorios(mapa, quantidade);

        // Verificar se deseja continuar
        printf("\nDeseja realizar outro ataque? (1 - Sim, 0 - Nao): ");
        scanf_s("%d", &continuar);
        limparBuffer();
    }

    // Liberar memória alocada
    liberarMemoria(mapa);

    printf("\n=== FIM DA SIMULACAO ===\n");
    return 0;
}

// Função para cadastrar territórios
Territorio* cadastrarTerritorios(int quantidade) {
    // Alocar memória dinamicamente para o vetor de territórios
    Territorio* territorios = (Territorio*)calloc(quantidade, sizeof(Territorio));

    if (territorios == NULL) {
        return NULL;
    }

    // Cores disponíveis para os exércitos
    char cores[][10] = { "Vermelho", "Azul", "Verde", "Amarelo", "Preto", "Branco" };
    int numCores = 6;

    for (int i = 0; i < quantidade; i++) {
        printf("\n--- Cadastro do Territorio %d ---\n", i + 1);

        // Nome do território
        printf("Digite o nome do territorio: ");
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remover quebra de linha

        // Cor do exército (atribuição automática)
        strcpy_s(territorios[i].cor, sizeof(territorios[i].cor), cores[i % numCores]);
        printf("Cor do exercito atribuida: %s\n", territorios[i].cor);

        // Número de tropas (inicial entre 5 e 15)
        territorios[i].tropas = 5 + (rand() % 11);
        printf("Tropas iniciais: %d\n", territorios[i].tropas);
    }

    return territorios;
}

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* mapa, int quantidade) {
    printf("\n=== MAPA DE TERRITORIOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Territorio %d: %s | Exercito: %s | Tropas: %d\n",
            i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    // Simular dados de batalha (1-6 para cada lado)
    int dadoAtacante = 1 + (rand() % 6);
    int dadoDefensor = 1 + (rand() % 6);

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // Determinar vencedor
    if (dadoAtacante > dadoDefensor) {
        // Atacante vence
        printf("\n>>> VITORIA DO ATACANTE! <<<\n");

        // Defensor perde todas as tropas
        int tropasPerdidasDefensor = defensor->tropas;
        defensor->tropas = 0;

        // Atacante perde 1 tropa
        atacante->tropas -= 1;

        // Transferir cor e metade das tropas do atacante para o defensor
        strcpy_s(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        // Atacante mantém metade das tropas (arredondando para cima)
        atacante->tropas = (atacante->tropas + 1) / 2;

        printf("O territorio defensor agora pertence ao exercito %s!\n", defensor->cor);
        printf("Tropas perdidas pelo defensor: %d\n", tropasPerdidasDefensor);

    }
    else if (dadoDefensor > dadoAtacante) {
        // Defensor vence
        printf("\n>>> VITORIA DO DEFENSOR! <<<\n");

        // Atacante perde 1 tropa
        atacante->tropas -= 1;

        printf("O defensor manteve seu territorio!\n");
        printf("O atacante perdeu 1 tropa.\n");

    }
    else {
        // Empate - defensor vence por defender
        printf("\n>>> EMPATE - DEFENSOR VENCE! <<<\n");

        // Atacante perde 1 tropa
        atacante->tropas -= 1;

        printf("Em caso de empate, o defensor vence!\n");
        printf("O atacante perdeu 1 tropa.\n");
    }

    printf("Situacao apos a batalha:\n");
    printf("Atacante (%s): %d tropas\n", atacante->nome, atacante->tropas);
    printf("Defensor (%s): %d tropas | Exercito: %s\n",
        defensor->nome, defensor->tropas, defensor->cor);
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio* mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("Memoria liberada com sucesso!\n");
    }
}

// Função auxiliar para limpar o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
#include <stdio.h>
#include <stdlib.h> // Para malloc
#include <string.h> // Para strcpy

/**
 * @brief Estrutura para representar um cômodo (sala) da mansão.
 * Cada sala é um nó na árvore binária.
 */
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda; // Caminho para a sala à esquerda (filho esquerdo)
    struct Sala *direita;  // Caminho para a sala à direita (filho direito)
} Sala;

/**
 * @brief Cria uma nova sala com alocação dinâmica.
 * @param nome O nome do cômodo.
 * @return Sala* Um ponteiro para a nova sala criada.
 */
Sala* criarSala(const char *nome) {
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a sala");
        exit(EXIT_FAILURE);
    }
    
    // Copia o nome para o campo 'nome' da struct
    strncpy(novaSala->nome, nome, 49);
    novaSala->nome[49] = '\0'; // Garante terminação nula
    
    // Inicializa os ponteiros dos caminhos como nulos
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Permite a exploração interativa da mansão.
 * O jogador escolhe ir para a esquerda ('e') ou direita ('d').
 * A exploração continua até que o jogador chegue a um nó-folha.
 * @param atual O ponteiro para a sala atual onde o jogador está.
 */
void explorarSalas(Sala *atual) {
    char escolha;
    Sala *proximo = atual;

    printf("\n--- 🧭 Explorando a Mansão ---\n");
    
    // Loop de exploração: continua enquanto houver um caminho
    while (proximo != NULL) {
        atual = proximo; // A sala atual é a próxima sala visitada
        
        printf("\nVocê está em: **%s**\n", atual->nome);

        // Verifica se é um nó-folha (sem caminhos para esquerda ou direita)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("FIM DA LINHA! Este cômodo não tem mais saídas. Missão cumprida!\n");
            return; // Encerra a exploração
        }

        // Guia o jogador nas opções de navegação
        printf("Para onde você quer ir? ");
        if (atual->esquerda != NULL) {
            printf("[e] Esquerda (%s) ", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("[d] Direita (%s) ", atual->direita->nome);
        }
        printf("ou [s] Sair da exploração: ");

        // Limpa o buffer antes de ler o char para evitar problemas de leitura
        while (getchar() != '\n'); 
        scanf(" %c", &escolha);

        proximo = NULL; // Reset para a próxima iteração
        
        switch (escolha) {
            case 'e':
            case 'E':
                if (atual->esquerda != NULL) {
                    proximo = atual->esquerda;
                } else {
                    printf("❌ Não há um cômodo para a ESQUERDA. Tente novamente.\n");
                }
                break;
            case 'd':
            case 'D':
                if (atual->direita != NULL) {
                    proximo = atual->direita;
                } else {
                    printf("❌ Não há um cômodo para a DIREITA. Tente novamente.\n");
                }
                break;
            case 's':
            case 'S':
                printf("Encerrando a exploração. Voltando para o Hall de Entrada.\n");
                return; // Encerra a exploração
            default:
                printf("❌ Opção inválida. Digite 'e', 'd' ou 's'.\n");
                break;
        }
    }
}

/**
 * @brief Libera a memória alocada dinamicamente para a árvore.
 * Função importante para boas práticas de programação.
 * @param raiz O nó raiz da subárvore a ser desalocada.
 */
void liberarMemoria(Sala *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarMemoria(raiz->esquerda);
    liberarMemoria(raiz->direita);
    
    // Libera o nó atual
    // printf("Desalocando: %s\n", raiz->nome); // Opcional para debug
    free(raiz);
}

// --------------------- FUNÇÃO PRINCIPAL ---------------------

/**
 * @brief Monta o mapa inicial da mansão (árvore binária) e inicia a exploração.
 */
int main() {
    printf("--- DETECTIVE QUEST: Iniciando a Simulação de Mapa ---\n");

    // 1. Criação e montagem da árvore binária (Mapa da Mansão)
    
    // Nível 0: Raiz
    Sala *hallEntrada = criarSala("Hall de Entrada");

    // Nível 1
    Sala *salaEstar = criarSala("Sala de Estar");
    Sala *cozinha = criarSala("Cozinha");
    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;

    // Nível 2
    Sala *escritorio = criarSala("Escritório");
    Sala *jardim = criarSala("Jardim");
    Sala *biblioteca = criarSala("Biblioteca");
    salaEstar->esquerda = escritorio;
    salaEstar->direita = jardim;
    cozinha->direita = biblioteca; // Cozinha só tem caminho para a direita

    // Nível 3 (Nós-folha para o nível novato)
    Sala *quartoPrincipal = criarSala("Quarto Principal");
    Sala *salaJantar = criarSala("Sala de Jantar");
    jardim->esquerda = quartoPrincipal;
    biblioteca->direita = salaJantar;
    
    // Nós-folha (salas sem caminhos adicionais)
    // - Escritório (Nível 2)
    // - Quarto Principal (Nível 3)
    // - Sala de Jantar (Nível 3)

    printf("Mapa da Mansão (Árvore Binária) Criado Automaticamente.\n");

    // 2. Início da Exploração Interativa
    explorarSalas(hallEntrada);

    // 3. Limpeza de memória
    printf("\nFinalizando o programa. Liberando memória alocada...\n");
    liberarMemoria(hallEntrada);
    
    printf("Memória liberada com sucesso.\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura do Pokémon
typedef struct {
    char nome[20];
    int ataque;
    int defesa;
    int vida;
    char tipo[10];
} Pokemon;

// Função para ler dados de Pokémon de um arquivo
void ler_dados_pokemon(FILE *arquivo, Pokemon pokemons[], int n) {
    for (int i = 0; i < n; i++) {
        fscanf(arquivo, "%s %d %d %d %s", pokemons[i].nome, &pokemons[i].ataque, &pokemons[i].defesa, &pokemons[i].vida, pokemons[i].tipo);
    }
}

// Função para determinar o dano causado por um ataque
int calcular_dano(Pokemon atacante, Pokemon defensor) {
    int dano = atacante.ataque - defensor.defesa;
    if (strcmp(atacante.tipo, defensor.tipo) == 0) {
        dano = dano / 2;
    } else if ((strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Água") == 0) ||
               (strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Fogo") == 0) ||
               (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Gelo") == 0) ||
               (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Pedra") == 0) ||
               (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Elétrico") == 0)) {
        dano = dano * 1.2;
    } else if ((strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Elétrico") == 0) ||
               (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Água") == 0) ||
               (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Fogo") == 0) ||
               (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Gelo") == 0) ||
               (strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Pedra") == 0)) {
        dano = dano / 1.2;
    }
    return dano;
}

// Função para simular uma batalha entre dois Pokémon
void batalhar(Pokemon *p1, Pokemon *p2) {
    int dano_p1 = calcular_dano(*p1, *p2);
    int dano_p2 = calcular_dano(*p2, *p1);

    if (dano_p1 > dano_p2) {
        printf("%s venceu %s\n", p1->nome, p2->nome);
    } else if (dano_p2 > dano_p1) {
        printf("%s venceu %s\n", p2->nome, p1->nome);
    } else {
        printf("Empate entre %s e %s\n", p1->nome, p2->nome);
    }
}

// Função principal do jogo
void jogar(char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int numero_pokemons_p1, numero_pokemons_p2;
    fscanf(file, "%d %d", &numero_pokemons_p1, &numero_pokemons_p2);

    Pokemon *pokemons1 = malloc(numero_pokemons_p1 * sizeof(Pokemon));
    Pokemon *pokemons2 = malloc(numero_pokemons_p2 * sizeof(Pokemon));

    ler_dados_pokemon(file, pokemons1, numero_pokemons_p1);
    ler_dados_pokemon(file, pokemons2, numero_pokemons_p2);

    fclose(file);

    // Simulando as batalhas
    int vitorias_p1 = 0, vitorias_p2 = 0;
    printf("Como saída, o programa deverá imprimir o resultado de cada batalha realizada entre os treinadores,\n"
           "o jogador que venceu, seus pokémon sobreviventes e os pokémon derrotados do jogador 1 e do jogador 2, respectivamente.\n\n");

    for (int i = 0; i < numero_pokemons_p1; i++) {
        for (int j = 0; j < numero_pokemons_p2; j++) {
            printf("Batalha entre %s e %s:\n", pokemons1[i].nome, pokemons2[j].nome);
            batalhar(&pokemons1[i], &pokemons2[j]);
            printf("\n");
        }
    }

    // Contando vitorias
    for (int i = 0; i < numero_pokemons_p1; i++) {
        for (int j = 0; j < numero_pokemons_p2; j++) {
            int dano_p1 = calcular_dano(pokemons1[i], pokemons2[j]);
            int dano_p2 = calcular_dano(pokemons2[j], pokemons1[i]);

            if (dano_p1 > dano_p2) {
                vitorias_p1++;
            } else if (dano_p2 > dano_p1) {
                vitorias_p2++;
            }
        }
    }

    // Exibindo resultados finais
    printf("Jogador 1 ");
    if (vitorias_p1 > vitorias_p2) {
        printf("venceu\n");
    } else if (vitorias_p2 > vitorias_p1) {
        printf("venceu\n");
    } else {
        printf("e Jogador 2 empataram\n");
    }

    printf("Pokémon sobreviventes do Jogador 1:\n");
    for (int i = 0; i < numero_pokemons_p1; i++) {
        printf("%s\n", pokemons1[i].nome);
    }

    printf("Pokémon derrotados do Jogador 1:\n");
    for (int i = 0; i < numero_pokemons_p1; i++) {
        printf("%s\n", pokemons1[i].nome);
    }

    printf("Pokémon sob

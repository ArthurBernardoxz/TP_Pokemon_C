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

//Função para determinar o dano causado por um ataque
int calcular_dano(Pokemon atacante, Pokemon defensor) {
    int dano = atacante.ataque - defensor.defesa;
    if(strcmp(atacante.tipo, defensor.tipo) == 0){
        dano = dano;
    } else if((strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Água") == 0) || (strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Fogo") == 0) || (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Gelo")==0) || (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Pedra")==0) || (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Elétrico")==0)) {
        dano = dano * 1.2;
    } else if((strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Pedra") == 0) || (strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Elétrico") == 0) || (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Água")==0) || (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Fogo")==0) || (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Gelo")==0)) {
        dano = dano * 0.8;
    }
    return dano;
}

// Função para ler dados de Pokémon de um arquivo
void ler_dados(FILE *arquivo, Pokemon pokemons[], int n) {
    for(int i = 0; i < n; i++) {
        fscanf(arquivo, "%s %d %d %d %s", pokemons[i].nome, &pokemons[i].ataque, &pokemons[i].defesa, &pokemons[i].vida, pokemons[i].tipo);
    }
}

int lutar(Pokemon *p1, Pokemon *p2) {
    int dano_p1 = calcular_dano(*p1, *p2);
    int dano_p2 = calcular_dano(*p2, *p1);

    if (dano_p1 > p2->defesa) {
        p2->vida -= dano_p1;
        if (p2->vida <= 0) {
            printf("%s venceu %s\n", p1->nome, p2->nome);
            return 1;
        }
    } else if (dano_p2 > p1->defesa) {
        p1->vida -= dano_p2;
        if (p1->vida <= 0) {
            printf("%s venceu %s\n", p2->nome, p1->nome);
            return 2;
        }
    }
}

// Função principal para o jogo
void jogar(char *arquivo){
    FILE *file = fopen(arquivo, "r");
    if(file == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }
    int numero_pokemons_p1, numero_pokemons_p2, n_vitorias_P1 = 0, n_vitorias_P2 = 0, vitoria_atual;
    fscanf(file, "%d %d", &numero_pokemons_p1, &numero_pokemons_p2);

    Pokemon *P1 = malloc(numero_pokemons_p1 * sizeof(Pokemon));
    Pokemon *P2 = malloc(numero_pokemons_p2 * sizeof(Pokemon));


    ler_dados(file, P1, numero_pokemons_p1);
    ler_dados(file, P2, numero_pokemons_p2);

    fclose(file);
    for (int i = 0; i < numero_pokemons_p1; i++) {
        for (int j = 0; j < numero_pokemons_p2; j++) {
            vitoria_atual = lutar(&P1[i], &P2[j]);
            if (vitoria_atual == 1) {
                n_vitorias_P1++;
            } else if (vitoria_atual == 2) {
                n_vitorias_P2++;
            }
        }
    }
    if(n_vitorias_P1 > n_vitorias_P2){
        printf("Jogador 1 venceu");
    } else {
        printf("Jogador 2 venceu");
    }
    // Liberar a memória alocada
    free(P1);
    free(P2);
}

int main() {
    jogar("teste.txt");
    return 0;
}
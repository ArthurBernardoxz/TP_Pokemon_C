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
    }else if(())

}

// Função para ler dados de Pokémon de um arquivo
void ler_dados(FILE *arquivo, Pokemon pokemons[], int n) {
    for(int i = 0; i < n; i++) {
        fscanf(arquivo, "%s %d %d %d %s", pokemons[i].nome, &pokemons[i].ataque, &pokemons[i].defesa, &pokemons[i].vida, pokemons[i].tipo);
    }
}

void lutar (Pokemon *p1, Pokemon *p2){
    int dano_p1 = calcular_dano(*p1, *p2);
    int dano_p2 = calcular_dano(*p2, *p1);

}

// Função principal para o jogo
void jogar(char *arquivo){
    FILE *file = fopen(arquivo, "r");
    if(file == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return;
    }
    int numero_pokemons_p1, numero_pokemons_p2, n_vitorias_P1 = 0, n_vitorias_P2 = 0;
    fscanf(file, "%d %d", &numero_pokemons_p1, &numero_pokemons_p2);

    Pokemon *P1 = malloc(numero_pokemons_p1 * sizeof(Pokemon));
    Pokemon *P2 = malloc(numero_pokemons_p2 * sizeof(Pokemon));
    Pokemon *Pokemons_sobreviventes = malloc((numero_pokemons_p1 + numero_pokemons_p1) * sizeof(Pokemon));
    Pokemon *Pokemons_derrotados = malloc((numero_pokemons_p1 + numero_pokemons_p1) * sizeof(Pokemon));

    ler_dados(file, P1, numero_pokemons_p1);
    ler_dados(file, P2, numero_pokemons_p2);

    fclose(file);
    for(int i = 0; i < numero_pokemons_p1; i++){
        printf("%s %d %d %d %s\n", P1[i].nome, P1[i].ataque, P1[i].defesa, P1[i].vida, P1[i].tipo);
    }
    fclose(file);
    for(int i = 0; i < numero_pokemons_p2; i++){
        printf("%s %d %d %d %s\n", P2[i].nome, P2[i].ataque, P2[i].defesa, P2[i].vida, P2[i].tipo);
    }

    
    // Liberar a memória alocada
    free(P1);
    free(P2);
}

int main() {
    jogar("teste.txt");
    return 0;
}
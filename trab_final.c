#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do Pokémon
typedef struct {
    char nome[20];
    int ataque;
    int defesa;
    int vida;
    char tipo[10];
} Pokemon;

// Função para calcular o dano de um ataque
int calcularDano(Pokemon atacante, Pokemon defensor) {
    int dano = atacante.ataque - defensor.defesa;

    // Verifica a vantagem de tipo
    if(strcmp(atacante.tipo, defensor.tipo) == 0){
        dano = dano;
    } else if((strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Água") == 0) || (strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Fogo") == 0) || (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Gelo")==0) || (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Pedra")==0) || (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Elétrico")==0)) {
        dano = dano * 1.2; // Aumenta o dano em 20% se há vantagem de tipo
    } else if((strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Pedra") == 0) || (strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Elétrico") == 0) || (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Água")==0) || (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Fogo")==0) || (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Gelo")==0)) {
        dano = dano * 0.8; // Reduz o dano em 20% se há desvantagem de tipo
    }

    // Se o dano for menor que zero, não causa dano
    if (dano < 0) {
        dano = 0;
    }

    return dano;
}

// Função para ler dados de Pokémon de um arquivo
void lerDados(FILE *arquivo, Pokemon pokemons[], int n) {
    for(int i = 0; i < n; i++) {
        // Lê os dados de cada Pokémon do arquivo e os armazena na estrutura correspondente
        fscanf(arquivo, "%s %d %d %d %s", pokemons[i].nome, &pokemons[i].ataque, &pokemons[i].defesa, &pokemons[i].vida, pokemons[i].tipo);
    }
}

// Função para simular uma batalha entre dois Pokémon
int batalhar(Pokemon *p1, Pokemon *p2) {
    while (p1->vida > 0 && p2->vida > 0) {
        int danoP1 = calcularDano(*p1, *p2);
        int danoP2 = calcularDano(*p2, *p1);

        // Se o dano de um atacante for menor que a defesa do defensor, o atacante perde 1 ponto de vida
        if (danoP1 <= p2->defesa) {
            p1->vida -= 1;
        }
        if (danoP2 <= p1->defesa) {
            p2->vida -= 1;
        }

        // Verifica se algum Pokémon ficou com a vida zerada
        if (p1->vida <= 0) {
            printf("%s venceu %s\n", p2->nome, p1->nome);
            return 2; // Retorna 2 indicando que p2 venceu
        } else if (p2->vida <= 0) {
            printf("%s venceu %s\n", p1->nome, p2->nome);
            return 1; // Retorna 1 indicando que p1 venceu
        }
    }
    return 0; // Empate
}

// Função principal do programa
int main() {
    FILE *file = fopen("teste.txt", "r");
    if(file == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return 1; // Retorna 1 em caso de erro ao abrir o arquivo
    }

    // Variáveis para armazenar o número de Pokémon de cada jogador e o resultado das batalhas
    int numeroPokemonsP1, numeroPokemonsP2, vitoriasP1 = 0, vitoriasP2 = 0, resultadoBatalha;

    // Lê o número de Pokémon de cada jogador do arquivo
    fscanf(file, "%d %d", &numeroPokemonsP1, &numeroPokemonsP2);

    // Aloca memória para as equipes de Pokémon de cada jogador
    Pokemon *equipeP1 = malloc(numeroPokemonsP1 * sizeof(Pokemon));
    Pokemon *equipeP2 = malloc(numeroPokemonsP2 * sizeof(Pokemon));

    // Lê os dados dos Pokémon de cada jogador do arquivo
    lerDados(file, equipeP1, numeroPokemonsP1);
    lerDados(file, equipeP2, numeroPokemonsP2);

    // Fecha o arquivo após a leitura dos dados
    fclose(file);

    // Simula as batalhas entre os Pokémon de ambos os jogadores
    for (int i = 0; i < numeroPokemonsP1; i++) {
        for (int j = 0; j < numeroPokemonsP2; j++) {
            resultadoBatalha = batalhar(&equipeP1[i], &equipeP2[j]);
            if (resultadoBatalha == 1) {
                vitoriasP1++; // Incrementa o número de vitórias do jogador 1
            } else if (resultadoBatalha == 2) {
                vitoriasP2++; // Incrementa o número de vitórias do jogador 2
            }
        }
    }

    // Imprime o resultado do jogo (quem venceu ou se houve empate)
    if(vitoriasP1 > vitoriasP2){
        printf("Jogador 1 venceu\n");
    } else if(vitoriasP1 < vitoriasP2){
        printf("Jogador 2 venceu\n");
    } else {
        printf("Empate\n");
    }

    // Imprime os Pokémon sobreviventes de cada jogador
    printf("Pokemons Sobreviventes\n");
    for(int y = 0; y < numeroPokemonsP1; y++){
        if(equipeP1[y].vida > 0){
            printf("%s\n", equipeP1[y].nome);
        }
    }
    for(int y = 0; y < numeroPokemonsP2; y++){
        if(equipeP2[y].vida > 0){
            printf("%s\n", equipeP2[y].nome);
        }
    }

    // Imprime os Pokémon derrotados de cada jogador
    printf("Pokemons Derrotados\n");
    for(int z = 0; z < numeroPokemonsP1; z++){
        if(equipeP1[z].vida <= 0){
            printf("%s ", equipeP1[z].nome);
        }
    }
    for(int z = 0; z < numeroPokemonsP2; z++){
        if(equipeP2[z].vida <= 0){
            printf("%s ", equipeP2[z].nome);
        }
    }

    // Libera a memória alocada para as equipes de Pokémon
    free(equipeP1);
    free(equipeP2);

    return 0; // Retorna 0 indicando sucesso
}
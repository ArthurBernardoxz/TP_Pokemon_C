#include <stdio.h> // Inclui a bibloteca com as funções de entrada e saída
#include <stdlib.h> // Inclui a biblioteca com as funções para alocação de memória
#include <string.h> // Inclui a biblioteca para conseguirmos manipular strings

#define TAMANHO_NOME 20
#define TAMANHO_TIPO 10


// Aqui definimos a variável estruturada Pokémon
typedef struct {
    char nome[TAMANHO_NOME]; // Variável para o nome do pokémon
    float ataque; // Variável para os pontos de ataque do pokémon
    int defesa; // Variável para os pontos de defesa do pokémon
    float vida; // Variável para os pontos de vida do pokémon
    char tipo[TAMANHO_TIPO]; // Variável para o tipo do pokémon
} Pokemon;

// Função para ler dados de Pokémon de um arquivo
void ler_dados(FILE *arquivo, Pokemon pokemons[], int n) {
    // Loop para ler os dados de cada Pokémon do arquivo
    for(int i = 0; i < n; i++) {
        if (fscanf(arquivo, "%s %f %d %f %s", pokemons[i].nome, &pokemons[i].ataque, &pokemons[i].defesa, &pokemons[i].vida, pokemons[i].tipo) != 5) { //tratamento de erros para o caso de falta de dados para a execução do programa 
            printf("Erro ao ler os dados do arquivo!\n");
            exit(1);
        }
        if (strlen(pokemons[i].nome) == 0 || pokemons[i].ataque <= 0 || pokemons[i].defesa <= 0 || pokemons[i].vida <= 0) { // tratamento de erros para o caso de valores negativos
            printf("Erro os valores para as variaveis inteiras (ataque, defesa e vida) devem ser todos inteiros!\n");
            exit(1);
        }
    }
}

// Função para calcular o dano de acordo com o tipo dos pokemons ao atacar
float calcular_dano(Pokemon atacante, Pokemon defensor) {
    float dano; // Usando float para precisão nos cálculos

    if((strcmp(atacante.tipo, "eletrico") == 0 && strcmp(defensor.tipo, "agua") == 0)||
       (strcmp(atacante.tipo, "agua") == 0 && strcmp(defensor.tipo, "fogo") == 0) || 
       (strcmp(atacante.tipo, "fogo") == 0 && strcmp(defensor.tipo, "gelo")== 0) || 
       (strcmp(atacante.tipo, "gelo") == 0 && strcmp(defensor.tipo, "pedra")== 0) || 
       (strcmp(atacante.tipo, "pedra") == 0 && strcmp(defensor.tipo, "eletrico")== 0)) {
        dano = atacante.ataque * 1.2; // Aumenta o dano em 20% para relações de tipo favoráveis
    } else if((strcmp(atacante.tipo, "eletrico") == 0 && strcmp(defensor.tipo, "pedra") == 0) ||
              (strcmp(atacante.tipo, "agua") == 0 && strcmp(defensor.tipo, "eletrico") == 0) ||
              (strcmp(atacante.tipo, "fogo") == 0 && strcmp(defensor.tipo, "agua")== 0) ||
              (strcmp(atacante.tipo, "gelo") == 0 && strcmp(defensor.tipo, "fogo")== 0) ||
              (strcmp(atacante.tipo, "pedra") == 0 && strcmp(defensor.tipo, "gelo")== 0)) {
        dano = atacante.ataque * 0.8; // Reduz o dano em 20% para relações de tipo desfavoráveis
    } else {
        dano = atacante.ataque; // Dano padrão se os tipos forem iguais
    }

    return dano; // Converte o dano de volta para int antes de retornar
}

void printP(Pokemon * p){
    printf("%s %f %d %f %s\n", p->nome, p->ataque, p->defesa, p->vida, p->tipo);
}

// Função para simular a luta entre dois pokemons
int lutar(Pokemon *p1, Pokemon *p2, int turno){
    // Loop para a luta acontecer enquanto os dois pokemons tiverem vida > 0, ou seja vivos
    while (p1->vida > 0 && p2->vida > 0) {

        if(turno){ //se turno igual a 1 o jogador 1 comeca atacando
            // primeiro calculamos o dano do primeiro pokemon
            float dano_p1 = calcular_dano(*p1, *p2);

            // Se o dano do pokemon 1 for maior que a defesa do pokemon 2, entao o pokemon 2 perde vida igual a diferenca do ataque pela defesa
            if (dano_p1 > p2->defesa) {
                p2->vida = p2->vida - (dano_p1 - p2->defesa);
            } else { // caso o contrario o pokemon 2 perde 1 de vida
                p2->vida--;
            }

            // Verifica se p2 foi derrotado
            if (p2->vida <= 0) {
                printf("%s venceu %s\n", p1->nome, p2->nome);
                return 1; // Retorna 1 indicando que pokemon 1 venceu
            }
            turno = 0;
        } else { //se turno igual a zero jogador 2 que joga
            // Ataque do p2 contra p1
            float dano_p2 = calcular_dano(*p2, *p1);
            // Se o dano do pokemon 2 for maior que a defesa do pokemon 1, entao o pokemon 1 perde vida igual a diferenca do ataque pela defesa
            if (dano_p2 > p1->defesa) {
                p1->vida = p1->vida - (dano_p2 - p1->defesa);
            } else { // caso o contrario o pokemon 1 perde 1 de vida
                p1->vida--;
            }

            // Verifica se p1 foi derrotado
            if (p1->vida <= 0) {
                printf("%s venceu %s\n", p2->nome, p1->nome);
                return 2; // Retorna 2 indicando que pokemon 2 venceu
            }
            turno = 1;
        }
    }
}



// Função principal para o jogo que pede como parametro um ponteiro para a posicao de memoria do arquivo
void jogar(char *arquivo){
    //1 Etapa - Declaração de variaveis e Leitura de dados

    FILE *file = fopen(arquivo, "r"); // Abre o arquivo no modo de leitura
    if(file == NULL) { // Aqui verificamos se ouve algum erro na abertura do arquivo
        perror("Erro ao abrir o arquivo.\n"); // Imprimi a mensagem de erro indicando que não foi possivel abrir o arquivo
        return; // Retorna a funcao antes logo encerrando o programa
    }
    
    int numero_pokemons_p1, numero_pokemons_p2, n_vitorias_P2 = 0, n_vitorias_P1 = 0, vitoria_atual = 0; //Declaracao das variaveis utilizadas durante o programa
    fscanf(file, "%d %d", &numero_pokemons_p1, &numero_pokemons_p2); // Lê do arquivo o número de pokemons do jogador 1 e 2 e atribui as respectivas variaveis

    //verificacao de limites de pokemons de cada jogador
    if(numero_pokemons_p1 > 100 || numero_pokemons_p2 > 100){
        perror("Erro: o numero maximo de pokemons para cada jogador e 100");
        return;
    }

    // ALocamos dinamicamente a quantidade de mémoria necessaria para armazenas os pokemons de cada jogador
    Pokemon *P1 = malloc(numero_pokemons_p1 * sizeof(Pokemon));
    //Verificação de erro de alocacao
    if(P1 == NULL){
        printf("Erro ao alocar memoria para o Jogador 1");
        free(P1);
        exit(1);
    }
    Pokemon *P2 = malloc(numero_pokemons_p2 * sizeof(Pokemon));
    if(P2 == NULL){
        printf("Erro ao alocar memoria para o Jogador 2");
        free(P2);
        exit(1);
    }
    // Lê os dados dos pokémons de cada jogador do arquivo
    ler_dados(file, P1, numero_pokemons_p1);
    ler_dados(file, P2, numero_pokemons_p2);

    fclose(file); // Agora que já lemos os dados que precisamos podemos fechar o arquivo

    // 2 Etapa - Simulacao das batalas
    //Loop para simular as batalhas entre os pokemons de cada jogador
    int turno = 1;
    while(n_vitorias_P2 < numero_pokemons_p1 && n_vitorias_P1 < numero_pokemons_p2){ // Para rodar enquanto numero de vitorias dos dois jogadores for menor que o numero de pokemons de cada jogador

        vitoria_atual = lutar(&P1[n_vitorias_P2], &P2[n_vitorias_P1], turno); // Realizamos a batalha entre dois pokemnos na posicao em que cada jogador venceu, pois se ele venceu e o nvitorias aumenta ele ja puxa o proximo pokeon

        // Estrutura para atualizar as vitorias de cada jogador
        if (vitoria_atual == 1) { // Se o retorno da funcao lutar foi 1 entao o jogador 1 venceu uma batalha
            n_vitorias_P1++; // Se o jogador numero 1 ganha aumenta o ndevitorias1
            turno = 0; //variavel utilizada para controlar qual jogador vai ataca se o turno é zero quem comeca atacando é o jogador 2
        } else if (vitoria_atual == 2) { // Se não se o retorno da funcao lutar foi 2 entao o jogador 2 venceu uma batalha
            n_vitorias_P2++; // Se o jogador numero 2 ganha aumenta o ndevitorias2
            turno = 1; // variavel utilizada para controlar qual jogador vai atacar seo turno é 1 quem comeca é o jogador 1
        }
    }

    // 3 Etapa - Verificar quem venceu a maioria das batalhas e assim quem venceu o jogo
    if(n_vitorias_P2 > n_vitorias_P1){
        printf("Jogador 2 venceu\n");
    } else {
        printf("Jogador 1 venceu\n");
    } 

    // 4 Etapa - Mostrar os Pokemons que sobreviveram as lutas 
    printf("Pokemons Sobreviventes\n");

    // Loop para mostrar os pokemons que sobreviveram do jogador 1
    for(int y = 0; y < numero_pokemons_p1; y++){
        if(P1[y].vida > 0){
            printf("%s\n", P1[y].nome);
        }
    }
    // Loop para mostrar os pokemons que sobreviveram do jogador 2
    for(int y = 0; y < numero_pokemons_p2; y++){
        if(P2[y].vida > 0){
            printf("%s\n", P2[y].nome);
        }
    }

    // 5 Etapa - Mostrar os pokemons que foram derrotados
    printf("Pokemons Derrotados\n");

    //Loop para mostrar os pokemons que foram derrotados do jogador 1
    for(int z = 0; z < numero_pokemons_p1; z++){
        if(P1[z].vida <= 0){
            printf("%s\n", P1[z].nome);
        }
    }
    //Loop para mostrar os pokemons que foram derrotados do Jogador 2
    for(int z = 0; z < numero_pokemons_p2; z++){
        if(P2[z].vida <= 0){
            printf("%s\n", P2[z].nome);
        }
    }

    //Liberar a memória alocada para os Pokémons
    free(P1);
    free(P2);
}

// Função principal do programa
int main() {
    jogar("teste2.txt"); // Chama a função jogar e passa o nome do arquivo como parametro
    return 0; // Retorno da funcao principal
}
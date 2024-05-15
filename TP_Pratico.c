#include <stdio.h> // Inclui a bibloteca com as funções de entrada e saída
#include <stdlib.h> // Inclui a biblioteca com as funções para alocação de memória
#include <string.h> // Inclui a biblioteca para conseguirmos manipular strings

// Aqui definimos a variável estruturada Pokémon
typedef struct {
    char nome[20]; // Variável para o nome do pokémon
    int ataque; // Variável para os pontos de ataque do pokémon
    int defesa; // Variável para os pontos de defesa do pokémon
    int vida; // Variável para os pontos de vida do pokémon
    char tipo[10]; // Variável para o tipo do pokémon
} Pokemon;

// Função para ler dados de Pokémon de um arquivo
void ler_dados(FILE *arquivo, Pokemon pokemons[], int n) {
    // Loop para ler os dados de cada Pokémon do arquivo
    for(int i = 0; i < n; i++) {
        if (fscanf(arquivo, "%s %d %d %d %s", pokemons[i].nome, &pokemons[i].ataque, &pokemons[i].defesa, &pokemons[i].vida, pokemons[i].tipo) != 5) { //tratamento de erros para o caso de falta de dados para a execução do programa 
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
int calcular_dano(Pokemon atacante, Pokemon defensor) {
    int dano = atacante.ataque - defensor.defesa;
    if(strcmp(atacante.tipo, defensor.tipo) == 0){
        dano = dano; // Dano padrão se os tipos forem iguais
    } else if((strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Água") == 0)||
     (strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Fogo") == 0) || 
     (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Gelo")==0) || 
     (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Pedra")==0) || 
     (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Elétrico")==0)) {
        dano = dano * 1.2; // Aumenta o dano em 20% para relações de tipo favoráveis
    } else if((strcmp(atacante.tipo, "Elétrico") == 0 && strcmp(defensor.tipo, "Pedra") == 0) ||
     (strcmp(atacante.tipo, "Água") == 0 && strcmp(defensor.tipo, "Elétrico") == 0) ||
      (strcmp(atacante.tipo, "Fogo") == 0 && strcmp(defensor.tipo, "Água")==0) ||
       (strcmp(atacante.tipo, "Gelo") == 0 && strcmp(defensor.tipo, "Fogo")==0) ||
        (strcmp(atacante.tipo, "Pedra") == 0 && strcmp(defensor.tipo, "Gelo")==0)) {
        dano = dano * 0.8; // Reduz o dano em 20% para relações de tipo desfavoráveis
    }

    return dano; // Retorna o dano calculado
}

// Função para simular a luta entre dois pokemons
int lutar(Pokemon *p1, Pokemon *p2){
    // Loop para a luta acontecer enquanto os dois pokemons tiverem vida > 0, ou seja vivos
    while (p1->vida > 0 && p2->vida > 0) {

        // primeiro calculamos o dano do primeiro pokemon
        int dano_p1 = calcular_dano(*p1, *p2);

        // Se o dano do pokemon 1 for maior que a defesa do pokemon 2, entao o pokemon 2 perde vida igual a diferenca do ataque pela defesa
        if (dano_p1 > p2->defesa) {
            p2->vida -= dano_p1;
        } else { // caso o contrario o pokemon 2 perde 1 de vida
            p2->vida--;
        }

        // Verifica se p2 foi derrotado
        if (p2->vida <= 0) {
            printf("%s venceu %s\n", p1->nome, p2->nome);
            return 1; // Retorna 1 indicando que pokemon 1 venceu
        }

        // Ataque do p2 contra p1
        int dano_p2 = calcular_dano(*p2, *p1);
        // Se o dano do pokemon 2 for maior que a defesa do pokemon 1, entao o pokemon 1 perde vida igual a diferenca do ataque pela defesa
        if (dano_p2 > p1->defesa) {
            p1->vida -= dano_p2;
        } else { // caso o contrario o pokemon 1 perde 1 de vida
            p1->vida--;
        }

        // Verifica se p1 foi derrotado
        if (p1->vida <= 0) {
            printf("%s venceu %s\n", p2->nome, p1->nome);
            return 2; // Retorna 2 indicando que pokemon 2 venceu
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
    
    int numero_pokemons_p1, numero_pokemons_p2, n_vitorias_P1 = 0, n_vitorias_P2 = 0, vitoria_atual; //Declaracao das variaveis utilizadas durante o programa
    fscanf(file, "%d %d", &numero_pokemons_p1, &numero_pokemons_p2); // Lê do arquivo o número de pokemons do jogador 1 e 2 e atribui as respectivas variaveis

    // ALocamos dinamicamente a quantidade de mémoria necessaria para armazenas os pokemons de cada jogador
    Pokemon *P1 = malloc(numero_pokemons_p1 * sizeof(Pokemon));
    Pokemon *P2 = malloc(numero_pokemons_p2 * sizeof(Pokemon));

    // Lê os dados dos pokémons de cada jogador do arquivo
    ler_dados(file, P1, numero_pokemons_p1);
    ler_dados(file, P2, numero_pokemons_p2);

    fclose(file); // Agora que já lemos os dados que precisamos podemos fechar o arquivo

    // 2 Etapa - Simulacao das batalas
    //Loop para simular as batalhas entre os pokemons de cada jogador
    for(int i = 0; i < numero_pokemons_p1; i++){
        for(int j = 0; j < numero_pokemons_p2; j++){
            vitoria_atual = lutar(&P1[i], &P2[j]); // Realizamos a batalha entre dois pokemnos

            // Estrutura para atualizar as vitorias de cada jogador
            if (vitoria_atual == 1) { // Se o retorno da funcao lutar foi 1 entao o jogador 1 venceu uma batalha
                n_vitorias_P1++;
            } else if (vitoria_atual == 2) { // Se não se o retorno da funcao lutar foi 2 entao o jogador 2 venceu uma batalha
                n_vitorias_P2++;
            }
        }
    }

    // 3 Etapa - Verificar quem venceu a maioria das batalhas e assim quem venceu o jogo
    if(n_vitorias_P1 > n_vitorias_P2){
        printf("Jogador 1 venceu\n");
    } else {
        printf("Jogador 2 venceu\n");
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
            printf("%s ", P1[z].nome);
        }
    }
    //Loop para mostrar os pokemons que foram derrotados do Jogador 2
    for(int z = 0; z < numero_pokemons_p2; z++){
        if(P2[z].vida <= 0){
            printf("%s ", P2[z].nome);
        }
    }

    //Liberar a memória alocada para os Pokémons
    free(P1);
    free(P2);
}

// Função principal do programa
int main() {
    jogar("teste.txt"); // Chama a função jogar e passa o nome do arquivo como parametro
    return 0; // Retorno da funcao principal
}
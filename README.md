## Índice

1. [Introdução](#introdução)
2. [Estrutura do Programa](#estrutura-do-programa)
3. [Estrutura de Dados](#estrutura-de-dados)
4. [Funções](#funções)
    - [ler_dados](#ler_dados)
    - [calcular_dano](#calcular_dano)
    - [lutar](#lutar)
    - [Jogar](#jogar)
    - [main](#main)
5. [Como Rodar](#como-rodar)
6. [Aprendizados e Considerações Finais](#aprendizados-e-considerações-finais)

## Introdução

O programa feito simula uma batalha pokémon entre dois jogadores. Onde cada jogador possui um determinado número de pokémons e eles se enfrentam até que um dos jogadores não tenha mais pokémons "vivos" naquela partida.

## Estrutura do Programa

O programa foi estruturado utilizando várias funções para desempenhar um papel específico durante a execução do programa. Veja:

- **Inclusão das bibliotecas:**
  - `stdlib.h`: Biblioteca utilizada para alocação de memória para as variáveis estruturadas Pokémon.
  - `string.h`: Biblioteca utilizada para manipulação das strings que surgem durante a execução.
  - `stdio.h`: Biblioteca utilizada para pegar as entradas e mostrar as saídas para o usuário.
- **Declaração da variável estruturada Pokémon com os atributos (Nome, ataque, defesa, vida e tipo)**
- **Função `ler_dados`:** Função responsável por ler os dados dos pokémons do arquivo de entrada e colocar nas variáveis que serão utilizadas durante o programa.
- **Função `calcular_dano`:** Função responsável por calcular o dano de ataque de cada pokémon levando em consideração o tipo do pokémon que está atacando e o tipo do pokémon que está recebendo o ataque.
- **Função `lutar`:** Função responsável por simular as lutas entre os pokémons, levando em consideração a vida de cada um e retornando que jogador venceu cada batalha.
- **Função `jogar`:** Função principal do jogo onde foi criada a lógica principal do programa, ou seja, declaração de variáveis, chamadas das outras funções e as saídas para o usuário.
- **Função `main`:** Função principal do programa, onde apenas chamamos a função `jogar`.

## Estrutura de Dados

`Pokemon` foi o nome dado à variável estruturada para guardarmos os atributos dos pokémons, então declaramos o nome como uma string de tamanho 20, o ataque, a defesa e a vida declaramos como inteiro e, por fim, uma string de tamanho 10 para o tipo de cada pokémon.

Em seguida, na função `jogar` foi alocado dinamicamente memória (`malloc`) para dois vetores de pokémons, onde seu tamanho é de acordo com a entrada do arquivo que indica o número de pokémons de cada jogador.

## Funções

### `ler_dados`

- **Descrição:** Função lê os dados dos Pokémon de um arquivo e os armazena em um array de estruturas `Pokemon`.
- **Parâmetros:**
  - `FILE *arquivo`: Ponteiro para o arquivo contendo os dados dos Pokémon.
  - `Pokemon pokemons[]`: Um vetor de variáveis estruturadas `Pokemon` para armazenar os dados lidos do arquivo.
  - `int n`: O número de Pokémon a serem lidos do arquivo.
- **Retorno:** A função não possui retorno, pois ela é do tipo `void`.

### `calcular_dano`

- **Descrição:** Esta função calcula o dano que um Pokémon que está atacando causa em outro Pokémon levando em consideração o tipo de cada um.
- **Parâmetros:**
  - `Pokemon atacante`: O `Pokemon` que está atacando.
  - `Pokemon defensor`: O `Pokemon` que está recebendo o ataque.
- **Retorno:** Retorna o dano calculado como inteiro para ser utilizado na função `lutar`.

### `lutar`

- **Descrição:** Função responsável por simular uma batalha entre dois Pokémon. Funciona da seguinte maneira: primeiro temos um if para verificar o turno, onde se turno é igual a 1 o jogador começa atacando e se turno é igual a 0 o jogador 2 começa atacando, ela executa enquanto os pokémons têm vida maior que 0.
- **Parâmetros:**
  - `Pokemon *p1`: Ponteiro para o Pokémon do jogador 1.
  - `Pokemon *p2`: Ponteiro para o Pokémon do jogador 2.
  - `int turno`: Inteiro para sabermos qual jogador vai começar atacando.
- **Retorno:** Retorna um valor inteiro indicando qual foi o resultado da batalha (1 para vitória do jogador 1 e 2 para vitória do jogador 2).

### `Jogar`

- **Descrição:** Função principal responsável por coordenar o jogo, lendo os dados do arquivo, simulando batalhas, determinando o vencedor, os pokémons sobreviventes e os pokémons derrotados. Para simular as batalhas, criei um loop que executa enquanto um jogador tem menos vitórias do que o número de pokémons do outro. Dentro do loop, quando o retorno da função `lutar` é 1, o número de vitórias do jogador 1 aumenta, e a próxima luta é simulada com o vetor de pokémons do jogador 2 na posição do número de vitórias e vice-versa. Dessa forma, foi possível implementar uma lógica que percorre os vetores à medida que cada jogador vence.
- **Parâmetros:**
  - `char *arquivos`: O nome do arquivo que contém os dados dos Pokémons que serão utilizados no programa.
- **Retorno:** Não possui retorno.

### `main`

- **Descrição:** Função principal do programa, onde chamamos a função `jogar` e informamos o nome do arquivo com os dados.
- **Parâmetros:** Não possui parâmetros.
- **Retorno:** 0.

## Como Rodar

Primeiro é necessário um arquivo `.txt` com entradas padronizadas para serem lidas durante o programa e utilizadas nas variáveis. Em seguida, deve-se colocar o arquivo de extensão `.txt` na mesma pasta que o executável gerado ao compilar o código C. Seguindo os passos descritos, basta apenas executar o código e realizar os testes.

### Exemplo de teste no meu Computador:

- **Diretório:**

- **txt de teste 1:**

- **saída:**

## Aprendizados e Considerações Finais

De forma geral o trabalho teve sim alguns momentos em que agarrei para resolver algumas coisas, mas no fim foi bem tranquilo. Por exemplo:

- A leitura dos dados do arquivo eu demorei bastante para entender como faria o programar ler o arquivo e extrair perfeitamente cada dado e depois atribuir a suas respectivas variáveis e propriedades. Logo, foi preciso pesquisar mais sobre o assunto e enfim conseguir suprir essa parte do trabalho.
- Além disso houve erros de lógica para as batalhas, pois diversas vezes chegava em resultados errados e na minha cabeça estava tudo certo, mas novamente com calma foi possível chegar as saídas esperadas.
- Por fim, a última parte que tive bastante trabalho foi na lógica dos turnos que demorei para conseguir pensar em algo, porém depois de diversas horas pensando consegui fazer funcionar tudo certinho.

Em relação à lógica desenvolvida, foi criada a estrutura Pokémon com os atributos necessários conforme as instruções. Em seguida, foi alocado dinamicamente um vetor de Pokémon, levando em consideração a quantidade de Pokémon de cada jogador. As funções foram divididas para garantir a organização e implementadas de acordo com seus objetivos específicos. Vale ressaltar que o código está totalmente comentado para facilitar ao máximo a compreensão.

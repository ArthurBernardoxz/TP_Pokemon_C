# Documentação do Trabalho Prático

Nome: Arthur Bernardo Alves Costa  
Matrícula: 2024099100  
Curso: Programação e Desenvolvimento de Software  

O programa simula uma batalha Pokémon entre dois jogadores. Cada jogador possui um número determinado de Pokémon, e eles se enfrentam até que um dos jogadores não tenha mais Pokémon "vivos" naquela partida.

## Estrutura do Programa
O programa é estruturado utilizando várias funções para desempenhar papéis específicos durante a execução. A estrutura inclui a inclusão das bibliotecas `stdlib.h`, `string.h`, e `stdio.h`, bem como a declaração da estrutura de dados Pokémon. As funções incluem "ler_dados", "calcular_dano", "lutar", "jogar", e "main".

## Estrutura de Dados
A estrutura de dados é composta pela variável estruturada Pokémon, que armazena os atributos dos Pokémon. São declarados os atributos: nome (string de tamanho 20), ataque, defesa e vida (inteiros), e tipo (string de tamanho 10) para cada Pokémon.

## Funções
### "ler_dados":
- **Descrição:** Lê os dados dos Pokémon de um arquivo e os armazena em um array de estruturas Pokémon.
- **Parâmetros:** `FILE *arquivo`, `Pokemon pokemons[]`, `int n`.
- **Retorno:** Void.

### "calcular_dano":
- **Descrição:** Calcula o dano que um Pokémon causará em outro, considerando o tipo de cada um.
- **Parâmetros:** `Pokemon atacante`, `Pokemon defensor`.
- **Retorno:** Dano calculado (inteiro).

### "lutar":
- **Descrição:** Simula uma batalha entre dois Pokémon.
- **Parâmetros:** `Pokemon *p1`, `Pokemon *p2`.
- **Retorno:** Resultado da batalha (1 para vitória do jogador 1, 2 para vitória do jogador 2).

### "Jogar":
- **Descrição:** Função principal responsável pela lógica do jogo.
- **Parâmetros:** `char *arquivos`.
- **Retorno:** Void.

### "main":
- **Descrição:** Função principal do programa, chama a função "jogar".
- **Parâmetros:** Void.
- **Retorno:** 0.

## Como Rodar
É necessário um arquivo .txt com entradas padronizadas. Coloque o arquivo .txt na mesma pasta que o executável gerado ao compilar o código C.

## Aprendizados e Considerações Finais
O trabalho apresentou desafios, especialmente na leitura dos dados do arquivo e na lógica das batalhas. A pesquisa e a resolução dos problemas foram fundamentais para o desenvolvimento do projeto. A estrutura do código foi cuidadosamente planejada e documentada, visando facilitar sua compreensão e manutenção.

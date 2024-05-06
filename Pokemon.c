#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
   /*int N_pokemons_P1, N_pokemons_P2;*/
   typedef struct Pokemon_P1 {
      char nome;
      int ataque;
      int defesa;
      int vida;
      char tipo;
   };
  /* typedef struct Pokemon_P2 {
      char nome;
      int ataque;
      int defesa;
      int vida;
      char tipo;
   };*/
   struct Pokemon_P1 P1;
   /*struct Pokemon_P2 P2;*/
   scanf("%s %d %d %d %s", P1.nome,&P1.ataque,&P1.defesa,&P1.vida,P1.tipo);   
   printf("%s %d %d %d %s", P1.nome,P1.ataque,P1.defesa,P1.vida,P1.tipo);   
   return 0;
}
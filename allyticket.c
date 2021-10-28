#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
struct filme
{
  char *nome;
  int classificacao;
  char *categoria;
};

typedef struct filme Filme;

void create(Filme *nomeFilme);

void read(Filme *nomeFilme);
void update();
void delete ();

int main()
{
  Filme dunha;
  Filme *dunhacptr = &dunha;
  char nome[30] = "Duna";
  dunha.nome = nome;
  dunha.classificacao = 0;
  char categoria[20] = "Sci-Fi";
  dunha.categoria = categoria;
  //create(dunhacptr);
  read(dunhacptr);
}

void create(Filme *nomeFilme)
{
  FILE *file;
  file = fopen("allyticket.txt", "a");
  fprintf(file, "\nNome: %s\nClassificacao: %d\nCategoria: %s", nomeFilme->nome, nomeFilme->classificacao, nomeFilme->categoria);
  fclose(file);
}
void read(Filme *nomeFilme)
{
  FILE *file;
  file = fopen("allyticket.txt", "r");

  if (file == NULL){
    printf("Arquivo nao encontrado.\n");
    return;
  }
  char nome[52];
  int classificacao;
  char categoria[52];
  fscanf(file, "%s %d %s", &nome, &classificacao, &categoria);
  printf("Nome: %s\nClassificacao: %d\nCategoria: %s\n", nome, classificacao, categoria);
  
  fclose(file);
}

void delete ()
{
}

void update()
{
}
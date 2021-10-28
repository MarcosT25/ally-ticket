#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
struct filme
{
  char *nome;
  char *classificacao;
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
  char classificacao[20] = "14";
  dunha.classificacao = classificacao;
  char categoria[20] = "Sci-Fi";
  dunha.categoria = categoria;
  //create(dunhacptr);
  read(dunhacptr);
}

void create(Filme *nomeFilme)
{
  FILE *file;
  file = fopen("allyticket.txt", "a");
  fprintf(file, "Nome: %s\nClassificacao: %s\nCategoria: %s\n", nomeFilme->nome, nomeFilme->classificacao, nomeFilme->categoria);
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
  char classificacao[52];
  char categoria[52];

  fgets(nome, sizeof(nome), file);
  fgets(classificacao, sizeof(classificacao), file);
  fgets(categoria, sizeof(categoria), file);

  printf("%s%s%s", nome, classificacao, categoria);
  fclose(file);
}

void delete ()
{
}

void update()
{
}
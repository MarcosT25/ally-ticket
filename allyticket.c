#include <stdio.h>
#include <stdbool.h>
struct filme
{
  char *nome;
  int classificacao;
  char *categoria;
};

typedef struct filme Filme;

void create(Filme *nomeFilme);

void read();
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
  create(dunhacptr);
}

void create(Filme *nomeFilme)
{
  FILE *file;
  file = fopen("allyticket.txt", "a");
  fprintf(file, "\nNome: %s\nClassificacao: %d\nCategoria: %s", nomeFilme->nome, nomeFilme->classificacao, nomeFilme->categoria);
  fclose(file);
}
void read()
{
}

void delete ()
{
}

void update()
{
}
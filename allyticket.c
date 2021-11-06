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

int tamanho_arquivo();
void create(Filme *nomeFilme);
void read();
void update(int filmeIndex, int filmeCampo);
void delete ();

int main()
{
  printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n0 - Sair\nEscolha: ");
  int escolha;
  scanf("%d", &escolha);
  while (escolha != 0) {
    if (escolha == 1) {
      Filme filme;
      char nome[52];
      printf("Digite o nome do filme a ser inserido: ");
      scanf("%s", &nome);
      filme.nome = nome;
      char classificacao[32];
      printf("Digite a classificação do filme: ");
      scanf("%s", classificacao);
      filme.classificacao = classificacao;
      char categoria[52];
      printf("Digite a categoria do filme: ");
      scanf("%s", &categoria);
      filme.categoria = categoria;
      Filme *filme_ptr = &filme;
      create(filme_ptr);
    }
    if (escolha == 2) {
      read();
    }
    if (escolha == 3) {
      printf("Os filmes disponíveis para edição e seus respectivos números são:\n");
      read();
      printf("Digite o número do filme que deseja editar: ");
      int escolhaFilme;
      scanf("%d", &escolhaFilme);
      printf("Qual campo deseja modificar?\n1 - Nome\n2 - Classificação\n3 - Categoria\nEscolha: ");
      int escolhaCampo;
      scanf("%d", &escolhaCampo);
      update(escolhaFilme, escolhaCampo);
    }
    printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n0 - Sair\nEscolha: ");
    scanf("%d", &escolha);
  }
}

int tamanho_arquivo() {
  char linha[102];
  int tamanho = 0;
  FILE *file;
  file = fopen("allyticket.txt", "r");
  while (!feof(file)) {
    fgets(linha, 100, file);
    tamanho++;
  }
  return tamanho;
}

void create(Filme *nomeFilme)
{
  FILE *file;
  file = fopen("allyticket.txt", "a");
  if (tamanho_arquivo() > 2) {
    fprintf(file, "\n");
  }
  fprintf(file, "Nome: %s\nClassificacao: %s\nCategoria: %s", nomeFilme->nome, nomeFilme->classificacao, nomeFilme->categoria);
  fclose(file);
}
void read()
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
  int filmeIndex = 0;

  while(!feof(file)) {
    fgets(nome, sizeof(nome), file);
    fgets(classificacao, sizeof(classificacao), file);
    fgets(categoria, sizeof(categoria), file);
    filmeIndex++;
    printf("Filme número %d:\n", filmeIndex);
    printf("%s%s%s", nome, classificacao, categoria);
  }  
  printf("\n");
  fclose(file);
}

void update(int filmeIndex, int filmeCampo)
{
  FILE *file;
  FILE *tempFile;

  int line = (filmeIndex - 1)*3 + filmeCampo;

  char linhaAntiga[102];
  char newLine[102];
  int count = 0;

  file = fopen("allyticket.txt", "r");
  tempFile = fopen("replace.tmp", "w");

  if(filmeCampo == 1) {
    char formatNome[102] = "Nome: ";
    printf("Digite o novo nome do filme: ");
    scanf("%s", &newLine);
    strcat(formatNome, newLine);
    while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count == line) {
        fputs(formatNome, tempFile);
      }
      else {
        fputs(linhaAntiga, tempFile);
      }
    }
  }
  if(filmeCampo == 2) {
    char formatClass[102] = "Classificação: ";
    printf("Digite a nova classificação do filme: ");
    scanf("%s", &newLine);
    strcat(formatClass, newLine);
    while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count == line) {
        fputs(formatClass, tempFile);
      }
      else {
        fputs(linhaAntiga, tempFile);
      }
    }
  }
  if(filmeCampo == 3) {
    char formatCategoria[102] = "Categoria: ";
    printf("Digite a nova categoria do filme: ");
    scanf("%s", &newLine);
    strcat(formatCategoria, newLine);
    while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count == line) {
        fputs(formatCategoria, tempFile);
      }
      else {
        fputs(linhaAntiga, tempFile);
      }
    }
  }

fclose(tempFile);
fclose(file);

remove("allyticket.txt");
rename("replace.tmp", "allyticket.txt");

}

void delete ()
{
}

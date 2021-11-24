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

int tamanhoArquivo();
void createFilme(Filme *nomeFilme);
void read(char *arquivo);
void updateFilme(int filmeIndex, int filmeCampo);
void deleteFilme(int filmeIndex);

int main()
{
  printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n4 - Excluir um filme\n0 - Sair\nEscolha: ");
  int escolha;
  scanf("%d", &escolha);
  while (escolha != 0) {
    if (escolha == 1) {
      Filme filme;
      char nome[52];
      printf("Digite o nome do filme a ser inserido: ");
      while ( getchar() != '\n' );
      scanf("%[^\n]", nome);
      filme.nome = nome;
      char classificacao[32];
      printf("Digite a classificação do filme: ");
      while ( getchar() != '\n' );
      scanf("%[^\n]", classificacao);
      filme.classificacao = classificacao;
      char categoria[52];
      printf("Digite a categoria do filme: ");
      while ( getchar() != '\n' );
      scanf("%[^\n]", categoria);
      filme.categoria = categoria;
      Filme *filmePtr = &filme;
      createFilme(filmePtr);
    }
    else if (escolha == 2) {
      read("allyticket.txt");
    }
    else if (escolha == 3) {
      printf("Os filmes disponíveis para edição e seus respectivos números são:\n");
      read("allyticket.txt");
      printf("Digite o número do filme que deseja editar: ");
      int escolhaFilme;
      scanf("%d", &escolhaFilme);
      printf("Qual campo deseja modificar?\n1 - Nome\n2 - Classificação\n3 - Categoria\nEscolha: ");
      int escolhaCampo;
      scanf("%d", &escolhaCampo);
      updateFilme(escolhaFilme, escolhaCampo);
    }
    else if (escolha == 4) {
      printf("Os filmes disponíveis para exclusão e seus respectivos números são:\n");
      read("allyticket.txt");
      printf("Digite o número do filme que deseja excluir: ");
      int escolhaFilme;
      scanf("%d", &escolhaFilme);
      deleteFilme(escolhaFilme);
    }
    else {
      printf("Nenhuma ação corresponde ao valor inserido, por favor selecione uma ação válida.\n");
    }
    printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n4 - Excluir um filme\n0 - Sair\nEscolha: ");
    scanf("%d", &escolha);
  }
}

int tamanhoArquivo() {
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

void createFilme(Filme *nomeFilme)
{
  FILE *file;
  file = fopen("allyticket.txt", "a");
  if (tamanhoArquivo() > 2) { //caso já exista algum filme no arquivo, insere um \n antes de inserir o filme
    fprintf(file, "\n");
  }
  fprintf(file, "Nome: %s\nClassificacao: %s\nCategoria: %s", nomeFilme->nome, nomeFilme->classificacao, nomeFilme->categoria);
  fclose(file);
}
void read(char *arquivo)
{
  FILE *file;
  file = fopen(arquivo, "r");

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

void updateFilme(int filmeIndex, int filmeCampo)
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
    while ( getchar() != '\n' );
    scanf("%[^\n]", newLine);
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
    while ( getchar() != '\n' );
    scanf("%[^\n]", newLine);
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
    while ( getchar() != '\n' );
    scanf("%[^\n]", newLine);
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

void deleteFilme(int filmeIndex)
{
  FILE *file;
  FILE *tempFile;

  int line = (filmeIndex - 1)*3 + 1;

  char linhaAntiga[102];
  int count = 0;

  file = fopen("allyticket.txt", "r");
  tempFile = fopen("replace.tmp", "w");

  while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count != line && count != line + 1 && count != line + 2) {
        if (line == tamanhoArquivo() - 2 && count == line - 1) {
          linhaAntiga[strcspn(linhaAntiga, "\n")] = 0;
        }
        fputs(linhaAntiga, tempFile);
      }
    }

  fclose(tempFile);
  fclose(file);

  remove("allyticket.txt");
  rename("replace.tmp", "allyticket.txt");
}

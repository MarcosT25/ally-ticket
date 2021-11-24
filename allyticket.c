#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MOVIE_FILE "filmes.txt"
#define SESSION_FILE "sessoes.txt"

struct filme
{
  char *nome;
  char *classificacao;
  char *categoria;
  char *duracao;
};

typedef struct filme Filme;

int tamanhoArquivo();
void createFilme(Filme *nomeFilme);
void readFilme();
void updateFilme(int filmeIndex, int filmeCampo);
void deleteFilme(int filmeIndex);
void readSession();

int main()
{
  int escolhaPerfil;
  int escolhaAcaoCliente;
  int escolhaAcaoFuncionario;
  printf("Você é:\n1 - Cliente;\n2 - Funcionário\n0 - Sair\nEscolha: ");
  scanf("%d", &escolhaPerfil);
  while (escolhaPerfil != 0) {
    if (escolhaPerfil == 1) {
      printf("O que deseja fazer?\n1 - Ver filmes disponíveis;\n2 - Ver sessões disponíveis;\n3 - Comprar um ingresso\n0 - Sair\nEscolha: ");
      scanf("%d", &escolhaAcaoCliente);
      if (escolhaAcaoCliente == 0) {
          escolhaPerfil = 0;
      }
      while (escolhaAcaoCliente != 0) {
        if (escolhaAcaoCliente == 1) {
          readFilme();
          break;
        }
        else if (escolhaAcaoCliente == 2) {
          readSession();
          break;
        }
        else if (escolhaAcaoCliente == 3) {
          readSession();
          printf("Qual sessão deseja comprar?\nDigite o número da sessão: ");
          break;
        }
        
        else {
          printf("Nenhuma ação corresponde ao valor inserido, por favor selecione uma ação válida.\n");
        }
      }
    }
    else if (escolhaPerfil == 2) {
      printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n4 - Excluir um filme\n0 - Sair\nEscolha: ");
      scanf("%d", &escolhaAcaoFuncionario);
      if (escolhaAcaoFuncionario == 0) {
          escolhaPerfil = 0;
      }
      while (escolhaAcaoFuncionario != 0) {
        if (escolhaAcaoFuncionario == 1) {
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
          char duracao[52];
          printf("Digite a duração do filme: ");
          while ( getchar() != '\n' );
          scanf("%[^\n]", duracao);
          filme.duracao = duracao;
          Filme *filmePtr = &filme;
          createFilme(filmePtr);
        }
        else if (escolhaAcaoFuncionario == 2) {
          readFilme();
        }
        else if (escolhaAcaoFuncionario == 3) {
          printf("Os filmes disponíveis para edição e seus respectivos números são:\n");
          readFilme();
          printf("Digite o número do filme que deseja editar: ");
          int escolhaFilme;
          scanf("%d", &escolhaFilme);
          printf("Qual campo deseja modificar?\n1 - Nome\n2 - Classificação\n3 - Categoria\n4 - Duração\nEscolha: ");
          int escolhaCampo;
          scanf("%d", &escolhaCampo);
          updateFilme(escolhaFilme, escolhaCampo);
        }
        else if (escolhaAcaoFuncionario == 4) {
          printf("Os filmes disponíveis para exclusão e seus respectivos números são:\n");
          readFilme();
          printf("Digite o número do filme que deseja excluir: ");
          int escolhaFilme;
          scanf("%d", &escolhaFilme);
          deleteFilme(escolhaFilme);
        }
        else {
          printf("Nenhuma ação corresponde ao valor inserido, por favor selecione uma ação válida.\n");
        }
        printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n4 - Excluir um filme\n0 - Sair\nEscolha: ");
        scanf("%d", &escolhaAcaoFuncionario);
      }
    }
    else {
      printf("Nenhuma ação corresponde ao valor inserido, por favor selecione uma ação válida.\n");
      printf("Você é:\n1 - Cliente;\n2 - Funcionário\n0 - Sair\nEscolha: ");
      scanf("%d", &escolhaPerfil);
    }
  }

  
}

int tamanhoArquivo() {
  char linha[102];
  int tamanho = 0;
  FILE *file;
  file = fopen(MOVIE_FILE, "r");
  while (!feof(file)) {
    fgets(linha, 100, file);
    tamanho++;
  }
  return tamanho;
}

void createFilme(Filme *nomeFilme)
{
  FILE *file;
  file = fopen(MOVIE_FILE, "a");
  if (tamanhoArquivo() > 2) { //caso já exista algum filme no arquivo, insere um \n antes de inserir o filme
    fprintf(file, "\n");
  }
  fprintf(file, "%s\n%s\n%s\n%s", nomeFilme->nome, nomeFilme->classificacao, nomeFilme->categoria, nomeFilme->duracao);
  fclose(file);
}
void readFilme() {
  FILE *file;
  file = fopen("filmes.txt", "r");

  char nome[52];
  char classificacao[52];
  char categoria[52];
  char duracao[52];
  int filmeIndex = 0;

  while(!feof(file)) {
    fgets(nome, sizeof(nome), file);
    fgets(classificacao, sizeof(classificacao), file);
    fgets(categoria, sizeof(categoria), file);
    fgets(duracao, sizeof(duracao), file);
    filmeIndex++;
    duracao[strcspn(duracao, "\n")] = 0;
    printf("Filme número %d:\n", filmeIndex);
    printf("Nome: %sClassificação: %sCategoria: %sDuração: %smin\n", nome, classificacao, categoria, duracao);
  }  
  printf("\n");
  fclose(file);
}

void updateFilme(int filmeIndex, int filmeCampo)
{
  FILE *file;
  FILE *tempFile;

  int line = (filmeIndex - 1)*4 + filmeCampo;

  char linhaAntiga[102];
  char newLine[102];
  int count = 0;

  file = fopen(MOVIE_FILE, "r");
  tempFile = fopen("replace.tmp", "w");

  if(filmeCampo == 1) {
    printf("Digite o novo nome do filme: ");
    while ( getchar() != '\n' );
    scanf("%[^\n]", newLine);
    strcat(newLine, "\n");
    while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count == line) {
        fputs(newLine, tempFile);
      }
      else {
        fputs(linhaAntiga, tempFile);
      }
    }
  }
  if(filmeCampo == 2) {
    printf("Digite a nova classificação do filme: ");
    while ( getchar() != '\n' );
    scanf("%[^\n]", newLine);
    strcat(newLine, "\n");
    while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count == line) {
        fputs(newLine, tempFile);
      }
      else {
        fputs(linhaAntiga, tempFile);
      }
    }
  }
  if(filmeCampo == 3) {
    printf("Digite a nova categoria do filme: ");
    while ( getchar() != '\n' );
    scanf("%[^\n]", newLine);
    strcat(newLine, "\n");
    while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count == line) {
        fputs(newLine, tempFile);
      }
      else {
        fputs(linhaAntiga, tempFile);
      }
    }
  }
  if(filmeCampo == 4) {
    printf("Digite a nova duração do filme: ");
    while ( getchar() != '\n' );
    scanf("%[^\n]", newLine);
    strcat(newLine, "\n");
    while((fgets(linhaAntiga, 100, file)) != NULL) {
      count++;
      if (count == line) {
        fputs(newLine, tempFile);
      }
      else {
        fputs(linhaAntiga, tempFile);
      }
    }
  }
  fclose(tempFile);
  fclose(file);

  remove(MOVIE_FILE);
  rename("replace.tmp", MOVIE_FILE);
}

void deleteFilme(int filmeIndex)
{
  FILE *file;
  FILE *tempFile;

  int line = (filmeIndex - 1)*4 + 1;

  char linhaAntiga[102];
  int count = 0;

  file = fopen(MOVIE_FILE, "r");
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

  remove(MOVIE_FILE);
  rename("replace.tmp", MOVIE_FILE);
}

void readSession() {
  FILE *file;
  file = fopen(SESSION_FILE, "r");

  char filme[52];
  char sala[5];
  char lugares[5];
  int sessaoIndex = 0;

  while(!feof(file)) {
    fgets(filme, sizeof(filme), file);
    fgets(sala, sizeof(sala), file);
    fgets(lugares, sizeof(lugares), file);
    sessaoIndex++;
    printf("Sessão número %d:\n", sessaoIndex);
    printf("%sSala número: %sAssentos disponíveis: %s", filme, sala, lugares);
  }  
  printf("\n");
  fclose(file);
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MOVIE_FILE "filmes.txt"
#define SESSION_FILE "sessoes.txt"

#define ROOM_1_START "68"
#define ROOM_2_START "124"
#define ROOM_3_START "96"

struct filme {
  char *nome;
  char *classificacao;
  char *categoria;
  char *duracao;
};

typedef struct filme Filme;

struct sessao {
  char *filme;
  char *sala;
  char *lugares;
  char *horario;
  char *valor;
}; 

typedef struct sessao Sessao;

int tamanhoArquivo();
void createFilme(Filme *nomeFilme);
void readFilme();
void updateFilme(int filmeIndex, int filmeCampo);
void deleteFilme(int filmeIndex);
void createSessao(Sessao *nomeSessao);
void readSessao();

int main() {
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
          readSessao();
          break;
        }
        else if (escolhaAcaoCliente == 3) {
          readSessao();
          printf("Qual sessão deseja comprar?\nDigite o número da sessão: ");
          break;
        }
        
        else {
          printf("Nenhuma ação corresponde ao valor inserido, por favor selecione uma ação válida.\n");
        }
      }
    }
    else if (escolhaPerfil == 2) {
      printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n4 - Excluir um filme\n5 - Criar uma sessão\n6 - Visualizar todas as sessões\n0 - Sair\nEscolha: ");
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
        else if(escolhaAcaoFuncionario == 5) {
          Sessao sessao;
          char nomeFilme[52];
          printf("Digite o nome do filme a ser inserido: ");
          while ( getchar() != '\n' );
          scanf("%[^\n]", nomeFilme);
          sessao.filme = nomeFilme;
          char sala[5];
          printf("Digite o número da sala dessa sessão (opções: sala 1, 2 ou 3): ");
          while ( getchar() != '\n' );
          scanf("%[^\n]", sala);
          sessao.sala = sala;
          if (strcmp(sala, "1") == 0) {
            sessao.lugares = ROOM_1_START;
          } 
          else if (strcmp(sala, "2") == 0) {
            sessao.lugares = ROOM_2_START;
          } 
          else if (strcmp(sala, "3") == 0){ 
            sessao.lugares = ROOM_3_START;
          }
          char horario[12];
          printf("Digite o horário do filme (formato xx:xx): ");
          while ( getchar() != '\n' );
          scanf("%[^\n]", horario);
          sessao.horario = horario;
          char valor[12];
          printf("Digite o valor do ingresso do filme (formato: xx,xx): ");
          while ( getchar() != '\n' );
          scanf("%[^\n]", valor);
          sessao.valor = valor;
          Sessao *sessaoPtr = &sessao;
          createSessao(sessaoPtr);
        } 
        else if (escolhaAcaoFuncionario == 6) {
          readSessao();
        }
        else {
          printf("Nenhuma ação corresponde ao valor inserido, por favor selecione uma ação válida.\n");
        }
        printf("Escolha o que deseja fazer:\n1 - Adicionar um filme à lista;\n2 - Visualizar todos os filmes\n3 - Editar um filme\n4 - Excluir um filme\n5 - Criar uma sessão\n6 - Visualizar todas as sessões\n0 - Sair\nEscolha: ");
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
    printf("Nome: %sClassificação: %sCategoria: %sDuração: %s min\n", nome, classificacao, categoria, duracao);
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
    if (line != tamanhoArquivo()) {
      strcat(newLine, "\n");
    }
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

void createSessao(Sessao *nomeSessao){
  FILE *file;
  file = fopen(SESSION_FILE, "a");
  if (tamanhoArquivo() > 2) { //caso já exista algum filme no arquivo, insere um \n antes de inserir o filme
    fprintf(file, "\n");
  }
  fprintf(file, "%s\n%s\n%s\n%s\n%s", nomeSessao->filme, nomeSessao->sala, nomeSessao->lugares, nomeSessao->horario, nomeSessao->valor);
  fclose(file);
}

void readSessao() {
  FILE *file;
  file = fopen(SESSION_FILE, "r");

  char filme[52];
  char sala[5];
  char lugares[5];
  char horario[12];
  char valor[12];
  int sessaoIndex = 0;

  while(!feof(file)) {
    fgets(filme, sizeof(filme), file);
    fgets(sala, sizeof(sala), file);
    fgets(lugares, sizeof(lugares), file);
    fgets(horario, sizeof(horario), file);
    fgets(valor, sizeof(valor), file);
    sessaoIndex++;
    printf("Sessão número %d:\n", sessaoIndex);
    printf("%sSala número: %sAssentos disponíveis: %sHorário: %sValor do ingresso: %s", filme, sala, lugares, horario, valor);
  }  
  printf("\n");
  fclose(file);
}

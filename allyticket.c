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
void update();
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

  while(!feof(file)) {
    fgets(nome, sizeof(nome), file);
    fgets(classificacao, sizeof(classificacao), file);
    fgets(categoria, sizeof(categoria), file);

    printf("%s%s%s", nome, classificacao, categoria);
  }  
  printf("\n");
  fclose(file);
}

void delete ()
{
}

void update(Filme *nomeFilme)
{
  FILE *file;
  file = fopen("allyticket.txt", "r+");
 
  if(file==NULL){
    printf("Filme inexistente.\n");
    return;
  }
  
  char nome[30], classificacao[20], categoria[20];
  int escolha;
  char new_nome[30], new_classificacao[20], new_categoria[20];
 
  fgets(nome, sizeof(nome), file); fflush(stdin);
  fgets(classificacao, sizeof(classificacao), file); fflush(stdin);
  fgets(categoria, sizeof(categoria), file); fflush(stdin);
 
  int tam_nome=strlen(nome)+strlen(classificacao)+strlen(categoria)+2;
  int tam_class=strlen(classificacao)+strlen(categoria)+1;
  int tam_cat=strlen(categoria);
 
  printf("%s%s%s\n", nome, classificacao, categoria);
  printf("\nDeseja editar:\n 1. Nome\n 2. Classificacao\n 3. Categoria\n");
 
  scanf("%d", &escolha);
 
  if(escolha==1){
    printf("Insira o novo nome:\n");
    fflush(stdin);
    scanf("%s", &new_nome);
    fseek(file, -tam_nome, SEEK_CUR);
    fprintf(file, "Nome: %s\n%s%s", new_nome, classificacao, categoria);
    }
  if(escolha==2){
    printf("Insira a nova classificacao:\n");
    fflush(stdin);
    scanf("%s", &new_classificacao);
    fseek(file, -tam_class, SEEK_CUR);
    fprintf(file, "Classificacao: %s\n%s", new_classificacao, categoria);
  }
  if(escolha==3){
    printf("Insira a nova categoria:\n");
    fflush(stdin);
    scanf("%s", &new_categoria);
    fseek(file, -tam_cat, SEEK_CUR);
    fprintf(file, "Categoria: %s", new_categoria);
  }
fclose(file);
}

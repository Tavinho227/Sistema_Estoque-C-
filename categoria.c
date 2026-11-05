#include "categoria.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

#define ARQUIVO_CATEGORIAS "categorias.txt"

int buscar_categoria_por_codigo(const Categoria categorias[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (categorias[i].codigo == codigo) return i;
    }
    return -1;
}

void cadastrar_categoria(Categoria categorias[], int *total) {
    Categoria nova;
    if (*total >= MAX_CATEGORIAS) {
        puts("Limite de 20 categorias atingido.");
        return;
    }
    puts("\n--- CADASTRAR CATEGORIA ---");
    while (1) {
        nova.codigo = ler_inteiro_minimo("Codigo da categoria: ", 1);
        if (buscar_categoria_por_codigo(categorias, *total, nova.codigo) == -1) break;
        puts("Esse codigo ja existe. Digite outro.");
    }
    ler_texto("Nome da categoria: ", nova.nome, sizeof(nova.nome));
    categorias[*total] = nova;
    (*total)++;
    printf("Categoria '%s' cadastrada com sucesso!\n", nova.nome);
}

void listar_categorias(const Categoria categorias[], int total) {
    int i;
    puts("\n--- LISTAR CATEGORIAS ---");
    if (total == 0) {
        puts("Nenhuma categoria cadastrada.");
        return;
    }
    for (i = 0; i < total; i++) {
        printf("Codigo: %d | Nome: %s\n", categorias[i].codigo, categorias[i].nome);
    }
}

void carregar_categorias(Categoria categorias[], int *total) {
    FILE *arquivo;
    char linha[256];
    char *campos[2];
    int codigo;
    *total = 0;
    arquivo = fopen(ARQUIVO_CATEGORIAS, "r");
    if (arquivo == NULL) return;  /* Primeira execucao: lista vazia. */
    while (fgets(linha, sizeof(linha), arquivo) != NULL && *total < MAX_CATEGORIAS) {
        if (!separar_campos(linha, campos, 2)) continue;
        if (!converter_inteiro(campos[0], &codigo) || codigo <= 0) continue;
        if (strlen(campos[1]) >= sizeof(categorias[0].nome)) continue;
        if (buscar_categoria_por_codigo(categorias, *total, codigo) != -1) continue;
        categorias[*total].codigo = codigo;
        strcpy(categorias[*total].nome, campos[1]);
        (*total)++;
    }
    fclose(arquivo);
}

int salvar_categorias(const Categoria categorias[], int total) {
    FILE *arquivo;
    int i, erro = 0;
    arquivo = fopen(ARQUIVO_CATEGORIAS, "w");
    if (arquivo == NULL) {
        puts("Erro: nao foi possivel abrir categorias.txt para salvar.");
        return 0;
    }
    for (i = 0; i < total; i++) {
        if (fprintf(arquivo, "%d|%s\n", categorias[i].codigo, categorias[i].nome) < 0) erro = 1;
    }
    if (fclose(arquivo) != 0) erro = 1;
    if (erro) puts("Erro ao salvar categorias.txt.");
    return !erro;
}

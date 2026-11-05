#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 20

typedef struct {
    int codigo;
    char nome[30];
} Categoria;

int buscar_categoria_por_codigo(const Categoria categorias[], int total, int codigo);
void cadastrar_categoria(Categoria categorias[], int *total);
void listar_categorias(const Categoria categorias[], int total);
void carregar_categorias(Categoria categorias[], int *total);
int salvar_categorias(const Categoria categorias[], int total);

#endif

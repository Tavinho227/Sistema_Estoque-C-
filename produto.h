#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

#define MAX_PRODUTOS 50

typedef struct {
    int codigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel;
    int categoria_codigo;
    int ativo;
} Produto;

/* Busca todas as posicoes, inclusive as de produtos removidos.
   Assim, um codigo antigo nunca pode ser reutilizado. */
int buscar_produto_por_codigo(const Produto produtos[], int total, int codigo);
/* Pesquisa somente produtos ativos, como exige a tarefa. */
int buscar_produto_por_nome(const Produto produtos[], int total, const char nome[]);
void cadastrar_produto(Produto produtos[], int *total,
                       const Categoria categorias[], int total_categorias);
void exibir_produto(Produto produto, const Categoria categorias[], int total_categorias);
void listar_produtos(const Produto produtos[], int total,
                     const Categoria categorias[], int total_categorias);
void pesquisar_produto(const Produto produtos[], int total,
                       const Categoria categorias[], int total_categorias);
void alterar_estoque(Produto produtos[], int total,
                     const Categoria categorias[], int total_categorias);
void remover_produto(Produto produtos[], int total);
void carregar_produtos(Produto produtos[], int *total,
                       const Categoria categorias[], int total_categorias);
int salvar_produtos(const Produto produtos[], int total);

#endif

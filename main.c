#include "produto.h"
#include "categoria.h"
#include "util.h"
#include <locale.h>
#include <stdio.h>

static void menu_categorias(Categoria categorias[], int *total_categorias) {
    int opcao;
    do {
        puts("\n===== MENU DE CATEGORIAS =====");
        puts("1 - Cadastrar Categoria");
        puts("2 - Listar Categorias");
        puts("3 - Voltar");
        opcao = ler_inteiro_intervalo("Escolha uma opcao: ", 1, 3);
        switch (opcao) {
            case 1:
                cadastrar_categoria(categorias, total_categorias);
                salvar_categorias(categorias, *total_categorias);
                break;
            case 2:
                listar_categorias(categorias, *total_categorias);
                break;
        }
    } while (opcao != 3);
}

int main(void) {
    Produto produtos[MAX_PRODUTOS];
    Categoria categorias[MAX_CATEGORIAS];
    int total_produtos = 0;
    int total_categorias = 0;
    int opcao;

    /* Os precos sao gravados com ponto nos arquivos de texto. */
    setlocale(LC_NUMERIC, "C");
    carregar_categorias(categorias, &total_categorias);
    carregar_produtos(produtos, &total_produtos, categorias, total_categorias);
    printf("Sistema iniciado: %d categoria(s) e %d registro(s) de produto carregado(s).\n",
           total_categorias, total_produtos);

    do {
        puts("\n===== SISTEMA DE ESTOQUE =====");
        puts("1 - Cadastrar Produto");
        puts("2 - Listar Produtos");
        puts("3 - Pesquisar Produto");
        puts("4 - Alterar Estoque de um Produto");
        puts("5 - Remover Produto");
        puts("6 - Categorias");
        puts("7 - Sair");
        opcao = ler_inteiro_intervalo("Escolha uma opcao: ", 1, 7);
        switch (opcao) {
            case 1:
                cadastrar_produto(produtos, &total_produtos, categorias, total_categorias);
                salvar_produtos(produtos, total_produtos);
                break;
            case 2:
                listar_produtos(produtos, total_produtos, categorias, total_categorias);
                break;
            case 3:
                pesquisar_produto(produtos, total_produtos, categorias, total_categorias);
                break;
            case 4:
                alterar_estoque(produtos, total_produtos, categorias, total_categorias);
                salvar_produtos(produtos, total_produtos);
                break;
            case 5:
                remover_produto(produtos, total_produtos);
                salvar_produtos(produtos, total_produtos);
                break;
            case 6:
                menu_categorias(categorias, &total_categorias);
                break;
            case 7: {
                int salvou_categorias = salvar_categorias(categorias, total_categorias);
                int salvou_produtos = salvar_produtos(produtos, total_produtos);
                if (salvou_categorias && salvou_produtos) {
                    puts("Dados salvos em categorias.txt e produtos.txt.");
                } else {
                    puts("Atencao: houve um erro ao salvar algum arquivo.");
                }
                puts("Programa encerrado.");
                break;
            }
        }
    } while (opcao != 7);
    return 0;
}

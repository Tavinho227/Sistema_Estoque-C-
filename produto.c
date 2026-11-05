#include "produto.h"
#include "util.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define ARQUIVO_PRODUTOS "produtos.txt"

/* IMPORTANTE: nao ignorar inativos nesta busca. Codigo removido nao se reutiliza. */
int buscar_produto_por_codigo(const Produto produtos[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].codigo == codigo) return i;
    }
    return -1;
}

int buscar_produto_por_nome(const Produto produtos[], int total, const char nome[]) {
    int i;
    for (i = 0; i < total; i++) {
        if (produtos[i].ativo == 1 && strcmp(produtos[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

static void atualizar_disponibilidade(Produto *produto) {
    produto->disponivel = produto->quantidade > 0 ? 1 : 0;
}

void exibir_produto(Produto produto, const Categoria categorias[], int total_categorias) {
    int pos = buscar_categoria_por_codigo(categorias, total_categorias, produto.categoria_codigo);
    printf("Codigo: %d\n", produto.codigo);
    printf("Nome: %s\n", produto.nome);
    printf("Prateleira: %c\n", produto.prateleira);
    printf("Preco: R$ %.2f\n", (double)produto.preco);
    printf("Quantidade: %d\n", produto.quantidade);
    printf("Disponivel: %s\n", produto.disponivel ? "Sim" : "Nao");
    printf("Categoria: %s\n", pos >= 0 ? categorias[pos].nome : "Desconhecida");
    puts("------------------------------");
}

void cadastrar_produto(Produto produtos[], int *total,
                       const Categoria categorias[], int total_categorias) {
    Produto novo;
    if (total_categorias == 0) {
        puts("Cadastre ao menos uma categoria antes de cadastrar produtos.");
        return;
    }
    if (*total >= MAX_PRODUTOS) {
        puts("Limite de 50 produtos atingido, incluindo registros removidos.");
        return;
    }
    puts("\n--- CADASTRAR PRODUTO ---");
    while (1) {
        novo.codigo = ler_inteiro_minimo("Codigo do produto: ", 1);
        if (buscar_produto_por_codigo(produtos, *total, novo.codigo) == -1) break;
        puts("Esse codigo ja existe (mesmo se removido). Digite outro.");
    }
    ler_texto("Nome do produto: ", novo.nome, sizeof(novo.nome));
    novo.prateleira = ler_prateleira("Prateleira (A, B, C ou D): ");
    novo.preco = (float)ler_preco("Preco unitario (ex.: 19,90): ");
    novo.quantidade = ler_inteiro_minimo("Quantidade em estoque: ", 0);
    atualizar_disponibilidade(&novo);
    novo.ativo = 1;
    puts("\nCategorias disponiveis:");
    listar_categorias(categorias, total_categorias);
    while (1) {
        novo.categoria_codigo = ler_inteiro_minimo("Codigo da categoria: ", 1);
        if (buscar_categoria_por_codigo(categorias, total_categorias, novo.categoria_codigo) >= 0)
            break;
        puts("Categoria inexistente. Digite um codigo cadastrado.");
    }
    produtos[*total] = novo;
    (*total)++;
    puts("\nProduto cadastrado com sucesso:");
    exibir_produto(novo, categorias, total_categorias);
}

void listar_produtos(const Produto produtos[], int total,
                     const Categoria categorias[], int total_categorias) {
    int i, encontrados = 0;
    puts("\n--- LISTAR PRODUTOS ---");
    for (i = 0; i < total; i++) {
        if (produtos[i].ativo == 1) {
            exibir_produto(produtos[i], categorias, total_categorias);
            encontrados++;
        }
    }
    if (!encontrados) puts("Nenhum produto ativo cadastrado.");
}

void pesquisar_produto(const Produto produtos[], int total,
                       const Categoria categorias[], int total_categorias) {
    int opcao, codigo, pos;
    char nome[50];
    puts("\n--- PESQUISAR PRODUTO ---");
    puts("1 - Pesquisar por codigo");
    puts("2 - Pesquisar por nome");
    opcao = ler_inteiro_intervalo("Escolha: ", 1, 2);
    if (opcao == 1) {
        codigo = ler_inteiro_minimo("Codigo do produto: ", 1);
        pos = buscar_produto_por_codigo(produtos, total, codigo);
        if (pos != -1 && produtos[pos].ativo != 1) pos = -1;
    } else {
        ler_texto("Nome exato do produto: ", nome, sizeof(nome));
        pos = buscar_produto_por_nome(produtos, total, nome);
    }
    if (pos == -1) puts("Produto nao encontrado.");
    else exibir_produto(produtos[pos], categorias, total_categorias);
}

void alterar_estoque(Produto produtos[], int total,
                     const Categoria categorias[], int total_categorias) {
    int codigo, pos, tipo, quantidade;
    Produto *produto;
    puts("\n--- ALTERAR ESTOQUE ---");
    codigo = ler_inteiro_minimo("Codigo do produto: ", 1);
    pos = buscar_produto_por_codigo(produtos, total, codigo);
    if (pos == -1 || produtos[pos].ativo != 1) {
        puts("Produto nao encontrado ou removido. Nenhuma alteracao realizada.");
        return;
    }
    produto = &produtos[pos];
    printf("Produto: %s | Estoque atual: %d\n", produto->nome, produto->quantidade);
    puts("1 - Entrada de mercadoria");
    puts("2 - Saida de mercadoria");
    tipo = ler_inteiro_intervalo("Escolha: ", 1, 2);
    quantidade = ler_inteiro_minimo("Quantidade para movimentar: ", 1);
    if (tipo == 1) {
        if (quantidade > INT_MAX - produto->quantidade) {
            puts("Entrada muito grande. Estoque nao alterado.");
            return;
        }
        produto->quantidade += quantidade;
        puts("Entrada registrada com sucesso.");
    } else {
        if (quantidade > produto->quantidade) {
            puts("Estoque insuficiente! Saida cancelada; a quantidade nao mudou.");
            return;
        }
        produto->quantidade -= quantidade;
        puts("Saida registrada com sucesso.");
    }
    atualizar_disponibilidade(produto);
    puts("Dados atualizados:");
    exibir_produto(*produto, categorias, total_categorias);
}

void remover_produto(Produto produtos[], int total) {
    int codigo, pos;
    puts("\n--- REMOVER PRODUTO ---");
    codigo = ler_inteiro_minimo("Codigo do produto: ", 1);
    pos = buscar_produto_por_codigo(produtos, total, codigo);
    if (pos == -1) {
        puts("Produto nao encontrado. Nenhuma alteracao realizada.");
    } else if (produtos[pos].ativo == 0) {
        puts("Produto ja estava removido.");
    } else {
        produtos[pos].ativo = 0;
        printf("Produto '%s' removido logicamente com sucesso.\n", produtos[pos].nome);
    }
}

/* Le os arquivos da Tarefa 4 (7 campos) e da Tarefa 5 (8 campos).
   O formato antigo guardava prateleiras 1/2/3/4; a migracao vira A/B/C/D.
   No formato novo: codigo|nome|prateleira|preco|quantidade|disponivel|categoria|ativo
*/
void carregar_produtos(Produto produtos[], int *total,
                       const Categoria categorias[], int total_categorias) {
    FILE *arquivo;
    char linha[512], copia[512];
    char *campos[8];
    Produto lido;
    int formato_antigo, antigo_numero, ativo;
    *total = 0;
    arquivo = fopen(ARQUIVO_PRODUTOS, "r");
    if (arquivo == NULL) return;
    while (fgets(linha, sizeof(linha), arquivo) != NULL && *total < MAX_PRODUTOS) {
        strcpy(copia, linha);
        formato_antigo = 0;
        if (!separar_campos(copia, campos, 8)) {
            strcpy(copia, linha);
            if (!separar_campos(copia, campos, 7)) continue;
            formato_antigo = 1;
        }
        if (!converter_inteiro(campos[0], &lido.codigo) || lido.codigo <= 0) continue;
        if (strlen(campos[1]) >= sizeof(lido.nome)) continue;
        strcpy(lido.nome, campos[1]);
        if (formato_antigo) {
            if (!converter_inteiro(campos[2], &antigo_numero) ||
                antigo_numero < 1 || antigo_numero > 4) continue;
            lido.prateleira = (char)('A' + antigo_numero - 1);
        } else {
            if (strlen(campos[2]) != 1 || campos[2][0] < 'A' || campos[2][0] > 'D')
                continue;
            lido.prateleira = campos[2][0];
        }
        {
            double preco_lido;
            if (!converter_decimal(campos[3], &preco_lido) ||
                preco_lido <= 0 || preco_lido > 1000000000.0) continue;
            lido.preco = (float)preco_lido;
        }
        if (!converter_inteiro(campos[4], &lido.quantidade) || lido.quantidade < 0)
            continue;
        /* A disponibilidade salva e ignorada: deve ser sempre recalculada. */
        atualizar_disponibilidade(&lido);
        if (!converter_inteiro(campos[6], &lido.categoria_codigo)) continue;
        if (buscar_categoria_por_codigo(categorias, total_categorias, lido.categoria_codigo) == -1)
            continue;
        if (formato_antigo) {
            ativo = 1;
        } else if (!converter_inteiro(campos[7], &ativo) || (ativo != 0 && ativo != 1)) {
            continue;
        }
        lido.ativo = ativo;
        if (buscar_produto_por_codigo(produtos, *total, lido.codigo) != -1) continue;
        produtos[*total] = lido;
        (*total)++;
    }
    fclose(arquivo);
}

int salvar_produtos(const Produto produtos[], int total) {
    FILE *arquivo;
    int i, erro = 0;
    arquivo = fopen(ARQUIVO_PRODUTOS, "w");
    if (arquivo == NULL) {
        puts("Erro: nao foi possivel abrir produtos.txt para salvar.");
        return 0;
    }
    for (i = 0; i < total; i++) {
        if (fprintf(arquivo, "%d|%s|%c|%.2f|%d|%d|%d|%d\n",
                    produtos[i].codigo, produtos[i].nome, produtos[i].prateleira,
                    (double)produtos[i].preco, produtos[i].quantidade,
                    produtos[i].disponivel, produtos[i].categoria_codigo,
                    produtos[i].ativo) < 0) erro = 1;
    }
    if (fclose(arquivo) != 0) erro = 1;
    if (erro) puts("Erro ao salvar produtos.txt.");
    return !erro;
}

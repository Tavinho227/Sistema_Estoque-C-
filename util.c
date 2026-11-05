#include "util.h"
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ler_linha(char *destino, size_t tamanho) {
    char *quebra;
    int ch;

    if (fgets(destino, (int)tamanho, stdin) == NULL) {
        puts("\nEntrada encerrada. Finalizando o programa.");
        exit(0);
    }
    quebra = strchr(destino, '\n');
    if (quebra != NULL) {
        *quebra = '\0';
        return 1;
    }
    if (feof(stdin)) return 1;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
    return 0;
}

char *remover_espacos(char *texto) {
    char *fim;
    while (isspace((unsigned char)*texto)) texto++;
    if (*texto == '\0') return texto;
    fim = texto + strlen(texto) - 1;
    while (fim > texto && isspace((unsigned char)*fim)) fim--;
    fim[1] = '\0';
    return texto;
}

int converter_inteiro(const char *texto, int *valor) {
    char *fim;
    long numero;
    errno = 0;
    numero = strtol(texto, &fim, 10);
    if (texto == fim || errno == ERANGE || numero < INT_MIN || numero > INT_MAX) return 0;
    while (isspace((unsigned char)*fim)) fim++;
    if (*fim != '\0') return 0;
    *valor = (int)numero;
    return 1;
}

int converter_decimal(const char *texto, double *valor) {
    char *fim;
    double numero;
    errno = 0;
    numero = strtod(texto, &fim);
    if (texto == fim || errno == ERANGE || !isfinite(numero)) return 0;
    while (isspace((unsigned char)*fim)) fim++;
    if (*fim != '\0') return 0;
    *valor = numero;
    return 1;
}

int ler_inteiro_minimo(const char *mensagem, int minimo) {
    char linha[128];
    int numero;
    while (1) {
        printf("%s", mensagem);
        if (!ler_linha(linha, sizeof(linha))) {
            puts("Entrada muito longa. Tente novamente.");
            continue;
        }
        if (converter_inteiro(remover_espacos(linha), &numero) && numero >= minimo)
            return numero;
        printf("Valor invalido. Digite um numero inteiro maior ou igual a %d.\n", minimo);
    }
}

int ler_inteiro_intervalo(const char *mensagem, int minimo, int maximo) {
    int numero;
    while (1) {
        numero = ler_inteiro_minimo(mensagem, minimo);
        if (numero <= maximo) return numero;
        printf("Escolha um valor entre %d e %d.\n", minimo, maximo);
    }
}

double ler_preco(const char *mensagem) {
    char linha[128];
    double numero;
    size_t i;
    while (1) {
        printf("%s", mensagem);
        if (!ler_linha(linha, sizeof(linha))) {
            puts("Entrada muito longa. Tente novamente.");
            continue;
        }
        for (i = 0; linha[i] != '\0'; i++) {
            if (linha[i] == ',') linha[i] = '.';
        }
        if (converter_decimal(remover_espacos(linha), &numero) && numero > 0 && numero <= FLT_MAX)
            return numero;
        puts("Preco invalido. Digite um numero maior que zero (ex.: 19,90).");
    }
}

void ler_texto(const char *mensagem, char *destino, size_t capacidade) {
    char linha[256];
    char *texto;
    while (1) {
        printf("%s", mensagem);
        if (!ler_linha(linha, sizeof(linha))) {
            puts("Texto muito longo. Tente novamente.");
            continue;
        }
        texto = remover_espacos(linha);
        if (*texto == '\0') {
            puts("O nome nao pode ficar em branco.");
        } else if (strchr(texto, '|') != NULL) {
            puts("O caractere | nao pode ser usado no nome.");
        } else if (strlen(texto) >= capacidade) {
            printf("O texto deve ter no maximo %u caracteres.\n", (unsigned)(capacidade - 1));
        } else {
            strcpy(destino, texto);
            return;
        }
    }
}

int separar_campos(char *linha, char *campos[], int quantidade) {
    int i;
    char *atual = linha;
    char *separador;
    linha[strcspn(linha, "\r\n")] = '\0';
    for (i = 0; i < quantidade - 1; i++) {
        separador = strchr(atual, '|');
        if (separador == NULL) return 0;
        *separador = '\0';
        campos[i] = remover_espacos(atual);
        atual = separador + 1;
    }
    if (strchr(atual, '|') != NULL) return 0;
    campos[quantidade - 1] = remover_espacos(atual);
    for (i = 0; i < quantidade; i++) {
        if (*campos[i] == '\0') return 0;
    }
    return 1;
}

char ler_prateleira(const char *mensagem) {
    char linha[128];
    char *texto;
    char letra;
    while (1) {
        printf("%s", mensagem);
        if (!ler_linha(linha, sizeof(linha))) {
            puts("Entrada muito longa. Tente novamente.");
            continue;
        }
        texto = remover_espacos(linha);
        letra = (char)toupper((unsigned char)texto[0]);
        if (texto[0] != '\0' && texto[1] == '\0' &&
            letra >= 'A' && letra <= 'D') {
            return letra;
        }
        puts("Prateleira invalida. Digite A, B, C ou D.");
    }
}

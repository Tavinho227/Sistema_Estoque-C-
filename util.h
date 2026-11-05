#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

int ler_inteiro_minimo(const char *mensagem, int minimo);
int ler_inteiro_intervalo(const char *mensagem, int minimo, int maximo);
double ler_preco(const char *mensagem);
char ler_prateleira(const char *mensagem);
void ler_texto(const char *mensagem, char *destino, size_t capacidade);
int converter_inteiro(const char *texto, int *valor);
int converter_decimal(const char *texto, double *valor);
int separar_campos(char *linha, char *campos[], int quantidade);
char *remover_espacos(char *texto);

#endif

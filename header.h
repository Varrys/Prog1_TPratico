#ifndef __HEADER_H__
#define __HEADER_H__

#include "../src/listas.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

char userLogin[50];
void menuLogin(ELUTI *iniLista, UTI utilizador, ELATA *iniLista2, ATA ata, PREVISAO *prev);
void menuAdmin(ELUTI *iniLista, UTI utilizador, ELATA *iniLista2, ATA ata, PREVISAO *prev);
void menuAcionista(ELUTI *iniLista, UTI utilizador, ELATA *iniLista2, ATA ata);

int efetuarLogin(ELUTI *iniLista, char userLogin[]);
int imprimeListaUti(ELUTI *iniLista);
int inserirInicioUti(ELUTI **iniLista, UTI *utilizador);
void carregaListaUti(ELUTI **iniLista);
void insereUtilizador(ELUTI *iniLista, UTI *utilizador);
int guardaUtilizador(ELUTI *iniLista);
int validaUtilizador(ELUTI *iniLista, char username[]);
int inserirInicioAtas(ELATA **iniLista2, ATA *ata);
void carregaListaAtas(ELATA **iniLista2);
int imprimeAta(ELATA *iniLista2, ATA ata);
int imprimeListaAtas(ELATA *iniLista2, ATA ata);
int carregarNumAtas(ELATA *iniLista2, ATA *ata);
void insereAtas(ELATA *iniLista2, ATA *ata, UTI *utilizador, PREVISAO *prev, ELUTI *iniLista);
int guardaAtas(ELATA *iniLista2);
int imprimeAtasEstado(ELATA *iniLista2, ATA *ata);
int imprimeAtasData(ELATA *iniLista2, ATA *ata);
void imprimeListaLocal(ELATA *iniLista2, ATA *ata);
int previsaoAtas(ELATA *iniLista2, ATA *ata, PREVISAO *prev);
void editaAtas(ELATA *iniLista2, ATA *ata);
ELATA *removerIni(ELATA *iniLista2);
ELATA *encontraRemoveNode(ATA ata, ELATA *iniLista2, int num);
ELATA *removerAta(ATA *ata, ELATA *iniLista2);
int assinarAta(ATA *ata, ELATA *iniLista2, char userLogin[]);
void imprimeAssinaturasEmFalta(ATA *ata, ELATA *iniLista2);
void imprimeListaEstadoData(ELATA *iniLista2, ATA *ata);
ELATA *inserirOrdenada(ELATA *iniLista2, ATA *ata);
void imprimeListaLocalData(ELATA *iniLista2, ATA *ata);

#endif
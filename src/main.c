#include "../include/header.h"

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    int opcao, opcao2, opcao3;
    PREVISAO prev;
    UTI utilizador;
    ATA ata;
    ELUTI *iniLista = NULL;
    ELATA *iniLista2 = NULL;
    carregaListaUti(&iniLista);
    carregaListaAtas(&iniLista2);

    menuLogin(iniLista, utilizador, iniLista2, ata, &prev);

    printf("\n### A terminar ###\n");
    return 0;
}
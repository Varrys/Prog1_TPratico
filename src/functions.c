#include "../include/header.h"

//**Funções gerais**
void menuLogin(ELUTI *iniLista, UTI utilizador, ELATA *iniLista2, ATA ata, PREVISAO *prev)
{
    int opcao, tipo = 0;
    do
    {
        printf("\n\n\t############# Login ##############\n");
        printf("\n[1] - Iniciar Sessao.");
        printf("\n[0] - >SAIR<\n");
        printf("\nEscolha a sua OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 0:
            exit(0);
            break;
        case 1:
            //  carregaListaUti(&iniLista);
            //imprimeListaUti(iniLista);
            tipo = efetuarLogin(iniLista, userLogin);
            printf("\nBem-vindo: %s", userLogin);
            if (tipo == 1)
            {
                menuAdmin(iniLista, utilizador, iniLista2, ata, prev);
                //arroz de batata
            }
            if (tipo == 2)
            {
                menuAcionista(iniLista, utilizador, iniLista2, ata);
            }
            break;
        case 2:

            break;
        case 3:

            break;

        default:
            printf("Opcao Invalida!");
        }
    } while (opcao != 0);
}

void menuAdmin(ELUTI *iniLista, UTI utilizador, ELATA *iniLista2, ATA ata, PREVISAO *prev)
{
    int opcao2;
    do
    {
        printf("\n\n\t############# MENU ADMIN ##############\n");
        printf("\n[1] - Inserir um novo utilizador.");
        printf("\n[2] - Listar utilizadores.");
        printf("\n[3] - Listar atas por estado.");
        printf("\n[4] - Listar atas por data.");
        printf("\n[5] - Listar atas por local");
        printf("\n[6] - Listar por local e por data");
        printf("\n[7] - Inserir uma ata.");
        printf("\n[8] - Editar uma ata");
        printf("\n[9] - Remover uma ata");
        printf("\n[10] - Assinar ata");
        printf("\n[11] - Listar assinaturas em falta de uma ata");
        printf("\n[0] - >SAIR<\n");
        printf("\nEscolha a sua OPCAO: ");
        scanf("%d", &opcao2);
        switch (opcao2)
        {
        case 0:
            break;
        case 1:
            insereUtilizador(iniLista, &utilizador);
            inserirInicioUti(&iniLista, &utilizador);
            guardaUtilizador(iniLista);
            break;
        case 2:
            imprimeListaUti(iniLista);
            break;
        case 3:
            //imprimeListaAtas(iniLista2);
            imprimeAtasEstado(iniLista2, &ata);
            break;
        case 4:
            imprimeAtasData(iniLista2, &ata);
            break;

        case 5:
            imprimeListaLocal(iniLista2, &ata);
            break;
        case 6:
            imprimeListaEstadoData(iniLista2, &ata);
            break;
        case 7:
            insereAtas(iniLista2, &ata, &utilizador, prev, iniLista);
            inserirInicioAtas(&iniLista2, &ata);
            guardaAtas(iniLista2);
            break;
        case 8:
            editaAtas(iniLista2, &ata);
            guardaAtas(iniLista2);
            break;
        case 9:
            iniLista2 = removerAta(&ata, iniLista2);
            guardaAtas(iniLista2);
            break;
        case 10:
            assinarAta(&ata, iniLista2, userLogin);
            break;
        case 11:
            imprimeAssinaturasEmFalta(&ata, iniLista2);
            break;
        default:
            printf("Opcao Invalida!");
        }
    } while (opcao2 != 0);
}

void menuAcionista(ELUTI *iniLista, UTI utilizador, ELATA *iniLista2, ATA ata)
{
    int opcao3;
    printf("\n\n\t############# MENU ACIONISTA ##############\n");
    printf("\n[1] - Assinar uma ata.");
    printf("\n[0] - >SAIR<\n");
    do
    {

        printf("\nEscolha a sua OPCAO: ");
        scanf("%d", &opcao3);
        switch (opcao3)
        {
        case 0:
            break;
        case 1:
            assinarAta(&ata, iniLista2, userLogin);
            break;
        case 2:

            break;
        default:
            printf("Opcao Invalida!");
        }
    } while (opcao3 != 0);
}

int efetuarLogin(ELUTI *iniLista, char userLogin[])
{
    char username[20];
    char password[30];
    int loginErro = 0;
    printf("\n");
    printf("\nIntroduza o username: ");
    fflush(stdin);
    scanf("%20[^\n]s", username);
    printf("\nIntroduza a password: ");
    fflush(stdin);
    scanf("%30[^\n]s", password);

    ELUTI *aux = NULL;
    if (iniLista == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    aux = iniLista;
    //imprimeListaUti(iniLista);
    while (aux != NULL && loginErro == 0)
    {
        if ((strcmp(username, aux->utilizador.username) == 0) && (strcmp(password, aux->utilizador.password) == 0))
        {
            printf("\nLogado com sucesso");
            loginErro = 1;
            strcpy(userLogin, aux->utilizador.username);
            return aux->utilizador.tipo;
        }
        aux = aux->seguinte;
    }

    if (loginErro == 0) //Se nao for efetuado login
    {
        printf("\nNao foi possivel efetuar login.");
        efetuarLogin(iniLista, userLogin);
    }
}

int imprimeListaUti(ELUTI *iniLista)
{
    ELUTI *aux = NULL;
    if (iniLista == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    for (aux = iniLista; aux != NULL; aux = aux->seguinte)
    {
        printf("%s; %s; %s; %d; \n", aux->utilizador.username, aux->utilizador.nome, aux->utilizador.password, aux->utilizador.tipo);
    }
}

int inserirInicioUti(ELUTI **iniLista, UTI *utilizador)
{
    ELUTI *novo = NULL;
    novo = (ELUTI *)calloc(1, sizeof(ELUTI));
    if (novo == NULL)
    {
        printf("Out of memory \n");
        return -1;
    }
    novo->utilizador = *utilizador;
    novo->seguinte = NULL;
    if (*iniLista == NULL)
    {
        *iniLista = novo;
    }
    else
    {
        novo->seguinte = *iniLista;
        *iniLista = novo;
    }
    return 0;
}

void carregaListaUti(ELUTI **iniLista)
{
    int res;
    UTI utilizador;
    FILE *fp;

    if ((fp = fopen("login.txt", "r")) != NULL)
    {
        while ((res = fscanf(fp, "%[^;];%[^;];%[^;];%d;\n", utilizador.username, utilizador.nome, utilizador.password, &utilizador.tipo)) != EOF)
        {
            inserirInicioUti(iniLista, &utilizador);
        }
    }
    fclose(fp);
}

int guardaUtilizador(ELUTI *iniLista)
{

    ELUTI *aux = NULL;
    if (iniLista == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    FILE *fp;
    fp = fopen("login.txt", "w");
    if (fp == NULL)
    {
        printf("Ocorreu um erro ao abrir o arquivo\n");
    }
    else
    {
        for (aux = iniLista; aux != NULL; aux = aux->seguinte)
        {
            fprintf(fp, "%s;%s;%s;%d;\n", aux->utilizador.username, aux->utilizador.nome, aux->utilizador.password, aux->utilizador.tipo);
        }
        fclose(fp);
    }
}

int validaUtilizador(ELUTI *iniLista, char username[])
{
    ELUTI *aux = NULL;
    if (iniLista == NULL)
    {
        printf("Lista vazia \n");
    }
    for (aux = iniLista; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->utilizador.username, username) == 0)
        {
            printf("\nO Username ja existe\n");
            return 0;
        }
    }
    return 1;
}

void insereUtilizador(ELUTI *iniLista, UTI *utilizador)
{
    int op, erro = 0, existe = 0;
    char password[50], username[20];
    printf("\n Insira o seu nome: ");
    fflush(stdin);
    scanf("%[^\n]", utilizador->nome);

    do
    {
        printf("\nUsername: ");
        fflush(stdin);
        scanf("%s", username);
        existe = validaUtilizador(iniLista, username);
        if (existe != 0)
        {
            strcpy(utilizador->username, username);
        }
    } while (existe == 0);

    do
    {
        printf("\n Insira uma password: ");
        fflush(stdin);
        scanf("%s", utilizador->password);
        printf("\n Confirme a password: ");
        fflush(stdin);
        scanf("%s", password);
        if ((strcmp(utilizador->password, password) == 0))
        {
            erro = 1;
        }
        else
        {
            printf("\nPasswords nao coincidem!");
        }
    } while (erro == 0);
    do
    {
        printf("\n Escolha o tipo de conta [1]-Admin // [2]-Acionista: ");
        scanf("%d", &utilizador->tipo);
    } while (utilizador->tipo != 1 && utilizador->tipo != 2);
    // inserirInicioUti(iniLista, utilizador);
}

int inserirInicioAtas(ELATA **iniLista2, ATA *ata)
{
    ELATA *novo = NULL;
    novo = (ELATA *)calloc(1, sizeof(ELATA));
    if (novo == NULL)
    {
        printf("Out of memory \n");
        return -1;
    }
    novo->ata = *ata;
    if (iniLista2)
    {
        novo->seguinte = *iniLista2;
    }
    else
    {
        novo->seguinte = NULL;
    }
    if (novo->seguinte)
    {
        novo->seguinte->anterior = novo;
    }
    novo->anterior = NULL;
    *iniLista2 = novo;
    return 0;
}

void carregaListaAtas(ELATA **iniLista2)
{
    int res;
    ATA ata;
    FILE *fp;

    if ((fp = fopen("atas.txt", "r")) != NULL)
    {
        while ((res = fscanf(fp, "%d;%d/%d/%d;%[^;];%[^;];%[^;];%d;%[^;];%d;%[^;];%d;%[^;];\n", &ata.nAta, &ata.dataAta.dia,
                             &ata.dataAta.mes, &ata.dataAta.ano, ata.local, ata.texto, ata.assin.acio1,
                             &ata.assin.assinado1, ata.assin.acio2, &ata.assin.assinado2, ata.assin.acio3, &ata.assin.assinado3,
                             ata.estado)) != EOF)
        {
            inserirInicioAtas(iniLista2, &ata);
        }
    }
    fclose(fp);
}

int imprimeAta(ELATA *iniLista2, ATA ata)
{
    ELATA *aux = NULL;
    aux = iniLista2;
    printf("\nNumero: %d", aux->ata.nAta);
    printf("\nData: %d/%d/%d", aux->ata.dataAta.dia, aux->ata.dataAta.mes, aux->ata.dataAta.ano);
    printf("\nLocal: %s", aux->ata.local);
    printf("\nTexto: %s", aux->ata.texto);
    printf("\nAcionistas: %s, %s, %s\n", aux->ata.assin.acio1, aux->ata.assin.acio2, aux->ata.assin.acio3);
}

int imprimeListaAtas(ELATA *iniLista2, ATA ata)
{
    ELATA *aux = NULL;
    if (iniLista2 == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        imprimeAta(aux, ata);
    }
}

int carregarNumAtas(ELATA *iniLista2, ATA *ata)
{
    ELATA *aux = NULL;
    int maior = 0;
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if (aux->ata.nAta > maior)
        {
            maior = aux->ata.nAta;
        }
    }
    return maior + 1;
}

void insereAtas(ELATA *iniLista2, ATA *ata, UTI *utilizador, PREVISAO *prev, ELUTI *iniLista)
{
    int previs = 0, cont = 1, numero = 0, i = 0, cont2 = 0;
    char opcao;
    ELUTI *aux = NULL;
    ata->nAta = carregarNumAtas(iniLista2, ata);
    printf("\nPretende inserir a data e local utilizando um ficheiro exterior?: S/N ");
    fflush(stdin);
    scanf("%s", &opcao);
    if (opcao == 's' || opcao == 'S')
    {
        previs = previsaoAtas(iniLista2, ata, prev);
        ata->dataAta.dia = prev[previs].dataP.dia;
        ata->dataAta.mes = prev[previs].dataP.mes;
        ata->dataAta.ano = prev[previs].dataP.ano;
        strcpy(ata->local, prev[previs].local);
    }
    else
    {
        do
        {
            printf("\nIntroduza o dia(Ex: 20/01/2021): ");
            scanf("%d/%d/%d", &ata->dataAta.dia, &ata->dataAta.mes, &ata->dataAta.ano);
        } while ((ata->dataAta.dia <= 0) || (ata->dataAta.dia > 31) || (ata->dataAta.mes <= 0) ||
                 (ata->dataAta.mes > 12) || (ata->dataAta.ano <= 2020) || (ata->dataAta.ano > 2022));

        printf("\nIntroduza o local: ");
        fflush(stdin);
        scanf("%s", ata->local);
    }
    printf("\nIntroduza a ata: ");
    fflush(stdin);
    scanf("%[^\n];", ata->texto);
    for (aux = iniLista; aux != NULL; aux = aux->seguinte)
    {
        printf("N_%d->%s;\n", cont, aux->utilizador.nome);
        cont++;
    }
    do
    {
        printf("\n Escolha os acionistas que pretende inscrever na assembleia: ");
        scanf("%d", &numero);
        for (aux = iniLista; aux != NULL; aux = aux->seguinte)
        {
            cont2++;
            if (cont2 == numero)
            {
                if (i == 0)
                {
                    strcpy(ata->assin.acio1, aux->utilizador.username);
                    ata->assin.assinado1 = 0;
                }
                if (i == 1)
                {
                    strcpy(ata->assin.acio2, aux->utilizador.username);
                    ata->assin.assinado2 = 0;
                }
                if (i == 2)
                {
                    strcpy(ata->assin.acio3, aux->utilizador.username);
                    ata->assin.assinado3 = 0;
                }
            }
        }
        cont2 = 0;
        i++;
    } while (i < 3);
    strcpy(ata->estado, "redacao");
}

int guardaAtas(ELATA *iniLista2)
{

    ELATA *aux = NULL;
    if (iniLista2 == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    FILE *fp;
    fp = fopen("atas.txt", "w");
    if (fp == NULL)
    {
        printf("Ocorreu um erro ao abrir o arquivo\n");
    }
    else
    {
        for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
        {
            fprintf(fp, "%d;%d/%d/%d;%s;%s;%s;%d;%s;%d;%s;%d;%s;\n", aux->ata.nAta, aux->ata.dataAta.dia, aux->ata.dataAta.mes,
                    aux->ata.dataAta.ano, aux->ata.local, aux->ata.texto, aux->ata.assin.acio1, aux->ata.assin.assinado1,
                    aux->ata.assin.acio2, aux->ata.assin.assinado2, aux->ata.assin.acio3, aux->ata.assin.assinado3, aux->ata.estado);
        }
        fclose(fp);
    }
}

int imprimeAtasEstado(ELATA *iniLista2, ATA *ata)
{
    int opc;
    char estado[20], naoha = 0;
    ELATA *aux = NULL;
    if (iniLista2 == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    do
    {
        do
        {
            printf("\nEscolha o estado que pretender verificar: ");
            printf("\n[1]-Em redacao.");
            printf("\n[2]-Para assinar.");
            printf("\n[3]-Concluida.");
            printf("\n[0]-Voltar.\n");
            printf("\nOpcao: ");
            scanf("%d", &opc);
        } while (opc < 0 && opc > 3);
        switch (opc)
        {
        case 1:
            strcpy(estado, "redacao");
            break;
        case 2:
            strcpy(estado, "assinatura");
            break;
        case 3:
            strcpy(estado, "concluida");
            break;
        }

        for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
        {
            if (strcmp(estado, aux->ata.estado) == 0)
            {
                imprimeAta(aux, *ata);
                naoha = 1;
            }
        }
        if (naoha == 0)
        {
            printf("\nNão existem dados para a listar.\n");
        }
        naoha = 0;
    } while (opc != 0);
}

int imprimeAtasData(ELATA *iniLista2, ATA *ata)
{
    int dia, mes, ano;
    ELATA *aux = NULL;
    if (iniLista2 == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    do
    {
        printf("Indique a data: ");
        scanf("%d/%d/%d", &dia, &mes, &ano);

    } while ((dia <= 0) || (dia > 31) || (mes <= 0) || (mes > 12));

    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if (aux->ata.dataAta.ano == ano)
        {
            if (aux->ata.dataAta.mes == mes)
            {
                if (aux->ata.dataAta.dia >= dia)
                {
                    imprimeAta(iniLista2, *ata);
                }
            }
            else if (aux->ata.dataAta.mes > mes)
            {
                imprimeAta(iniLista2, *ata);
            }
        }
        else if (aux->ata.dataAta.ano > ano)
        {
            imprimeAta(iniLista2, *ata);
        }
    }
}

void imprimeListaLocal(ELATA *iniLista2, ATA *ata)
{
    char local[30];
    int erro = 0;
    ELATA *aux = NULL;
    if (iniLista2 == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    do
    {
        printf("\nInsira o local que pretende pesquisar:");
        fflush(stdin);
        scanf("%30[^\n]", local);
        for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
        {
            if (strcmp(local, aux->ata.local) == 0)
            {
                imprimeAta(aux, *ata);
                erro = 1;
            }
        }
        if (erro == 0)
        {
            printf("\nLocal nao encontrado");
        }
        erro = 0;
    } while (erro == 1);
}

ELATA *inserirOrdenada(ELATA *iniLista2, ATA *ata)
{
    if (!iniLista2 || ata->dataAta.ano < iniLista2->ata.dataAta.ano)
    {
        ELATA *novo = (ELATA *)calloc(1, sizeof(ELATA));
        novo->ata = *ata;
        novo->seguinte = iniLista2;
        iniLista2 = novo;
    }
    else if (ata->dataAta.ano == iniLista2->ata.dataAta.ano)
    {

        if (!iniLista2 || ata->dataAta.mes < iniLista2->ata.dataAta.mes)
        {
            ELATA *novo = (ELATA *)calloc(1, sizeof(ELATA));
            novo->ata = *ata;
            novo->seguinte = iniLista2;
            iniLista2 = novo;
        }
        else if (ata->dataAta.mes == iniLista2->ata.dataAta.mes)
        {
            if (!iniLista2 || ata->dataAta.dia == iniLista2->ata.dataAta.dia || ata->dataAta.dia < iniLista2->ata.dataAta.dia)
            {
                ELATA *novo = (ELATA *)calloc(1, sizeof(ELATA));
                novo->ata = *ata;
                novo->seguinte = iniLista2;
                iniLista2 = novo;
            }
            else
            {
                iniLista2->seguinte = inserirOrdenada(iniLista2->seguinte, ata);
            }
        }
        else
        {
            iniLista2->seguinte = inserirOrdenada(iniLista2->seguinte, ata);
        }
    }
    else
    {
        iniLista2->seguinte = inserirOrdenada(iniLista2->seguinte, ata);
    }
    return iniLista2;
}

void imprimeListaEstadoData(ELATA *iniLista2, ATA *ata)
{
    ELATA *aux = NULL;
    ELATA *aux2 = NULL;
    ELATA *aux3 = NULL;
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {

        aux2 = inserirOrdenada(aux2, &aux->ata);
    }
    // imprimeListaAtas(aux2, *ata);
    printf("\nAssinar:\n");
    for (aux3 = aux2; aux3 != NULL; aux3 = aux3->seguinte)
    {
        // printf("-_>%s", aux2->ata.estado);
        if (strcmp(aux3->ata.estado, "assinatura") == 0)
        {
            imprimeAta(aux3, *ata);
        }
    }
    printf("\nConcluidos:\n");
    for (aux3 = aux2; aux3 != NULL; aux3 = aux3->seguinte)
    {
        //  printf("->%s", aux2->ata.estado);
        if (strcmp(aux3->ata.estado, "concluido") == 0)
        {
            imprimeAta(aux3, *ata);
        }
    }
    printf("\nRedacao:\n");
    for (aux3 = aux2; aux3 != NULL; aux3 = aux3->seguinte)
    {
        if (strcmp(aux3->ata.estado, "redacao") == 0)
        {
            imprimeAta(aux3, *ata);
        }
    }
}

int previsaoAtas(ELATA *iniLista2, ATA *ata, PREVISAO *prev)
{
    char ficheiro[30];
    int res = 0, i = 0, previ = 0;
    ELATA *aux = NULL;
    FILE *fp;
    do
    {
        printf("\nIndique o nome do ficheiro (ex: lista.csv) que pretende carregar: ");
        fflush(stdin);
        scanf("%30[^\n]", ficheiro);
    } while ((fp = fopen(ficheiro, "r")) == NULL);

    if ((fp = fopen(ficheiro, "r")) != NULL)
    {
        while ((res = fscanf(fp, "%d;%d;%d;%[^;];\n", &prev[i].dataP.dia, &prev[i].dataP.mes, &prev[i].dataP.ano, prev[i].local)) != EOF)
        {
            printf("\n[%d]-%d/%d/%d-%s", i, prev[i].dataP.dia, prev[i].dataP.mes, prev[i].dataP.ano, prev[i].local);
            i++;
        }
        printf("\nEscolha a opcao com a data e local correto: ");
        scanf("%d", &previ);
        return previ;
    }
    else
    {
        printf("\nFicheiro não foi localizado;");
    }

    fclose(fp);
}

void editaAtas(ELATA *iniLista2, ATA *ata)
{
    int edit = 0, esco;
    char newTexto[1000];
    ELATA *aux = NULL;
    if (iniLista2 == NULL)
    {
        printf("Lista vazia \n");
        return 0;
    }
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->ata.estado, "redacao") == 0)
        {
            imprimeAta(aux, *ata);
        }
    }
    printf("\nEscolha a ata que pretende editar: ");
    scanf("%d", &edit);
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if (edit == aux->ata.nAta)
        {
            printf("\n%s\n", aux->ata.texto);
            printf("\nInsira o novo texto da ata: ");
            fflush(stdin);
            scanf("%[^\n]s", newTexto);
            strcpy(aux->ata.texto, newTexto);
            printf("\nEscolha o estado da ata (1-redacao // 2- por assinar): ");
            scanf("%d", &esco);
            if (esco == 1)
            {
                strcpy(aux->ata.estado, "redacao");
            }
            if (esco == 2)
            {
                strcpy(aux->ata.estado, "assinatura");
            }
        }
    }
}

ELATA *removerIni(ELATA *iniLista2)
{
    ELATA *aux = NULL;
    aux = iniLista2;
    iniLista2 = aux->seguinte;
    free(aux);
    return iniLista2;
}

ELATA *encontraRemoveNode(ATA ata, ELATA *iniLista2, int num)
{
    ELATA *aux = iniLista2;
    while (aux != NULL)
    {
        if (num == aux->ata.nAta)
        {
            if (aux->seguinte)
                aux->seguinte->anterior = aux->anterior;

            if (aux->anterior)
                aux->anterior->seguinte = aux->seguinte;
            else
                iniLista2 = aux->seguinte;

            aux = removerIni(aux);
        }
        else
        {
            aux = aux->seguinte;
        }
    }
    return iniLista2;
}

ELATA *removerAta(ATA *ata, ELATA *iniLista2)
{
    FILE *fp = NULL;
    ELATA *aux = NULL;
    int num = 0;
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->ata.estado, "redacao") == 0)
        {
            imprimeAta(aux, *ata);
        }
    }
    printf("\nEscolha a ata que pretende remover: ");
    scanf("%d", &num);
    iniLista2 = encontraRemoveNode(*ata, iniLista2, num);
    return iniLista2;
}

int assinarAta(ATA *ata, ELATA *iniLista2, char userLogin[])
{
    ELATA *aux = NULL;
    int cont = 1, Nata = 0, temp = 0;
    char userIntr[20];
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if ((aux->ata.assin.assinado3 == 0) && (strcmp(userLogin, aux->ata.assin.acio3) == 0) && (strcmp(aux->ata.estado, "assinatura") == 0))
        {

            imprimeAta(aux, *ata);
            temp = 1;
        }
        if ((aux->ata.assin.assinado2 == 0) && (strcmp(userLogin, aux->ata.assin.acio2) == 0) && (strcmp(aux->ata.estado, "assinatura") == 0))
        {

            imprimeAta(aux, *ata);
            temp = 1;
        }
        if ((aux->ata.assin.assinado1 == 0) && (strcmp(userLogin, aux->ata.assin.acio1) == 0) && (strcmp(aux->ata.estado, "assinatura") == 0))
        {

            imprimeAta(aux, *ata);
            temp = 1;
        }
    }
    if (temp == 0)
    {
        printf("\nNão tem atas para assinar!");
        return 0;
    }

    printf("\nEscolha a ata que pretende assinar: ");
    scanf("%d", &Nata);
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if (Nata == aux->ata.nAta)
        {
            if (aux->ata.assin.assinado3 == 1)
            {
                if (aux->ata.assin.assinado2 == 1)
                {
                    if (strcmp(userLogin, aux->ata.assin.acio1) == 0)
                    {
                        printf("\nAssine com o seu nome de utilizador: ");
                        fflush(stdin);
                        scanf("%s", userIntr);
                        if (strcmp(userIntr, userLogin) == 0)
                        {
                            aux->ata.assin.assinado1 = 1;
                            strcpy(aux->ata.estado, "concluido");
                            guardaAtas(iniLista2);
                        }
                    }
                    else
                    {
                        printf("\nAinda nao e a sua vez de assinar!");
                    }
                }
                else
                {
                    if (strcmp(userLogin, aux->ata.assin.acio2) == 0)
                    {
                        printf("\nAssine com o seu nome de utilizador: ");
                        fflush(stdin);
                        scanf("%s", userIntr);
                        if (strcmp(userIntr, userLogin) == 0)
                        {
                            aux->ata.assin.assinado2 = 1;
                            guardaAtas(iniLista2);
                        }
                    }
                    else
                    {
                        printf("\nAinda nao e a sua vez de assinar!");
                    }
                }
            }
            else
            {
                if (strcmp(userLogin, aux->ata.assin.acio3) == 0)
                {
                    printf("\nAssine com o seu nome de utilizador: ");
                    fflush(stdin);
                    scanf("%s", userIntr);
                    if (strcmp(userIntr, userLogin) == 0)
                    {
                        aux->ata.assin.assinado3 = 1;
                        guardaAtas(iniLista2);
                    }
                }
                else
                {
                    printf("\nAinda nao e a sua vez de assinar!");
                }
            }
        }
    }
}

void imprimeAssinaturasEmFalta(ATA *ata, ELATA *iniLista2)
{
    ELATA *aux = NULL;
    int escolha;
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if (strcmp(aux->ata.estado, "assinatura") == 0)
        {
            if (aux->ata.assin.acio1)
            {
                imprimeAta(aux, *ata);
            }
        }
    }
    printf("\nEscolha a ata que pretende verificar as assinaturas em falta: ");
    scanf("%d", &escolha);
    printf("\nNa ata n%d faltam assinar os seguintes acionistas: ", escolha);
    for (aux = iniLista2; aux != NULL; aux = aux->seguinte)
    {
        if ((aux->ata.assin.assinado3 == 0) && (escolha == aux->ata.nAta))
        {
            printf("\n%s", aux->ata.assin.acio3);
        }
        if (aux->ata.assin.assinado2 == 0 && (escolha == aux->ata.nAta))
        {
            printf("\n%s", aux->ata.assin.acio2);
        }
        if (aux->ata.assin.assinado1 == 0 && (escolha == aux->ata.nAta))
        {
            printf("\n%s", aux->ata.assin.acio1);
        }
    }
}
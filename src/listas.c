typedef struct data
{
    int dia;
    int mes;
    int ano;
} DATA;

typedef struct hora
{
    int horas;
    int minutos;
} HORA;

typedef struct utilizador
{
    char username[20]; //não pode ter repetidos;
    char nome[50];
    char password[30];
    int tipo;
} UTI;

typedef struct eluti
{
    UTI utilizador;
    struct eluti *seguinte;
} ELUTI;

typedef struct assinaturas
{
    char acio1[30];
    int assinado1;
    char acio2[30];
    int assinado2;
    char acio3[30];
    int assinado3;
} ASSIN;

typedef struct ata
{
    int nAta; //introdução automatica e sequencial;
    DATA dataAta;
    char local[50];
    char texto[1000];
    ASSIN assin;
    char estado[10]; // (3) em redação.. para assinatura.. concluída;
} ATA;

typedef struct elata
{
    ATA ata;
    struct elata *seguinte;
    struct elata *anterior;
} ELATA;

typedef struct previsao
{
    char local[50];
    DATA dataP;
} PREVISAO;

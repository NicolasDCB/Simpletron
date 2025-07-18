#include <stdio.h>
#include <stdlib.h>

//Cabeçalho das definições de cada comando estatos do inicio do programa
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
#define MEMORIA 100
#define SENTINELA -9999
#define MAX 9999

int contadorInstrucao = 0;  // conta os comando e armazena na memoria
int memoria[MEMORIA] = {0};   // memoria
int acumulador = 0;
int totalEntradas = 0;
int indiceEntrada = 0;
int registradorInstrucao; // vai guardar um comando
int entradas[MEMORIA];
int codigoOperacao;     // codigo da operacao a direita
int operando;           // codigo de operando a esquerda




void simpletron() {
    int opcao;

    printf("Simpletron\n");
    printf("\nMenu:\n");
    printf("1 - Digitar o programa manualmente\n");
    printf("2 - Carregar o programa a partir de um arquivo \n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        comandosM();
    } else if (opcao == 2) {
        comandosArq();
    } else {
        printf("Opcao invalida. Encerrando...\n");
        exit(1);
    }
}

void comandosArq() {
    FILE *arquivo = fopen("programa.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    int comando, contador = 0;

    while (fscanf(arquivo, "%d", &comando) != EOF && comando != -9999) {
        if (comando < -9999 || comando > 9999) {
            printf("Comando inválido no arquivo: %d\n", comando);
            exit(1);
        }
        if (contador >= MEMORIA) {
            printf("Erro: programa excede o tamanho da memória (%d palavras)\n", MEMORIA);
            exit(1);
        }
        memoria[contador++] = comando;
    }

    while (fscanf(arquivo, "%d", &comando) != EOF) {
        entradas[totalEntradas++] = comando;
    }

    fclose(arquivo);
    printf("\nPrograma carregado corretamente!!\n");
}

void comandosM() {
    int comando;
    int contador = 0;

    while (1) {
        printf("%02d ? ", contador);
        scanf("%d", &comando);

        if (comando == SENTINELA) {
            break;
        }

        if (comando < -9999 || comando > 9999) {
            printf("Comando fora de escala! Tente novamente.\n");
            continue;
        }

        memoria[contador++] = comando;

        if (contador >= MEMORIA) {
            printf("Memória cheia!\n");
            break;
        }
    }

    printf("\nDigite os valores para os comandos READ, um por linha:\n");
   int numReads = contarREADs();
    while (totalEntradas < numReads) {
        printf("Entrada:%d: ", totalEntradas + 1);
        if (scanf("%d", &entradas[totalEntradas++]) != 1) {
            break;
        }
    }
}

int contarREADs() {
    int count = 0;
    for (int i=0; i<MEMORIA; i++) {
        if (memoria[i] / 100 == READ) {
            count++;
        }
    }
    return count;
}




void comandos()
{
    int retornoOperacao = 1;

    while (contadorInstrucao < MEMORIA && retornoOperacao == 1)
    {

    registradorInstrucao = memoria[contadorInstrucao];

    codigoOperacao = registradorInstrucao / 100;

    operando = registradorInstrucao % 100;

    switch (codigoOperacao)
    {

        case READ:
            if (indiceEntrada >= totalEntradas) {
                printf("\nErro: faltam valores de entrada no arquivo\n");
                despejar();
                retornoOperacao = 0;
                break;
            }

            memoria[operando] = entradas[indiceEntrada++];

            if (memoria[operando] <= SENTINELA || memoria[operando] > MAX) {
                printf ("\nComando fora de escala\n");
                despejar();
                retornoOperacao = 0;
            }
            break;

        case WRITE:

            printf ("\nValor em %d: %d", operando, memoria[operando]);

            break;

        case LOAD:

            acumulador = memoria[operando];

            break;

        case STORE:

            memoria[operando] = acumulador;

            break;

        case ADD:

            acumulador += memoria[operando];

            if (acumulador < SENTINELA || acumulador > MAX){
                printf ("\nAcumulador fora de escala (ADD)");
                despejar();
                retornoOperacao = 0;
            }

            break;

        case SUBTRACT:

            acumulador -= memoria[operando];

            if (acumulador < SENTINELA || acumulador > MAX){
                printf ("\nAcumulador fora de escala (SUB)");
                despejar();
                retornoOperacao = 0;
            }


            break;

        case DIVIDE:

            if (memoria[operando] == 0){
                printf ("\nNao pode dividir por zero!");
                despejar();
                retornoOperacao = 0;
                break;
            }

            acumulador /= memoria[operando];

            break;

        case MULTIPLY:

            acumulador *= memoria[operando];

            if (acumulador < SENTINELA || acumulador > MAX){
                printf ("\nAcumulador fora de escala (MUL)");
                despejar();
                retornoOperacao = 0;
            }

            break;

        case BRANCH:

            contadorInstrucao = operando;

            break;

        case BRANCHNEG:

            if (acumulador < 0) {
                contadorInstrucao = operando;
            }
            break;

        case BRANCHZERO:

            if (acumulador == 0){
                contadorInstrucao = operando;
            }
            break;

        case HALT:
            despejar();
            retornoOperacao = 0;
            break;

        default:
            despejar();
            retornoOperacao = 0;
            break;
    }
    contadorInstrucao++;
    }

}

void despejar()
{
    printf ("\n\n\nRegristros:\n");
    printf ("Acumulador: %d\n", acumulador);
    printf ("Contador de instrucao: %d\n", contadorInstrucao);
    printf ("Registro de instrucao: %d\n", registradorInstrucao);
    printf ("Codigo de operacao: %d\n", codigoOperacao);
    printf ("Operando: %d\n", operando);


    printf ("\nMEMORIA:\n");
    printf ("       ");
    for (int i=0; i<10; i++)
    {
        printf("%d      ", i);
    }

    printf ("\n");

    for (int i=0; i<MEMORIA; i+=10)
    {
        printf ("%02d  ",i);

        for (int j=0; j<10; j++)
        {
            printf(" %+05d ",memoria[i+j]);
        }
        printf ("\n");
    }
}


int main ()
{
    simpletron();
    comandos();

    return 0;
}

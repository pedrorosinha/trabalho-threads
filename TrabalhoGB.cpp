
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Variáveis de tipos e arquivos
const char *logs[] = {"Interface", "Input", "Operacao", "Localizacao", "Propaganda", "Calculo"};
const char *nomeArquivos[] = {"buffer.log",
                              "Interface.log", "Input.log", "Operacao.log", "Localizacao.log", "Propaganda.log", "Calculo.log",
                              "Omega.log", "KleubsMax.log", "ChirpTome.log"};
#define nTipoLogs 6
#define nArquivos 10

typedef struct
{
    int id;
    pthread_mutex_t mutex;
} ArquivoData;

typedef struct
{
    pthread_t thread;
    int id;
    bool stop;
    bool acessando[nArquivos]; // true se acessando
} ThreadData;



// Dados globais
ArquivoData arquivos[nArquivos];
ThreadData threadBuffer;
ThreadData threadInterface;
ThreadData threadOperacao;
ThreadData threadLocalizacao;
ThreadData threadPropaganda;
ThreadData threadCalculo;
ThreadData threadOmega;
ThreadData threadKlebsMax;
ThreadData threadChirpTome;
ThreadData t;

// Funções das threads
void *ThreadBuffer(void *arg);
void *ThreadInterface(void *arg);
void *ThreadOperacao(void *arg);
void *ThreadLocalizacao(void *arg);
void *ThreadPropaganda(void *arg);
void *ThreadCalculo(void *arg);
void *ThreadOmega(void *arg);
void *ThreadKlebsMax(void *arg);
void *ThreadChirpTome(void *arg);

// Funções e structs auxiliares
void moveLogs(const char *origem, const char *destino, const char *palavra, ThreadData *t) ;
void geraLogs(const char *name);
void LogThread(ThreadData *t);

int main()
{
    srand(time(NULL));

    printf("Iniciando...\n");

    // Inicializa os arquivos e mutexes
    for (int i = 0; i < nArquivos; i++)
    {
        arquivos[i].id = i;
    }

    // Inicializa thread de buffer
    for (int i = 0; i < nArquivos; i++)
        threadBuffer.acessando[i] = false;
    threadBuffer.stop = false;

    pthread_create(&threadBuffer.thread, NULL, ThreadBuffer, &threadBuffer); // arquivo 0 = buffer
    pthread_create(&threadInterface.thread, NULL, ThreadInterface, &threadInterface); // arquivo 1 = interface
    pthread_create(&threadOperacao.thread, NULL, ThreadOperacao, &threadOperacao); // arquivo 3 = operacao
    pthread_create(&threadLocalizacao.thread, NULL, ThreadLocalizacao, &threadLocalizacao); // arquivo 4 = localizacao
    pthread_create(&threadPropaganda.thread, NULL, ThreadPropaganda, &threadPropaganda); // arquivo 5 = propaganda
    pthread_create(&threadCalculo.thread, NULL, ThreadCalculo, &threadCalculo); // arquivo 6 = calculo
    pthread_create(&threadOmega.thread, NULL, ThreadOmega, &threadOmega); // arquivo 7 = omega
    pthread_create(&threadKlebsMax.thread, NULL, ThreadKlebsMax, &threadKlebsMax); // arquivo 8 = klebs
    pthread_create(&threadChirpTome.thread, NULL, ThreadChirpTome, &threadChirpTome); // arquivo 9 = chirp

    // Deixa rodar por 3 segundos
    sleep(20);

    printf("Parando threads.\n");

    threadBuffer.stop = true;
    threadInterface.stop = true;
    threadOperacao.stop = true;
    threadLocalizacao.stop = true;
    threadPropaganda.stop = true;
    threadCalculo.stop = true;
    threadOmega.stop = true;
    threadKlebsMax.stop = true;
    threadChirpTome.stop = true;

    pthread_join(threadBuffer.thread, NULL);
    pthread_join(threadInterface.thread, NULL);
    pthread_join(threadOperacao.thread, NULL);
    pthread_join(threadLocalizacao.thread, NULL);
    pthread_join(threadPropaganda.thread, NULL);
    pthread_join(threadCalculo.thread, NULL);
    pthread_join(threadOmega.thread, NULL);
    pthread_join(threadKlebsMax.thread, NULL);
    pthread_join(threadChirpTome.thread, NULL);

    printf("Finalizando.\n");

    return 0;
}

///////////////////////
// Funções das Threads
void *ThreadBuffer(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[0];

    while (!myself->stop)
    {
        pthread_mutex_lock(&d->mutex);
        threadBuffer.acessando[0] = true;

        LogThread(myself);
        geraLogs(nomeArquivos[d->id]);

        threadBuffer.acessando[0] = false;
        pthread_mutex_unlock(&d->mutex);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadInterface(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[1];

    while (!myself->stop)
    {

        moveLogs("buffer.log", "Interface.log", "Interface", myself);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadOperacao(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[3];

    while (!myself->stop)
    {

        moveLogs("buffer.log", "Operacao.log", "Operacao", myself);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadLocalizacao(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[4];

    while (!myself->stop)
    {

        moveLogs("buffer.log", "Localizacao.log", "Localizacao", myself);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadPropaganda(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[5];

    while (!myself->stop)
    {

        moveLogs("buffer.log", "Propaganda.log", "Propaganda", myself);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadCalculo(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[6];

    while (!myself->stop)
    {

        moveLogs("buffer.log", "Calculo.log", "Calculo", myself);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadOmega(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[7];

    while (!myself->stop)
    {

        moveLogs("Operacao.log", "Omega.log", "Operacao", myself);

        moveLogs("Propaganda.log", "Omega.log", "Propaganda", myself);

        moveLogs("Calculo.log", "Omega.log", "Calculo", myself);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadKlebsMax(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[7];

    while (!myself->stop)
    {

        moveLogs("Propaganda.log", "KleubsMax.log", "Propaganda", myself);

        moveLogs("Interface.log", "KleubsMax.log", "Interface", myself);

        moveLogs("Localizacao.log", "KleubsMax.log", "Localizacao", myself);

        sleep(1);
    }
    return NULL;
}
///////////////////////

void *ThreadChirpTome(void *arg)
{

    ThreadData *myself = (ThreadData *)arg;
    ArquivoData *d = &arquivos[8];

    while (!myself->stop)
    {

        moveLogs("Calculo.log", "ChirpTome.log", "Calculo", myself);

        moveLogs("Localizacao.log", "ChirpTome.log", "Localizacao", myself);

        moveLogs("buffer.log", "ChirpTome.log", "Input", myself);


        sleep(1);
    }
    return NULL;
}
///////////////////////

///////////////////////
// Funções auxiliares
void geraLogs(const char *name)
{
    FILE *f = fopen(name, "a");

    for (int i = 0; i < 5; i++)
    {
        fprintf(f, "%s\n", logs[rand() % nTipoLogs]);
    }

    fclose(f);
}
void moveLogs(const char *origem, const char *destino, const char *palavra, ThreadData *t)
{
    int idOrigem, idDestino;

    for (int i = 0; i < nArquivos; i++)
    {
        if (strcmp(origem, nomeArquivos[i]) == 0) idOrigem = i;
        if (strcmp(destino, nomeArquivos[i]) == 0) idDestino = i;
    }

    t->acessando[idOrigem] = true;
    pthread_mutex_lock(&arquivos[idOrigem].mutex);

    t->acessando[idDestino] = true;
    pthread_mutex_lock(&arquivos[idDestino].mutex);

    char tempName[100];
    strcat(tempName, origem);
    strcat(tempName, "_temp.log");

    FILE *fin = fopen(origem, "r");
    FILE *fout = fopen(destino, "a");
    FILE *ftemp = fopen(tempName, "w");

    char linha[256];
    while (fgets(linha, sizeof(linha), fin))
    {
        if (strstr(linha, palavra))
            fputs(linha, fout);
        else
            fputs(linha, ftemp);
    }

    LogThread(t);

    fclose(fin);
    fclose(fout);
    fclose(ftemp);

    remove(origem);
    rename(tempName, origem);

    t->acessando[idDestino] = false;
    pthread_mutex_unlock(&arquivos[idDestino].mutex);

    t->acessando[idOrigem] = false;
    pthread_mutex_unlock(&arquivos[idOrigem].mutex);
}
void LogThread(ThreadData *t)
{
    printf("Thread %d:", t->thread);
    for (int i = 0; i < nArquivos; i++)
        printf(" %c:%d", nomeArquivos[i][0], t->acessando[i]);
    printf("\n");
}
///////////////////////

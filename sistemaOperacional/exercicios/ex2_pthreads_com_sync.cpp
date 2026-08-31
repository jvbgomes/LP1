#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

#define NTHREADS 5

pthread_t threads[NTHREADS];
int status, i;
void *thread_return;

int soma = 0;

void* hello_world(void *tid) {
    if ((int) (size_t)tid > 0) {
        pthread_join(threads[(size_t)tid - 1], &thread_return);
        cout << "Esta e a Thread " << (int) (size_t)tid << ". A Thread " << (int) (size_t)tid - 1 << " terminou." << endl;
    } 
    else {
        cout << "Esta e a Primeira Thread." << endl;
    }
    soma += 1;
    cout << "O valor de soma eh: " << soma << endl;
    sleep(1);
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {


    for (i = 0; i < NTHREADS; i++) {
        cout << "Processo principal criando thread #" << i << endl;
        status = pthread_create(&threads[i], NULL, hello_world, (void *)(size_t)i);

        if (status != 0) {
            cout << "Erro na criacao da thread. Codigo de Erro: " << status << endl;
            return 1;
        }
    }

    cout << "Esperando Thread " << i - 1 << " finalizar..." << endl;
    pthread_join(threads[i - 1], &thread_return);
    cout << "Thread " << i - 1 << " finalizada" << endl;

    cout << "Processo pai vai finalizar e a soma = " << soma << endl;

    return 0;
}
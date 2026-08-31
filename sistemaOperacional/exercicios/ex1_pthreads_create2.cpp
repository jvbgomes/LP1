#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

#define NTHREADS 5

void* hello_world(void *tid) {
    printf("Hello World. Esta e a thread %d\n", (int)(size_t)tid);
    sleep(((int)(size_t)tid + 1) * 2);
    pthread_exit(NULL);
}


int main(int argc, char *argv[]) {

    pthread_t threads[NTHREADS];
    int status, i;
    void *thread_return;

    for (i = 0; i < NTHREADS; i++) {
        cout << "Processo principal criando thread #" << i << endl;
        status = pthread_create(&threads[i], NULL, hello_world, (void *)(size_t)i);

        if (status != 0) {
            cout << "Erro na criacao da thread. Codigo de Erro: " << status << endl;
            return 1;
        }
    }

    for (i = 0; i < NTHREADS; i++) {
        printf("Processo principal esperando a thread %d finalizar...\n", i);
        pthread_join(threads[i], &thread_return);
        cout << "Thread " << i << " finalizada" << endl;
    }
    cout << "Processo vai finalizar" << endl;

    return 0;
}
#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

void *hello_world(void *tid) {
    cout << "Hello World! Essa e a thread: " << (int) (size_t)tid << endl;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    pthread_t thread;
    int status;
    void *thread_return;

    cout << "Processo principal criando thread" << endl;
    status = pthread_create(&thread, NULL, hello_world, 0);

    if (status != 0) {
        cout << "Erro na criacao da thread: " << status << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Esperando a thread terminar" << endl;
    pthread_join(thread, &thread_return);
    cout << "Thread finalizada" << endl;

    cout << "Processo pai vai finalizar" << endl;

    return 0;
}
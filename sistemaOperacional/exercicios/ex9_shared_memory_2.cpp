#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

int a = 0;
void implementacao_filho1(int *a) {
    *a = *a + 1;
    cout << "executando filho 1: " << getpid() << endl;
}

void implementacao_filho2(int *a) {
    *a = *a * 2;
    cout << "executando filho 2: " << getpid() << endl;
}

int main() {
    int filho1, filho2, pid, status, i;
    int *mem;
    int valor = shmget(IPC_PRIVATE, sizeof(int),IPC_CREAT | 0666);

    mem = (int *)shmat(valor, NULL, 0);
    if (*mem < 0) {
        cout << "Erro ao alocar memória compartilhada" << endl;
        return 0;
    }
    *mem = 5;
    cout << "Pai comecou (PID: " << getpid() << ")" << " e o valor do inteiro é: " << *mem << endl;
    filho1 = fork();
    if (filho1 > 0) {
        filho2 = fork();
    }
    if (filho1 == 0) { // se for filho...
        mem = (int *)shmat(valor, NULL, 0);
        //sleep(1);
        implementacao_filho1(mem);
        cout << "Filho 1 finalizou (PID: " << getpid() << ")" << " e o valor do inteiro é: " << *mem << endl;
        shmdt(mem);
        exit(0);
    }
    else if (filho2 == 0) { // se for filho...
        mem = (int *)shmat(valor, NULL, 0);
        implementacao_filho2(mem);
        cout << "Filho 2 finalizou (PID: " << getpid() << ")" << " e o valor do inteiro é: " << *mem << endl;
        shmdt(mem);
        exit(0);
    }
    
    for (i = 0; i < 2; i++) {
        wait(NULL);
    }
    
    shmctl(valor, IPC_RMID, NULL);  
    cout << "Valor = " << *mem << endl;
    cout << "Pai terminou" << endl;
    exit(0);

    return 0;
}
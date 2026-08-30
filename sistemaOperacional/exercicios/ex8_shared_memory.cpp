#include <iostream>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

int a = 0;
void implementacao_filho1(int &a) {
    a = a + 1;
    cout << "executando filho 1: " << getpid() << endl;
}

void implementacao_filho2(int &a) {
    a = a + 2;
    cout << "executando filho 2: " << getpid() << endl;
}



int main() {
    int filho1, filho2, pid, status;
    char *mem;

    int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char),IPC_CREAT | 0666);

    cout << "Pai comecou (PID: " << getpid() << ")" << endl;

    filho1 = fork();
    if (filho1 == 0) { // se for filho...
        implementacao_filho1(a);
        mem = (char *)shmat(seg_id, NULL, 0);
        sprintf(mem, "escrevendo teste");
        cout << mem << " no processo PID = " << getpid() << endl;
        shmdt(mem);
        exit(0);
    }
    status = wait(NULL);

    if (filho1 > 0) {
        filho2 = fork();
        if (!filho2) { // se for filho...
            implementacao_filho2(a);
            mem = (char *)shmat(seg_id, NULL, 0);
            cout << mem << " no processo PID = " << getpid() << endl;
            shmdt(mem);
            exit(0);
        }

    }
    status = wait(NULL);
    cout << "(PID: " << getpid() << ") Processo sendo finalizado" << endl;
    cout << "Valor final de a = " << a << endl;
    shmctl(seg_id, IPC_RMID, NULL);
    exit(0);
    cout << "Pai terminou" << endl;

    return 0;
}
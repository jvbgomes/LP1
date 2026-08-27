#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

int main() {
    pid_t pid[5] = {-1, -1, -1, -1, -1};
    int status;
    pid[0] = fork();
    
    if (pid[0] < 0) {
        cout << "Erro ao criar o processo #0." << "\n";
       return 1;
    }
    if (pid[0] > 0) { //se for o pai...
        cout << "PAI: criando o segundo processo." << "\n";
        pid[1] = fork();
        if (pid[1] < 0) {
            cout << "Erro ao criar o processo #1." << "\n";
            return 1;
        }
    }

    //os filhos...
    if (pid[0] == 0) {
        cout << "FILHO#0: Criando o processo filho do filho cujo PID é " << getpid() << "\n";
        pid[2] = fork();
    }

    if (pid[1] == 0) {
        cout << "FILHO#1: Criando o processo filho do filho cujo PID é " << getpid() << "\n";
        pid[3] = fork();
    }

    if ((pid[2] == 0) || (pid[3] == 0)) {

        //for(;;);
        //execlp("/bin/ls", "ls", "-l", NULL);
    }
    else {
        status = wait(NULL);
        cout << "Processo-Filho #" << status << " finalizou." << "\n";
    }

    return 0;
}
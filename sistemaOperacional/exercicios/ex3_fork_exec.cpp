#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0 ) {
        cout << "Erro ao criar o processo." << "\n";
        exit(-1);
    } 
    else if (pid == 0) {
        cout << "Esta e a execucao do filho PID: " << getpid() << " cujo pai tem PID: " << getppid() << "\n";
        execlp("/bin/ls", "ls", "-l", NULL);
        cout << "Testando execelp" << "\n";
        exit(0);
    } 
    else {
        wait(NULL);
        cout << "Processo-Filho finalizou." << "\n";
        exit(0);
    }
    return 0;
}

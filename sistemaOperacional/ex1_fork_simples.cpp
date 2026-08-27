#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0 ) {
        cout << "Erro ao criar o processo." << "\n";
        return 1;
    } 
    else if (pid == 0) {
        cout << "Esta e a execucao do filho" << "\n";
        for(;;);
    } 
    else {
        cout << "O pai esta esperando o filho." << "\n";
        for(;;);
        cout << "Processo-Filho finalizou." << "\n";
    }
    return 0;
}

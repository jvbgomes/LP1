#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid, pid1;
    pid = fork();

    if (pid < 0) {
        cout << "Erro ao criar o processo." << "\n";
        return 1;
    } 
    else if (pid == 0) {
        pid1 = getpid();
        cout << "Filho: pid = " << pid << "\n";
        cout << "Filho: pid1 = " << pid1 << "\n";
    } 
    else {
        pid1 = getpid();
        cout << "Pai: pid = " << pid << "\n";
        cout << "Pai: pid1 = " << pid1 << "\n";
        wait(NULL);
    }
    return 0;
}
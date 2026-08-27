#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

    int a=0;

void implementacao_filho1(int &a) {
    a = a + 1;
    cout << "Executando o filho 1 (PID: " << getpid() << " )" << "\n";
}   

void implementacao_filho2(int &a) {
    a = a + 2;
    cout << "Executando o filho 2 (PID: " << getpid() << " )" << "\n";
}  


int main() {

    int filho1, filho2, pid, status;
    cout << "Pai comecou (PID: " << getpid() << " )" << "\n";
    
    filho1 = fork();
    if (!filho1) { //se for o filho...
        implementacao_filho1(a);
        cout << "PID=" << getpid() << "; Valor de a no filho 1 = " << a << "\n";
        exit(0);
    }
    wait(NULL);
    if (filho1 > 0) {
        filho2 = fork();
        if (!filho2) { //se for o filho...
            implementacao_filho2(a);
            cout << "PID=" << getpid() << "; Valor de a no filho 2 = " << a << "\n";   
            exit(0);
        }
    }

    pid = wait(NULL);
    cout << "(PID= " << getpid() << ") O pid do processo finalizado é: " << pid << "." << "\n";
    cout << "Valor final de a = " << a << "\n";

    exit(0);
    cout << "Pai finalizou" << "\n";

    return 0;
}
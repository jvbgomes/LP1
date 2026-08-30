#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int value = 5;

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        value += 15;
        return 0;
    }
    else if (pid > 0) {
        wait(NULL);
        cout << "PAI: value = " << value << "\n";\
        return 0;
    }

}
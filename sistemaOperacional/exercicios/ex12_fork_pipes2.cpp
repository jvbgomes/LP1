#include <iostream>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_SIZE 4
using namespace std;

int main(int argc, char * argv[]) {
    int vetor_pipe_ida[2], vetor_pipe_volta[2];
    pid_t pid;
    char buffer[MAX_SIZE];
    int num, resposta;

    pipe(vetor_pipe_ida); // cria o pipe
    pipe(vetor_pipe_volta); // cria o pipe
    pid = fork();

    if (pid == 0) { // filho
        
        close(vetor_pipe_ida[1]); //fecha caminho de escrita do pipe de ida do filho
        while (read(vetor_pipe_ida[0], buffer, MAX_SIZE) > 0);
        
        sscanf(buffer, "%d", &num);
        close(vetor_pipe_ida[0]); // fecha o caminho de leitura do pipe pois ja leu o que precisava
        cout << "FILHO: O filho leu: " << num << endl;

        num = num + 1;
        sprintf(buffer, "%d", num);

//agora vamos RESPONDER ao pai

        close(vetor_pipe_volta[0]); // fecha a leitura
        write(vetor_pipe_volta[1], buffer, MAX_SIZE); // escreve a resposta no pipe
        close(vetor_pipe_volta[1]); // fecna o caminho de escrita do pipe de volta para o pai

        cout << "FILHO: O filho escreveu: " << num << endl;
        cout << "FILHO: O filho terminou" << endl;

        exit(0);

    } else { // pai
        num = atoi(argv[1]);
        sprintf(buffer, "%d", num);
        close(vetor_pipe_ida[0]);
        write(vetor_pipe_ida[1], buffer, MAX_SIZE);
        close(vetor_pipe_ida[1]);
        cout << "PAI: O pai escreveu: " << buffer << endl;
        
        //agora vamos LER a resposta do filho

        close(vetor_pipe_volta[1]);
        while (read(vetor_pipe_volta[0], buffer, MAX_SIZE) > 0);
        close(vetor_pipe_volta[0]);

        sscanf(buffer, "%d", &num);
        cout << "PAI: O pai leu: " << num << endl;

        wait(NULL);
        cout << "PAI: O filho terminou" << endl;
        cout << "PAI: O pai terminou" << endl;
        exit(0);
    }

    return 0;
}

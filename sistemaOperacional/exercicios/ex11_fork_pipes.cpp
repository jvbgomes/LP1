#include <iostream>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
using namespace std;

int main (int argc, char * argv[]) {
    int vetor_pipe[2], TAM; // 0 para ler e 1 para escrever; apenas uma convencao....
    pid_t pid;
    TAM =  strlen(argv[1]) + 1;
    char buffer[TAM];

    pipe(vetor_pipe); // cria o pipe
    pid = fork(); // cria um novo processo
    if (pid == 0) { // se for filho...
        close(vetor_pipe[1]); // fecha a extremidade de escrita do pipe
        while(read(vetor_pipe[0], buffer, TAM) > 0) {}// leia enquanto 
        close(vetor_pipe[0]); // fecha a extremidade de leitura do pipe
        cout << "Filho: terminou de ler: " << buffer << endl;  
        exit(EXIT_SUCCESS);
    } 
    else { // se for o processo pai...
        close(vetor_pipe[0]); // fecha a extremidade de leitura do pipe pois nao sera utilizada
        sleep(2);
        write(vetor_pipe[1], argv[1], TAM); // envia o conteudo do parametro
        close(vetor_pipe[1]); // fecha a extremidade de escrita do pipe caracterizando o fim (EOF)
        cout << "Pai: terminou e escreveu: " << argv[1] << endl;
        wait(NULL); // espera ate que o filho termine
        cout << "Pai terminou" << endl;
        exit(EXIT_SUCCESS);

    }
    return 0;
}
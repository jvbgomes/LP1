#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

unsigned long long s(unsigned long long n) { // n --> 64 bits com unsigned long long
    unsigned long long passos = 0;
    while (n != 1) {
    if (n % 2 == 0) {
        n = n / 2;
    } else {
        n = (3 * n) + 1;
    }
    passos++;
    }
    return passos;
}


int main(int argc, char* argv[]) { // argc = quantidade de argumentos, argv = vetor de argumentos
    if (argc < 8) {
        cerr << "Uso: " << argv[0] << " <n1> <n2> <n3> <n4> <n5> <n6> <n7>" << endl;
        return 1;
    }

    unsigned long long A = stoull(argv[1]);
    unsigned long long B = stoull(argv[2]);
    unsigned long long LIMIAR = stoull(argv[3]); // stoull converte string para unsigned long long
    int W = atoi(argv[4]); // atoi converte string para int
    string modo = argv[5]; // modo de execucao
    string particao = argv[6];
    string arquivo_saida = argv[7];

    unsigned long long L = B - A;

    // tempo_total comeca a contar daqui(antes mesmo de criar as unidades);
    auto inicio_total = chrono::high_resolution_clock::now();

    // === trabalho da unidade de execucao(sendo so o 1, W = 1) ===
    auto inicio_worker = chrono::high_resolution_clock::now();

    unsigned long long QTD = 0;
    unsigned long long RECORDE_N = A;
    unsigned long long RECORDE_S = s(A);
    if (RECORDE_S > LIMIAR) QTD++;

    for (unsigned long long n = A + 1; n <= B; n++) {
        unsigned long long passos = s(n);
        if (passos > LIMIAR) {
            QTD++;
        }
        if (passos > RECORDE_S) {
            RECORDE_S = passos;
            RECORDE_N = n;
        }
    }

    auto fim_worker = chrono::high_resolution_clock::now();
    // === fim do trabalho da unidade ===

    auto fim_total = chrono::high_resolution_clock::now();

    double tempo_worker = chrono::duration_cast<chrono::duration<double>>(fim_worker - inicio_worker).count(); // tempo de execucao da unidade
    double tempo_total = chrono::duration_cast<chrono::duration<double>>(fim_total - inicio_total).count(); // tempo total de execucao do programa
    double tempo_agregacao = tempo_total - tempo_worker;

    ofstream out(arquivo_saida, ios::app); // abre o arquivo de saida para escrita, adicionando no final do arquivo (ios::app)
    out << scientific << setprecision(2); // define o formato de saida para notacao cientifica com 2 casas decimais
    out << modo << "," << particao << "," << W << "," << L << "," << tempo_total << "," << tempo_worker << "," << tempo_worker << "," << tempo_agregacao << "," << QTD << "," << RECORDE_N << "," << RECORDE_S << endl;
    out.close();

    return 0;
}
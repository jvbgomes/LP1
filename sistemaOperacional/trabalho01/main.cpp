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
using namespace std::chrono;

struct Resultado {
    unsigned long long QTD = 0;
    unsigned long long RECORDE_N;
    unsigned long long RECORDE_S;
};
// uso de um bit-trick para acelerar a contagem de passos
// o ctz é count trailling zeros e o ll é para a versão long long
// 40 em binario = 101000 --> 3 zeros no final --> qtd de vezes necessaria para chegar em impar
unsigned long long s(unsigned long long n) { // n --> 64 bits com unsigned long long
    unsigned long long passos = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            // conta o número de zeros à direita
            int zeros = __builtin_ctzll(n); //ganho de performance, devido ao shift right, que é mais rápido que a divisão
            n >>= zeros; // n = n / (2^zeros)
            passos += zeros;
        } else {
            n = (3 * n) + 1;
            passos++;
        }
    }
    return passos;
}

Resultado processar_intervalo(unsigned long long inicio, unsigned long long fim, unsigned long long LIMIAR) {
    Resultado r;
    r.RECORDE_N = inicio;
    r.RECORDE_S = s(inicio);
    if (r.RECORDE_S > LIMIAR) r.QTD++;

    for (unsigned long long n = inicio + 1; n <= fim; n++) {
        unsigned long long passos = s(n);
        if (passos > LIMIAR) {
            r.QTD++;    
        }
        if (passos > r.RECORDE_S) {
            r.RECORDE_S = passos;
            r.RECORDE_N = n;
        }
    }
    return r;
}


void gravar_csv(const string& arquivo_saida, const string& modo, const string& particao, int W, unsigned long long L, double tempo_total, double tempo_unidade, double tempo_agregacao, const Resultado& r) {
ofstream out(arquivo_saida, ios::app);

out << scientific << setprecision(2); //notacao cientifica com 2 casas decimais
out << modo << "," << particao << "," << W << "," << L << "," << tempo_total << "," << tempo_unidade << "," << tempo_unidade << "," << tempo_agregacao << "," << r.QTD << "," << r.RECORDE_N << "," << r.RECORDE_S << endl;
out.close();
}


int main(int argc, char* argv[]) { // argc = quantidade de argumentos, argv = vetor de argumentos
    if (argc < 8) {
        cerr << "Uso: ./varredor <A> <B> <LIMIAR> <W> <modo> <particao> <arquivo_saida>" << endl;
        return 1;
    }

    unsigned long long A = stoull(argv[1]);
    unsigned long long B = stoull(argv[2]);
    unsigned long long LIMIAR = stoull(argv[3]); // stoull string para unsigned long..
    int W = atoi(argv[4]); // atoi converte string para int
    string modo = argv[5];
    string particao = argv[6];
    string arquivo_saida = argv[7];

    if (B < A) {
        cerr << "Erro: B deve ser maior ou igual a A." << endl;
        return 1;
    }
    unsigned long long L = B - A;

    // tempo_total comeca a contar daqui(antes mesmo de criar as unidades);
    auto inicio_total = high_resolution_clock::now();

    // trabalho da unidade de execucao(sendo so o 1, W = 1)
    auto inicio_unidade = high_resolution_clock::now();

    Resultado r = processar_intervalo(A, B, LIMIAR);

    auto fim_unidade = high_resolution_clock::now();
    // fim do trabalho da unidade

    auto fim_total = high_resolution_clock::now();

    double tempo_unidade = duration<double>(fim_unidade - inicio_unidade).count(); // tempo de execucao da unidade

    double tempo_total = duration<double>(fim_total - inicio_total).count(); // tempo total de execucao do programa
    
    double tempo_agregacao = tempo_total - tempo_unidade;

    gravar_csv(arquivo_saida, modo, particao, W, L, tempo_total, tempo_unidade, tempo_agregacao, r);

    return 0;
}
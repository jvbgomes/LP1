#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include <thread>
#include <algorithm>
using namespace std;
using namespace std::chrono;

struct Resultado {
    unsigned long long QTD = 0;
    unsigned long long RECORDE_N;
    unsigned long long RECORDE_S;
};

unsigned long long s(unsigned long long n) {
    unsigned long long passos = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            int zeros = __builtin_ctzll(n);
            n >>= zeros;
            passos += zeros;
        } else {
            n = (3 * n) + 1;
            passos++;
        }
    }
    return passos;
}

Resultado processar_intervalo(unsigned long long inicio, unsigned long long fim,
                               unsigned long long passo, unsigned long long LIMIAR) {
    Resultado r;
    r.RECORDE_N = inicio;
    r.RECORDE_S = s(inicio);
    if (r.RECORDE_S > LIMIAR) r.QTD++;

    for (unsigned long long n = inicio + passo; n <= fim; n += passo) {
        unsigned long long passos = s(n);
        if (passos > LIMIAR) r.QTD++;
        if (passos > r.RECORDE_S) {
            r.RECORDE_S = passos;
            r.RECORDE_N = n;
        }
    }
    return r;
}

void calcular_faixa_bloco(unsigned long long A, unsigned long long N, int W, int i,
                           unsigned long long &inicio_i, unsigned long long &fim_i) {
    unsigned long long base = N / W;
    unsigned long long resto = N % W;
    unsigned long long idx = (unsigned long long) i;

    unsigned long long quantidade = base + (idx < resto ? 1 : 0);
    unsigned long long deslocamento = idx * base + min(idx, resto);

    inicio_i = A + deslocamento;
    fim_i = inicio_i + quantidade - 1;
}

void calcular_faixa_ciclico(unsigned long long A, unsigned long long B, int W, int i,
                             unsigned long long &inicio_i, unsigned long long &fim_i) {
    inicio_i = A + (unsigned long long) i;
    unsigned long long distancia = B - inicio_i;
    fim_i = inicio_i + (distancia / W) * W;
}

void calcular_faixa(const string &particao, unsigned long long A, unsigned long long B, unsigned long long N,
                     int W, int i, unsigned long long &inicio_i, unsigned long long &fim_i, unsigned long long &passo) {
    if (particao == "bloco") {
        passo = 1;
        calcular_faixa_bloco(A, N, W, i, inicio_i, fim_i);
    } else {
        passo = (unsigned long long) W;
        calcular_faixa_ciclico(A, B, W, i, inicio_i, fim_i);
    }
}

void executar_unidade_thread(int i, unsigned long long inicio_i, unsigned long long fim_i, unsigned long long passo,
                              unsigned long long LIMIAR, vector<Resultado> &resultados, vector<double> &tempos) {
    auto inicio_cronometro = high_resolution_clock::now();
    resultados[i] = processar_intervalo(inicio_i, fim_i, passo, LIMIAR);
    auto fim_cronometro = high_resolution_clock::now();
    tempos[i] = duration<double>(fim_cronometro - inicio_cronometro).count();
}

void escrever_parcial(int i, const Resultado &r, double tempo) {
    ofstream out("parcial_" + to_string(i) + ".txt");
    out << r.QTD << " " << r.RECORDE_N << " " << r.RECORDE_S << " " << tempo << endl;
    out.close();
}

Resultado ler_parcial(int i, double &tempo) {
    ifstream in("parcial_" + to_string(i) + ".txt");
    Resultado r;
    in >> r.QTD >> r.RECORDE_N >> r.RECORDE_S >> tempo;
    in.close();
    return r;
}

Resultado agregar_resultados(const vector<Resultado> &resultados) {
    Resultado final;
    final.RECORDE_N = resultados[0].RECORDE_N;
    final.RECORDE_S = resultados[0].RECORDE_S;

    for (const Resultado &parcial : resultados) {
        final.QTD += parcial.QTD;
        if (parcial.RECORDE_S > final.RECORDE_S ||
            (parcial.RECORDE_S == final.RECORDE_S && parcial.RECORDE_N < final.RECORDE_N)) {
            final.RECORDE_S = parcial.RECORDE_S;
            final.RECORDE_N = parcial.RECORDE_N;
        }
    }
    return final;
}

void gravar_csv(const string &arquivo_saida, const string &modo, const string &particao, int W,
                 unsigned long long L, double tempo_total, double tempo_max_unidade, double tempo_min_unidade,
                 double tempo_agregacao, const Resultado &r) {
    ofstream out(arquivo_saida, ios::app);
    out << scientific << setprecision(2);
    out << modo << "," << particao << "," << W << "," << L << "," << tempo_total << ","
        << tempo_max_unidade << "," << tempo_min_unidade << "," << tempo_agregacao << ","
        << r.QTD << "," << r.RECORDE_N << "," << r.RECORDE_S << endl;
    out.close();
}

int main(int argc, char *argv[]) {
    if (argc < 8) {
        cerr << "Uso: ./varredor <A> <B> <LIMIAR> <W> <modo> <particao> <arquivo_saida>" << endl;
        return 1;
    }

    unsigned long long A = stoull(argv[1]);
    unsigned long long B = stoull(argv[2]);
    unsigned long long LIMIAR = stoull(argv[3]);
    int W = atoi(argv[4]);
    string modo = argv[5];
    string particao = argv[6];
    string arquivo_saida = argv[7];

    if (B < A) {
        cerr << "Erro: B deve ser maior ou igual a A." << endl;
        return 1;
    }
    if (modo != "thread" && modo != "processo") {
        cerr << "Modo invalido, use 'thread' ou 'processo'." << endl;
        return 1;
    }
    if (particao != "bloco" && particao != "ciclico") {
        cerr << "Particao invalida, use 'bloco' ou 'ciclico'." << endl;
        return 1;
    }

    unsigned long long L = B - A;
    unsigned long long N = L + 1;

    vector<Resultado> resultados(W);
    vector<double> tempos(W);

    auto inicio_total = high_resolution_clock::now();

    if (modo == "thread") {
        vector<thread> threads;
        for (int i = 0; i < W; i++) {
            unsigned long long inicio_i, fim_i, passo;
            calcular_faixa(particao, A, B, N, W, i, inicio_i, fim_i, passo);
            threads.push_back(thread(executar_unidade_thread, i, inicio_i, fim_i, passo, LIMIAR,
                                      ref(resultados), ref(tempos)));
        }
        for (int i = 0; i < W; i++) threads[i].join();
    } else {
        vector<pid_t> pids(W);
        for (int i = 0; i < W; i++) {
            unsigned long long inicio_i, fim_i, passo;
            calcular_faixa(particao, A, B, N, W, i, inicio_i, fim_i, passo);

            pid_t pid = fork();
            if (pid < 0) {
                cerr << "Erro ao criar processo filho " << i << endl;
                return 1;
            }
            if (pid == 0) {
                auto inicio_cronometro = high_resolution_clock::now();
                Resultado r = processar_intervalo(inicio_i, fim_i, passo, LIMIAR);
                auto fim_cronometro = high_resolution_clock::now();
                double tempo_i = duration<double>(fim_cronometro - inicio_cronometro).count();
                escrever_parcial(i, r, tempo_i);
                _exit(0);
            }
            pids[i] = pid;
        }
        for (int i = 0; i < W; i++) waitpid(pids[i], nullptr, 0);
        for (int i = 0; i < W; i++) resultados[i] = ler_parcial(i, tempos[i]);
    }

    auto fim_paralelo = high_resolution_clock::now();

    Resultado r = agregar_resultados(resultados);

    auto fim_total = high_resolution_clock::now();

    double tempo_total = duration<double>(fim_total - inicio_total).count();
    double tempo_agregacao = duration<double>(fim_total - fim_paralelo).count();
    double tempo_max_unidade = *max_element(tempos.begin(), tempos.end());
    double tempo_min_unidade = *min_element(tempos.begin(), tempos.end());

    gravar_csv(arquivo_saida, modo, particao, W, L, tempo_total, tempo_max_unidade, tempo_min_unidade,
               tempo_agregacao, r);

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include "astronautas.h"
#include "voo.h"
#include "agencia.h"
using namespace std;


int main() {
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    string comando;
    while (cin >> comando) {
        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            cin.ignore();
            getline(cin, nome);
            cadastrarAstronauta(astronautas, cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            cadastrarVoo(voos, codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            int codigo;
            string cpf;
            cin >> cpf >> codigo;
            adicionarAstronautaAoVoo(astronautas, voos, cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            int codigo;
            string cpf;
            cin >> cpf >> codigo;
            removerAstronautaDoVoo(astronautas, voos, cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            iniciarVoo(astronautas, voos, codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            finalizarVoo(astronautas, voos, codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            explodirVoo(astronautas, voos, codigo);
        } else if (comando == "LISTAR_VOOS") {
            listarVoos(astronautas, voos);
        } else if (comando == "LISTAR_MORTOS") {
            listarMortos(astronautas);
        } else if (comando == "FIM") {
            break;
        }
    }

    return 0;
}

// g++ main.cpp astronautas.cpp voo.cpp agencia.cpp -o agencia
// ./agencia < eventos.txt
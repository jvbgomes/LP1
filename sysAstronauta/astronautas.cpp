#include "astronautas.h"
#include <iostream>
using namespace std;

Astronauta::Astronauta(string cpf, string nome, int idade) {
    this->cpf = cpf;
    this->nome = nome;
    this->idade = idade;
    this->vivo = true;
    this->disponivel = true;
}

int buscarAstronauta(const vector<Astronauta> &astronautas, string cpf) {
    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].cpf == cpf) {
            return i;
        }
    }
    return -1;
}

#include "voo.h"
using namespace std;

Voo::Voo(int codigo) {
    this->codigo = codigo;
    this->estado = PLANEJADO;
}

int buscarVoo(const vector<Voo> &voos, int codigo) {
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

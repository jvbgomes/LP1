#ifndef VOO_H
#define VOO_H
#include <string>
#include <vector>

enum EstadoVoo {
    PLANEJADO,
    EM_CURSO,
    SUCESSO,
    EXPLODIDO
};

class Voo {
public:
    int codigo;
    std::vector<std::string> cpfsAstronautas;
    EstadoVoo estado;

    Voo(int codigo);
};

int buscarVoo(const std::vector<Voo> &voos, int codigo);

#endif

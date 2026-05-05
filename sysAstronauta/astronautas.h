#ifndef ASTRONAUTAS_H
#define ASTRONAUTAS_H
#include <vector>
#include <string>

class Astronauta {
public:
    std::string cpf;
    std::string nome;
    int idade;
    bool vivo;
    bool disponivel;

    std::vector<int> voosParticipados;

    Astronauta(std::string cpf, std::string nome, int idade);
};

int buscarAstronauta(const std::vector<Astronauta> &astronautas, std::string cpf);

#endif

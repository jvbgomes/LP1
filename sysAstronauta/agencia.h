#ifndef AGENCIA_H
#define AGENCIA_H

#include "voo.h"
#include "astronautas.h"
#include <vector>
#include <string>

void cadastrarAstronauta(std::vector<Astronauta> &astronautas, std::string cpf, std::string nome, int idade);
void cadastrarVoo(std::vector<Voo> &voos, int codigo);
void adicionarAstronautaAoVoo(std::vector<Astronauta> &astronautas, std::vector<Voo> &voos, std::string cpf, int codigo);
void removerAstronautaDoVoo(std::vector<Astronauta> &astronautas, std::vector<Voo> &voos, std::string cpf, int codigo);
void iniciarVoo(std::vector<Astronauta> &astronautas, std::vector<Voo> &voos, int codigo);
void finalizarVoo(std::vector<Astronauta> &astronautas, std::vector<Voo> &voos, int codigo);
void explodirVoo(std::vector<Astronauta> &astronautas, std::vector<Voo> &voos, int codigo);
void listarVoos(std::vector<Astronauta> &astronautas, std::vector<Voo> &voos);
void listarMortos(std::vector<Astronauta> &astronautas);

#endif

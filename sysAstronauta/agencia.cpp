#include "astronautas.h"
#include "voo.h"
#include "agencia.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void cadastrarAstronauta(vector<Astronauta> &astronautas, string cpf, string nome, int idade) {
    if (buscarAstronauta(astronautas, cpf) == -1) {
        astronautas.push_back(Astronauta(cpf, nome, idade));
        cout << "Astronauta " << cpf << " cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro: Astronauta " << cpf << " já cadastrado!" << endl;
    }
}

void cadastrarVoo(vector<Voo> &voos, int codigo) {
    if (buscarVoo(voos, codigo) == -1) {
        voos.push_back(Voo(codigo));
        cout << "Voo " << codigo << " cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro: Voo " << codigo << " já cadastrado!" << endl;
    }
}

void adicionarAstronautaAoVoo(vector<Astronauta> &astronautas, vector<Voo> &voos, string cpf, int codigo) {
    int vooIndice = buscarVoo(voos, codigo);
    int astroIndice = buscarAstronauta(astronautas, cpf);
    if (vooIndice == -1) {
        cout << "Erro: Voo " << codigo << " não encontrado!" << endl;
    } else if (astroIndice == -1) {
        cout << "Erro: Astronauta " << cpf << " não encontrado!" << endl;
    } else if (!astronautas[astroIndice].vivo) {
        cout << "Erro: Astronauta " << cpf << " não está vivo!" << endl;
    } else if (!astronautas[astroIndice].disponivel) {
        cout << "Erro: Astronauta " << cpf << " não disponível!" << endl;
    } else if (voos[vooIndice].estado != PLANEJADO) {
        cout << "Erro: Voo " << codigo << " não está planejado!" << endl;
    } else {
        voos[vooIndice].cpfsAstronautas.push_back(cpf);
        astronautas[astroIndice].disponivel = false;
        cout << "Astronauta " << cpf << " adicionado ao voo " << codigo << " com sucesso!" << endl;
    }
}

void removerAstronautaDoVoo(vector<Astronauta> &astronautas, vector<Voo> &voos, string cpf, int codigo) {
    int vooIndice = buscarVoo(voos, codigo);
    int astroIndice = buscarAstronauta(astronautas, cpf);
    if (vooIndice == -1) {
        cout << "Erro: Voo " << codigo << " não encontrado!" << endl;
    } else if (astroIndice == -1) {
        cout << "Erro: Astronauta " << cpf << " não encontrado!" << endl;
    } else if (voos[vooIndice].estado != PLANEJADO) {
        cout << "Erro: Voo " << codigo << " não está planejado!" << endl;
    } else {
        auto &cpfs = voos[vooIndice].cpfsAstronautas;
        auto it = find(cpfs.begin(), cpfs.end(), cpf);
        if (it != cpfs.end()) {
            cpfs.erase(it);
            astronautas[astroIndice].disponivel = true;
            cout << "Astronauta " << cpf << " removido do voo " << codigo << " com sucesso!" << endl;
        } else {
            cout << "Erro: Astronauta " << cpf << " não está no voo " << codigo << "!" << endl;
        }
    }
}

void iniciarVoo(vector<Astronauta> &astronautas, vector<Voo> &voos, int codigo) {
    int vooIndice = buscarVoo(voos, codigo);
    if (vooIndice == -1) {
        cout << "Erro: Voo " << codigo << " não encontrado!" << endl;
    } else if (voos[vooIndice].estado != PLANEJADO) {
        cout << "Erro: Voo " << codigo << " não está planejado!" << endl;
    } else if (voos[vooIndice].cpfsAstronautas.empty()) {
        cout << "Erro: Voo " << codigo << " não tem astronautas!" << endl;
    } else {
        voos[vooIndice].estado = EM_CURSO;
        for (int i = 0; i < voos[vooIndice].cpfsAstronautas.size(); i++) {
            int astroIndice = buscarAstronauta(astronautas, voos[vooIndice].cpfsAstronautas[i]);
            if (astroIndice != -1) {
                astronautas[astroIndice].voosParticipados.push_back(codigo);
            }
        }
        cout << "Voo " << codigo << " iniciado com sucesso!" << endl;
    }
}

void finalizarVoo(vector<Astronauta> &astronautas, vector<Voo> &voos, int codigo) {
    int vooIndice = buscarVoo(voos, codigo);
    if (vooIndice == -1) {
        cout << "Erro: Voo " << codigo << " não encontrado!" << endl;
    } else if (voos[vooIndice].estado != EM_CURSO) {
        cout << "Erro: Voo " << codigo << " não está em curso!" << endl;
    } else {
        voos[vooIndice].estado = SUCESSO;
        for (const string &cpf : voos[vooIndice].cpfsAstronautas) {
            int astroIndice = buscarAstronauta(astronautas, cpf);
            if (astroIndice != -1) {
                astronautas[astroIndice].disponivel = true;
            }
        }
        cout << "Voo " << codigo << " finalizado com sucesso!" << endl;
    }
}

void explodirVoo(vector<Astronauta> &astronautas, vector<Voo> &voos, int codigo) {
    int vooIndice = buscarVoo(voos, codigo);
    if (vooIndice == -1) {
        cout << "Erro: Voo " << codigo << " não encontrado!" << endl;
    } else if (voos[vooIndice].estado != EM_CURSO) {
        cout << "Erro: Voo " << codigo << " não está em curso!" << endl;
    } else {
        voos[vooIndice].estado = EXPLODIDO;
        for (const string &cpf : voos[vooIndice].cpfsAstronautas) {
            int astroIndice = buscarAstronauta(astronautas, cpf);
            if (astroIndice != -1) {
                astronautas[astroIndice].disponivel = false;
                astronautas[astroIndice].vivo = false;
            }
        }
        cout << "Voo " << codigo << " explodiu com sucesso!" << endl;
    }
}

void listarVoos(vector<Astronauta> &astronautas, vector<Voo> &voos) {
    EstadoVoo estados[] = {PLANEJADO, EM_CURSO, SUCESSO, EXPLODIDO};
    string nomesEstados[] = {"Planejado", "Em Curso", "Sucesso", "Explodido"};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < voos.size(); j++) {
            if (voos[j].estado == estados[i]) {
                cout << "Voo " << voos[j].codigo << " - " << nomesEstados[i] << endl;
                for (int k = 0; k < voos[j].cpfsAstronautas.size(); k++) {
                    int astroIndice = buscarAstronauta(astronautas, voos[j].cpfsAstronautas[k]);
                    if (astroIndice != -1) {
                        cout << " " << voos[j].cpfsAstronautas[k] << " - " << astronautas[astroIndice].nome << endl;
                    }
                }
            }
        }
    }
}

void listarMortos(vector<Astronauta> &astronautas) {
    for (int i = 0; i < astronautas.size(); i++) {
        if (!astronautas[i].vivo) {
            cout << "Astronauta " << astronautas[i].cpf << " - " << astronautas[i].nome << " está morto." << endl;
            for (int j = 0; j < astronautas[i].voosParticipados.size(); j++) {
                cout << "  Participou do voo " << astronautas[i].voosParticipados[j] << endl;
            }
        }
    }
}
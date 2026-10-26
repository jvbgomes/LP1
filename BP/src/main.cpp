/**
 * @file main.cpp
 * @brief Programa de demonstração do AgendaFácil: reproduz o roteiro do código-base original
 * e imprime, para cada ação, o resultado ou o motivo da falha.
 */
#include "agenda.hpp"

#include <iostream>

namespace {

using agendafacil::Agenda;
using agendafacil::Atendimento;
using agendafacil::ConflitoDeHorarioException;
using agendafacil::ErroAgenda;

/// Imprime uma lista de atendimentos no formato "hora paciente profissional status", um por linha.
void imprimir_atendimentos(std::vector<Atendimento> const& atendimentos) {
    for (Atendimento const& atendimento : atendimentos) {
        std::cout << atendimento.hora << " " << atendimento.paciente << " " << atendimento.profissional
                   << " " << agendafacil::texto_status(atendimento.status) << std::endl;
    }
}

/// Tenta marcar um atendimento e relata o resultado; conflito de horário vira "Horario ocupado"
/// (mesmo texto do sistema original) e qualquer outra violação de regra mostra o motivo.
void demonstrar_marcacao(Agenda& agenda, std::string const& paciente, std::string const& profissional,
                          std::string const& data, int hora, int duracao_minutos) {
    try {
        agenda.marcar(paciente, profissional, data, hora, duracao_minutos);
        std::cout << "Atendimento marcado para " << paciente << std::endl;
    } catch (ConflitoDeHorarioException const&) {
        std::cout << "Horario ocupado" << std::endl;
    } catch (ErroAgenda const& erro) {
        std::cout << "Falha ao marcar atendimento de " << paciente << ": " << erro.what() << std::endl;
    }
}

/// Tenta remarcar um atendimento e relata o resultado, nos mesmos moldes de demonstrar_marcacao.
void demonstrar_remarcacao(Agenda& agenda, std::string const& paciente, std::string const& data_atual,
                            int hora_atual, std::string const& nova_data, int nova_hora) {
    try {
        agenda.remarcar(paciente, data_atual, hora_atual, nova_data, nova_hora);
        std::cout << "Remarcado" << std::endl;
    } catch (ConflitoDeHorarioException const&) {
        std::cout << "Horario ocupado" << std::endl;
    } catch (ErroAgenda const& erro) {
        std::cout << "Falha ao remarcar atendimento de " << paciente << ": " << erro.what() << std::endl;
    }
}

}  // namespace

/**
 * @brief Reproduz o cenário do código-base original: dois agendamentos concorrentes (um deles em
 * conflito), um terceiro agendamento livre, uma remarcação e a listagem final do dia. É o roteiro
 * usado para comprovar que o caminho feliz não mudou de comportamento após a refatoração.
 */
int main() {
    Agenda agenda;

    demonstrar_marcacao(agenda, "Ana", "Dr. Silva", "2026-10-05", 9, 30);
    demonstrar_marcacao(agenda, "Bruno", "Dr. Silva", "2026-10-05", 9, 30);
    demonstrar_marcacao(agenda, "Carla", "Dra. Souza", "2026-10-05", 14, 60);
    demonstrar_remarcacao(agenda, "Ana", "2026-10-05", 9, "2026-10-06", 10);

    try {
        imprimir_atendimentos(agenda.consultar_por_data("2026-10-05"));
    } catch (ErroAgenda const& erro) {
        std::cout << "Falha ao listar atendimentos: " << erro.what() << std::endl;
    }

    return 0;
}

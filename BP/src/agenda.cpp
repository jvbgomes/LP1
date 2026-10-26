/**
 * @file agenda.cpp
 * @brief Implementação das validações e das regras de negócio declaradas em agenda.hpp.
 */
#include "agenda.hpp"

#include <algorithm>
#include <cctype>

namespace agendafacil {

namespace {

/// Quantidade de dias de cada mês num ano não bissexto (índice 1 = janeiro).
constexpr int DIAS_POR_MES[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool eh_ano_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int dias_no_mes(int mes, int ano) {
    if (mes == 2 && eh_ano_bissexto(ano)) {
        return 29;
    }
    return DIAS_POR_MES[mes];
}

}  // namespace

std::string texto_status(StatusAtendimento status) {
    switch (status) {
        case StatusAtendimento::Marcado:
            return "MARCADO";
        case StatusAtendimento::Remarcado:
            return "REMARCADO";
    }
    // Decisão: nunca deveria chegar aqui com um StatusAtendimento válido; tratamos como erro
    // interno em vez de deixar a função cair no fim sem retorno (comportamento indefinido).
    throw std::logic_error("StatusAtendimento desconhecido");
}

void validar_campo_obrigatorio(std::string const& valor, std::string const& nome_campo) {
    if (valor.empty()) {
        throw CampoObrigatorioAusenteException("O campo '" + nome_campo + "' não pode ser vazio.");
    }
}

void validar_data(std::string const& data) {
    bool const formato_ok = data.size() == 10 && data[4] == '-' && data[7] == '-' &&
                             std::all_of(data.begin(), data.begin() + 4, ::isdigit) &&
                             std::all_of(data.begin() + 5, data.begin() + 7, ::isdigit) &&
                             std::all_of(data.begin() + 8, data.begin() + 10, ::isdigit);
    if (!formato_ok) {
        throw DataInvalidaException("Data '" + data + "' fora do formato esperado AAAA-MM-DD.");
    }

    int const ano = std::stoi(data.substr(0, 4));
    int const mes = std::stoi(data.substr(5, 2));
    int const dia = std::stoi(data.substr(8, 2));

    if (mes < 1 || mes > 12) {
        throw DataInvalidaException("Data '" + data + "' tem mês inválido: " + std::to_string(mes) + ".");
    }
    if (dia < 1 || dia > dias_no_mes(mes, ano)) {
        throw DataInvalidaException("Data '" + data + "' tem dia inválido: " + std::to_string(dia) + ".");
    }
}

void validar_duracao(int duracao_minutos) {
    if (duracao_minutos < DURACAO_MINIMA_MINUTOS || duracao_minutos > DURACAO_MAXIMA_MINUTOS) {
        throw DuracaoInvalidaException("Duração " + std::to_string(duracao_minutos) +
                                        " min fora da faixa permitida [" +
                                        std::to_string(DURACAO_MINIMA_MINUTOS) + ", " +
                                        std::to_string(DURACAO_MAXIMA_MINUTOS) + "] minutos.");
    }
    if (duracao_minutos % DURACAO_PASSO_MINUTOS != 0) {
        throw DuracaoInvalidaException("Duração " + std::to_string(duracao_minutos) +
                                        " min não é múltipla de " +
                                        std::to_string(DURACAO_PASSO_MINUTOS) + " minutos.");
    }
}

void validar_horario_no_expediente(int hora, int duracao_minutos) {
    if (hora < HORA_INICIO_EXPEDIENTE || hora > HORA_FIM_EXPEDIENTE) {
        throw HorarioForaDoExpedienteException(
            "Horário de início " + std::to_string(hora) + "h fora do expediente (permitido " +
            std::to_string(HORA_INICIO_EXPEDIENTE) + "h-" + std::to_string(HORA_FIM_EXPEDIENTE) + "h).");
    }
    int const minuto_termino = hora * 60 + duracao_minutos;
    if (minuto_termino > MINUTO_ENCERRAMENTO_EXPEDIENTE) {
        throw HorarioForaDoExpedienteException(
            "Atendimento das " + std::to_string(hora) + "h com duração de " +
            std::to_string(duracao_minutos) + " min terminaria depois do fim do expediente (" +
            std::to_string(MINUTO_ENCERRAMENTO_EXPEDIENTE / 60) + "h).");
    }
}

bool Agenda::existe_conflito(std::string const& profissional, std::string const& data, int hora,
                              std::optional<std::size_t> indice_ignorado) const {
    for (std::size_t i = 0; i < atendimentos_.size(); ++i) {
        if (indice_ignorado.has_value() && i == indice_ignorado.value()) {
            continue;
        }
        Atendimento const& atendimento = atendimentos_[i];
        if (atendimento.profissional == profissional && atendimento.data == data && atendimento.hora == hora) {
            return true;
        }
    }
    return false;
}

Atendimento Agenda::marcar(std::string const& paciente, std::string const& profissional,
                            std::string const& data, int hora, int duracao_minutos) {
    validar_campo_obrigatorio(paciente, "paciente");
    validar_campo_obrigatorio(profissional, "profissional");
    validar_data(data);
    validar_duracao(duracao_minutos);
    validar_horario_no_expediente(hora, duracao_minutos);

    if (existe_conflito(profissional, data, hora, std::nullopt)) {
        throw ConflitoDeHorarioException("Profissional '" + profissional + "' já tem atendimento em " +
                                          data + " às " + std::to_string(hora) + "h.");
    }

    atendimentos_.push_back({paciente, profissional, data, hora, duracao_minutos, StatusAtendimento::Marcado});
    return atendimentos_.back();
}

Atendimento Agenda::remarcar(std::string const& paciente, std::string const& data_atual, int hora_atual,
                              std::string const& nova_data, int nova_hora) {
    validar_campo_obrigatorio(paciente, "paciente");

    std::optional<std::size_t> indice;
    for (std::size_t i = 0; i < atendimentos_.size(); ++i) {
        if (atendimentos_[i].paciente == paciente && atendimentos_[i].data == data_atual &&
            atendimentos_[i].hora == hora_atual) {
            indice = i;
            break;
        }
    }
    if (!indice.has_value()) {
        throw AtendimentoNaoEncontradoException("Nenhum atendimento de '" + paciente + "' encontrado em " +
                                                 data_atual + " às " + std::to_string(hora_atual) + "h.");
    }

    validar_data(nova_data);
    validar_horario_no_expediente(nova_hora, atendimentos_[indice.value()].duracao_minutos);

    std::string const& profissional = atendimentos_[indice.value()].profissional;
    if (existe_conflito(profissional, nova_data, nova_hora, indice)) {
        throw ConflitoDeHorarioException("Profissional '" + profissional + "' já tem atendimento em " +
                                          nova_data + " às " + std::to_string(nova_hora) + "h.");
    }

    atendimentos_[indice.value()].data = nova_data;
    atendimentos_[indice.value()].hora = nova_hora;
    atendimentos_[indice.value()].status = StatusAtendimento::Remarcado;
    return atendimentos_[indice.value()];
}

std::vector<Atendimento> Agenda::consultar_por_data(std::string const& data) const {
    validar_data(data);
    std::vector<Atendimento> resultado;
    for (Atendimento const& atendimento : atendimentos_) {
        if (atendimento.data == data) {
            resultado.push_back(atendimento);
        }
    }
    return resultado;
}

}  // namespace agendafacil

/**
 * @file agenda.hpp
 * @brief Modelo de dados, exceções e regras de negócio da agenda de atendimentos do AgendaFácil.
 */
#ifndef AGENDAFACIL_AGENDA_HPP
#define AGENDAFACIL_AGENDA_HPP

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace agendafacil {

/// Duração mínima permitida para um atendimento, em minutos.
constexpr int DURACAO_MINIMA_MINUTOS = 15;

/// Duração máxima permitida para um atendimento, em minutos.
constexpr int DURACAO_MAXIMA_MINUTOS = 120;

/// Passo ao qual a duração do atendimento deve ser múltipla, em minutos.
constexpr int DURACAO_PASSO_MINUTOS = 15;

/// Primeira hora em que um atendimento pode começar (inclusive).
constexpr int HORA_INICIO_EXPEDIENTE = 8;

/// Última hora em que um atendimento pode começar (inclusive).
constexpr int HORA_FIM_EXPEDIENTE = 17;

/// Horário em que o expediente se encerra, em minutos desde 0h: nenhum atendimento pode terminar depois disso.
constexpr int MINUTO_ENCERRAMENTO_EXPEDIENTE = 18 * 60;

/// Situação atual de um atendimento agendado.
enum class StatusAtendimento {
    Marcado,
    Remarcado,
};

/**
 * @brief Converte o status para o texto usado nos relatórios (ex.: "MARCADO").
 * @param status status a converter.
 * @return "MARCADO" ou "REMARCADO".
 */
std::string texto_status(StatusAtendimento status);

/// Um atendimento agendado na clínica, com todos os seus dados em campos nomeados.
struct Atendimento {
    std::string paciente;
    std::string profissional;
    std::string data;  ///< Sempre no formato AAAA-MM-DD.
    int hora;           ///< Hora de início do atendimento (8 a 17).
    int duracao_minutos;
    StatusAtendimento status;
};

/// Erro base para toda violação de regra de negócio da agenda. Permite tratar qualquer
/// falha de validação do módulo com um único catch, sem esconder qual regra foi violada.
class ErroAgenda : public std::runtime_error {
public:
    explicit ErroAgenda(std::string const& mensagem) : std::runtime_error(mensagem) {}
};

/// Lançada quando a data informada não está no formato AAAA-MM-DD ou não é uma data de calendário válida.
class DataInvalidaException : public ErroAgenda {
public:
    using ErroAgenda::ErroAgenda;
};

/// Lançada quando o horário de início ou de término do atendimento cai fora do expediente (8h-18h).
class HorarioForaDoExpedienteException : public ErroAgenda {
public:
    using ErroAgenda::ErroAgenda;
};

/// Lançada quando a duração não está entre 15 e 120 minutos ou não é múltipla de 15.
class DuracaoInvalidaException : public ErroAgenda {
public:
    using ErroAgenda::ErroAgenda;
};

/// Lançada quando um campo de texto obrigatório (paciente ou profissional) está vazio.
class CampoObrigatorioAusenteException : public ErroAgenda {
public:
    using ErroAgenda::ErroAgenda;
};

/// Lançada quando o profissional já tem outro atendimento marcado no mesmo dia e horário.
class ConflitoDeHorarioException : public ErroAgenda {
public:
    using ErroAgenda::ErroAgenda;
};

/// Lançada quando uma remarcação não encontra nenhum atendimento correspondente para remarcar.
class AtendimentoNaoEncontradoException : public ErroAgenda {
public:
    using ErroAgenda::ErroAgenda;
};

/**
 * @brief Valida que um campo de texto obrigatório não está vazio.
 * @param valor valor recebido do chamador.
 * @param nome_campo nome do campo, usado apenas para compor a mensagem de erro.
 * @throws CampoObrigatorioAusenteException se `valor` estiver vazio.
 */
void validar_campo_obrigatorio(std::string const& valor, std::string const& nome_campo);

/**
 * @brief Valida que `data` está no formato AAAA-MM-DD e representa uma data de calendário existente.
 * @param data texto a validar.
 * @throws DataInvalidaException se o formato estiver errado ou a data não existir no calendário.
 */
void validar_data(std::string const& data);

/**
 * @brief Valida que a duração está entre DURACAO_MINIMA_MINUTOS e DURACAO_MAXIMA_MINUTOS e é
 * múltipla de DURACAO_PASSO_MINUTOS.
 * @param duracao_minutos duração a validar, em minutos.
 * @throws DuracaoInvalidaException se a duração estiver fora da faixa ou não for múltipla do passo.
 */
void validar_duracao(int duracao_minutos);

/**
 * @brief Valida que um atendimento iniciado em `hora` e com a duração dada cabe inteiramente
 * dentro do expediente (começa entre 8h e 17h e termina até as 18h).
 * @param hora hora de início do atendimento.
 * @param duracao_minutos duração do atendimento, em minutos.
 * @throws HorarioForaDoExpedienteException se o início ou o término ficarem fora do expediente.
 */
void validar_horario_no_expediente(int hora, int duracao_minutos);

/**
 * @brief Agenda de atendimentos de uma clínica: mantém os atendimentos em memória e garante,
 * num único lugar, todas as regras de negócio do AgendaFácil.
 *
 * Nenhum método desta classe imprime nada: cada chamada agenda/remarca/consulta e devolve o
 * resultado (ou lança uma exceção descrevendo a regra violada), deixando para quem chamou a
 * decisão de como relatar isso ao usuário.
 */
class Agenda {
public:
    /**
     * @brief Agenda um novo atendimento.
     * @param paciente nome do paciente.
     * @param profissional nome do profissional.
     * @param data data do atendimento, no formato AAAA-MM-DD.
     * @param hora hora de início do atendimento (8 a 17).
     * @param duracao_minutos duração do atendimento em minutos (15 a 120, múltipla de 15).
     * @return o atendimento recém-criado, com status Marcado.
     * @throws CampoObrigatorioAusenteException se paciente ou profissional estiverem vazios.
     * @throws DataInvalidaException se `data` não estiver no formato AAAA-MM-DD.
     * @throws DuracaoInvalidaException se a duração estiver fora de [15, 120] ou não for múltipla de 15.
     * @throws HorarioForaDoExpedienteException se o atendimento começar ou terminar fora de 8h-18h.
     * @throws ConflitoDeHorarioException se o profissional já tiver outro atendimento nesse dia e horário.
     */
    Atendimento marcar(std::string const& paciente, std::string const& profissional,
                        std::string const& data, int hora, int duracao_minutos);

    /**
     * @brief Remarca um atendimento existente para uma nova data e horário, mantendo a duração original.
     * @param paciente nome do paciente do atendimento a remarcar.
     * @param data_atual data atual do atendimento, usada para localizá-lo.
     * @param hora_atual hora atual do atendimento, usada para localizá-lo.
     * @param nova_data nova data do atendimento, no formato AAAA-MM-DD.
     * @param nova_hora nova hora de início do atendimento (8 a 17).
     * @return o atendimento remarcado, com status Remarcado.
     * @throws AtendimentoNaoEncontradoException se não existir atendimento de `paciente` em `data_atual`/`hora_atual`.
     * @throws DataInvalidaException se `nova_data` não estiver no formato AAAA-MM-DD.
     * @throws HorarioForaDoExpedienteException se o novo horário ficar fora de 8h-18h.
     * @throws ConflitoDeHorarioException se o profissional já tiver outro atendimento no novo dia e horário.
     */
    Atendimento remarcar(std::string const& paciente, std::string const& data_atual, int hora_atual,
                          std::string const& nova_data, int nova_hora);

    /**
     * @brief Consulta todos os atendimentos marcados para uma data.
     * @param data data a consultar, no formato AAAA-MM-DD.
     * @return cópia dos atendimentos daquela data, na ordem em que foram agendados.
     * @throws DataInvalidaException se `data` não estiver no formato AAAA-MM-DD.
     */
    std::vector<Atendimento> consultar_por_data(std::string const& data) const;

private:
    std::vector<Atendimento> atendimentos_;

    /// Indica se `profissional` já tem um atendimento em `data`/`hora`, ignorando opcionalmente
    /// a posição `indice_ignorado` (usado pela remarcação, para não comparar o atendimento consigo mesmo).
    bool existe_conflito(std::string const& profissional, std::string const& data, int hora,
                          std::optional<std::size_t> indice_ignorado) const;
};

}  // namespace agendafacil

#endif  // AGENDAFACIL_AGENDA_HPP

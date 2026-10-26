# Relatório — AgendaFácil (Unidade 1)

**Aluno:** João Victor Bezerra Gomes — matrícula 20250025604

## Etapa 1 — Diagnóstico

Antes de mexer em qualquer linha, rodei o checklist das cinco categorias da Aula 2 em cima do
código-base (`base-original/agenda_base.cpp`, mantido intocado no repositório só para servir de
referência). As linhas citadas na tabela abaixo são sempre as dessa versão original.

| Categoria | Anomalia encontrada (e onde) | Por que é um problema |
|---|---|---|
| 1. Adequação e lógica | `add()` (linhas 27-29) só checa `h>=8 && h<18`; não existe checagem do término do atendimento. `add("X","Y","2026-10-05",17,120)` é aceito, mas terminaria às 19h. | A regra de negócio ("o último atendimento termina até as 18h") fica apenas parcialmente implementada; o sistema aceita silenciosamente um agendamento que viola o próprio expediente. |
| 1. Adequação e lógica | `add()` não valida `dur` além de `dur>0` (linha 29); nenhuma checagem de faixa [15,120] nem de múltiplo de 15. | A regra de duração do negócio não existe no código — qualquer duração positiva (ex.: 1, 7, 200) é aceita. |
| 1. Adequação e lógica | Nenhuma das três funções (`add`, `rem`, `lst`) valida o formato de `d`/`nd`; qualquer string é aceita como data (linhas 24, 49, 76). | A regra "Data: formato AAAA-MM-DD, qualquer outro formato é inválido" não é verificada em lugar nenhum. |
| 1. Adequação e lógica | `rem()` (linhas 49-68) não valida expediente, duração nem formato de data para o novo horário — só reaproveita a checagem de conflito do profissional. | Uma remarcação pode mover um atendimento para um horário que o próprio `add()` teria recusado (ex.: `nh=20`), tornando as duas operações inconsistentes entre si. |
| 2. Manutenibilidade | A checagem de conflito (mesmo profissional, mesma data, mesma hora) está duplicada: uma vez dentro do laço de `add()` (linhas 31-35) e de novo, quase idêntica, dentro de `rem()` (linhas 54-58). | Mudar a regra de conflito (ex.: considerar também a duração) exige lembrar de alterar os dois lugares; é fácil corrigir um e esquecer o outro. |
| 2. Manutenibilidade | `catch (...) {}` vazio em `add()` (linhas 45-46) engole qualquer exceção sem registrar nada. | Qualquer erro inesperado (ex.: `bad_alloc` do `push_back`) desaparece silenciosamente; não há como diagnosticar uma falha em produção. |
| 2. Manutenibilidade | Cabeçalho do arquivo com histórico manual de alterações (linhas 1-6: "Alterado por: Joao - 15/05/2025", "Alterado por: Marina - 09/01/2026") e função `desmarcar` inteira comentada com um `TODO` datado (linhas 70-74). | Duplica o que o `git log` já registra de forma confiável (o comentário fica desatualizado), e código morto/TODO sem dono nem prazo é dívida técnica que ninguém vai resolver. |
| 3. Organização e estética | Estado global mutável `vector<A> ag` (linha 22), acessado diretamente pelas três funções soltas no escopo global. | Qualquer código futuro no mesmo arquivo pode ler ou alterar `ag` sem passar pelas (poucas) checagens de `add`/`rem`, quebrando os invariantes da agenda sem aviso. |
| 3. Organização e estética | Nomes de uma ou duas letras em tudo: `struct A`, campos `p, pr, d, h, dur, st`, funções `add, rem, lst`, variáveis `ok, i, j` (linhas 13-20, 24, 49, 76). | Nenhum nome diz o que representa (paciente? profissional? status?); quem lê o código precisa adivinhar ou decorar, o que convida a erros de uso. |
| 3. Organização e estética | `add()` (linhas 27-29) aninha três `if` dentro de um `try`, quatro níveis de indentação, antes de fazer qualquer coisa útil. | Fluxo de controle difícil de acompanhar; bastaria inverter as condições e sair cedo (guard clauses) para o mesmo efeito com metade da profundidade. |
| 4. Programação defensiva e segurança | `add()`/`rem()` recebem `string p, string pr` etc. e nunca checam se são vazias (linhas 24, 49). | Um paciente ou profissional com nome `""` é aceito e agendado normalmente, poluindo os dados sem nenhum aviso. |
| 4. Programação defensiva e segurança | Quando `h<8`, `h>=18` ou `dur<=0`, o `if` correspondente simplesmente não entra (linhas 27-29) — não há `else`, não há exceção, não há mensagem. | É exatamente o cenário citado no enunciado: marcar às 20h "não faz nada, e ninguém fica sabendo" — a operação falha em silêncio total. |
| 4. Programação defensiva e segurança | `catch (...) {}` genérico e vazio em `add()` (linhas 45-46). | Esconde qualquer exceção, violando a prática de nunca deixar um bloco de captura vazio ou genérico. |
| 5. Desempenho e recursos | Todos os parâmetros de `add`/`rem`/`lst` são recebidos por valor (`string p`, `string d`, `string nd`, ...) em vez de `const string&` (linhas 24, 49, 76). | Cada chamada copia cada string recebida, mesmo sem necessidade — custo evitável que cresce com o tamanho da agenda e o número de chamadas. |
| 5. Desempenho e recursos | `rem()` faz uma busca O(n) por `(p,d,h)` e, para cada candidato encontrado, ainda percorre `ag` inteiro de novo checando conflito (linhas 51-58) — um `for` dentro de outro `for` sobre a mesma lista. | Custo quadrático no pior caso só para remarcar um atendimento; não há nenhuma estrutura de índice (por profissional/data/hora) para evitar a varredura completa a cada chamada. |

*(Observação lateral, fora do checklist: compilar `base-original/agenda_base.cpp` com `-Wall` já produz quatro avisos `-Wsign-compare`, de comparar `int i` com `ag.size()` — sintoma direto do uso de índices `int` em vez de `std::size_t`.)*

### O que eu resolvi e o que ficou como dívida técnica

**Resolvi** na refatoração (Etapas 2-4) as quatorze anomalias acima: dei uma responsabilidade só
para cada função, centralizei a checagem de conflito de horário num único lugar
(`Agenda::existe_conflito`), troquei a struct por posição por um `Atendimento` com campos nomeados,
unifiquei a nomenclatura (`snake_case` para funções/variáveis, `PascalCase` para tipos,
`MAIUSCULAS_COM_UNDERSCORE` para constantes), passei a receber os parâmetros por `const&`, validei
expediente/duração/data/campos obrigatórios com exceções específicas, tirei o código morto e o
cabeçalho com histórico manual, e não deixei nenhum `catch` vazio ou genérico.

**Deixei como dívida técnica**, por estar fora do escopo desta unidade (não podia criar
funcionalidade nova nem trocar a estrutura de dados por outra categoria):
- A `Agenda` ainda guarda os atendimentos num `std::vector` e consulta com busca linear (`O(n)`
  por chamada). Para o tamanho de uma clínica pequena isso não é problema, mas se a agenda crescer
  muito valeria a pena um índice por `(profissional, data, hora)` para resolver de vez o ponto 5
  da tabela.
- Não fiz nenhuma checagem de fuso horário nem de data retroativa (ex.: marcar um atendimento em
  2020 passa). O enunciado só pedia validar formato/calendário, então deixei esse refinamento de
  fora pra não mexer além do que foi pedido.

## Etapa 2 — Refatoração

Troquei o `vector<A> ag` global pelo estado privado de uma classe `agendafacil::Agenda`
(`include/agenda.hpp`, `src/agenda.cpp`), com três métodos públicos — `marcar`, `remarcar`,
`consultar_por_data` — cada um fazendo só uma coisa. A checagem de conflito de horário ficou num
único lugar, `Agenda::existe_conflito`, usado tanto por `marcar` quanto por `remarcar` (antes
estava duplicada nas duas funções). O registro de atendimento (`struct A` por posição) virou
`struct Atendimento` com campos nomeados (`paciente`, `profissional`, `data`, `hora`,
`duracao_minutos`, `status`). Os valores soltos com significado de negócio (8, 17, 18h, 15, 120)
viraram constantes nomeadas em `agenda.hpp` (`HORA_INICIO_EXPEDIENTE`, `DURACAO_MAXIMA_MINUTOS`
etc.), em vez de números mágicos espalhados pelo código.

Testei com as entradas do programa de demonstração original (`Ana`/`Bruno`/`Carla`, todas válidas
pelas regras de negócio) e a saída depois da refatoração ficou byte a byte igual à original — ver a
seção "Compilar e executar" do `README.md`.

## Etapa 3 — Documentação

Documentei todas as funções e métodos públicos de `agenda.hpp`/`agenda.cpp` com o contrato Doxygen
completo (`@brief`, `@param`, `@return`, `@throws`). Tirei o cabeçalho com histórico manual de
alterações (isso já fica registrado no `git log`, não precisa estar duplicado no arquivo); também
tirei o código morto (`desmarcar` comentado) e o `TODO` sem dono — não documentei essas partes
porque não tinha nada ali que valesse a pena preservar.

Comentário de decisão (o "porquê" que o código sozinho não explica): em `src/agenda.cpp`, a função
`texto_status()` termina com `throw std::logic_error("StatusAtendimento desconhecido")` depois do
`switch` já cobrir os dois valores do enum. Na prática isso nunca deveria executar com um
`StatusAtendimento` válido, mas deixei assim pra função não "cair" no fim sem `return`
(comportamento indefinido) se um dia alguém adicionar um novo valor ao enum e esquecer de atualizar
algum `switch`.

## Etapa 4 — Programação defensiva

**Atenção — mudança de comportamento para entradas inválidas (registrando como o enunciado pede):**
no código-base, uma entrada inválida (por exemplo hora 20h, duração de 7 minutos, data
`"05-10-2026"`) era simplesmente ignorada dentro de `add()`, sem nenhum aviso. No caso de conflito
de horário, o código já avisava ("Horario ocupado"), mas só imprimindo — não dava pra quem chamasse
a função saber programaticamente que tinha dado errado. Agora, qualquer violação de regra de
negócio lança uma exceção específica derivada de `agendafacil::ErroAgenda` (`DataInvalidaException`,
`HorarioForaDoExpedienteException`, `DuracaoInvalidaException`, `CampoObrigatorioAusenteException`,
`ConflitoDeHorarioException`, `AtendimentoNaoEncontradoException`), cada uma com uma mensagem que
diz qual valor causou o problema. Não deixei nenhuma validação acontecer em silêncio.

Essa mudança não quebra o caminho feliz: o programa de demonstração (`src/main.cpp`) só usa
entradas válidas pelas quatro regras de negócio, então nenhuma exceção de validação é lançada nele.
A única exceção que aparece na demonstração é `ConflitoDeHorarioException`, no caso
"Bruno"/"Dr. Silva" às 9h — que o código-base já tratava como resultado de negócio esperado (e não
um bug) — e que continua imprimindo "Horario ocupado" na saída.

Decisão de projeto que tomei: tratar o conflito de horário como exceção
(`ConflitoDeHorarioException`) também, e não como um valor de retorno booleano, mesmo ele sendo, no
fundo, um resultado de negócio normal ("profissional ocupado") e não um erro de formato. Pensei em
fazer `marcar()` devolver um booleano/enum de resultado em vez de lançar exceção só pra esse caso,
mas preferi manter um único jeito de sinalizar falha (exceções) pras quatro regras de negócio,
porque `marcar()`/`remarcar()` já não podem imprimir nada (princípio "quem agenda não imprime") —
se eu tivesse duas formas de sinalizar problema (exceção pra formato/expediente/duração e retorno
pra conflito), quem chamasse a função ia precisar lembrar de checar as duas coisas, que é
justamente o tipo de inconsistência que motivou essa refatoração toda. Quem chama
(`src/main.cpp`) decide, a partir da exceção capturada, se imprime "Horario ocupado" (texto do
caminho feliz) ou uma mensagem com `erro.what()` (pra qualquer outra violação).

## Sobre o uso de IA

Usei o Claude (assistente de IA, via Claude Code) para me ajudar em algumas partes deste projeto —
principalmente na refatoração do código em `src/agenda.cpp`/`include/agenda.hpp` e na escrita dos
comentários Doxygen e deste relatório. Conferi o diagnóstico, testei os cenários de erro manualmente
(hora fora do expediente, duração inválida, data malformada, conflito de horário etc.) e revisei as
decisões antes de considerar o projeto pronto.

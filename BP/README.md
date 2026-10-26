# AgendaFácil

Agenda de atendimentos de uma clínica pequena: marca, remarca e lista atendimentos de pacientes
com profissionais, tudo em memória (sem banco de dados e sem interface gráfica).

Este repositório é o meu projeto da Unidade 1 da disciplina DIM0501 — Boas Práticas de Programação
(DIMAp/UFRN, Prof. Marcus Terra, 2026.1): refatoração de qualidade do código-base
`base-original/agenda_base.cpp`, sem adicionar funcionalidade nova. No `RELATORIO.md` tem o
diagnóstico e as decisões que tomei durante o projeto.

**Integrante:** João Victor Bezerra Gomes — 20250025604

**Ferramentas de apoio:** usei o Claude (assistente de IA) para me ajudar em algumas partes do
projeto, principalmente na refatoração do código e na redação da documentação Doxygen. As decisões
de projeto e o diagnóstico foram revisados e validados por mim.

## Estrutura

```
base-original/agenda_base.cpp   código-base fornecido, intocado (referência do diagnóstico)
include/agenda.hpp              tipos, exceções e a API pública da agenda
src/agenda.cpp                  implementação das validações e das regras de negócio
src/main.cpp                    programa de demonstração (mesmo roteiro do código-base)
Doxyfile                        configuração para gerar a documentação de API
RELATORIO.md                    diagnóstico (Etapa 1) e decisões de projeto
```

## Compilar e executar

Requer apenas um compilador C++17 (ex.: g++) e `make`; nenhuma biblioteca externa é usada.

```sh
make        # compila (g++ -std=c++17 -Wall -Wextra -Iinclude src/agenda.cpp src/main.cpp -o agenda)
make run    # compila (se preciso) e executa o programa de demonstração
```

Ou diretamente, sem `make`:

```sh
g++ -std=c++17 -Wall -Wextra -Iinclude src/agenda.cpp src/main.cpp -o agenda
./agenda
```

A saída esperada do programa de demonstração é:

```
Atendimento marcado para Ana
Horario ocupado
Atendimento marcado para Carla
Remarcado
14 Carla Dra. Souza MARCADO
```

## Regras de negócio

| Regra       | Definição                                                                   |
|-------------|------------------------------------------------------------------------------|
| Expediente  | Atendimentos só podem começar entre 8h e 17h; o último termina até as 18h.   |
| Duração     | Entre 15 e 120 minutos, em múltiplos de 15.                                  |
| Conflito    | Um profissional não pode ter dois atendimentos no mesmo dia e horário.       |
| Data        | Formato AAAA-MM-DD, representando uma data de calendário existente.          |

Qualquer violação lança uma exceção derivada de `agendafacil::ErroAgenda` (ver `include/agenda.hpp`
para a lista completa e qual exceção cada regra usa), com uma mensagem que descreve o que estava
errado e qual valor causou o problema. Nenhuma função da agenda imprime nada — quem chama decide o
que fazer com o resultado ou com a exceção.

## Gerar a documentação de API

A documentação (Doxygen) é gerada a partir dos comentários `/** ... */` de `include/agenda.hpp` e
`src/agenda.cpp`.

```sh
sudo dnf install doxygen graphviz   # ou apt install doxygen graphviz, se preciso instalar
make docs                           # equivale a `doxygen Doxyfile`
```

O resultado fica em `docs/html/index.html`. Essa pasta é gerada (não versionada no git — ver
`.gitignore`); rode `make docs` localmente para obtê-la.

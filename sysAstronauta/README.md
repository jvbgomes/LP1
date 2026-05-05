# sysAstronauta

## Como compilar e rodar

```bash
g++ main.cpp astronautas.cpp voo.cpp agencia.cpp -o agencia
./agencia < eventos.txt
```

## Comandos

```
CADASTRAR_ASTRONAUTA <cpf> <idade> <nome>
CADASTRAR_VOO <codigo>
ADICIONAR_ASTRONAUTA <cpf> <codigo_voo>
REMOVER_ASTRONAUTA <cpf> <codigo_voo>
LANCAR_VOO <codigo>
FINALIZAR_VOO <codigo>
EXPLODIR_VOO <codigo>
LISTAR_VOOS
LISTAR_MORTOS
FIM
```

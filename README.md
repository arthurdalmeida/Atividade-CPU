# Atividade-CPU

## Descrição

Esta atividade implementa uma MiniCPU em C usando o ciclo:

FETCH -> DECODE -> EXECUTE

O desafio consiste em encontrar o menor valor do array:

34, 12, 56, 3, 78, 45, 9, 67

Os valores são armazenados nos endereços 0x10 até 0x17. O menor valor encontrado é armazenado no endereço 0x20.

## Compilação

gcc -Wall minicpu.c -o minicpu

## Execução

./minicpu


Durante a execução o programa mostra o trace de cada ciclo.

## Resultado esperado

Menor valor encontrado: 3
Resultado armazenado em mem[0x20].

## Integrantes

João Mafra
Arthur Almeida 
Gabriel Malta 
Marcio Rodriguez 
Matheus Assis 
Guilherme Silva
Gabriel Mendes
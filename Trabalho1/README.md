# Trabalho 1 - Simulated Annealing, Busca Tabu e GRASP

**Aluno:** Vítor Oliveira Amorim  
**Matrícula:** 2023018592  
**Disciplina:** Heurísticas e Metaheurísticas  
**Professor:** Guilhlerme de Castro Pena  

---

## Descrição 

O presente trabalho consiste na implementação e avaliação de 3 metaheurísticas de otimização: 

- Simulated Annealing 
- Busca Tabu 
- GRASP (Greedy Randomized Adaptive Search Procedure)

Cada metaheurística foi aplicada a 2 problemas clássicos de otimização: 

- Problema da Mochila 0/1 (Knapsack)
- Problema do Caixeiro Viajante (TSP)

Além da execução padrão com parâmetros predefinidos, o projeto inclui a execução de testes fatoriais para o ajuste de parâmetros.

---

## Estrutura do Projeto

O projeto está dividido em pastas, cada uma para seu propósito especial. 

A pasta `Input/` conta com duas outras pastas (`Backpack` e `TSP`) que armazenam os arquivos de entrada para cada um dos problemas abordados no trabalho. 

A pasta `Modules` conta com uma série de outras pastas, que contém módulos .h que são usados em diferentes heurísticas.

As demais pastas redirecionam para as heurísticas implementadas. Dentro de cada uma delas, é possível encontrar duas pastas (`Backpack` e `TSP`), que levam para a implementação da heurística para resolução de cada um dos problemas abordados no trabalho.

## Compilação

A compilação das soluções são realizadas via `Makefile`.

### Exemplo de Compilação

```bash
make
```

## Execução

A execução das soluções permite escolher diferentes arquivos de entrada, desde que localizados na pasta de arquivos de entrada dedicada para cada tipo de problema, localizadas dentro do diretório `Input/`, que pode ser encontrado na raíz do projeto.

Para especificar um arquivo de entrada, basta utilizar a *flag* `-i`, seguida do nome do arquivo de entrada.

Além disso, é possível alternar entre a solução básica do algoritmo e a aplicação de um teste fatorial para encontrar os melhores parâmetros do algoritmo.

Para isso, basta utilizar a *flag* `-s`, suguida de `1`, para a solução simples, ou `2`, para o teste fatorial.

### Exemplo de Execução

```bash
make run ARGS="-s <id_da_solucao> -i <arquivo_de_entrada>"
```

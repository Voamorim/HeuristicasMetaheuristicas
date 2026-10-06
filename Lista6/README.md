# Greedy Randomized Adaptive Search Procedures (GRASP) para o Problema do Caixeiro Viajante (TSP)

**Aluno:** Vítor Oliveira Amorim  
**Matrícula:** 2023018592  
**Professor:** Guilherme de Castro Pena  
**Disciplina:** Heurísticas e Metaheurísticas  

---

## Compilação e Execução

A compilação do programa é feita via `Makefile`, através da diretiva `make` quando dentro do diretório `Src/` deste projeto. 

### Exemplo de Compilação

```bash
make
```

A execução também é feita via `Makefile`, através da diretiva `make run`. Ela permite especificar o arquivo de entrada para o algoritmo utilizando a *flag* `-i`, seguida do nome do arquivo de entrada, que deve estar localizado obrigatóriamente dentro da pasta `Input/` deste projeto.

### Exemplo de Execução

```bash
make run ARGS="-i berlin52.tsp"
```

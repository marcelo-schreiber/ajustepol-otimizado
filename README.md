# Aproximação polinomial de funções por mínimos quadrados com calculo intervalar

## Alunos

- Felipe Quaresma Vieira GRR20215516
- Marcelo Augusto Rissette Schreiber GRR20220063

## Estruturas de dados utilizadas

    DoubleIntUnion (interval_operations.h): Estrutura de dados que auxilia na conversão de double para float.

    Interval (interval_operations.h): Estrutura de dados responsável para criar o intervalo de um número.

    Matrix (matrix.h): Estrutura de dados responsável por criar uma matriz de intervalos.

    Vector (matrix.h): Estrutura de dados responsável por criar um vetor de intervalos

    polong long int (matrix.h): Estrutura que abriga um ponto (x,y)

    points (matrix.h): Estrutura que abriga um vetor de pontos (x,y)

## Explicação dos módulos

    interval_operations: Guarda todas as operações com intervalos

    main_io: Guarda as funções utilizadas na main

    main: Módulo principal do programa, responsável por ler as entradas.

    matrix: Guarda todas as operações que envolvem matriz (exceto a dos minimos quadrados).

    mmq: Guarda as funções responsáveis pelo método dos mínimos quadrados e do resíduo.

    utils: Módulo criado pelo professor para auxílio no trabalho.

## Usando script

Para usar o com likwid, somente é necessário rodar o programa com

```bash
python3 likwid.py
```

Ele irá fazer um make clean e make automaticamente.
(<https://www.codeproject.com/Articles/6154/Writing-Efficient-C-and-C-Code-Optimization>)

## O que foi otimizado (deveria ser otimizado)

### Otimizações gerais

- [v] Transformar a matriz em um vetor linear.

- [v] Reaproveitar diagonais da matriz no método dos mínimos quadrados.

- [v] aproveitar cálculo anterior quando há exponenciação (x^9 = x^8 * x, etc).

## Otimizações básicas

- [v] refatorar algumas funções que não foram vetorizadas.

- [v] usar const em variáveis que não são alteradas.

- [v] const quando uma funcao recebe um ponteiro e não altera o valor.

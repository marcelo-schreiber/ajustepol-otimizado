
/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */
#include "main_io.h"
#include <stdio.h>
#include <stdlib.h>

// funcao que le n e k
void read_n_k(long long int *n, long long int *k)
{
  int scanf_result = scanf("%lld", n);

  if (scanf_result != 1)
  {
    printf("Erro ao ler o grau do polinômio\n");
    exit(EXIT_FAILURE);
  }

  scanf_result = scanf("%lld", k);

  if (scanf_result != 1)
  {
    printf("Erro ao ler o número de pontos\n");
    exit(EXIT_FAILURE);
  }
}

// funcao que le os pontos
points_t *read_points(long long int k)
{
  points_t *points = (points_t *)malloc(sizeof(points_t));
  points->num_of_points = k - 1;
  points->points = (point_t *)malloc(points->num_of_points * sizeof(point_t));

  for (size_t i = 0; i < points->num_of_points; i++)
  {
    int scanf_result = scanf("%lf %lf\n", &(points->points[i].x), &(points->points[i].y));

    if (scanf_result != 2)
    {
      printf("Erro ao ler os pontos\n");
      exit(EXIT_FAILURE);
    }
  }

  return points;
}

void free_points(points_t *points)
{
  free(points->points);
  free(points);
}
/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */
#include <likwid.h>
#include "main_io.h"
#include "utils.h"

int main(void)
{
  long long int n, k;
  LIKWID_MARKER_INIT;

  read_n_k(&n, &k);

  points_t *points = read_points(k);

  // Create the coefficient matrix (A) and the right-hand side vector (b)
  Matrix *A = initialize_matrix(n);
  Vector *b = initialize_vector(n);

  double t_gen = timestamp();
  LIKWID_MARKER_START("generate_matrix");
  generate_matrix(A, b, points, n);
  LIKWID_MARKER_STOP("generate_matrix");

  t_gen = timestamp() - t_gen;

  double t_solve = timestamp();

  LIKWID_MARKER_START("solve_system");
  // Solve the system
  b = solve_system(A, b);
  LIKWID_MARKER_STOP("solve_system");
  t_solve = timestamp() - t_solve;

  print_vector(*b);

  print_residue(points, b);

  printf("%1.8e\n%1.8e\n", t_gen, t_solve);

  // Clean up memory
  free_matrix(A);
  free_vector(b);
  LIKWID_MARKER_CLOSE;

  free_points(points);

  return EXIT_SUCCESS;
}
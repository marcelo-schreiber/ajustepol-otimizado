
/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */
#include "mmq.h"
#include "utils.h"
#include <stdio.h>

void print_residue(const points_t *points, const Vector *b)
{
    long long int num_points = points->num_of_points;
    long long int max_power = b->size - 1;

    for (long long int i = 0; i < num_points; ++i)
    {
        Interval sum = interval(0.0);
        Interval current_power = interval(1.0);
        Interval x = interval(points->points[i].x);

        // Calculate powers without the need for an if statement
        for (long long int j = 0; j < max_power; ++j)
        {
            sum = interval_sum(sum, interval_mul(b->data[j], current_power));
            current_power = interval_mul(current_power, x);
        }

        // Special case for the last power
        sum = interval_sum(sum, interval_mul(b->data[max_power], current_power));

        Interval residue = interval_sub(interval(points->points[i].y), sum);
        printf("[%1.8e,%1.8e]  ", residue.lower, residue.upper);
    }
    printf("\n");
}

void generate_matrix(Matrix *A, Vector *b, const points_t *points, unsigned long long int order)
{
    size_t m_size = A->size;

    // Fill the upper and lower triangular parts of the matrix
    for (long long int i = 0; i < m_size; ++i)
    {
        // Lower triangular part
        for (long long int j = 0; j < i; ++j)
        {
            A->data[i * m_size + j] = A->data[j * m_size + i];
        }

        // Upper triangular part
        for (long long int j = i; j < m_size; ++j)
        {
            A->data[i * m_size + j] = interval(0.0);
            for (long long int k = 0; k < points->num_of_points; k++)
            {
                Interval x_pow = interval_pow(interval(points->points[k].x), i + j);
                A->data[i * m_size + j] = interval_sum(A->data[i * m_size + j], x_pow);
            }
        }
    }

    // Fill the vector b
    for (long long int i = 0; i < b->size; ++i)
    {
        b->data[i] = interval(0.0);
        for (long long int k = 0; k < points->num_of_points; ++k)
            b->data[i] = interval_sum(b->data[i], interval_mul(interval_pow(interval(points->points[k].x), i), interval(points->points[k].y)));
    }
}

Vector *solve_system(Matrix *A, Vector *b)
{
    triangulate_matrix_by_gauss(A, b);
    return get_solution_by_substitution(*A, *b);
}

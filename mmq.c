#include "mmq.h"
#include "utils.h"
#include <stdio.h>

void print_residue(points_t *points, Vector *b)
{
    int num_points = points->num_of_points;
    
    for (int i = 0; i < num_points; i++)
    {
        Interval sum = interval(0.0);
        for (int j = 0; j < b->size; j++)
        {
            sum = interval_sum(sum, interval_mul(b->data[j], interval_pow(interval(points->points[i].x), j)));
        }
        Interval residue = interval_sub(interval(points->points[i].y), sum);
        printf("[%1.8e,%1.8e]  ", residue.lower, residue.upper);
    }
    printf("\n");
}

void generate_matrix(Matrix *A, Vector *b, points_t *points, unsigned int order)
{
    // Fill the matrix and the vector
    for (int i = 0; i < A->size; i++)
    {
        for (int j = 0; j < A->size; j++)
        {
            A->data[i][j] = interval(0.0);
            for (int k = 0; k < points->num_of_points; k++)
                A->data[i][j] = interval_sum(A->data[i][j], interval_pow(interval(points->points[k].x), i + j));
        }
    }

    for (int i = 0; i < b->size; i++)
    {
        b->data[i] = interval(0.0);
        for (int k = 0; k < points->num_of_points; k++)
            b->data[i] = interval_sum(b->data[i], interval_mul(interval_pow(interval(points->points[k].x), i), interval(points->points[k].y)));
    }
}

Vector* solve_system(Matrix *A, Vector *b)
{
    triangulate_matrix_by_gauss(A, b);
    return get_solution_by_substitution(*A, *b);
}


/*
 * Autores:
 * Marcelo Augusto Rissette Schreiber GRR20220063
 * Felipe Quaresma Vieira GRR20215516
 *
 * Data: 8/10/2023
 */

#include "interval_operations.h"
#include <math.h>

#define MAX(A,B) ((A>B) ? (A):(B))
#define MIN(A,B) ((A<B) ? (A):(B))

inline double m(double x)
{
  return nextafter(x, DBL_MIN);
}

inline double M(double x)
{
  return x;
}

Interval interval(double x)
{
  Interval result;

  result.lower = m(x);
  result.upper = M(x);

  return result;
}

Interval interval_sum(Interval a, Interval b)
{
  Interval result;

  result.lower = m(a.lower + b.lower);
  result.upper = M(a.upper + b.upper);

  return result;
}

Interval interval_sub(Interval a, Interval b)
{
  Interval result;

  result.lower = m(a.lower - b.upper);
  result.upper = M(a.upper - b.lower);

  return result;
}

Interval interval_mul(Interval a, Interval b)
{
  Interval result;

  double products[4] = {a.lower * b.lower, a.lower * b.upper, a.upper * b.lower, a.upper * b.upper};

  result.lower = m(MIN(MIN(products[0], products[1]), MIN(products[2], products[3])));
  result.upper = M(MAX(MAX(products[0], products[1]), MAX(products[2], products[3])));

  return result;
}

Interval interval_div(Interval a, Interval b)
{
  Interval inverse;

  if (b.lower <= 0 && b.upper >= 0) // b contém 0
  {
    inverse.lower = -INFINITY;
    inverse.upper = INFINITY;
    return inverse;
  }

  inverse.lower = 1 / b.upper;
  inverse.upper = 1 / b.lower;

  Interval result;

  double products[4] = {a.lower * inverse.lower, a.lower * inverse.upper, a.upper * inverse.lower, a.upper * inverse.upper};

  result.lower = m(MIN(MIN(products[0], products[1]), MIN(products[2], products[3])));
  result.upper = M(MAX(MAX(products[0], products[1]), MAX(products[2], products[3])));

  return result;
}

// [a,b]p =    [1,1]                      se p = 0
//                  [ap,bp]                   se p é ímpar
//                  [ap,bp]                   se p é par e a ≥ 0
//                  [bp,ap]                   se p é par e b < 0
//                  [0,max{ap,bp}]     se p é par e a < 0 ≤ b
Interval interval_pow(Interval i, long long int p)
{
  Interval result;
  double a = i.lower;
  double b = i.upper;

  if (p == 0)
  {
    result = interval(1);
    return result;
  }

  if (p % 2 != 0)
  {
    result.lower = pow(a, p);
    result.upper = pow(b, p);
    return result;
  }

  if (a >= 0)
  {
    result.lower = pow(a, p);
    result.upper = pow(b, p);
    return result;
  }

  if (b < 0)
  {
    result.lower = pow(b, p);
    result.upper = pow(a, p);
    return result;
  }

  if (a < 0 && b >= 0)
  {
    result.lower = 0;
    result.upper = MAX(pow(a, p), pow(b, p));
    return result;
  }

  return result;
}

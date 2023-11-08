#!/bin/python

from os import system

system("make clean")

system("make")

print('')
print('-=' * 24)
print("Executando ajustePol")

print('-=' * 24)
print("Operações com float (MFLOP/s)")
print('-=' * 24)
system("likwid-perfctr -C 3 -g FLOPS_DP -m ./ajustePol < pontos.in > resultado.out")
system("grep -e DP -e AVX -e generate_matrix -e solve_system resultado.out")
print('')
print('-=' * 24)
print("Energia (J)")
print('-=' * 24)
system("likwid-perfctr -C 3 -g ENERGY -m ./ajustePol < pontos.in > resultado.out")
system("grep -e [J] -e generate_matrix -e solve_system resultado.out")
print('-=' * 24)

system("make clean")
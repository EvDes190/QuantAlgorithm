//
// Created by EvDes on 01.06.2026.
//

#ifndef QUANTALGORITHM_ORACLE_H
#define QUANTALGORITHM_ORACLE_H

#include <complex.h>

void set_answer(int x);
int get_answer();

//void Uf(int n, double complex amplitudes[n], double complex out[n + 1]);
void Uf(int n, double complex amplitudes[n]);

#endif //QUANTALGORITHM_ORACLE_H

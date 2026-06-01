//
// Created by EvDes on 31.05.2026.
//

#ifndef QUANTALGORITHM_GATES_H
#define QUANTALGORITHM_GATES_H

#include <complex.h>

void Identity(const int n, double complex amplitudes[n]);
void H(const int n, double complex amplitudes[n]);
void NOT(const int n, double complex amplitudes[n]);
void PauliY(const int n, double complex amplitudes[n], int q);
void PauliZ(const int n, double complex amplitudes[n], int q);
void QFT(const int n, double complex amplitudes[n]);
void QFTi(const int n, double complex amplitudes[n]);


#endif //QUANTALGORITHM_GATES_H

//
// Created by EvDes on 31.05.2026.
//

#ifndef QUANTALGORITHM_GATES_H
#define QUANTALGORITHM_GATES_H

#include <complex.h>

void Identity(int n, double complex amplitudes[n]);
void H_full(const int n, double complex amplitudes[n]);
void H(int n, double complex amplitudes[n], int q);
void NOT(int n, double complex amplitudes[n], int q);
void Y(int n, double complex amplitudes[n], int q);
void Z(int n, double complex amplitudes[n], int q);
void QFT(int n, double complex amplitudes[n]);
void QFTi(int n, double complex amplitudes[n]);
void A(int n, double complex amplitudes[n]);


#endif //QUANTALGORITHM_GATES_H

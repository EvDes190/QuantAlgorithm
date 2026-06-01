#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>

#include "gates.h"

void Identity(const int n, double complex amplitudes[n]) {
    // nothing
}

void H(const int n, double complex amplitudes[n]) {
    // O(N * log_2(N)) Hadamara's transformation

    for (int j = 0; j < 1 << n; j++)
        printf("%.3lf ", cabs(amplitudes[j]));
    printf("\n\n");

    for (int iter = 0; iter < n; iter++) {
        int bucket = 1 << iter;
        // j - current bucket's pair
        for (int j = 0; j < 1 << (n - iter - 1); j++) {
            for (int bucket_i = j * bucket * 2; bucket_i < bucket * (j * 2 + 1); bucket_i++) {
                double temp = amplitudes[bucket_i];
                amplitudes[bucket_i] += amplitudes[bucket_i + bucket];
                amplitudes[bucket_i + bucket] = temp - amplitudes[bucket_i + bucket];
            }
        }
        for (int j = 0; j < 1 << n; j++)
            printf("%.3lf ", cabs(amplitudes[j]));
        printf("\n\n");
    }

    // multiplication by 1/sqrt(2^n)
    double k = pow(sqrt(2), n);
    for (int i = 0; i < 1 << n; i++) {
        amplitudes[i] /= k;
    }
}

// Pauli X
void NOT(const int n, double complex amplitudes[n], int q) {
    if (q >= n || q < 0) {
        fprintf(stderr, "Invalid \"q\" argument in NOT(), when n = %d: %d\n", n, q);
        return;
    }

    for (int i = 0; i < 1 << n; i++) {
        amplitudes[i] = amplitudes[
                (i / (1 << (n - q)) * (1 << (n - q))) +
                (1 << (n - q - 1)) * (i % (1 << (n - q)) < (1 << (n - q - 1))) +
                i % (1 << (n - q - 1))
        ];
    }
}

// Pauli Y
void PauliY(const int n, double complex amplitudes[n], int q) {
    if (q >= n || q < 0) {
        fprintf(stderr, "Invalid \"q\" argument in PauliY(), when n = %d: %d\n", n, q);
        return;
    }

    NOT(n, amplitudes, q);
    for (int i = 0; i < 1 << n; i++)
        amplitudes[i] *= I;
    PauliZ(n, amplitudes, q);
}

// Pauli Z
void PauliZ(const int n, double complex amplitudes[n], int q) {
    if (q >= n || q < 0) {
        fprintf(stderr, "Invalid \"q\" argument in PauliZ(), when n = %d: %d\n", n, q);
        return;
    }
    for (int i = 0; i < 1 << n; i++)
        amplitudes[i] *= 2 * ((i % (1 << (n - q))) / (1 << (n - q - 1))) - 1; // set sign
}

// Quantum Fourier Transform
void QFT(const int n, double complex amplitudes[n]) {
    double complex *new_amplitudes = calloc((1 << n), sizeof(double complex));
    double complex w = cexp(-2 * M_PI * I / (1 << n));
    double complex root_N = csqrt(1 << n);

    for (int k = 0; k < 1 << n; k++) {
        double complex w_k = cpow(w, k);
        for (int j = 0; j < 1 << n; j++)
            new_amplitudes[k] += amplitudes[j] * cpow(w_k, j);
        new_amplitudes[k] /= root_N;
    }

    memmove(amplitudes, new_amplitudes, (1 << n) * sizeof(double complex));
    free(new_amplitudes);
}

// inverse Quantum Fourier Transform
void QFTi(const int n, double complex amplitudes[n]) {
    double complex *new_amplitudes = calloc((1 << n), sizeof(double complex));
    double complex w = cexp(2 * M_PI * I / (1 << n));
    double complex root_N = csqrt(1 << n);
    for (int k = 0; k < 1 << n; k++) {
        double complex w_k = cpow(w, k);
        for (int j = 0; j < 1 << n; j++)
            new_amplitudes[k] += amplitudes[j] * cpow(w_k, j);
        new_amplitudes[k] /= root_N;
    }

    memmove(amplitudes, new_amplitudes, (1 << n) * sizeof(double complex));
    free(new_amplitudes);
}
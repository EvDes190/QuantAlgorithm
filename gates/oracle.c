#include <string.h>
#include <stdio.h>

#include "oracle.h"

int answer = 0;

void set_answer(int x) {
    answer = x;
}

int get_answer() {
    return answer;
}

void Uf(const int n, double complex amplitudes[n]) {
//void Uf(const int n, double complex amplitudes[n], double complex out[n + 1]) {
//    memmove(out, amplitudes, (1 << n) * sizeof(double complex));
//    memset(out + (1 << n), 0, (1 << n) * sizeof(double complex));
//    FILE *output = fopen("debug.txt", "w");
//    fprintf(output, "%lf + (%lf)\n", creal(amplitudes[x]), cimag(amplitudes[x]));
//    out[x + (1 << n)] = amplitudes[x];
//    out[x] = 0;
    amplitudes[get_answer()] *= -1;
}
#include <string.h>

#include "oracle.h"

void Uf(const int x, const int n, double complex amplitudes[n], double complex out[n + 1]) {
    memmove(out, amplitudes, (1 << n) * sizeof(double complex));
    out[x | (1 << (n + 1))] = amplitudes[x];
    out[x] = 0;
}
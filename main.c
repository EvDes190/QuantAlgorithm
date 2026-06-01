#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>


#include "gates/gates.h"
#include "gates/oracle.h"

#pragma STDC CX_LIMITED_RANGE ON

#define n 2


void to_binary(char word[n + 1], int x) {
    for (int i = n - 1; i >= 0; i--) {
        word[i] = x % 2 + 48;
        x /= 2;
    }
}

void grover(double complex amplitudes[n + 1]) {

}

int main() {
    double complex *amplitudes = calloc(1 << n, sizeof(double complex));
    amplitudes[0] = sqrt(0.3);
    amplitudes[1] = sqrt(0.2);
    amplitudes[2] = sqrt(0.4);
    amplitudes[3] = sqrt(0.1);


    char word[n + 1];
    word[n] = '\0';

    for (int i = 0; i < 1 << n; i++) {
        to_binary(word, i);
        printf("%s - %.4lf\n", word, creal(amplitudes[i]));
    }

    free(amplitudes);
    return 0;
}

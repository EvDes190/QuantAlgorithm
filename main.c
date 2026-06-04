#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "gates/gates.h"
#include "gates/oracle.h"

#pragma STDC CX_LIMITED_RANGE ON


FILE *output;
bool debug = 0;

void ifprint(char *text) {
    if (debug == 1)
        fprintf(output, "%s", text);
}

void to_binary(int n, char word[n + 1], int a) {
    for (int i = n - 1; i >= 0; i--) {
        word[i] = a % 2 + 48;
        a /= 2;
    }
}

void god_watch(FILE *stream, int n, double complex amplitudes[n]) {
    if (debug == 0)
        return;
    char word[n + 1];
    word[n] = '\0';

    double sum = 0;

    fprintf(stream, "========================\nQUBITS STATE\n\n");

    for (int i = 0; i < 1 << n; i++) {
        sum += pow(cabs(amplitudes[i]), 2);
        to_binary(n, word, i);
        fprintf(stream, "%s - |%.2lf + (%.2lf)i|^2 = %.4lf\n", word, creal(amplitudes[i]), cimag(amplitudes[i]), pow(cabs(amplitudes[i]), 2));
    }
    fprintf(stream, "\n> %.4lf\n========================\n\n", sum);
}

int watch(int n, double complex amplitudes[n]) {
    int max_i = 0;
    for (int i = 0; i < 1 << n; i++) {
        if (cabs(amplitudes[i]) > cabs(amplitudes[max_i]))
            max_i = i;
    }

    return max_i;
}

void Grover(int n, double complex amplitudes[n]) {
    H_full(n, amplitudes);
    for (int iter = 1; (double) iter < (M_PI / 4.0) * sqrt(1 << n); iter++) {
        fprintf(output, "ITERATION %d>\n", iter);

        Uf(n, amplitudes);
        ifprint("after Z:\n");
        god_watch(output, n, amplitudes);

        A(n, amplitudes);
        ifprint("after A:\n");
        god_watch(output, n, amplitudes);
    }

}


int main(int argc, char* argv[]) {
    int n = 3;

    for (int i = 1; i < argc; i++) {
        assert(argv[i][1] == '=' && "Invalid arguments");

        switch (argv[i][0]) {
            case 'q':
                n = (int) strtoul(argv[i] + 2, NULL, 10);
                assert(n > 0 && n <= 20 && "Invalid qubit number argument\n");
                break;
            case 'd':
                debug = strcmp(argv[i] + 2, "true");
                debug = !debug;
                break;
            case 'a':
                set_answer((int) strtoul(argv[i] + 2, NULL, 10));
        }
    }
    assert(get_answer() >= 0 && get_answer() < (1 << n) && "Invalid answer argument\n");

    output = fopen("output.txt", "w");
    double complex *amplitudes = calloc(1 << n, sizeof(double complex));
    assert(amplitudes != NULL);
    amplitudes[0] = 1;

    Grover(n, amplitudes);

    int answer = watch(n, amplitudes);
    fprintf(output, "Answer = %d\nChance = %.4lf\n", answer, cabs(amplitudes[answer]));

    free(amplitudes);
    return 1;
}

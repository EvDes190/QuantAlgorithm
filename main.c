#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

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

void god_watch(int n, double complex amplitudes[n]) {
    // print complex values of amplitudes in qubit register
    if (debug == 0)
        return;
    char word[n + 1];
    word[n] = '\0';

    double sum = 0;

    fprintf(output, "========================\nQUBITS STATE\n\n");

    for (int i = 0; i < 1 << n; i++) {
        sum += pow(cabs(amplitudes[i]), 2);
        to_binary(n, word, i);
        fprintf(output, "%s - |%.2lf + (%.2lf)i|^2 = %.4lf\n", word, creal(amplitudes[i]), cimag(amplitudes[i]), pow(cabs(amplitudes[i]), 2));
    }
    fprintf(output, "\n> %.4lf\n========================\n\n", sum);
}

int watch(int n, double complex amplitudes[n]) {
    int max_i = 0;
    for (int i = 0; i < 1 << n; i++) {
        if (cabs(amplitudes[i]) > cabs(amplitudes[max_i]))
            max_i = i;
    }

    return max_i;
}

int Grover(int n, double complex amplitudes[n]) {
    // Hadamara operation for all qubits in register
    H_full(n, amplitudes);

    int iterations = (int) ((M_PI / 4.0) * sqrt(1 << n));
    for (int iter = 1; iter < iterations; iter++) {
        fprintf(output, "ITERATION %d>\n", iter);
        fflush(output);

        // call Oracle for negate x's amplitude
        Uf(n, amplitudes);
        ifprint("after Z:\n");
        god_watch(n, amplitudes);

        // diffusion operation
        A(n, amplitudes);
        ifprint("after A:\n");
        god_watch(n, amplitudes);
    }

    return iterations - 1;
}


int main(int argc, char* argv[]) {
    int n = 3;
    output = stdout;

    // options handling
    for (int i = 1; i < argc; i++) {
        assert(argv[i][1] == '=' && "Invalid arguments");

        switch (argv[i][0]) {
            case 'q':
                // set qubit number
                n = (int) strtoul(argv[i] + 2, NULL, 10);
                assert(n > 0 && n <= 100 && "Invalid qubit number argument\n");
                break;
            case 'd':
                // set debug flag
                debug = strcmp(argv[i] + 2, "true");
                debug = !debug;
                break;
            case 'a':
                // set answer number of equation f(x) = 1
                set_answer((int) strtoul(argv[i] + 2, NULL, 10));
            case 'f':
                // set output file
                output = fopen(argv[i] + 2, "w");
                assert(output != NULL && "Opening file failed\n");
        }
    }
    assert(get_answer() >= 0 && get_answer() < (1 << n) && "Invalid answer argument\n");

    // Init amplitudes of quant register
    double complex *amplitudes = calloc(1 << n, sizeof(double complex));
    assert(amplitudes != NULL);
    amplitudes[0] = 1;

    clock_t start = clock();
    // count iterations of grover
    int iterations = Grover(n, amplitudes);
    clock_t end = clock();

    int answer = watch(n, amplitudes);
    fprintf(output, "\nAnswer = %d\nIterations = %d\nChance = %.10lf\nTime = %.3lf seconds\n", answer, iterations, cabs(amplitudes[answer]), (double) (end - start) / CLOCKS_PER_SEC);

    free(amplitudes);
    return 1;
}

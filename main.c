#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define n 2
#define N 1 << n

typedef struct {
    double real;
} amplitude_t;

void to_binary(char word[n + 1], int x) {
    for (int i = n - 1; i >= 0; i--) {
        word[i] = x % 2 + 48;
        x /= 2;
    }
}

void H(amplitude_t *amplitudes) {
    // O(N * log_2(N)) Hadamara's transformation

    for (int j = 0; j < 1 << n; j++)
        printf("%.3lf ", amplitudes[j].real);
    printf("\n\n");
    // i - iteration
    for (int i = 0; i < n; i++) {
        int bucket = 1 << i;
        // j - current bucket's pair
        for (int j = 0; j < 1 << (n - i - 1); j++) {
            for (int bucket_i = j * bucket * 2; bucket_i < bucket * (j * 2 + 1); bucket_i++) {
                double temp = amplitudes[bucket_i].real;
                amplitudes[bucket_i].real += amplitudes[bucket_i + bucket].real;
                amplitudes[bucket_i + bucket].real = temp - amplitudes[bucket_i + bucket].real;
            }
        }
        for (int j = 0; j < 1 << n; j++)
            printf("%.3lf ", amplitudes[j].real);
        printf("\n\n");
    }

    // multiplication by 1/sqrt(2^n)
    double k = pow(sqrt(2), n);
    for (int i = 0; i < 1 << n; i++) {
        amplitudes[i].real /= k;
    }
}

void NOT(amplitude_t *amplitudes) {
    for (int i = 0; i < 1 << n; i += 2) {
        // swap amplitudes[i] <=> amplitudes[i + 1]
        amplitude_t temp = amplitudes[i];
        amplitudes[i] = amplitudes[i + 1];
        amplitudes[i + 1] = temp;
    }
}

int main() {
//    amplitude_t *amplitudes = calloc(1 << n, sizeof(amplitude_t));
    amplitude_t amplitudes[1 << n];
    amplitudes[0] = (amplitude_t){ sqrt(0.3)};
    amplitudes[1] = (amplitude_t){ sqrt(0.2)};
    amplitudes[2] = (amplitude_t){ sqrt(0.4)};
    amplitudes[3] = (amplitude_t){ sqrt(0.1)};
    NOT(amplitudes);
//    H(amplitudes);

    char word[n + 1];
    word[n] = '\0';

    for (int i = 0; i < 1 << n; i++) {
        to_binary(word, i);
        printf("%s - %.4lf\n", word, amplitudes[i].real * amplitudes[i].real);
    }

//    free(amplitudes);
    return 0;
}
